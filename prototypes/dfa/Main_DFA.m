function [alfa1,alfa2] = Main_DFA(signal)
%UNTITLED3 Summary of this function goes here
%   Detailed explanation goes here
[window, fluctuation] = DFA(signal);

s = 7; % podzia³ wektora na  m1 = [4 6 8 10 12 14 16], m2 = [32 - 64]
% dane nsr001
log_m = log(window);
log_f = log(fluctuation);


alfa1 = polyfit(log_m(1:s), log_f(1:s), 1);
alfa2 = polyfit(log_m(s:end), log_f(s:end), 1);


line_alfa1 = polyval(alfa1, log_m(1:s));
line_alfa2 = polyval(alfa2, log_m(s:end));

figure
h = plot(log_m, log_f, 'k.');
hold on
h = plot(log_m(1:s), line_alfa1, 'b');
h = plot(log_m(s:end), line_alfa2, 'c');
xlabel('log \Deltam', 'fontsize', 18)
ylabel('log F(\Deltam)', 'fontsize', 18)
grid on

hold off
end

