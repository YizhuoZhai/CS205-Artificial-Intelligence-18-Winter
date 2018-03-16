function main()
    disp('Welcome to my Feature Selection Algorithm.');
    fileName = input('Type in the name of the file to test :', 's');
    disp('Type the number of the algorithm you want to run.');
    disp('1) Forward Selection')
    disp('2) Backward Elimination')
    disp('3) Forward Pruning (Make Forward Selection faster)')
    choice = input('4) Backward Pruning (Make Backward Selection faster)');
    
    data = load(fileName);
    [row, coloumn] = size(data);
    disp(['This dataset has ', num2str(coloumn-1) ' features (not including the class attribute), with ', num2str(row), ' instances'])
    disp('Please wait while I normalize the data...')
    normData = dataNormalization(data);
    disp('Done!')
    %run all the features to get an accuracy
    allFeatures(1:coloumn - 1)  = 1:1:(coloumn - 1);
    acc = validation(normData, allFeatures,0,0,0); 
    disp(['Running nearest neighbor with all ', num2str(coloumn-1),  ' features, using leaving-one-out evaluation,'])
    disp(['I get an accuracy of ', num2str(acc*100), '%']);
    disp('Beginning search.');
    %0 means with out speed up, 1 means speed up algorithm
    if choice == 1
        forward(normData, 0)
    elseif choice == 2
        backward(normData, 0)
    elseif choice == 3
        forward(normData, 1)
    elseif choice == 4
        backward(normData, 1)
    else
        disp('invalid input, bye~!');
    end
end

function normData = dataNormalization(data)
    [row, coloumn] = size(data);
    featureData = data(:, 2:coloumn);
    [resultData, dataMean, dataStd] = zscore(featureData);
    label = data(:, 1);
    normData = [label, resultData];
end

%arg1@data: the whole normalized traning data with lable.
%arg2@opt: opt = 0 means no optimization, opt = 1 means speed up algorithm.
function forward(data,opt)
    current_set_of_features = []; % Initialize an empty set
    optimal_set_of_features = []; % Store the optimal result
    optimal_accuracy = 0;
    
    %Comparing the time, we use tic and toc to record the searching time.
    tic;
    t1 = clock;
    for i = 1 : size(data,2)-1 
        %%disp(['On the ',num2str(i),'th level of the search tree'])
        feature_to_add_at_this_level = [];
        best_so_far_accuracy = 0;
    
        for k = 1 : size(data,2)-1
            if isempty(intersect(current_set_of_features,k)) 
                if opt == 0
                    %leave_one_out_cross_validation
                    accuracy = validation(data,current_set_of_features,k, 1, 0);
                elseif opt == 1
                    accuracy = validation(data,current_set_of_features,k, 1, best_so_far_accuracy);
                end
                %%disp(['        Using feature(s){ ',num2str(current_set_of_features),'  ' num2str(k),' }', 'accuracy is ', num2str(100*accuracy), '%']);
        
                if accuracy > best_so_far_accuracy 
                    best_so_far_accuracy = accuracy;
                    feature_to_add_at_this_level = k;
                end
            end
        end
        %%disp(['On level ', num2str(i),' I added feature ', num2str(feature_to_add_at_this_level), ' to current set']);  
        current_set_of_features = [current_set_of_features, feature_to_add_at_this_level];
        %disp(['Feature set {', num2str(current_set_of_features), ' } was best, accuracy is ', num2str(100*best_so_far_accuracy), '%']);
        
        if best_so_far_accuracy > optimal_accuracy
            optimal_accuracy = best_so_far_accuracy;
            optimal_set_of_features = current_set_of_features;
        elseif best_so_far_accuracy < optimal_accuracy
            %disp('(Warning, Accuracy has decreased! Continuing search in case of local maxima)');
        end  
    end 
    toc;
    disp(['Finished search!! The best feature subset is {', num2str(optimal_set_of_features), '}, which has an accuracy of ',num2str(100*optimal_accuracy), '%']);
    
