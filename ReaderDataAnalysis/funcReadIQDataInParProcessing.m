function IQData = funcReadIQDataInParProcessing(sFileName, gnReadRange, nRawFs, nFs, nDivCount, nMaxCoreCount)
%% Parameters and return values
% - sFileName：file name
% - gnReadRange：Read Range，[a, b]Represents reading the part between files a and b，
% and 0<=a<b<=1。such as [0.1, 0.9]  it means reading a portion between 10% and 90%
% - nRawFs：The original frequency of the signal in sFileName
% - nFs：New sampling frequency
% - nDivCount：Divide the file into nDivCount shares, and the partition score is positively correlated with parallel processing ability. 
% But too many shards, or shards greater than the number of computer CPU cores, may lead to performance degradation
% - nMaxCoreCount：When the number of cores called to the computer is greater than the actual number of cores, 
% it will be set to the actual number of cores
% - IQData：Returns the read IQ signal, and returns the number 0 if the read fails
%% code
    % Input legal judgment
    if gnReadRange(1) < 0 || gnReadRange(1) > 1 || gnReadRange(2) < 0 || gnReadRange(2) > 1
        IQData = 0;
        return;
    end

    % Calculate file size
    pFile = fopen(sFileName, "r");
    fseek(pFile,0,'eof'); 
    nFileSize = ftell(pFile);
    fclose(pFile);
    
    % Parameter initialization
    nFileSkipDistance = nRawFs/nFs; % The distance skipped after reading one complete complex number at a time (how many complex numbers are skipped)
    IQ = cell(1, nDivCount);  % In order to separate the IQ data during parallel processing, cells are used to load data from different parts during calculation
    nStartLocation = nFileSize*gnReadRange(1);
    nEndLocation = nFileSize*gnReadRange(2);
    nStartLocation = nStartLocation - rem(nStartLocation, 8);  % Start reading position
    nEndLocation = nEndLocation - rem(nEndLocation, 8);  % Read cutoff position
    nReadSize = nEndLocation - nStartLocation;  % Read in size
    
    parfor (i = 1:nDivCount, nMaxCoreCount)  % Parallel for
        pFile = fopen(sFileName, "r");
        fseek(pFile, (i-1)*4*2*floor(nReadSize/(nDivCount*4*2))+nStartLocation, "bof"); %Multiplying by 4 is because float32 is 4 bytes, and multiplying by 2 is because the real and imaginary parts each have one float32
        while ftell(pFile) < i*4*2*floor(nReadSize/(nDivCount*4*2))+nStartLocation
            IQ{1,i} = [IQ{1,i} complex(fread (pFile, 1, 'float32'), fread (pFile, 1, 'float32'))];
            fseek(pFile, nFileSkipDistance*4*2, "cof");
        end
        fclose(pFile);
    end
    
    IQData = cell2mat(IQ);
end