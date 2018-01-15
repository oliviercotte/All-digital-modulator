function [ pk_snr pk_amp ] = ComputePeakSNR( H,OSR )
%COMPUTESNR Summary of this function goes here
%   Detailed explanation goes here
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
end

