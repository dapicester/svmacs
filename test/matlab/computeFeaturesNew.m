function features = computeFeaturesNew(sound, fs, blocking)
% Extract a feature array for the given sound.
% Args:
%   sound       the waveform,
%   fs          sample rate
%   blocking   if true, use three trunks in ratio 3:4:3
% Returns:
%   the feature vector

    if (nargin < 3)
        blocking = false; 
    end
    
    %% window signal
    L = length(sound);
    M = floor(0.025 * fs);          % window length
    R = floor(M/2);                 % hop size
    win = hamming(M);   
    Nframes = floor( (L-R)/(M-R) );	% number of frames
    
    % pad signal
    sound = [sound; flipud(sound(end-R:end))];
       
    N_MFCC = 6;
    N_FEAT = 5 + N_MFCC + 1;
    temp = zeros(Nframes,N_FEAT);
    
    Nfft = 1024;
    numFilters = 24;

    % compute mel filters
    wts = generateMelFilters(Nfft-1,fs,numFilters);
    wts = wts(:,1:Nfft/2);
    
    i = 1;
    for j = 1:R:L-M,
        frame = sound(j:j+M-1) .* win;
        spectrum = fft(frame,Nfft);
        spectrum = spectrum(1:Nfft/2);
          
        % extract features
        temp(i,1) = zcr(frame,fs);
        temp(i,2) = energy(frame,fs);
        
        [ss,cc] = ass(spectrum);
        temp(i,3) = ss;
        temp(i,4) = cc;
        clear('ss','cc')
        
        temp(i,5) = srf(spectrum);
        temp(i,6) = hr(frame);
        temp(i,7:end) = mfcc(abs(spectrum),N_MFCC,wts,numFilters);
            
        i = i + 1;
    end
    
    %% data reduction 
    reduced = [];
    if (blocking)
        reduced = zeros(3,N_FEAT);
        for k = 1:N_FEAT,
            reduced(:,k) = reduceData(temp(:,k));
        end
    else % mean
        reduced = zeros(1,N_FEAT); 
        for k = 1:N_FEAT,
            reduced(:,k) = mean(temp(:,k));
        end
    end
    
    features = reduced(:);    
end
