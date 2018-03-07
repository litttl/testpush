function RESULT = plot_value(VALUE_TO_PLOT,COMPARE_STYLE,BLOCK_NO)

% function RESULT = plot_value(VALUR_TO_PLOT,COMPARE_STYLE)
% plot_value 函数的作用是：根据数据需求，绘制出相应的比较图
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% RESULT - 返回函数运行状态
% VALUE_TO_PLOT - 待绘制的图像数据,该部分采用cell(1×n)数据结构
% COMPARE_STYLE - 选择图像绘制的比较模式:
%                   1. COMPARE_2D_ALLBLOCK
%                   2. COMPARE_2D_SAMEBLOCK
%                   3. COMPARE_3D_ALLBLOCK
%                   4. COMPARE_3D_SAMEBLOCK
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% version: 0-0@fh
% modify: none
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% 显示状态
disp('%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%');
disp('--->>> plot compare figure ...');
% input 
value_to_plot = VALUE_TO_PLOT;
compare_style = COMPARE_STYLE;

% 获取数据尺寸信息
[rows_data,cols_data] = size(value_to_plot);
[rows_mean,cols_mean,channels_mean] = size(value_to_plot{1});

% 依据比较方式，绘制比较图
switch compare_style
    case 'COMPARE_2D_ALLBLOCK'
        disp('---<<< compare style - COMPARE_2D_ALLBLOCK');
        x = 1:1:cols_mean;
        figure;hold on;
        for i=1:1:cols_data
            switch mod(i,10)
                case 1
                    plot(x,value_to_plot{i}(1,:,1),'rd-.');plot(x,value_to_plot{i}(1,:,2),'gd-.');plot(x,value_to_plot{i}(1,:,3),'bd-.');
                case 2
                    plot(x,value_to_plot{i}(1,:,1),'rs-.');plot(x,value_to_plot{i}(1,:,2),'gs-.');plot(x,value_to_plot{i}(1,:,3),'bs-.');
                case 3
                    plot(x,value_to_plot{i}(1,:,1),'ro-.');plot(x,value_to_plot{i}(1,:,2),'go-.');plot(x,value_to_plot{i}(1,:,3),'bo-.');
                case 4
                    plot(x,value_to_plot{i}(1,:,1),'r*-.');plot(x,value_to_plot{i}(1,:,2),'g*-.');plot(x,value_to_plot{i}(1,:,3),'b*-.');
                case 5
                    plot(x,value_to_plot{i}(1,:,1),'r+-.');plot(x,value_to_plot{i}(1,:,2),'g+-.');plot(x,value_to_plot{i}(1,:,3),'b+-.');
                case 6
                    plot(x,value_to_plot{i}(1,:,1),'rd--');plot(x,value_to_plot{i}(1,:,2),'gd--');plot(x,value_to_plot{i}(1,:,3),'bd--');
                case 7
                    plot(x,value_to_plot{i}(1,:,1),'rs--');plot(x,value_to_plot{i}(1,:,2),'gs--');plot(x,value_to_plot{i}(1,:,3),'bs--');
                case 8
                    plot(x,value_to_plot{i}(1,:,1),'ro--');plot(x,value_to_plot{i}(1,:,2),'go--');plot(x,value_to_plot{i}(1,:,3),'bo--');
                case 9
                    plot(x,value_to_plot{i}(1,:,1),'r*--');plot(x,value_to_plot{i}(1,:,2),'g*--');plot(x,value_to_plot{i}(1,:,3),'b*--');
                case 0
                    plot(x,value_to_plot{i}(1,:,1),'r+--');plot(x,value_to_plot{i}(1,:,2),'g+--');plot(x,value_to_plot{i}(1,:,3),'b+--');  
            end
