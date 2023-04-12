
function data = funcCutProfile(s,debug)   

    window_wid = 20;
    L_Thresh = 10;
    H_Thresh = 150;
    data_1 = s;
    data_len = length(data_1);
    sub = zeros(data_len-window_wid,1);
    for i = 1:data_len-window_wid
        sub(i,1) = max(data_1(i:i+window_wid)) - min(data_1(i:i+window_wid));
    end
    for sb = 2:data_len-window_wid-window_wid
        if( sub(sb) <= L_Thresh)
            if( sub(sb + window_wid) <= L_Thresh)
                sb1 = sb;
                break
            end
        end
    end
    for sbb = sb1:data_len-window_wid
         if( sub(sbb) >= H_Thresh)
                sb2 = sbb;
                break
         end
    end
    s1 = smooth(s,50,'moving');
    [m,~] = find(s1(sb1:sb2)==max(s1(sb1:sb2)));
    mid = m;
    if mid >= 13000
        if length(sb1:sb2)>13000
            sb2 = sb2-(length(sb1:sb2)-13000);
            data = s1(sb1:sb2);
        else
            data = s1(sb1:sb2);
        end
    else
        if mid+sb1+6500>length(s1)
            mid = mid-3000;
            data = s1(mid+sb1-6500+1:mid+sb1+6500);
        else
            data = s1(mid+sb1-6500+1:mid+sb1+6500);
        end
    end
    % for debug
    if debug==1
        figure
        plot(s1)
        hold on
        plot(data)
    end
end