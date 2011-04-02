function [ret,r] = periodicity(frame,fs)
% compute periodicity over a frame

    band = [500 4000]; % frequencies in Hz
    nband = floor((1./band).*fs); % normalized frequencies
    
    lagLF = floor(nband(1)*1.5);
    lagHF = floor(nband(2)/1.5);
    L = lagLF;
    N = floor(length(frame)/L); % number of lags
    %rp = zeros(1,N);
    
    r = zeros(1,L);
    s = frame(min(1:L,length(frame))); s = s/norm(s);
    %s = frame/norm(frame);
    for k = lagHF:lagLF, % compute correlation
        s_k = frame(min(k:L+k-1,length(frame)));
        s_k = s_k/norm(s_k);
        r(k+1) = sum(s.*s_k);
    end
    plot(r)
    % compute maximum correlatio
    ret = max(r);
end