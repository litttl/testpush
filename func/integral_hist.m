function INTEGRAL_CNT = integral_hist(PH_IN)

% function A = integral_hist(PH_IN)
% integral_hist 函数用于计算积分直方图，便于取出对应点的概率

ph_in = PH_IN;
[cnt,gray] = imhist(ph_in);

sum_cnt = sum(cnt);

integral_cur = 0;
integral_cnt = zeros(256);
for i = 0:1:255
   integral_cur = integral_cur+cnt(i+1);
   integral_cnt(i+1) = integral_cur/sum_cnt;
end

INTEGRAL_CNT = integral_cnt;


