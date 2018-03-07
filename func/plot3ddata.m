function A = plot3ddata(FILE_ROAD,SHAPE_COLOR)

% function A = plot3ddata(file_road)
% plot3ddata 为画出file_road 下的数据

file_road = FILE_ROAD;
shape_color = SHAPE_COLOR;

data = xlsread(file_road);

[rows_data,cols_data] = size(data);

for i=1:1:rows_data
    plot3(data(i,2),data(i,3),data(i,4),shape_color);
    text(data(i,2),data(i,3),data(i,4),num2str(data(i,1)),'fontsize',10);
end

A = 0;
