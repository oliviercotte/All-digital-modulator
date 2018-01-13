%% File: spectral_estimation.m
% Produce a record of sigma-delta data and analyzing it
%
% Use of the FFt to calculate a sine-wave scaled PSD

%% Close everything, reset workspace
clear; close all; clc; warning('off','all');

%% Creates a different seed each time
rng shuffle;

%% Synthesizes a 8th-order NTF (zeros optimized), creates the binary sigma-delta data, and compute modulator output and actual NTF
order = 2;
OSR = 16;
H_opt = 1;
%H_inf = 2;
ntf0 = synthesizeNTF(order,OSR,H_opt,[]);
N = 122.88e6;
fbin = 2.25e6; % Set an odd FFT bin to ensure that the input data contains no repeated segments
u = 1/2*sin(2*pi*fbin/N*(0:N-1));
[v, tmpl, tmp2, y] = simulateDSM(u,ntf0);
k = mean(abs(y)/mean(y.^2)); % estimates the quantizer gain and computes the actual NTF.
ntf = ntf0 / (k + (1-k)*ntf0);
%% Compute windowed FFT and NBW
% Scaled and windowed FFf, as well as NBW.
w = hann(N).^2;    % or ones(l,N) or hann(N).^2
nb = 5;         % 1 for Rect; 5 for Hann A2
w1 = norm(w,1);
w2 = norm(w,2);
NBW = (w2/w1)^2;
V = fft(v'.*w)/(w1/2);
%% Compute SNR
signal_bins = fbin + (-(nb-1)/2:(nb-1)/2);
inband_bins = 0:N/(2*OSR);
noise_bins = setdiff(inband_bins,signal_bins);
snr = dbp( sum(abs(V(signal_bins+1)).^2) / sum(abs(V(noise_bins+1)).^2) );

%% Make plots
figure; clf;
semilogx((1:N/2)/N,dbv(V(2:N/2+1)),'b','Linewidth',1);
hold on;
[f, p] = logsmooth(V,fbin,2,nb);
plot(f,p,'m','Linewidth',1.5)
Sq = 4/3 * evalTF(ntf,exp(2i*pi*f)).^2;
plot(f,dbp(Sq*NBW),'k--','Linewidth',1)
figureMagic([1/N 0.5],[],[],[-140 0],10,2);
xlabel('Normalized Frequency (f \rightarrow f_s)');
ylabel('PSD (dBFS/NBW)');
text_handle = text(10e-8,-10, sprintf('SNR=%4.1fdB @ OSR=%d',snr,OSR),'vert','cap');
set(text_handle,'fontsize',18);
legend('Smoothed FFT', 'Hann-windowed FFT', 'Theoretical spectrum', 'Location','southeast')
