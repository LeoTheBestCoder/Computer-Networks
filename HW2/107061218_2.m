% clc; clear;
load('inputdata.mat')
C_x = [1 0 0 0 0 0 1 0 0 1 1 0 0 0 0 0 1 0 0 0 1 1 1 0 1 1 0 1 1 0 1 1 1];  % CRC-32
M_x = packet;                       % original packet
T_x = [packet, zeros(1, 32)];       % packet with 32 extended zeros
R_x = [];                           % remainder
original_remainder = [];
new_remainder = [];
E_x = zeros(1, 12032);
min_diff_pos = -1;

min_diff = 32;
min_diff_remainder = [];

for i = 1: 12000
    if T_x(i) == 1
        R_x(1:32) = xor(T_x(i+1:i+32), C_x(2:33));
        T_x(i+1:i+32) = R_x(1:32);
    end
end
original_remainder(1:32) = T_x(12001:12032);
codepacket = [M_x(1:12000), T_x(12001:12032)];

for pos = 1:12000
    new_M_x = packet;
    if new_M_x(pos) == 1
        new_M_x(pos) = 0;
    else
        new_M_x(pos) = 1;
    end

    % doing CRC check to find new remainder
    new_T_x = [new_M_x, zeros(1, 32)];
    new_R_x = [];
    for i = 1:12000
        if new_T_x(i) == 1
            new_R_x(1:32) = xor(new_T_x(i+1:i+32), C_x(2:33));
            new_T_x(i+1:i+32) = new_R_x(1:32);
        end
    end
    new_remainder(1:32) = new_T_x(12001:12032);
    
    % compare the bit difference between new remainder and the old one
    diff = 0;
    for j = 1: 32
        if new_remainder(j) ~= original_remainder(j)
            diff = diff + 1;
        end
    end
    
    % if mod(pos, 500) == 0
    %     YY = sprintf('running process: pos = %d', pos);
    %     disp(YY);
    % end
    if diff < 10
        % XX = sprintf('pos = %d, diff = %d', pos, diff);
        % disp(XX);
        if diff < min_diff
            min_diff = diff;
            min_diff_remainder = new_remainder;
            min_diff_pos = pos;
            % YY = sprintf('best solution updated, min_diff = %d', min_diff);
            % disp(YY);
        end
    end
end

E_x(min_diff_pos) = 1;
for idx = 1:32
    if min_diff_remainder(idx) ~= original_remainder(idx)
        E_x(12000 + idx) = 1;
    end
end

save('HW2_107061218_2.mat', 'codepacket', 'E_x');

disp('Best solution: ');
disp('remainder = ');
disp(min_diff_remainder);
ZZ = sprintf('min_diff_pos = %d, min_diff = %d', min_diff_pos, min_diff);
disp(ZZ);