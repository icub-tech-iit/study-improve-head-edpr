% Copyright (C) 2021 Fondazione Istituto Italiano di Tecnologia (IIT)  
% All Rights Reserved.

arg_list = argv();
fin = arg_list{1};
f = load(fin);

view(3);
hold("on");

r = 0.05;
p0 = zeros(3, 1);
sz = size(f);
for i = 1:sz(1)
    p1 = [f(i, 4), f(i, 8), f(i, 12)];
    x  = [f(i, 1), f(i, 5), f(i, 9)];
    y  = [f(i, 2), f(i, 6), f(i, 10)];
    z  = [f(i, 3), f(i, 7), f(i, 11)];
    plot3([p1(1), p1(1)+r*x(1)], [p1(2) p1(2)+r*x(2)], [p1(3) p1(3)+r*x(3)], 'r-');
    plot3([p1(1), p1(1)+r*y(1)], [p1(2) p1(2)+r*y(2)], [p1(3) p1(3)+r*y(3)], 'g-');
    plot3([p1(1), p1(1)+r*z(1)], [p1(2) p1(2)+r*z(2)], [p1(3) p1(3)+r*z(3)], 'b-');
    plot3([p0(1), p1(1)], [p0(2) p1(2)], [p0(3) p1(3)], 'k-');
    p0 = p1;
end

xlabel('x [m]');
ylabel('y [m]');
zlabel('z [m]');
axis('equal');
grid('minor');

hold("off");

% save plot as file
saveas(gcf, 'frames.png');
