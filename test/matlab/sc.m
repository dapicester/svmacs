function ret = sc(spectrum)
% Compute the spectral centroid for a given spectrum
    
    spectrum = spectrum(2:end);
    spectrum = abs(spectrum);
    
    %bins = [1:size(spectrum,1)]';
    bins = [1:length(spectrum)]';
    
    %ret = (spectrum'*[1:nbins]')./(sum(spectrum))';
    if (sum(spectrum)==0),      % null spectrum has
        ret = 0;                % null centroid
    else
        ret = sum(bins.*spectrum)/sum(spectrum);
    end
    
    %plot(spectrum), hold on, stem(ret,max(spectrum),'g'), hold off;
end