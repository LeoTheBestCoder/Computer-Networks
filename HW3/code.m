% clc; clear; 

%% load matrix A and define some matrices
load('network_A.mat')
tree = zeros(100, 100);
is_visited = zeros(1, 100);     % whether the node is visited by BFS algo
is_visited(1) = 1;              % since we start from the root, set the value of root to 1
dis_from_root = zeros(1, 100);  % distance from root
test = 0;                       % debugging parameter

%% initialization
for i = 1: 100
    % connect the edges in "tree" where were originally directly connected with root in A
    if A(1, i) == 1
        is_visited(i) = 1;
        dis_from_root(i) = 1;
        tree(i, 1) = 1;
        tree(1, i) = 1;
    end
end

%% BFS
for distance = 1: 100                                                   % update from nodes that has a smaller distance from root
    for idx = 1: 100
        if dis_from_root(idx) == distance
            for node_idx = 1: 100
                if is_visited(node_idx) ~= 1 && A(idx, node_idx) == 1
                    % disp(idx);
                    disp(node_idx);
                    test = test + node_idx;                             % update debuf param.
                    % if the node is not visited yet and it's connected in A, 
                    % update tree, i.e. connected them
                    is_visited(node_idx) = 1;                           % update the value from unvisited to visited
                    dis_from_root(node_idx) = dis_from_root(idx) + 1;   % increment the distance by 1
                    tree(idx, node_idx) = 1;                            % connect the edges
                    tree(node_idx, idx) = 1;                            % connect the edges
                end
            end
        end
    end
end
disp(test);  % print debug param.


%% save the result
save("result.mat", "tree");