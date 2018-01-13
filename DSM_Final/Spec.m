%% Test tone spectrum
% Compute_Tone_Spectrum(u);
% Compute_Tone_Spectrum(u_baseband);
CHANNEL_FILTER_OUT = shiftdim(CHANNEL_FILTER_OUT,2)';
HB1_OUT = shiftdim(HB1_OUT,2)';
HB2_OUT = shiftdim(HB2_OUT,2)';
HB3_OUT = shiftdim(HB3_OUT,2)';
HB4_OUT = shiftdim(HB4_OUT,2)';
Compute_Tone_Spectrum(CHANNEL_FILTER_OUT);
Compute_Tone_Spectrum(HB1_OUT);
Compute_Tone_Spectrum(HB2_OUT);
% Compute_Tone_Spectrum(DAC_OUT20');
Compute_Tone_Spectrum(HB3_OUT);
Compute_Tone_Spectrum(HB4_OUT);
%% 
%% 
