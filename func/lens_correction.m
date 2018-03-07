function MAP_GAIN = lens_correction(PH,LEVEL_CORRECT)

% function MAP_GAIN = lens_correction(PH)
% lens_correction 用于计算图像的边沿矫正输出整图矫正比,该处方法由于在后端处理，故还相应的做了一个等效的亮度归一化
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% MAP_GAIN - 函数输出，对应计算出来的LENS 校正增益值
% PH - 输入的待校正参考图，要求该图片能正常反应lens 的成像特性
% LEVEL_CORRECT - 校正强度，取0-100，表示最边沿校正到中心亮度比重
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
% 对输入图像进行预处理，降低噪音影响
ph(:,:,1) = medfilt2(PH(:,:,1),[5,5]);
ph(:,:,2) = medfilt2(PH(:,:,2),[5,5]);
ph(:,:,3) = medfilt2(PH(:,:,3),[5,5]);

% 以图像中心区域取均值作为校正亮度
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