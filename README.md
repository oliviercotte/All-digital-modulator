# All-digital-modulator
All digital lowpass delta-sigma modulator (+ its digital up-converter) tune to fmax = 9 MHz

The top_fpga.vhd contains:
	- A direct-digital-frequency synthesizer
	- A channel filter, Fpass = 9 MHz, Fstop = 10 MHz, Fs = 30.72 MHz
	- Four halfband interpolator (4 x 2 = 16), Fs1 = 61.44 MHz, Fs2 = 122.88 MHz, Fs3 = 245.76 MHz, Fs4 = 491.52 MHz
	- One fourth and eight order lowpass 46 bits (40 fractional), delta-sigma-modulator (OSR = 491.52/30.72 = 16)
	
The sequence of operation is has follow:
	- Execute Model3.m to compute the delta-sigma filter coefficients
	- Execute the Simulink simulation DAC_SIM_HL.slx
	- The nominal spectrum is compute using spectral_estimation.m
	- Compare using simulink_spectrum.m on the output of the Simulink simulation
	
This repository contain a MATLAB model (Model3.m), Simulink model (DAC_SIM_HL.slx) and a Cosimulation model (COSIM.slx).

In order to make things work you will need:
	- Xilinx ISE 14.7
	- Modelsim PE student edition
	- MATLAB R2017b
