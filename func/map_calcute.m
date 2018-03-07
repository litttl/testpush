function [MAP_LOW,MAP_HIGH] = map_calcute(PH_IN,INTEGRAL_HIST,THRESHOD_LOW,THRESHOD_HIGH)

% function [MAP_LOW,MAP_HIGH] = map_calcute(INTEGRAL_HIST,THRESHOD_LOW,THRESHOD_HIGH)
% map_calcute 用于计算在下阈值和上阈值之间的map
%%%%%%%%%%%%%%%%%%%%%
% PH_IN - 输入图像
% INTEGRAL_HIST - 直方图积分
% THRESHOD_LOW  - 低阈值
% THRESHOD_HIGH - 高阈值
% MAP_LOW       - 低阈值下的map
% MAP_HIGH      - 高阈值下的map
%%%%%%%%%%%%%%%%%%%%%


ph_in = PH_IN;
integral_hist = INTEGRAL_HIST;
threshod_low  = THRESHOD_LOW;
threshod_high = THRESHOD_HIGH;

% 找出阈值对应的像素值
gray_low  = uint8(0);
gray_high = uint8(0);
for i=1:1:255
    if((integral_hist(i)<=threshod_low) && (integral_hist(i+1)>=threshod_low))
        gray_low = i;
    end
end

for i=1:1:255
    if((integral_hist(i)<=threshod_high) && (integral_hist(i+1)>=threshod_high))
        gray_high = i;
    end
end

[rows_map,cols_map] = size(ph_in);

% gray_low
% gray_high

map_low  = zeros(rows_map,cols_map);
map_high = zeros(rows_map,cols_map);

for i=1:1:rows_map
    for j = 1:1:cols_map
        if(ph_in(i,j)<=gray_low)
            map_low(i,j) = 0;
        else
            map_low(i,j) = 255;
        end
    end
end


for i=1:1:rows_map
    for j = 1:1:cols_map
        if(ph_in(i,j)>=gray_high)
            map_high(i,j) = 0;
        else
            map_high(i,j) = 255;
        end
    end
end

MAP_LOW = map_low;
MAP_HIGH = map_high;



