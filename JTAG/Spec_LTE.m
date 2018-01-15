%% Test tone spectrum
Compute_Tone_Spectrum(u);
Compute_Tone_Spectrum(u_baseband);
LTE_CHANNEL_FILTER_OUT = shiftdim(LTE_CHANNEL_FILTER_OUT,2)';
LTE_HB1_OUT = shiftdim(LTE_HB1_OUT,2)';
LTE_HB2_OUT = shiftdim(LTE_HB2_OUT,2)';
LTE_HB3_OUT = shiftdim(LTE_HB3_OUT,2)';
LTE_HB4_OUT = shiftdim(LTE_HB4_OUT,2)';
Compute_Tone_Spectrum(LTE_CHANNEL_FILTER_OUT);
Compute_Tone_Spectrum(LTE_HB1_OUT);
Compute_Tone_Spectrum(LTE_HB2_OUT);
Compute_Tone_Spectrum(LTE_HB3_OUT);
Compute_Tone_Spectrum(LTE_HB4_OUT);

%% Modelsim Simulation
% Compute_Tone_Spectrum(DAC_OUT15');
% Compute_Tone_Spectrum(DAC_OUT16');
% Compute_Tone_Spectrum(DAC_OUT17');
% Compute_Tone_Spectrum(DAC_OUT18');
% Compute_Tone_Spectrum(DAC_OUT19');
% Compute_Tone_Spectrum(DAC_OUT20');
