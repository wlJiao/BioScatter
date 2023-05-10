
function data = funcCutProfile(s,debug)   

    window_wid = 120;
    L_Thresh = 20;
%     H_Thresh = 150;
    data_1 = s;
    data_len = length(data_1);
    sub = zeros(data_len-window_wid,1);
    for i = 1:data_len-window_wid
        sub(i,1) = max(data_1(i:i+window_wid)) - min(data_1(i:i+window_wid));
    end
    for sb = 2:data_len-window_wid-window_wid
        if(sub(sb) <= L_Thresh) && (s(sb)<=260)
%             if( sub(sb + window_wid) <= L_Thresh)
                sb1 = sb+2;
                break
%             end
        end
    end
    for sbb = data_len-window_wid:-1:sb1
         if(sub(sbb) <= L_Thresh) && (s(sbb)<=350)
             sb2 = sbb;
                break
         end
    end
    s1 = smoothdata(s,'movmean',50);
%     if max(s1(sb1:sb2))>300
% %         flag=1
% %         A = max(s1(sb1:sb2));
%         temp = abs(s1(sb1:sb2)-300);
%         [m,~] = find(temp==min(temp));
%         mid = m+sb1;
%     else
% %         flag=0;
%         A = max(s1(sb1:sb2));
%         [~,n] = find(s1(sb1:sb2)==A);
% %         n
%         mid = n+sb1;
%     end
%     if mid >= 13000
% %         indicator = 1
%         if length(sb1:sb2)>13000
%             sb2 = sb2-(length(sb1:sb2)-13000);
%         end
%     end       
%         sb1
%         sb2
%         sb1_new = mid-6500+1
%         sb2_new = mid+6500
    sb1_new = sb1+floor((length(sb1:sb2)-13000)/2);
    sb2_new = sb2-ceil((length(sb1:sb2)-13000)/2);
    data = s1(sb1_new:sb2_new);

%     X = length(sb1_new:sb2_new)

    % for debug
    if debug==1
        figure
        plot(s1)
        hold on
        plot(data)
    end
end