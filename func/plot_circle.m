function A = plot_circle(R)

% function A = plot_circle(R)
% plot_circle �������ڻ���ͬ��Բ

r = R;

ta = 0:0.0001:2*pi;
x_5 = r*cos(ta);y_5 = r*sin(ta);
plot(x_5,y_5,'-')

