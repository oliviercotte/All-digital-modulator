%% Close everything, reset workspace
clear all; close all; clc; warning('off','all');

%% For Xilinx FPGA boards with Spartan-6 or Virtex-6 FPGAs, run:
hdlsetuptoolpath('ToolName', 'Xilinx ISE', 'ToolPath', 'C:\Xilinx\14.7\ISE_DS\ISE\bin\nt\ise.exe');

%% Creates a different seed each time
rng shuffle;

%%
% -w -intstyle xflow -g StartUpClk:JtagClk jtagcosim_top.ncd 

%%
% xlSgRoot = 

% % Generate the configuration for a given Reference Measurement Channel
% rmc = lteRMCDL('R.50');
% 
% %% Generate a random signal to transmit
% Data = randi([0 1], 1, sum(rmc.PDSCH.TrBlkSizes));
% 
% %% Generate the standard-compliant data
% [waveform, txgrid, RMCcfgOut] = lteRMCDLTool(rmc, Data);
% 
% %% Display signal and its spectrum
% figure
% plot(real(waveform));
% figure
% plot(real(waveform(:,1)));
% 
% figure
% LTE_signal = real(waveform(:,1))';
% ts = timeseries(LTE_signal);
% LTE_SamplingRate = RMCcfgOut.SamplingRate
% [y,f] = periodogram(LTE_signal,[],[],LTE_SamplingRate,'centered');
% plot(f,10*log10(y)); grid on;
% 
% u = LTE_signal;
% tx.time = [];
% tx.signals.values = u';
% tx.signals.dimensions = 1;
% 
% T_LTE = 1/LTE_SamplingRate;

%% Generate the noise transfer function of the modulator
echo on
nLev        = 512;
order       = 2;
OSR         = 16;
H_opt       = 1;
H_inf       = 1.5;
H           = synthesizeNTF(8,OSR,H_opt,H_inf);
H1          = synthesizeNTF(2,OSR,H_opt,H_inf);
H2          = synthesizeNTF(4,OSR,H_opt,H_inf);
H3          = synthesizeNTF(5,OSR,H_opt,H_inf);
H4          = synthesizeNTF(6,OSR,H_opt,H_inf);

%% Realizing an NTF with the CRFB structure.
form = 'CRFB';
[a,g,b,c] = realizeNTF(H,form);
[a1,g1,b1,c1] = realizeNTF(H1,form);
[a2,g2,b2,c2] = realizeNTF(H2,form);
[a3,g3,b3,c3] = realizeNTF(H3,form);
[a4,g4,b4,c4] = realizeNTF(H4,form);
b(2:end) = 0; % for a maximally flat STF
b1(2:end) = 0;
b2(2:end) = 0;
b3(2:end) = 0;
b4(2:end) = 0;

%% Create a sine wave of ftest Hz, up to fB.
ftest   = 9e6;
Fpass   = 30.72e6;              % Original sampling frequency
Tpass   = 1/Fpass;
Fs      = OSR * Fpass;          % Digital-Up-Converted sampling frequency
Ts      = 1/Fs;
N       = 2^13;                 % N = Fs;
fB      = ceil(Fs/(2*OSR));
t       = 0:1/Fs:1-1/Fs;        % Time vector of 1 second
t_baseband = 0:1/Fpass:1-1/Fpass; 
A       = 0.5*(2-1);
u       = A*sin(2*pi*ftest*t(1:N));  % half-scale sine-wave input; ftest samples per period N
u_baseband = A*sin(2*pi*ftest*t_baseband); 
% v       = simulateDSM(u,H1,2);
v1      = simulateDSM(u,H1,2);
v2      = simulateDSM(u,H2,2);
v3      = simulateDSM(u,H3,2);
v4      = simulateDSM(u,H4,2);
tone.time = [];
tone.signals.values = u_baseband';
tone.signals.dimensions = 1;
echo off;

%% Test tone spectrum
figure
Nfft        = 2^13; % Length of FFT
X           = fft(u,Nfft);
magX        = (abs(X));
spec        = 20*log10(magX);
spec        = spec-max(spec);
spec        = max(spec, -40*ones(1, length(spec)));
fn          = 0:1/Nfft:1-1/Nfft;
plot(fn, spec); axis([0 0.5 -40 1.2]); grid;
xlabel('Normalized Frequency (cycles per sample)');
ylabel('Magnitude (dB)');

%% Modulator output
% figure;
% t = 0:100;
% stairs(t, u(t+1),'r');
% hold on;
% stairs(t,v(t+1),'g');
% axis([0 100 -1.2 1.2]);
% xlabel('Sample Number');
% ylabel('u, v');
% hold off

