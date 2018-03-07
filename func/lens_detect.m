function A = lens_detect(PH_IN)

% function A = lens_detect(PH_IN)
% lens_detect 函数用于分析显示不同图片之间的lens shade差异
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% A - 程序运行情况返回值
% PH_IN - 输入图片组
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% version: 0-0@fh
% modify: none
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% 赋值
ph_in = PH_IN;

close all;

% 定义取图区域
[rows_phno,cols_phno] = size(ph_in);
[rows_img,cols_img,channels_img]= size(ph_in{1})

  figure(10);hold on;
 for phno=1:1:cols_phno
     for m = 1:1:9
         for n = 1:1:9
%        n = 5
             switch phno
                 case 1
                    plot((n-1)*9+m,ph_in{phno}(uint16(rows_img*n/9),uint16(cols_img*m/9),1),'r*');
                    plot((n-1)*9+m,ph_in{phno}(uint16(rows_img*n/9),uint16(cols_img*m/9),2),'g*');
                    plot((n-1)*9+m,ph_in{phno}(uint16(rows_img*n/9),uint16(cols_img*m/9),3),'b*');
                 case 2 
                    plot((n-1)*9+m,ph_in{phno}(uint16(rows_img*n/9),uint16(cols_img*m/9),1),'r>');
                    plot((n-1)*9+m,ph_in{phno}(uint16(rows_img*n/9),uint16(cols_img*m/9),2),'g>');
                    plot((n-1)*9+m,ph_in{phno}(uint16(rows_img*n/9),uint16(cols_img*m/9),3),'b>');
                 case 3
                    plot((n-1)*9+m,ph_in{phno}(uint16(rows_img*n/9),uint16(cols_img*m/9),1),'r<');
                    plot((n-1)*9+m,ph_in{phno}(uint16(rows_img*n/9),uint16(cols_img*m/9),2),'g<');
                    plot((n-1)*9+m,ph_in{phno}(uint16(rows_img*n/9),uint16(cols_img*m/9),3),'b<');                     
                 case 4
                    plot((n-1)*9+m,ph_in{phno}(uint16(rows_img*n/9),uint16(cols_img*m/9),1),'ro');
                    plot((n-1)*9+m,ph_in{phno}(uint16(rows_img*n/9),uint16(cols_img*m/9),2),'go');
                    plot((n-1)*9+m,ph_in{phno}(uint16(rows_img*n/9),uint16(cols_img*m/9),3),'bo');
             end 
         end
    end
 end
 
 figure(12);hold on;
 
  for phno=1:1:cols_phno
     for m = 1:1:9
         for n = 1:1:9
             switch phno
                 case 1
                    plot3(ph_in{phno}(uint16(rows_img*n/9),uint16(cols_img*m/9),1),ph_in{phno}(uint16(rows_img*n/9),uint16(cols_img*m/9),2),ph_in{phno}(uint16(rows_img*n/9),uint16(cols_img*m/9),3),'r*');
                 case 2 
                    plot3(ph_in{phno}(uint16(rows_img*n/9),uint16(cols_img*m/9),1),ph_in{phno}(uint16(rows_img*n/9),uint16(cols_img*m/9),2),ph_in{phno}(uint16(rows_img*n/9),uint16(cols_img*m/9),3),'g>');
                 case 3
                    plot3(ph_in{phno}(uint16(rows_img*n/9),uint16(cols_img*m/9),1),ph_in{phno}(uint16(rows_img*n/9),uint16(cols_img*m/9),2),ph_in{phno}(uint16(rows_img*n/9),uint16(cols_img*m/9),3),'b<');
                 case 4
                    plot3(ph_in{phno}(uint16(rows_img*n/9),uint16(cols_img*m/9),1),ph_in{phno}(uint16(rows_img*n/9),uint16(cols_img*m/9),2),ph_in{phno}(uint16(rows_img*n/9),uint16(cols_img*m/9),3),'yo');
              end 
         end
     end
 end
 
 
 figure(11);hold on;
 axis([0,1280,0,720]);
 axis([0,1280,0,720]);
 %imshow(ph_in{1});

 
 for m= 4:1:6
     for n= 4:1:6
%          plot(uint16(cols_img*n/9),uint16(rows_img*m/9),'gs');
        ph_in{1}(uint16(rows_img*n/9),uint16(cols_img*m/9),1) = 0;
        ph_in{1}(uint16(rows_img*n/9),uint16(cols_img*m/9),2) = 0;
        ph_in{1}(uint16(rows_img*n/9),uint16(cols_img*m/9),3) = 0;
     end
 end
 
 imshow(ph_in{1});
 A = 0;


