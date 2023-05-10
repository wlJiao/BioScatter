function y=funcBandpassFilter(x,f1,f3,fsl,fsh,rp,rs,Fs)
%Bandpass filtering
%Precautions for use of band-pass filtering: 
% the selection range of the cut-off frequency and sampling rate of the passband or stopband cannot exceed half of the sampling rate
%That is, the values of f1, f3, fs1, fsh are less than Fs/2
%x: Sequences that require bandpass filtering
% f 1: Left boundary of passband
% f 3: Right boundary of passband
% fs1：Attenuation cutoff left boundary
% fsh：Decay cutoff right boundary
%rp：Sideband attenuation DB number setting
%rs：Setting the number of attenuation DB in the cutoff zone
%Fs：Sampling frequency of sequence x
wp1=2*pi*f1/Fs;
wp3=2*pi*f3/Fs;
wsl=2*pi*fsl/Fs;
wsh=2*pi*fsh/Fs;
wp=[wp1 wp3];
ws=[wsl wsh];
% Design of Chebyshev filters；
[n,wn]=cheb1ord(ws/pi,wp/pi,rp,rs);
[bz1,az1]=cheby1(n,rp,wp/pi);
%View the curve of the designed filter
[h,w]=freqz(bz1,az1,256,Fs);
h=20*log10(abs(h));
figure;
plot(w,h);
title('The passband curve of the designed filter');grid on;
y=filter(bz1,az1,x);
end