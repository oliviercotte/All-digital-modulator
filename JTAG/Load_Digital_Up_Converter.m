load('channel_filter.mat')
load('hb1.mat')
load('hb2.mat')
load('hb3.mat')
load('hb4.mat')

DUC = dsp.FilterCascade(channel_filter, hb1, hb2, hb3, hb4);
fvtool(DUC);

% t = 0:1/Fs:1-1/Fs;
% stim = 0.5*sin(2*pi*ftest*t); % half-scale sine-wave input
% 
% workingdir = tempname;
% generatehdl(DUC, 'Name', 'hdlduc',...
%                   'TargetLanguage', 'VHDL',...
%                   'TargetDirectory', workingdir, ...
%                   'GenerateHDLTestbench', 'on', ...
%                   'TestBenchUserStimulus', stim, ...
%                   'InputDataType', numerictype(1,46,40));

Num=channel_filter.Numerator;
Num1=hb1.Numerator;
Num2=hb2.Numerator;
Num3=hb3.Numerator;
Num4=hb4.Numerator;