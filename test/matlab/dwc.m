function coeff = dwc(frame,level,N)
% compute Discrete Wavelet Transform
% use the WAVELET TOOLBOX
% level : decomposition level
% N     : how many coefficients

   wvname = 'db8';  % daubechies wavelet with 4 moments
   %level = 7;       % 
   
   coeff = wavedec(frame,level,wvname);
   
   %N = 100;         % we  use the first 100 coefficients
   coeff = coeff(1:N);
end