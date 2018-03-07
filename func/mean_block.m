function [MEAN_BLOCK,NORM_BLOCK] = mean_block(PH,NO_BLOCK,WIDE_BLOCK,PH_STORESTYLE,NORM_STYLE)

% function [MEAN_BLOCK,NORM_BLOCK] = mean_block(PH,NO_BLOCK,WIDE_BLOCK,PH_STORESTYLE,NORM_STYLE)
% mean_block
% �����������ǣ����ڼ���ָ��������NO_BLOCK����ɫ�飨�������ѡ��Ϊ���ģ���չ��������WIDE_BLOCK��С��ɫ�飩��ͳ�ƾ�ֵ
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% MEAN_BLOCK - �����ɫ���ֵ
% NORM_BLOCK - �����ɫ���һ������һ��������ѡ����ֵ
% PH - �����ͼ������
% NO_BLOCK - ��Ҫ�����ɫ������
% WIDE_BLOCK - ѡȡ��ɫ�����
% PH_STORESTYLE - ����ͼ��ķ�ʽ��1. SIGIMG-��ͼģʽ/�����ʽ��2. MULIMG-��ͼģʽ/cell��ʽ
% NORM_STYLE - ��һ����ʽ��1. NORM_RGB - ��R+G+B��ֵ��һ����2. NORM_Y - ������ֵ��һ����3.
% NORM_NONE ������һ������
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% version: 1-0@fh
% modify:   1. �޸�����ͼ��ķ�ʽΪ���֣��ֱ�Ϊ��ͼģʽ�Ͷ�ͼģʽ����ͼģʽ����0-0��ʽ����ͼģʽ�ɽϺ�����plot_value�������
%           2. ������һ����ʽΪ��ѡ
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% ��ʾ״̬
disp('%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%');
disp('--->>> compute mean and norm of color blocks...');
% input
ph = PH;
no_block = NO_BLOCK;
wide_block = WIDE_BLOCK;
ph_storestyle = PH_STORESTYLE;
norm_style = NORM_STYLE;

% ����ͼ��洢��ʽ��ѡ����
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
            %ͼ���봦��-�����ڿ���չ�ô�����������
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
        % -��ȡͼ��洢�ߴ�
        [rows_data,cols_data] = size(ph);
        figure(2);hold on;
        for n=1:1:cols_data
            figure(1);imshow(ph{n});
            for i=1:1:no_block
                figure(1);
                [pt_x,pt_y] = ginput(1);
                pt_x = floor(pt_x);pt_y=floor(pt_y);
                roi_block = ph{n}(pt_y-wide_block:pt_y+wide_block,pt_x-wide_block:pt_x+wide_block,:);
                %ͼ���봦��-�����ڿ���չ�ô�����������
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