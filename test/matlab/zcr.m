function ret = zcr(frame,fs)
% Compute the Zero Crossing Rate for a given frame

    frame = frame(:);
    sign_frame = sign(frame);
    diff_frame = sign_frame - ...
        [sign_frame(1); sign_frame(1:end-1)];
    ret = numel(diff_frame(diff_frame~=0)) / length(frame) * fs;
end
