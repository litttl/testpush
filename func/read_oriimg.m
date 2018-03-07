function [PH_ALL] = read_oriimg(FILE_ROAD,FILE_NO,FILE_STYLE,LSC_MODE)

% function [PH_ALL] = read_oriimg(FILE_ROAD,FILE_NO,LSC_MODE)
% read_oriimg �����������ǣ�����������ȡͼ��,������ѡ���Ƿ����lscУ��
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% PH_ALL - �����ͼ�񼯺ϣ���cell��ʽ���
% FILE_ROAD - ����ͼ���·����
% FILE_NO - ����ͼ������
% FILE_STYLE - ����ͼ��ĸ�ʽ
% LSC_MODE - lsc����ģʽ��1. LSC_ON ����lscУ����2. LSC_OFF ������lscУ��
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% version: 0-0@fh
% modify: none
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% ��ʾ״̬
disp('%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%');
disp('--->>> read some ori imgs...');
% input
file_road   = FILE_ROAD;
file_no     = FILE_NO;
file_style  = FILE_STYLE;
lsc_mode    = LSC_MODE;  

% ��ȡͼ��
for i=1:1:file_no
    str_file_no = int2str(i);
    switch file_style 
        case 'BMP'
            str_file_style = '.bmp';
        case 'JPG'
            str_file_style = '.jpg';
        case 'PNG'
            str_file_style = '.png';
    end
    file_name = [file_road,str_file_no,str_file_style];
    ph{i} = imread(file_name);
end

switch lsc_mode
    case 'LSC_ON'
        disp('---<<< lsc on mode');
        ph_ref = imread([file_road,'_ref',str_file_style]);
        gain_lsc = lens_correction(ph_ref,100);
        for i=1:1:file_no
            lsc{i} = uint8(gain_lsc.*double(ph{i}));
        end
        PH_ALL = lsc;
        
    case 'LSC_OFF'
        disp('---<<< lsc off mode');
        PH_ALL = ph;
end


disp('--->>> read some ori imgs completed!');
disp('%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%');

