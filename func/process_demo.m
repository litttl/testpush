function [MEAN_VALUE,NORM_VALUE] = process_demo(FILE_ROAD,FILE_NO,FILE_STYLE,LSC_MODE,NO_BLOCK,WIDE_BLOCK,NORM_STYLE,COMPARE_STYLE,COMPARE_BLOCK_NO,PLOT_COMPARE_STYLE)

% function [MEAN_VALUE,NORM_VALUE] = process_demo(FILE_ROAD,FILE_NO,FILE_STYLE,LSC_MODE,NO_BLOCK,WIDE_BLOCK,PH_STORESTYLE,NORM_STYLE,COMPARE_STYLE,BLOCK_NO)
% process_demo �����������ǣ�����ֱ�����������Ҫ�Ľ��ֵ
% ����ʹ�ùؼ�˵���� FILE_ROAD �����ǰ·������ͼƬ�洢·���£���Ҫ������·����+ͼƬ����ǰ��ͼƬ�����˴���׼ȷ�Ա�֤�ļ��Ŀɼ�����  
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% MEAN_VALUE        - �����ͼ��ɫ���ֵ
% NORM_VALUE        - �����ͼ��ɫ���һ��ֵ
% FILE_ROAD         - ��ȡͼ���·��
% FILE_NO           - ��ȡͼƬ����
% FILE_STYLE        - ͼƬ��ʽ��'BMP'/'JPG'/'PNG'
% LSC_MODE          - ѡ��LSCģʽ��1. LSC_ON������LSC�� 2. LSC_OFF���ر�LSC��
% NO_BLOCK          - Ҫ�����ɫ������
% WIDE_BLOCK        - �����ѡ�е�Ϊ���ģ��ķ�����չ����Ԫ���
% NORM_STYLE        - ��һ��ģʽѡ��1. NORM_RGB - ��R+G+B��ֵ��һ����2. NORM_Y - ������ֵ��һ����3. NORM_NONE ������һ������
% COMPARE_STYLE     - ѡ��ͼ����Ƶ�ģ���Ƚ�ģʽ��
%                       1. COMPARE_ALLBLOCK���Ƚ�����ģ�飩 2. COMPARE_SAMEBLOCK���Ƚ�ѡ�����ض�ģ�飩
% COMPARE_BLOCK_NO  - ��COMPARE_SAMEBLOCKģʽ�£�ѡ����Ҫ�Ƚϵľ���ģ�����
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

