function K = srf(spectrum,alpha)
% Compute the spectral roll-off at alpha/100 for a given spectrum
    
    if (nargin < 2)
        alpha = .93;
    end
    
    L = length(spectrum);
    spectrum = abs(spectrum).^2;
    threshold = alpha*sum(spectrum);
    
    K = 0;
    for k = 1:L,
        if (sum(spectrum(1:k)) < threshold),
            K = k;
            break;
        end
    end
end