%             switch mod(i,10)
%                 case 1
%                     plot(x,value_to_plot{i}(1,:,1),'yd-.');plot(x,value_to_plot{i}(1,:,2),'md-.');plot(x,value_to_plot{i}(1,:,3),'cd-.');
%                 case 2
%                     plot(x,value_to_plot{i}(1,:,1),'ys-.');plot(x,value_to_plot{i}(1,:,2),'ms-.');plot(x,value_to_plot{i}(1,:,3),'cs-.');
%                 case 3
%                     plot(x,value_to_plot{i}(1,:,1),'yo-.');plot(x,value_to_plot{i}(1,:,2),'mo-.');plot(x,value_to_plot{i}(1,:,3),'co-.');
%                 case 4
%                     plot(x,value_to_plot{i}(1,:,1),'y*-.');plot(x,value_to_plot{i}(1,:,2),'m*-.');plot(x,value_to_plot{i}(1,:,3),'c*-.');
%                 case 5
%                     plot(x,value_to_plot{i}(1,:,1),'y+-.');plot(x,value_to_plot{i}(1,:,2),'m+-.');plot(x,value_to_plot{i}(1,:,3),'c+-.');
%                 case 6
%                     plot(x,value_to_plot{i}(1,:,1),'yd--');plot(x,value_to_plot{i}(1,:,2),'md--');plot(x,value_to_plot{i}(1,:,3),'cd--');
%                 case 7
%                     plot(x,value_to_plot{i}(1,:,1),'ys--');plot(x,value_to_plot{i}(1,:,2),'ms--');plot(x,value_to_plot{i}(1,:,3),'cs--');
%                 case 8
%                     plot(x,value_to_plot{i}(1,:,1),'yo--');plot(x,value_to_plot{i}(1,:,2),'mo--');plot(x,value_to_plot{i}(1,:,3),'co--');
%                 case 9
%                     plot(x,value_to_plot{i}(1,:,1),'y*--');plot(x,value_to_plot{i}(1,:,2),'m*--');plot(x,value_to_plot{i}(1,:,3),'c*--');
%                 case 10
%                     plot(x,value_to_plot{i}(1,:,1),'y+--');plot(x,value_to_plot{i}(1,:,2),'m+--');plot(x,value_to_plot{i}(1,:,3),'c+--');  
%             end
        end
        
    case 'COMPARE_2D_SAMEBLOCK'
        disp('---<<< compare style - COMPARE_2D_SAMEBLOCK');
        x = 1:1:cols_data;
        figure;hold on;
        block_no = BLOCK_NO;
        for i = 1:1:cols_data
            mean_r(i) = value_to_plot{i}(1,block_no,1);
            mean_g(i) = value_to_plot{i}(1,block_no,2);
            mean_b(i) = value_to_plot{i}(1,block_no,3);
        end
        plot(x,mean_r,'rd-.');plot(x,mean_g,'gd-.');plot(x,mean_b,'bd-.');
        
    case 'COMPARE_3D_ALLBLOCK'
        disp('---<<< compare style - COMPARE_3D_ALLBLOCK');
        figure;hold on;
        grid on;
        axis([0,255,0,255,0,255]);
        xlabel('R');ylabel('G');zlabel('B');
        for x=1:1:cols_data
            switch mod(x,10)
                case 1
                    for i = 1:1:cols_mean
                        plot3(value_to_plot{x}(1,i,1),value_to_plot{x}(1,i,2),value_to_plot{x}(1,i,3),'rd');
                    end
                case 2
                    for i=1:1:cols_mean
                        plot3(value_to_plot{x}(1,i,1),value_to_plot{x}(1,i,2),value_to_plot{x}(1,i,3),'gs');
                    end
                case 3
                    for i=1:1:cols_mean
                        plot3(value_to_plot{x}(1,i,1),value_to_plot{x}(1,i,2),value_to_plot{x}(1,i,3),'bo');
                    end
                case 4
                    for i=1:1:cols_mean
                        plot3(value_to_plot{x}(1,i,1),value_to_plot{x}(1,i,2),value_to_plot{x}(1,i,3),'c*');
                    end
                case 5
                    for i = 1:1:cols_mean
                        plot3(value_to_plot{x}(1,i,1),value_to_plot{x}(1,i,2),value_to_plot{x}(1,i,3),'mv');
                    end
                case 6
                    for i=1:1:cols_mean
                        plot3(value_to_plot{x}(1,i,1),value_to_plot{x}(1,i,2),value_to_plot{x}(1,i,3),'y^');
                    end
                case 7
                    for i=1:1:cols_mean
                        plot3(value_to_plot{x}(1,i,1),value_to_plot{x}(1,i,2),value_to_plot{x}(1,i,3),'kp');
                    end
                case 8
                    for i=1:1:cols_mean
                        plot3(value_to_plot{x}(1,i,1),value_to_plot{x}(1,i,2),value_to_plot{x}(1,i,3),'wh');
                    end                        
                case 9
                    for i=1:1:cols_mean
                        plot3(value_to_plot{x}(1,i,1),value_to_plot{x}(1,i,2),value_to_plot{x}(1,i,3),'r<');
                    end
                case 0
                    for i=1:1:cols_mean
                        plot3(value_to_plot{x}(1,i,1),value_to_plot{x}(1,i,2),value_to_plot{x}(1,i,3),'r>');
                    end
            end
            
        end
        
    case 'COMPARE_3D_SAMEBLOCK'
        disp('---<<< compare style - COMPARE_3D_ALLBLOCK');
        figure;hold on;
        grid on;
        xlabel('R');ylabel('G');zlabel('B');
        block_no = BLOCK_NO;
        for x=1:1:cols_data
            switch mod(x,10)
                case 1
                    i = block_no;
                    plot3(value_to_plot{x}(1,i,1),value_to_plot{x}(1,i,2),value_to_plot{x}(1,i,3),'rd');
                case 2
                    i = block_no;
                    plot3(value_to_plot{x}(1,i,1),value_to_plot{x}(1,i,2),value_to_plot{x}(1,i,3),'gs');                
                case 3
                    i = block_no;
                    plot3(value_to_plot{x}(1,i,1),value_to_plot{x}(1,i,2),value_to_plot{x}(1,i,3),'bo');        
                case 4
                    i = block_no;
                    plot3(value_to_plot{x}(1,i,1),value_to_plot{x}(1,i,2),value_to_plot{x}(1,i,3),'c*');
                case 5
                    i = block_no;
                    plot3(value_to_plot{x}(1,i,1),value_to_plot{x}(1,i,2),value_to_plot{x}(1,i,3),'mv');
                case 6
                    i = block_no;
                    plot3(value_to_plot{x}(1,i,1),value_to_plot{x}(1,i,2),value_to_plot{x}(1,i,3),'y^');
                case 7
                    i = block_no;
                    plot3(value_to_plot{x}(1,i,1),value_to_plot{x}(1,i,2),value_to_plot{x}(1,i,3),'kp');
                case 8
                    i = block_no;
                    plot3(value_to_plot{x}(1,i,1),value_to_plot{x}(1,i,2),value_to_plot{x}(1,i,3),'wh');
                case 9
                    i = block_no;
                    plot3(value_to_plot{x}(1,i,1),value_to_plot{x}(1,i,2),value_to_plot{x}(1,i,3),'r<');                      
                case 0
                    i = block_no;
                    plot3(value_to_plot{x}(1,i,1),value_to_plot{x}(1,i,2),value_to_plot{x}(1,i,3),'r>');
            end
        end
end

RESULT = 0;

disp('--->>> plot compare figure completed');
disp('%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%');