end
%arg1@data: the whole normalized traning data with lable.
%arg2@opt: opt = 0 means no optimization, opt = 1 means speed up algorithm.
function backward(data, opt)
    
    [row, coloumn] = size(data);
    current_set_of_features(1:coloumn - 1)  = 1:1:(coloumn - 1); % Initialize a full feature set
    optimal_set_of_features = []; % Store the optimal result
    optimal_accuracy = 0;
    tic;
    t1 = clock;
    for i = 1 : size(data,2)-1 
        %%disp(['On the ',num2str(i),'th level of the search tree'])
        feature_to_exclude_at_this_level = [];
        best_so_far_accuracy = 0;
        best_so_far_features = [];
    
        for k = 1 : size(data,2)-1
            if ~isempty(intersect(current_set_of_features,k)) 
                if opt == 0
                    accuracy = validation(data,current_set_of_features,k,2, 0);
                elseif opt == 1
                    accuracy = validation(data,current_set_of_features,k,2, best_so_far_accuracy);
                end
                %%disp(['Using feature(s){ ',num2str(setdiff(current_set_of_features, k)),' }', 'accuracy is ', num2str(100*accuracy), '%']);
        
                if accuracy > best_so_far_accuracy 
                    best_so_far_accuracy = accuracy;
                    feature_to_exclude_at_this_level = k;
                    best_so_far_features = setdiff(current_set_of_features, k);
                end
            end
        end
        %disp(['Feature set  {', num2str(best_so_far_features), '} was best, accuracy is  ', num2str(best_so_far_accuracy)]);
        %disp(['On level ', num2str(i),' I excluded feature ', num2str(feature_to_exclude_at_this_level), ' to current set']);  
        
        current_set_of_features = setdiff(current_set_of_features, feature_to_exclude_at_this_level);
        if best_so_far_accuracy > optimal_accuracy
            optimal_accuracy = best_so_far_accuracy;
            optimal_set_of_features = best_so_far_features;
        elseif best_so_far_accuracy < optimal_accuracy
            %disp('(Warning, Accuracy has decreased! Continuing search in case of local maxima)');
        end 
    end 
    toc;
    disp(['Finished search!! The best feature subset is {', num2str(optimal_set_of_features), '}, which has an accuracy of ',num2str(100*optimal_accuracy), '%']);
end
%function @validation: leave_one_out_cross_validation
%arg1@data: the whole normalized traning data with lable.
%arg2@current_set_of_features: the feature No
%arg3@k: feature to add or exclude
%arg4@flag: if flag == 1, we add kth feature, flag == 2, we exclude it
%arg5@acc_so_far: To help speed up the algorithm
function acc = validation(data,current_set_of_features,k, flag, acc_so_far) 
    right = 0;
    wrong = 0;
    [row, coloumn] = size(data);
    if k~=0
        if flag == 1
            current_set_of_features = union(current_set_of_features, k);
        elseif flag == 2
            current_set_of_features = setdiff(current_set_of_features, k);
        end
    end
    
    [frow, fcol] = size(current_set_of_features);
    label = data(:, 1);
    featureData = data(:, 2:coloumn);
    
    %initialize training data
    tData = [];
    for i = 1 : fcol
        tData = [tData, featureData(:, current_set_of_features(1, i))];
    end
    tData = [label, tData];
    [trow, tcol] = size(tData);
    
    %leave one out
    for i = 1 : row
        %exclude the row
        testData = tData;
        testData(i, :) = [];
        %the lable of the rest training data
        trainLable = testData(:,1);
        %the features of the training data
        trainSet = testData(:, 2:tcol);
        %features of the test data
        test = tData(i, 2:tcol);
        %lable of the test data
        realLabel = tData(i, 1);
        classLable = knn(test, trainSet, trainLable, 1);
        if classLable == realLabel
            right = right + 1;
        else
            wrong = wrong + 1;
            if wrong > (row * (1 - acc_so_far))
               acc = 0;
               return;
            end
        end
    end

    acc = right/(right + wrong);
end

%knn algorithm, k = 1 since it's nearest neighbor
function classLabel = knn(test, data, labels, k)
    [row , col] = size(data);
    diffMat = repmat(test,[row,1]) - data ;
    distanceMat = sqrt(sum(diffMat.^2,2));
    [B , IX] = sort(distanceMat,'ascend');
    len = min(k,length(B));
    classLabel = mode(labels(IX(1:len)));
end

