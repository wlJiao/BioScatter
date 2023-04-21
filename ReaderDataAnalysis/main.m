clear; clc; close all;
%% Preprocessing parameter settings
RawFs = 5e6;  % Original sampling frequency
RawT = 1/RawFs;    % Original sampling period
Fs = 1e6;  % Resample raw data with Fs
T = 1/Fs; %New sampling period
%% Raw samples -- IQ Data read in，Fs(MHz)
% - data format：float32，One number occupies 4 bytes
% - A complex number has two numbers
tmp_dir = dir('*');
tmp_gsfilename = [];
for i = 3:length(tmp_dir)
    tmp_gsfilename = [tmp_gsfilename,string(tmp_dir(i).name)];
end
typestr = "UA"; % three options - UA, AA, Na
gsFilename = regexp(tmp_gsfilename, strcat(typestr,"\S*$"), 'match','once');
gsFilename = rmmissing(gsFilename); 
gsFilename = gsFilename.';
 % Signal: The signal after ABS, with the first line being the name, 
 % the second line being the time, and the third line being the data
s_Data = cell(3,length(gsFilename)); 
for i = 1:length(gsFilename)
    s_Data{3,i} = funcReadIQDataInParProcessing(gsFilename(i),[0, 1], RawFs, Fs, 800, 20);   % data
    s_Data{1,i} = gsFilename(i);  % name
    s_Data{2,i} = (0:length(s_Data{3,i})-1)*T;  % time
end
%%%%% sensing substance type %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
switch typestr
    case "UA"
        type=1;
    case "AA"
        type=2;
    case "Na"
        type=3;
end
if type ~=1 && type ~= 2 && type~=3
    disp('Wrong type.')
    return
end
%% IQ Normalization + Demodulate
if type==1 || type==2
    for k = 1:length(gsFilename)
        clear s_Data_Norm flag_cal data1
        flag_cal = 1; 
        % normalization
        s_Data_Norm = funcNormDivSeg(abs(s_Data{3,k}), 500000);
        data = s_Data_Norm;
        % demodulate and extract the DC profile
        data_return =  callDemodulateFunc(data,flag_cal);
        % extract IV profile
        data1 = funcCutProfile(data_return,0);
        % determine the direction of the IV curve; if it is reverse then flip
        % its direction
        [B,I] = sort(data1);
        index = find(I == round(length(data1)/2));
        percent = index/size(data1,2);
        if percent < 0.5
            flag_cal = 0;
            data_return = callDemodulateFunc(data,flag_cal);
        end
        % save demodulated IV profile
        s{1,k} = data_return;
        x = (0.8/length(data_return)):(0.8/length(data_return)):0.8;
        figure('color','w')
        plot(data_return); xlabel('Voltage (V)'); ylabel('Current (uA)');
        title(num2str(k))
        % save filename
        s{2,k} = s_Data{1,k};
    end
end
%% IV profile Extraction & Concentration Estimation
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% The fitted relationship between demodulated peak value and concentraiton
% Power = p1*concentration+p2;
%%%%%%%%% UA %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
if type == 1
    p1 =      0.2045;
    p2 =         274;
end
%%%%%%%%% AA %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
if type == 2
    p1 =      0.2302;
    p2 =       270.6;
end
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
for k = 1:length(gsFilename)
    data(:,k) = funcCutProfile(s{1,h},0);
    ind = 4601:4800;
    current_profile = data(ind,k);    
    current_mean(k) = mean(current_profile);
    estimated_concentration(k) = (current_mean-p2)/p1;
end
%% Concentration Level Identification
clc;
% for test; type = 1;
% estimated_concentration = [-10 1 10 15 20 25 30 35 40 45 50];
for k = 1:length(estimated_concentration)
    level(k) = funcLevelIdentification(estimated_concentration(k),type);
    % display result
    switch level(k)
        case -1
            disp('Invalid measurement')
        case 1
            disp('L1')
        case 2
            disp('L2')
        case 3
            disp('L3')        
        case 4
            disp('L4')   
        case 5
            disp('L5')     
    end
end