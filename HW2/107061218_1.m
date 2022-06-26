% find transmitted message P_x
% clc; clear;
load('inputdata.mat')
C_x = [1 0 0 0 0 0 1 0 0 1 1 0 0 0 0 0 1 0 0 0 1 1 1 0 1 1 0 1 1 0 1 1 1];  % CRC-32
M_x = packet;                       % original packet
T_x = [packet, zeros(1, 32)];       % packet with 32 extended zeros
R_x = [];                           % remainder

for i = 1: 12000
    if T_x(i) == 1
        R_x(1:32) = xor(T_x(i+1:i+32), C_x(2:33));
        T_x(i+1:i+32) = R_x(1:32);
    end
end


codepacket = [M_x(1:12000), T_x(12001:12032)];
save('HW2_107061218_1.mat', 'codepacket');
