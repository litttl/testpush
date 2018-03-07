function MAP_GAIN = lens_correction(PH,LEVEL_CORRECT)

% function MAP_GAIN = lens_correction(PH)
% lens_correction ���ڼ���ͼ��ı��ؽ��������ͼ������,�ô����������ں�˴����ʻ���Ӧ������һ����Ч�����ȹ�һ��
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% MAP_GAIN - �����������Ӧ���������LENS У������ֵ
% PH - ����Ĵ�У���ο�ͼ��Ҫ���ͼƬ��������Ӧlens �ĳ�������
% LEVEL_CORRECT - У��ǿ�ȣ�ȡ0-100����ʾ�����У�����������ȱ���
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% version: 0-0@fh
% modify: none
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

if nargin == 2
    level_correct = LEVEL_CORRECT/100;
else
    level_correct = 1;
end

% ph = PH;
% ������ͼ�����Ԥ������������Ӱ��
ph(:,:,1) = medfilt2(PH(:,:,1),[5,5]);
ph(:,:,2) = medfilt2(PH(:,:,2),[5,5]);
ph(:,:,3) = medfilt2(PH(:,:,3),[5,5]);

% ��ͼ����������ȡ��ֵ��ΪУ������
[rows_ph,cols_ph,channels_ph] = size(ph);
radius_ph = sqrt(double(rows_ph*rows_ph+cols_ph*cols_ph))/2;
ref_area = ph(rows_ph*5/12:rows_ph*7/12,cols_ph*5/12:cols_ph*7/12,:);
ref_area_r = medfilt2(ref_area(:,:,1),[3,3]);
ref_area_g = medfilt2(ref_area(:,:,2),[3,3]);
ref_area_b = medfilt2(ref_area(:,:,3),[3,3]);

% figure;
% subplot(2,2,1);imshow(ref_area);
% subplot(2,2,2);imshow(ref_area_r);
% subplot(2,2,3);imshow(ref_area_g);
% subplot(2,2,4);imshow(ref_area_b);

ref_value_r = mean(mean(ref_area_r));
ref_value_g = mean(mean(ref_area_g));
ref_value_b = mean(mean(ref_area_b));

map_gain = double(zeros(rows_ph,cols_ph,channels_ph));
for i=1:1:rows_ph
    for j=1:1:cols_ph
        radius_current = sqrt(double((i-rows_ph/2)*(i-rows_ph/2)+(j-cols_ph/2)*(j-cols_ph/2)));    
        ratio_lsc = 1-radius_current/radius_ph*(1-level_correct);
        map_gain(i,j,1)=((1-ratio_lsc)*double(ph(i,j,1))+ratio_lsc*ref_value_r)/double(ph(i,j,1));
        map_gain(i,j,2)=((1-ratio_lsc)*double(ph(i,j,2))+ratio_lsc*ref_value_g)/double(ph(i,j,2));
        map_gain(i,j,3)=((1-ratio_lsc)*double(ph(i,j,3))+ratio_lsc*ref_value_b)/double(ph(i,j,3));
    end
end


MAP_GAIN = map_gain;