%% Modulator output spectrum
% Simulink_Spectrum(v', N, H1, OSR, fB, ftest, Fs);
Simulink_Spectrum(v1', N, H1, OSR, fB, ftest, Fs);
Simulink_Spectrum(v2', N, H2, OSR, fB, ftest, Fs);
Simulink_Spectrum(v3', N, H3, OSR, fB, ftest, Fs);
Simulink_Spectrum(v4', N, H4, OSR, fB, ftest, Fs);
% f = linspace(0,0.5,N/2+1);
% echo on
% spec = fft(v(1:N).*ds_hann(N))/(N/4);
% echo off;
% figure; clf;
% hold on;
% grid on
% grid minor
% plot( f, dbv(spec(1:N/2+1)), 'b')
% axis([0 0.5 -120 0]);
% xlabel('Normalized Frequency')
% ylabel('dBFS')
% title('Output Spectrum');
% hold off
% 
% echo on
% snr = calculateSNR(spec(1:fB*N/Fs+3),ftest*N/Fs);
% echo off;
% text_handle = text(0.05,-10, sprintf('SNR = %4.1fdB @ OSR = %d',snr,OSR),'vert','middle');
% set(text_handle,'fontsize',18);
% 
% echo on
% NBW = 1.5/N;
% Sqq = 4 * evalTF(H1,exp(2i*pi*f)).^2 / 3;
% echo off
% hold on;
% plot( f, dbp(Sqq*NBW), 'm', 'Linewidth', 2 );
% text(0.5, -90, sprintf('NBW = %4.1E x f_s ',NBW),'Hor','right');
% legend('Simulation','Expected PSD');

% ComputePeakSNR(H,OSR);
% ComputePeakSNR(H1,OSR);
% ComputePeakSNR(H2,OSR);
% ComputePeakSNR(H3,OSR);
% ComputePeakSNR(H4,OSR);
% echo on
% [snr_pred,amp_pred] = predictSNR(H1,OSR);
% [snr,amp] = simulateSNR(H1,OSR);
% echo off
% figure; clf;
% plot(amp_pred,snr_pred,'-',amp,snr,'og');
% figureMagic([-100 0], 10, 1, [0 100], 10, 1,[],'SQNR');
% xlabel('Input Level (dBFS)');
% ylabel('SQNR (dB)');
% title('SNR curve- theory and simulation');
% [pk_snr pk_amp] = peakSNR(snr,amp);
% text(-25,85,sprintf('peak SNR = %4.1fdB\n@ OSR = %d\n',pk_snr,OSR),'Hor','right');
% echo off

%% NTF and STF calculation for the modulator realization
% figure;
% ABCD = stuffABCD(a,g,b,c,form);
% ABCD1 = stuffABCD(a1,g1,b1,c1,form);
% ABCD2 = stuffABCD(a2,g2,b2,c2,form);
% ABCD3 = stuffABCD(a3,g3,b3,c3,form);
% ABCD4 = stuffABCD(a4,g4,b4,c4,form);
% [Ha, Ga] = calculateTF(ABCD);
% [Ha1, Ga1] = calculateTF(ABCD1);
% [Ha2, Ga2] = calculateTF(ABCD2);
% [Ha3, Ga3] = calculateTF(ABCD3);
% [Ha4, Ga4] = calculateTF(ABCD4);
% Compute_NTF_STF(Ha, Ga);
% Compute_NTF_STF(Ha1, Ga1);
% Compute_NTF_STF(Ha2, Ga2);
% Compute_NTF_STF(Ha3, Ga3);
% Compute_NTF_STF(Ha4, Ga4);
% [Ha, Ga] = calculateTF(ABCD);
% f = linspace(0, 0.5, 100);
% z = exp(2i*pi*f);
% magHa = dbv(evalTF(Ha,z));
% magGa = dbv(evalTF(Ga,z));
% plot(f,magHa, 'b', f,magGa, 'm', 'Linewidth',1);
% hold on
% grid on
% grid minor
% title('NTF and STF calculation for the modulator realization')
% xlabel('Normalized Frequency')
% ylabel('dB')
% legend('NTF', 'STF', 'Location','southwest')
% hold off

%% dynamic range scaling, plus a plot of the state magnitude as a function of the input level for the scaled modulator
% xLim = 0.9; f0 = 0;
% [ABCDs, umax] = scaleABCD(ABCD,2,f0,xLim);
% [ABCDs1, umax1] = scaleABCD(ABCD1,2,f0,xLim);
% [a, g, b, c] = mapABCD(ABCDs,form)
% [a1, g1, b1, c1] = mapABCD(ABCDs1,form)
% [a2, g2, b2, c2] = mapABCD(ABCDs2,form)
% [a3, g3, b3, c3] = mapABCD(ABCDs3,form)
% [a4, g4, b4, c4] = mapABCD(ABCDs4,form)

load('LTE_waveform.mat')
load('DAC_OUT.mat')

%% Correlation
% xcorr = dsp.Crosscorrelator;
% y = xcorr(DAC_OUT1,DAC_OUT5); %computes cross-correlation of x1 and x2
% figure,plot(t,DAC_OUT1,'b',t, DAC_OUT5, 'g');
% legend('Input signal 1',' Input signal 2')

% Load_Digital_Up_Converter