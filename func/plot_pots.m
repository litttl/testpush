function A = plot_pots(PH,PLOT_STYLE)

ph = PH;
plot_style = PLOT_STYLE;
[a,pic_no]=size(ph);

figure(21);hold on;grid on;
for i =1:1:pic_no
   figure(1);imshow(ph{i});
   [rows,cols] = ginput(1)
   rows = uint32(rows)
   cols = uint32(cols)
   mean_r = mean(mean(ph{i}(cols-10:cols+10,rows-10:rows+10,1)))
   mean_g = mean(mean(ph{i}(cols-10:cols+10,rows-10:rows+10,2)))
   mean_b = mean(mean(ph{i}(cols-10:cols+10,rows-10:rows+10,3)))
    
   figure(21);
   plot3(mean_r,mean_g,mean_b,plot_style);
   
end

