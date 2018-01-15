function [] = Compute_Tone_Spectrum(DAC_OUT)
%COMPUTE_TONE_SPECTRUM Summary of this function goes here
%   Detailed explanation goes here
figure
Nfft        = 2^13; % Length of FFT
X           = fft(DAC_OUT,Nfft);
magX        = (abs(X));
spec        = 20*log10(magX);
spec        = spec-max(spec);
spec        = max(spec, -40*ones(1, length(spec)));
fn          = 0:1/Nfft:1-1/Nfft;
plot(fn, spec); axis([0 0.5 -40 1.2]); grid;
xlabel('Normalized Frequency (cycles per sample)');
ylabel('Magnitude (dB)');
end

