% clc; clear;
%% load adjacency matrix of network A
load("network_A.mat")

%% initialize the connection of dijkstra's algorithm
connect = zeros(100, 100);
for i = 1 : 100
    for j = 1 : 100
        if A(i, j) == 1
            connect(i, j) = 1;
            connect(j, i) = 1;
        else
            connect(i, j) = inf;
            connect(j, i) = inf;
        end
    end
end

%% initialize the visited table
is_visited = zeros(100, 100);
for i = 1 : 100
    is_visited(i, i) = 1;
end

%% initialize the distance vector (d), which is the final answer I want
d = connect;                    % d will be updated step by step, while connect will remain the same

%% apply dijkstra's algorithm to find the spanning tree
for idx = 1 : 100                   % find the value of distance matrix for each node
    for start_idx = 1 : 100         % try to go to every destination in ONE step
        min = inf;
        for dest_idx = 1 : 100
            % find the min distance in one step
            if d(idx, dest_idx) < min && is_visited(idx, dest_idx) == 0
                temp = dest_idx;
                min = d(idx, dest_idx);
            end
        end
        is_visited(idx, temp) = 1;   % update the visited table  
        
        for end_idx = 1 : 100       % update d
            if connect(temp, end_idx) < inf && d(idx, end_idx) >= d(idx, temp) + connect(temp, end_idx)
                d(idx, end_idx) = d(idx, temp) + connect(temp, end_idx);
            end
        end
    end
end

%% save the result
save("result.mat", "d");
