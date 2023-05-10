function data_return = funcDemodulate(data_cal,flag_call)
%%%%demodulate the PWM signal and extract the DC power%%%%%%%%%%%%%%%%%%%%%
    data_call = data_cal;
    if(flag_call == 1)
            for i = 1:length(data_call)
            if data_call(i) <= 0.5
                data_call(i) = 0;
            else
                data_call(i) = 1;
            end
        
            end
    end
    if(flag_call == 0)
        for i = 1:length(data_call)
            if data_call(i) > 0.5
                data_call(i) = 0;
            else
                data_call(i) = 1;
            end
        end
    end
        temp = abs(spectrogram(data_call, 1000, 1, 1000, 1e6, 'yaxis'));
        data_return = temp(1,:);
end

