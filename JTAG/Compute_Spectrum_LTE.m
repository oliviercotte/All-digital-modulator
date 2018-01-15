%% Simulink simulation
% Simulink_Spectrum(DSM_MASH_SIM3, N, H, OSR, fB, ftest, Fs);
% Simulink_Spectrum(DSM_MOD8_SIM1, N, H, OSR, fB, ftest, Fs);
% Simulink_Spectrum(DAC_OUT, N, H1, OSR, fB, ftest, Fs);
Simulink_Spectrum_LTE(LTE_DAC_OUT1, N, H1, OSR, fB, ftest, Fs);
Simulink_Spectrum_LTE(LTE_DAC_OUT2, N, H2, OSR, fB, ftest, Fs);
Simulink_Spectrum_LTE(LTE_DAC_OUT3, N, H3, OSR, fB, ftest, Fs);
Simulink_Spectrum_LTE(LTE_DAC_OUT4, N, H4, OSR, fB, ftest, Fs);

%% System Generator simulation
% Simulink_Spectrum(LTE_DAC_OUT5, N, H1, OSR, fB, ftest, Fs);
% Simulink_Spectrum(LTE_DAC_OUT6, N, H2, OSR, fB, ftest, Fs);
% Simulink_Spectrum(LTE_DAC_OUT7, N, H3, OSR, fB, ftest, Fs);
% Simulink_Spectrum(LTE_DAC_OUT8, N, H4, OSR, fB, ftest, Fs);

%% JTAG simulation
% Simulink_Spectrum(LTE_DAC_OUT9, N, H1, OSR, fB, ftest, Fs);
% Simulink_Spectrum(LTE_DAC_OUT10, N, H2, OSR, fB, ftest, Fs);
% Simulink_Spectrum(LTE_DAC_OUT11, N, H3, OSR, fB, ftest, Fs);
% Simulink_Spectrum(LTE_DAC_OUT12, N, H4, OSR, fB, ftest, Fs);

%% Modelsim Simulation

%% Comparing Signals
% xcorr(LTE_DAC_OUT1,LTE_DAC_OUT5,0,'coeff')
% xcorr(LTE_DAC_OUT2,LTE_DAC_OUT6,0,'coeff')
% xcorr(LTE_DAC_OUT3,LTE_DAC_OUT7,0,'coeff')
% xcorr(LTE_DAC_OUT4,LTE_DAC_OUT8,0,'coeff')
% xcorr(LTE_DAC_OUT5,LTE_DAC_OUT9,0,'coeff') 
% xcorr(LTE_DAC_OUT6,LTE_DAC_OUT10,0,'coeff')   
% xcorr(LTE_DAC_OUT7,LTE_DAC_OUT11,0,'coeff') 
% xcorr(LTE_DAC_OUT8,LTE_DAC_OUT12,0,'coeff') 