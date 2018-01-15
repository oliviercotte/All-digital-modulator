function [ ] = Compute_NTF_STF( Ha, Ga )
%COMPUTE_NTF_STF Summary of this function goes here
%   Detailed explanation goes here
f = linspace(0, 0.5, 100);
z = exp(2i*pi*f);
magHa = dbv(evalTF(Ha,z));
magGa = dbv(evalTF(Ga,z));
figure; clf;
plot(f,magHa, 'b', f,magGa, 'm', 'Linewidth',1);
hold on
grid on
grid minor
title('NTF and STF calculation for the modulator realization')
xlabel('Normalized Frequency')
ylabel('dB')
legend('NTF', 'STF', 'Location','southwest')
hold off
end

