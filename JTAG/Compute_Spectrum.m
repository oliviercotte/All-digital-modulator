% %% Simulink simulation
% % Simulink_Spectrum(DSM_MASH_SIM3, N, H, OSR, fB, ftest, Fs);
% % Simulink_Spectrum(DSM_MOD8_SIM1, N, H, OSR, fB, ftest, Fs);
% % Simulink_Spectrum(DAC_OUT, N, H1, OSR, fB, ftest, Fs);
Simulink_Spectrum(DAC_OUT1, N, H1, OSR, fB, ftest, Fs);
Simulink_Spectrum(DAC_OUT2, N, H2, OSR, fB, ftest, Fs);
Simulink_Spectrum(DAC_OUT3, N, H3, OSR, fB, ftest, Fs);
Simulink_Spectrum(DAC_OUT4, N, H4, OSR, fB, ftest, Fs);

%% System Generator simulation
Simulink_Spectrum(DAC_OUT5, N, H1, OSR, fB, ftest, Fs);
Simulink_Spectrum(DAC_OUT6, N, H2, OSR, fB, ftest, Fs);
Simulink_Spectrum(DAC_OUT7, N, H3, OSR, fB, ftest, Fs);
Simulink_Spectrum(DAC_OUT8, N, H4, OSR, fB, ftest, Fs);

%% JTAG simulation
Simulink_Spectrum(DAC_OUT9, N, H1, OSR, fB, ftest, Fs);
Simulink_Spectrum(DAC_OUT10, N, H2, OSR, fB, ftest, Fs);
Simulink_Spectrum(DAC_OUT11, N, H3, OSR, fB, ftest, Fs);
Simulink_Spectrum(DAC_OUT12, N, H4, OSR, fB, ftest, Fs);

% Modelsim Simulation
% Simulink_Spectrum(DAC_OUT15, N, H1, OSR, fB, ftest, Fs);
% Simulink_Spectrum(DAC_OUT16, N, H2, OSR, fB, ftest, Fs);
% Simulink_Spectrum(DAC_OUT17, N, H3, OSR, fB, ftest, Fs);
% Simulink_Spectrum(DAC_OUT18, N, H4, OSR, fB, ftest, Fs);
% Simulink_Spectrum(DAC_OUT19, N, H3, OSR, fB, ftest, Fs);
% Simulink_Spectrum(DAC_OUT20, N, H4, OSR, fB, ftest, Fs);

Compute_Tone_Spectrum(DAC_OUT15);
Compute_Tone_Spectrum(DAC_OUT16);
Compute_Tone_Spectrum(DAC_OUT17);
Compute_Tone_Spectrum(DAC_OUT18);
Compute_Tone_Spectrum(DAC_OUT19);
Compute_Tone_Spectrum(DAC_OUT20);

% Comparing Signals
xcorr(DAC_OUT1,DAC_OUT5,0,'coeff')
xcorr(DAC_OUT2,DAC_OUT6,0,'coeff')
xcorr(DAC_OUT3,DAC_OUT7,0,'coeff')
xcorr(DAC_OUT4,DAC_OUT8,0,'coeff')
xcorr(DAC_OUT5,DAC_OUT9,0,'coeff') 
xcorr(DAC_OUT6,DAC_OUT10,0,'coeff')   
xcorr(DAC_OUT7,DAC_OUT11,0,'coeff') 
xcorr(DAC_OUT8,DAC_OUT12,0,'coeff')