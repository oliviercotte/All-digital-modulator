%% Close everything, reset workspace
clear all; close all; clc; warning('off','all');

%% For Xilinx FPGA boards with Spartan-6 or Virtex-6 FPGAs, run:
hdlsetuptoolpath('ToolName', 'Xilinx ISE', 'ToolPath', 'C:\Xilinx\14.7\ISE_DS\ISE\bin\nt\ise.exe');

%% For Xilinx FPGA boards with 7-series FPGAs, run:
hdlsetuptoolpath('ToolName','Xilinx Vivado','ToolPath','C:\Xilinx\Vivado\2017.4\bin\vivado.bat');

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

% Generate the configuration for a given Reference Measurement Channel
rmc = lteRMCDL('R.27');

%% Generate a random signal to transmit
Data = randi([0 1], 1, sum(rmc.PDSCH.TrBlkSizes));

%% Generate the standard-compliant data
[waveform, txgrid, RMCcfgOut] = lteRMCDLTool(rmc, Data);

%% Display signal and its spectrum
figure
plot(real(waveform));
figure
plot(real(waveform(:,2)));

figure
LTE_signal = real(waveform(:,2))';

% LTE_signal = LTE_signal .* 10;
ts1 = timeseries(LTE_signal);
LTE_SamplingRate = RMCcfgOut.SamplingRate
[y,f] = periodogram(LTE_signal,[],[],LTE_SamplingRate,'centered');
plot(f,10*log10(y)); grid on;

echo on
nLev = 2;
order = 4;
OSR = 16;
H_opt = 1;
H_inf = 1.5;
H = synthesizeNTF(2,OSR,H_opt,H_inf);
H1 = synthesizeNTF(12,OSR,H_opt,H_inf);
% Fs = RMCcfgOut.SamplingRate; % R2017b
Fs = 491.52e3; % Sampling frequency
Ts = 1/Fs;
% N = length(LTE_signal');
ftest=9e3; % Create a sine wave of ftest Hz, up to fB.
% u = real(waveform(:,1))';
t = 0:1/Fs:1-1/Fs; % Time vector of 1 second
t2 = 0:1/30.72e3:1-1/30.72e3; % Time vector of 1 second
A = 0.5*(nLev-1);
% u = LTE_signal';
u = A*sin(2*pi*ftest*t); % half-scale sine-wave input; ftest samples per period N
u2 = A*sin(2*pi*ftest*t2);
% rx=double([(0:length(LTE_signal)-1)', LTE_signal']);
N = Fs;
fB = ceil(N/(2*OSR));
%N = 2^14;
% N = LTE_SamplingRate;

v = simulateDSM(u,H,nLev);
echo off;

figure
Nfft = 2^13; % Length of FFT
% X = fft(LTE_signal,Nfft);
X = fft(u,Nfft);
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
axis([0 100 -nLev+0.5 nLev-0.5]);
xlabel('Sample Number');
ylabel('u, v');
hold off

f = linspace(0,0.5,N/2+1);
echo on
spec = fft(v(1:N).*ds_hann(N))/(N/4);
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
snr = calculateSNR(spec(1:fB*N/Fs+1),ftest*N/Fs);
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

echo on
[snr_pred,amp_pred] = predictSNR(H,OSR);
[snr,amp] = simulateSNR(H,OSR);
echo off
figure; clf;
plot(amp_pred,snr_pred,'-',amp,snr,'og');
figureMagic([-100 0], 10, 1, [0 100], 10, 1,[],'SQNR');
xlabel('Input Level (dBFS)');
ylabel('SQNR (dB)');
title('SNR curve- theory and simulation');
[pk_snr pk_amp] = peakSNR(snr,amp);
text(-25,85,sprintf('peak SNR = %4.1fdB\n@ OSR = %d\n',pk_snr,OSR),'Hor','right');
echo off

%% Realizing an NTF with the CRFB structure.
form = 'CRFB';
[a,g,b,c] = realizeNTF(H,form)
[a1,g1,b1,c1] = realizeNTF(H1,'CRFB')
b(2:end) = 0; % for a maximally flat STF
b1(2:end) = 0; % for a maximally flat STF

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
% xLim = 0.77; f0 = 0;
% [ABCDs, umax] = scaleABCD(ABCD,nLev,f0,xLim);
% [a, g, b, c] = mapABCD(ABCDs,form)

%% Test signals
DAC_IN1.time=[ ];
DAC_IN1.signals.values=LTE_signal';
DAC_IN1.signals.dimensions=1;

DAC_IN2.time=[ ];
DAC_IN2.signals.values=u2;
DAC_IN2.signals.dimensions=1;