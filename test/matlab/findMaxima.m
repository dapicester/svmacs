function [maxima,values] = findMaxima(x)
% Find the local maxima of a signal.
    x = x(:);
    updown = sign(diff(x));
    flags = [updown(1)<0; diff(updown) <0; updown(end)>0];
    maxima = find(flags);
    values = x(maxima);
end
