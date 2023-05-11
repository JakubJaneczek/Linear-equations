% Load data from the files and convert from ms to s
% jacobi_times = load('jacobi_times.txt') / 1000;
% gauss_times = load('gauss_times.txt') / 1000;
% LU_times = load('LU_times.txt') / 1000;
% 
% Create a vector of N values
% N = [100, 500, 1000, 2000, 3000];
% 
% Create the plot
% plot(N, jacobi_times);
% hold on
% plot(N, gauss_times);
% plot(N, LU_times);
% hold off
% ylim([0, 100]);
% xlabel('N');
% ylabel('Time');
% title('Execution Time Comparison');
% legend('Jacobi Method', 'Gauss Elimination', 'LU Decomposition');

N = [100, 500, 1000, 2000, 3000];
res1 = [9.8945e-16,
2.18437e-15,
3.11257e-15,
4.43584e-15,
5.39866e-15
];



%semilogy(iter1, res1,'r', 1:length(iter2), res2, 'g',1:length(iter3), res3, 'b',1:length(iter4), res4, 'm',1:length(iter5), res5, 'c')
plot(N, res1)
% add title and axis labels
title('Residuum norm in LU')
xlabel('N')
ylabel('Value of residuum')

% add legend




