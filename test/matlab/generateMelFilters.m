function wts = generateMelFilters(Nfft,fs,Nfilters)
% Generate mel filters
    freqMin= 0;
    freqMax = floor(fs/2);

    % initializate filter bank
    wts = zeros(Nfilters, Nfft);

    % extract frequency of each fft bin
    fft_freqs = [0:Nfft-1]/Nfft*fs;

    melMin = 2595 * log10(1+freqMin/700);
    melMax = 2595 * log10(1+freqMax/700);
    bin_freqs = 700 * ( 10.^( ...
      (melMin + [0:Nfilters+1] / (Nfilters+1) * (melMax-melMin)) / 2595 ...
      ) - 1 );

    %bins = round(bin_freqs/fs*(Nfft-1));

    for i = 1:Nfilters
        freqs = bin_freqs([0 1 2]+i);
        % lower and upper slopes for all bins
        loslope = (fft_freqs - freqs(1))/(freqs(2) - freqs(1));
        hislope = (freqs(3) - fft_freqs)/(freqs(3) - freqs(2));
        % .. then intersect them with each other and zero
        wts(i,:) = max(0,min(loslope, hislope));
    end

    % Make sure 2nd half of FFT is zero
    wts(:,floor(Nfft/2+1):Nfft) = 0;
end
