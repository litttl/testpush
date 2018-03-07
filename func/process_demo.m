function [MEAN_VALUE,NORM_VALUE] = process_demo(FILE_ROAD,FILE_NO,FILE_STYLE,LSC_MODE,NO_BLOCK,WIDE_BLOCK,NORM_STYLE,COMPARE_STYLE,COMPARE_BLOCK_NO,PLOT_COMPARE_STYLE)

% function [MEAN_VALUE,NORM_VALUE] = process_demo(FILE_ROAD,FILE_NO,FILE_STYLE,LSC_MODE,NO_BLOCK,WIDE_BLOCK,PH_STORESTYLE,NORM_STYLE,COMPARE_STYLE,BLOCK_NO)
% process_demo 函数的作用是：用于直接输出计算需要的结果值
% 顶层使用关键说明： FILE_ROAD 如果当前路径不在图片存储路径下，需要完整的路径名+图片数字前的图片名。此处的准确性保证文件的可加载性  
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% MEAN_VALUE        - 所求各图像色块均值
% NORM_VALUE        - 所求各图像色块归一化值
% FILE_ROAD         - 读取图像的路径
% FILE_NO           - 读取图片数量
% FILE_STYLE        - 图片格式：'BMP'/'JPG'/'PNG'
% LSC_MODE          - 选择LSC模式：1. LSC_ON（开启LSC） 2. LSC_OFF（关闭LSC）
% NO_BLOCK          - 要计算的色块数量
% WIDE_BLOCK        - 以鼠标选中点为中心，四方向扩展的象元宽度
% NORM_STYLE        - 归一化模式选择：1. NORM_RGB - 以R+G+B和值归一化；2. NORM_Y - 以亮度值归一化；3. NORM_NONE 不作归一化处理
% COMPARE_STYLE     - 选择图像绘制的模块间比较模式：
%                       1. COMPARE_ALLBLOCK（比较所有模块） 2. COMPARE_SAMEBLOCK（比较选定的特定模块）
% COMPARE_BLOCK_NO  - 在COMPARE_SAMEBLOCK模式下，选择需要比较的具体模块序号
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% version: 0-0@fh
% modify: none
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

warning('off');
ph_read = read_oriimg(FILE_ROAD,FILE_NO,FILE_STYLE,LSC_MODE);
[mean_value,norm_value] = mean_block(ph_read,NO_BLOCK,WIDE_BLOCK,'MULIMG',NORM_STYLE);
result0 = plot_value(mean_value,PLOT_COMPARE_STYLE,COMPARE_BLOCK_NO);
title(['mean value','+',LSC_MODE,'+',NORM_STYLE]);
result1 = plot_value(norm_value,PLOT_COMPARE_STYLE,COMPARE_BLOCK_NO);
title(['norm value','+',LSC_MODE,'+',NORM_STYLE]);

MEAN_VALUE = mean_value;
NORM_VALUE = norm_value;

