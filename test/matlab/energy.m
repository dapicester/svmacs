function ret = energy(frame,fs)
% Compute the energy of a given frame

    frame = frame(:);
    square = abs(frame).^2;
    
    ret = sum(square) / length(frame) * fs;
end
