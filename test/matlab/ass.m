function [ss,sc] = ass(spectrum)
% Compute the spectral spread (instantaneous bandwidth) for a given spectrum
    spectrum = abs(spectrum(2:end));
    bins = (1:length(spectrum))';
    
    summ = sum(spectrum);
    if (summ==0),   % null spectrum has
        sc = 0;     % null centroid
        ss = 0;     % null spread
    else
        sc = sum(bins.*spectrum)/summ;
        ss = sum(((bins-sc).^2).*spectrum)/summ;
    end
end