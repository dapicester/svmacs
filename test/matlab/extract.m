printf("loading ...\n");
itload("signal.it");

printf("signal ...\n");
featuresSignal = zeros(1,5);
featuresSignal(1) = zcr(signal, sampleRate);
featuresSignal(2) = energy(signal, sampleRate);
[featuresSignal(3), featuresSignal(4)] = ass(signalSpectrum);
featuresSignal(5) = srf(signalSpectrum);

printf("silence ...\n");
featuresSilence = zeros(1,5);
featuresSilence(1) = zcr(silence, sampleRate);
featuresSilence(2) = energy(silence, sampleRate);
[featuresSilence(3), featuresSilence(4)] = ass(silenceSpectrum);
featuresSilence(5) = srf(silenceSpectrum);

printf("saving...\n");
itsave("matlab.it", [featuresSignal], [featuresSilence]);

printf("DONE.\n\n");
