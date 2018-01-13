% Ndiff = N;
% N = 630000;
% simout = DAC_MOD1_SIM1;
simout = DAC_MOD2_SIM1;
% simout = DAC_MOD4_SIM2;
% simout = DAC_MOD6_SIM2;
% simout = DAC_MOD8_SIM2;
% simout = dsm_mod2_fi;
simout = simout';
simout = simout(1:N);

f = linspace(0,0.5,N/2+1);
echo on
spec = fft(simout.*ds_hann(N))/(N/4);
echo off;
figure; clf;
hold on;
grid on
grid minor
plot( f, dbv(spec(1:N/2+1)), 'b')
axis([0 0.5 -120 0]);
xlabel('Normalized Frequency')
ylabel('dBFS')
title('Output Spectrum');
hold off

echo on
snr = calculateSNR(spec(1:fB+1),ftest);
echo off;
text_handle = text(0.05,-10, sprintf('SNR = %4.1fdB @ OSR = %d',snr,OSR),'vert','middle');
set(text_handle,'fontsize',18);

echo on
NBW = 1.5/N;
Sqq = 4 * evalTF(H,exp(2i*pi*f)).^2 / 3;
echo off
hold on;
plot( f, dbp(Sqq*NBW), 'm', 'Linewidth', 2 );
text(0.5, -90, sprintf('NBW = %4.1E x f_s ',NBW),'Hor','right');
legend('Simulation','Expected PSD');

% N = Ndiff;
