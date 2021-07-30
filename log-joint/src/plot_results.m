function plot_results(filename)

A = importdata(filename);
% Create data and 2-by-1 tiled chart layout
x = A(:,1);
y1 = A(:,3);
y2 = A(:,2);
y3 = A(:,4);
y4 = A(:,5);
y5 = A(:,6);
y6 = A(:,7);

figure('color', 'white');
tiledlayout(5,1);

% Top plot
ax1 = nexttile;
stairs(ax1,x,y1)
grid on
title(ax1,'PID OUT')
xlabel(ax1, 'time (sec)')
ylabel(ax1,'PID out')

% Bottom plot
ax2 = nexttile;
Y = [y2, y3];
stairs(ax2,x,Y)
grid on
legend('pid ref','encoder')
title(ax2,'PID REF / ENCODER')
xlabel(ax2, 'time (sec)')
ylabel(ax2,'degrees')

% Bottom plot
ax3 = nexttile;
stairs(ax3,x,y4)
grid on
legend('motor current')
title(ax3,'motor current')
xlabel(ax3, 'time (sec)')
ylabel(ax3,'Ampere')

% Bottom plot
ax4 = nexttile;
stairs(ax4,x,y5)
grid on
legend('motor encoder')
title(ax4,'motor encoder')
xlabel(ax4, 'time (sec)')
ylabel(ax4,'degrees x 100')

% Bottom plot
ax5 = nexttile;
stairs(ax5,x,y6)
grid on
legend('PWM')
title(ax5,'PWM')
xlabel(ax5, 'time (sec)')
ylabel(ax5,'PWM %')

% Bundle the axes for zoom
linkaxes([ax1 ax2 ax3 ax4 ax5], 'x');
