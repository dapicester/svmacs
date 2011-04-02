function [coeffs, logEnergy] = mfcc(spectrum,numMfcc,wts,numFilters)
% Compute Mel-frequency cepstral coefficients.
% Usually, for N coefficient N+1 values are returned, where the first 
% coefficient is the logEnergy. 
% Here the logEnergy is picked off from the vector.
% Params:
%   wts     Mel filter bank
    
    % compute critical bands energy
    energy = wts * spectrum;
    
    % biasing to avoid log(0)
    energy = energy + 1;
    
    coeffs = zeros(numMfcc + 1,1);
    coeffs = cos([0:numMfcc]' * ...
        ([1:numFilters]-0.5)*(pi/numFilters))*log10(energy);
    
    logEnergy = coeffs(1);
    coeffs = coeffs(2:end);
end

