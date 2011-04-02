function [bframe,nbands] = getBands(frame,fs,bands)
% compute band-passed version of frame

    if (nargin < 3)
        bands = [500 1000; 2000 3000; 1000 2000; 1000 4000];
    end

    nbands = floor((1./bands)*fs);
    
    Nbands = size(bands,1);
    bframe = zeros(Nbands,length(frame));
    order = 10;
    
    for i=1:Nbands,
        h = fdesign.bandpass('N,Fc1,Fc2',order,bands(i,1),bands(i,2),fs);
        Hd = design(h,'butter');
        bframe(i,:) = filter(Hd,frame);
    end    
end