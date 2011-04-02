function ret = hr(frame)
% Compute the harmonic ratio (periodicity) of a signal.
    ret = 0;
    if (numel(find(frame)) == 0) % frame with all zeros
        return;
    end
    R = xcorr(frame,'coeff');
    R = R(floor(end/2):end);
    [maxima,val] = findMaxima(R);
    if (numel(val) == 1) % there is only one peak
        return
    end
    ret = max(val(2:end));
end
