%% Close everything, reset workspace
clear all; close all; clc; warning('off','all');

fig1pos1 = [0 630 300 200];
fig1pos2 = [0 372 777 355];
fig1pos3 = [8 562 300 250];
fig1pos4 = [0 200 777 600];
fig2pos1 = [336 562 450 250];
fig2pos2 = [185 372 662 355];
fig3pos1 = [815 565 254 247];
fig3pos2 = [275 365 520 362];

%% Creates a different seed each time
rng shuffle;

% Error using lteRMCDL>validateRMC (line 1444)
% The function call resulted in an error: The RC number 'R.31-3A FDD' is not valid, it must be one of 'R.0', 'R.1', 'R.2', 'R.3',
% 'R.4', 'R.5', 'R.6', 'R.7', 'R.8', 'R.9', 'R.10', 'R.11', 'R.12', 'R.13', 'R.14', 'R.25', 'R.26', 'R.27', 'R.28', 'R.31-3A',
% 'R.31-4', 'R.43', 'R.44', 'R.45', 'R.45-1', 'R.48', 'R.50', 'R.51', 'R.12-9RB', 'R.6-27RB', 'R.11-45RB'.
% 
% Error in lteRMCDL (line 521)
%         validateRMC(rmc.RC);
% 
% Error in Model3_LTE (line 17)
% rmc = lteRMCDL('R.31-3A FDD');
 

% Generate the configuration for a given Reference Measurement Channel
rmc = lteRMCDL('R.50');

%% Generate a random signal to transmit
Data = randi([0 1], 1, sum(rmc.PDSCH.TrBlkSizes));

%% Generate the standard-compliant data
[waveform, txgrid, RMCcfgOut] = lteRMCDLTool(rmc, Data);

figure
LTE_signal = real(waveform(:,1))';
% LTE_signal = LTE_signal .* (1+2+4+8);
ts = timeseries(LTE_signal);
LTE_SamplingRate = RMCcfgOut.SamplingRate
[y,f] = periodogram(LTE_signal,[],[],LTE_SamplingRate,'centered');
plot(f,10*log10(y)); grid on;

echo on
nLev = 2;
order = 4;
OSR = 32;
H_opt = 1;
H_inf = 1.5;
H = synthesizeNTF(order,OSR,H_opt,H_inf);
Fs = LTE_SamplingRate; % R2017b
Ts = 1/Fs;
ftest=2.25e3; % Create a sine wave of ftest Hz, up to fB.
N = length(LTE_signal');
u = LTE_signal;
rx=double([(0:length(LTE_signal)-1)', LTE_signal']);
% % N = Fs;
fB = ceil(N/(2*OSR));
v = simulateDSM(u,H,nLev);
echo off;

figure
Nfft = 2^13; % Length of FFT
X = fft(LTE_signal,Nfft);
% X = fft(u,Nfft);
magX = (abs(X));
spec = 20*log10(magX);
spec = spec-max(spec);
spec = max(spec, -40*ones(1, length(spec)));
fn = 0:1/Nfft:1-1/Nfft;
plot(fn, spec); axis([0 0.5 -40 1.2]); grid;
xlabel('Normalized Frequency (cycles per sample)');
ylabel('Magnitude (dB)');

figure;
t = 0:100;
stairs(t, u(t+1),'r');
hold on;
stairs(t,v(t+1),'g');
axis([0 100 -1.2 1.2]);
xlabel('Sample Number');
ylabel('u, v');
set(gcf,'NumberTitle','off'); 
set(gcf,'Name','Modulator Input & Output');
hold off

% set(1,'position',fig1pos2);
% changeFig(18,2,12);

f = linspace(0,0.5,N/2+1);
echo on
spec = fft(v.*ds_hann(N))/(N/4);
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
set(gcf,'NumberTitle','off'); 
set(gcf,'Name','Bistream frequency estimation');
hold off

%set(2,'position',fig2pos2);
%changeFig(18,2,12);

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

% set(2,'position',fig2pos1);
% legend('Simulation','Expected PSD');

%% Display signal and its spectrum
figure
plot(real(LTE_signal));
hold on;
plot( f, dbp(Sqq*NBW), 'm', 'Linewidth', 2 );
legend('Simulation','Expected PSD');
xlabel('Normalized Frequency (cycles per sample)');
ylabel('Magnitude (dB)');

echo on
[snr_pred,amp_pred] = predictSNR(H,OSR);
[snr,amp] = simulateSNR(H,OSR);
echo off
figure;
plot(amp_pred,snr_pred,'-',amp,snr,'og');
figureMagic([-100 0], 10, 1, [0 100], 10, 1,[],'SQNR');
xlabel('Input Level (dBFS)');
ylabel('SQNR (dB)');
title('SNR curve- theory and simulation');
[pk_snr pk_amp] = peakSNR(snr,amp);
text(-25,85,sprintf('peak SNR = %4.1fdB\n@ OSR = %d\n',pk_snr,OSR),'Hor','right');
echo off

%set(3,'position',fig3pos2);
%changeFig(18,2,12);

%% Realizing an NTF with the CRFB structure.
form = 'CRFB';
[a,g,b,c] = realizeNTF(H,form)
b(2:end) = 0; % for a maximally flat STF

%% NTF and STF calculation for the modulator realization
figure;
ABCD = stuffABCD(a,g,b,c,form);
[Ha, Ga] = calculateTF(ABCD);
f = linspace(0, 0.5, 100);
z = exp(2i*pi*f);
magHa = dbv(evalTF(Ha,z));
magGa = dbv(evalTF(Ga,z));
plot(f,magHa, 'b', f,magGa, 'm', 'Linewidth',1);
hold on
grid on
grid minor
title('NTF and STF calculation for the modulator realization')
xlabel('Normalized Frequency')
ylabel('dB')
legend('NTF', 'STF', 'Location','southwest')
hold off

%% dynamic range scaling, plus a plot of the state magnitude as a function of the input level for the scaled modulator
% xLim = 0.9; f0 = 0;
% [ABCDs, umax] = scaleABCD(ABCD,nLev,f0,xLim);
% [a, g, b, c] = mapABCD(ABCDs,form)
