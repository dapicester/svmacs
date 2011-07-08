clc;
clear all;
fprintf('loading ...\n');
itload('signal.it');

wts = generateMelFilters(nfft-1,sampleRate,24);
wts = wts(:,1:nfft/2);

fprintf('signal ...\n');
featuresSignal = zeros(1,12);
featuresSignal(1) = zcr(signal, sampleRate);
featuresSignal(2) = energy(signal, sampleRate);
[featuresSignal(3), featuresSignal(4)] = ass(signalSpectrum);
featuresSignal(5) = srf(signalSpectrum);
featuresSignal(6) = hr(signal);
featuresSignal(7:end) = mfcc(signalSpectrum, 6, wts, 24);

fprintf('silence ...\n');
featuresSilence = zeros(1,12);
featuresSilence(1) = zcr(silence, sampleRate);
featuresSilence(2) = energy(silence, sampleRate);
[featuresSilence(3), featuresSilence(4)] = ass(silenceSpectrum);
featuresSilence(5) = srf(silenceSpectrum);
featuresSilence(6) = hr(silence);
featuresSilence(7:end) = mfcc(silenceSpectrum, 6, wts, 24);

fprintf('saving...\n');
itsave('matlab.it', featuresSignal, featuresSilence, wts);

fprintf('DONE.\n\n');
