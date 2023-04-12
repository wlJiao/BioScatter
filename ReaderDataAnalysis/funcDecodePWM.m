function [gnBits,gnGaps,nSNR] = funcDecodePWM(gnSignal, nDivCount, nDurationOf1Bit, nDurationOffset)
%% explain
% variable
% - gnSignal：signal
% - nDivCount：Divide the signal into nDivCount parts，Perform KMeans++on each portion separately 
% (if there are too few partitions, it may result in inaccurate clustering)
% - nDurationOf1Bit：One Bit duration point
% - nDurationOffset：The error/jitter of a Bit duration point, usually taken as 1-10 points
% Return value
% - gnBits：The decoded signal consists of 0 and 1 for successful decoding, and -1 for failed decoding% - gnGaps：信号中每个0、1、-1对应的的持续点数
% - nSNR：The signal-to-noise ratio of the entire signal segment
%   When using clustering to calculate signal-to-noise ratio, ideally, after the clustering algorithm is completed, 
% the scatter plot will only have two points, while in reality, there will be noise, so two clusters will appear.
%   
%   - Then, noise power: the Euclidean distance between the cluster center and all signals in the cluster, and finally calculate the mean. Finally, 
% the average of each cluster is obtained and then averaged, which is the noise of the entire signal. (Intraclass divergence)
%   - Signal power: The Euclidean distance between cluster centers. (Inter class divergence)
%   - Signal to noise ratio: 20 * log10 (signal power/noise power)
%% decipher
gnBits = []; % Data 0, 1 for each level (non ID)gnGaps = [];
gnClusterIdx = [];
nEdge = 1;  % Left pointer
nDivLength = floor(length(gnSignal)/nDivCount);
nSNR = [];

% KMeans++clustering algorithm
for i= 1:nDivCount
    X = gnSignal((i-1)*nDivLength+1:i*nDivLength).';
    % KMeans
    [tmp_ClusterIdx, tmpClusterCenter] = kmeans(X, 2, 'Distance','cityblock',...
    'Replicates', 5);
    gnClusterIdx = [gnClusterIdx, tmp_ClusterIdx-1]; 
    % The cluster to which each point in the original signal belongs in the clustering algorithm is originally 1 and 2, but after subtracting 1, it becomes 0 and 1
    % Each paragraph SNR
    [l_ind,~] = find(tmp_ClusterIdx==1);
    [h_ind,~] = find(tmp_ClusterIdx==2);
    r_l = mean(sqrt((X(l_ind,1)-tmpClusterCenter(1,1)).^2),'all');
    r_h = mean(sqrt((X(h_ind,1)-tmpClusterCenter(2,1)).^2),'all');
    r_noise = (r_l+r_h)/2;
    r_signal = sqrt(sum((tmpClusterCenter(1,:)-tmpClusterCenter(2,:)).^2));
    tmp_snr = 20*log10(r_signal/r_noise);
    nSNR = [nSNR, tmp_snr];
end
% total SNR
nSNR = mean(nSNR);

% decipher
for k = 1:nDivLength*nDivCount
    if k+1 <= nDivLength*nDivCount &&  xor(gnClusterIdx(k),gnClusterIdx(k+1)) == 1  % 发生跳变时记录
        if k-nEdge >= nDurationOf1Bit - nDurationOffset &&  k-nEdge <= nDurationOf1Bit + nDurationOffset 
            gnBits = [gnBits, gnClusterIdx(k)];
        else
            gnBits = [gnBits, -1];
        end
        gnGaps = [gnGaps, k-nEdge+1];
        nEdge = k+1;
    elseif k+1 > nDivLength*nDivCount  % The last point also needs to be judged
        gnBits = [gnBits, -1];
        gnGaps = [gnGaps, k-nEdge+1];
    end
end

end