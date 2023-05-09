
function data = funcCutProfile(s,debug)   

    window_wid = 120;
    L_Thresh = 15;
    data_1 = s;
    data_len = length(data_1);
    sub = zeros(data_len-window_wid,1);
    for i = 1:data_len-window_wid
        sub(i,1) = max(data_1(i:i+window_wid)) - min(data_1(i:i+window_wid));
    end
    for sb = 2:data_len-window_wid-window_wid
        if(sub(sb) <= L_Thresh) && (s(sb)<=270)
                sb1 = sb+2;
                break
        end
    end
    for sbb = data_len-window_wid:-1:sb1
         if(sub(sbb) <= L_Thresh) && (s(sbb)<=350)
             sb2 = sbb;
                break
         end
    end
    s1 = smoothdata(s,'movmean',50);
    sb1_new = sb1+floor((length(sb1:sb2)-13000)/2);
    sb2_new = sb2-ceil((length(sb1:sb2)-13000)/2);
    data = s1(sb1_new:sb2_new);

    % for debug
    if debug==1
        figure
        plot(s1)
        hold on
        plot(data)
    end
end