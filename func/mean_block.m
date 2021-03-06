function [MEAN_BLOCK,NORM_BLOCK] = mean_block(PH,NO_BLOCK,WIDE_BLOCK,PH_STORESTYLE,NORM_STYLE)

% function [MEAN_BLOCK,NORM_BLOCK] = mean_block(PH,NO_BLOCK,WIDE_BLOCK,PH_STORESTYLE,NORM_STYLE)
% mean_block
% 函数的作用是：用于计算指定数量（NO_BLOCK）的色块（以鼠标所选点为中心，扩展上下左右WIDE_BLOCK大小的色块）的统计均值
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% MEAN_BLOCK - 输出各色块均值
% NORM_BLOCK - 输出各色块归一化（归一化方法可选）均值
% PH - 输入的图像数据
% NO_BLOCK - 需要计算的色块数量
% WIDE_BLOCK - 选取的色块宽度
% PH_STORESTYLE - 输入图像的方式：1. SIGIMG-单图模式/矩阵格式；2. MULIMG-多图模式/cell格式
% NORM_STYLE - 归一化方式：1. NORM_RGB - 以R+G+B和值归一化；2. NORM_Y - 以亮度值归一化；3.
% NORM_NONE 不作归一化处理
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% version: 1-0@fh
% modify:   1. 修改输入图像的方式为两种，分别为单图模式和多图模式，单图模式保留0-0方式，多图模式可较好连接plot_value分析结果
%           2. 新增归一化方式为可选
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% 显示状态
disp('%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%');
disp('--->>> compute mean and norm of color blocks...');
% input
ph = PH;
no_block = NO_BLOCK;
wide_block = WIDE_BLOCK;
ph_storestyle = PH_STORESTYLE;
norm_style = NORM_STYLE;

% 依据图像存储方式，选择处理
switch ph_storestyle
    case 'SIGIMG'
        disp('---<<< single img mode');
        figure(1);imshow(ph);
        figure(2);hold on;
        for i =1:1:no_block
            figure(1);
            [pt_x,pt_y] = ginput(1);
            pt_x = floor(pt_x);
            pt_y = floor(pt_y);
            roi_block = ph(pt_y-wide_block:pt_y+wide_block,pt_x-wide_block:pt_x+wide_block,:);
            %图像降噪处理-（后期可扩展该处处理方法）
            roi_block_r = medfilt2(roi_block(roi_block(:,:,1)),[3,3]);
            roi_block_g = medfilt2(roi_block(roi_block(:,:,2)),[3,3]);
            roi_block_b = medfilt2(roi_block(roi_block(:,:,3)),[3,3]);
        
            mean_block(1,i,1) = mean(mean(roi_block_r));
            mean_block(1,i,2) = mean(mean(roi_block_g));
            mean_block(1,i,3) = mean(mean(roi_block_b));
            
            switch norm_style
                case 'NORM_NONE'
                    sum_mean = 1;
                case 'NORM_RGB'
                    sum_mean = mean_block(1,i,1)+mean_block(1,i,2)+mean_block(1,i,3);
                case 'NORM_Y'
                    sum_mean = 0.2989*mean_block(1,i,1)+0.5870*mean_block(1,i,2)+0.1140*mean_block(1,i,3);
            end
            
            norm_block(1,i,1) = mean_block(1,i,1)/sum_mean;
            norm_block(1,i,2) = mean_block(1,i,2)/sum_mean;
            norm_block(1,i,3) = mean_block(1,i,3)/sum_mean;
            
            figure(2);subplot(1,no_block,i);imshow(roi_block);
        end
 
      
        
    case 'MULIMG'
        disp('---<<< img mode');
        % -获取图像存储尺寸
        [rows_data,cols_data] = size(ph);
        figure(2);hold on;
        for n=1:1:cols_data
            figure(1);imshow(ph{n});
            for i=1:1:no_block
                figure(1);
                [pt_x,pt_y] = ginput(1);
                pt_x = floor(pt_x);pt_y=floor(pt_y);
                roi_block = ph{n}(pt_y-wide_block:pt_y+wide_block,pt_x-wide_block:pt_x+wide_block,:);
                %图像降噪处理-（后期可扩展该处处理方法）
                roi_block_r = medfilt2(roi_block(:,:,1),[3,3]);
                roi_block_g = medfilt2(roi_block(:,:,2),[3,3]);
                roi_block_b = medfilt2(roi_block(:,:,3),[3,3]);
                
                mean_block{n}(1,i,1) = mean(mean(roi_block_r));
                mean_block{n}(1,i,2) = mean(mean(roi_block_g));
                mean_block{n}(1,i,3) = mean(mean(roi_block_b));
  
                switch norm_style
                    case 'NORM_NONE'
                        sum_mean = 1;
                    case 'NORM_RGB'
                        sum_mean = mean_block{n}(1,i,1)+mean_block{n}(1,i,2)+mean_block{n}(1,i,3);
                    case 'NORM_Y'
                        sum_mean = 0.2989*mean_block{n}(1,i,1)+0.5870*mean_block{n}(1,i,2)+0.1140*mean_block{n}(1,i,3);
                end
                
               norm_block{n}(1,i,1) = mean_block{n}(1,i,1)/sum_mean;
               norm_block{n}(1,i,2) = mean_block{n}(1,i,2)/sum_mean;
               norm_block{n}(1,i,3) = mean_block{n}(1,i,3)/sum_mean;
               
               figure(2);subplot(1,no_block,i);imshow(roi_block);title('Get data!','Color','g');
            end
            
%%%%%%%5555555        
        black_block = uint8(zeros(100,100,3));
        for i =1:1:no_block
            figure(2);subplot(1,no_block,i);imshow(black_block);title('Wait data!','Color','r');
        end
%%%%%%%%%%%%%%  
            
        end
end
        
MEAN_BLOCK = mean_block;
NORM_BLOCK = norm_block;

disp('--->>> compute mean and norm of color blocks completed');
disp('%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%');
