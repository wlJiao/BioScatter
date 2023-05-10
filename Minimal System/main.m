 
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% color data for plotting
cl = [0.00 0.45 0.74;
      0.85 0.33 0.10;
      0.93 0.69 0.13;
      0.49 0.18 0.56;
      0.47 0.67 0.19;
      0.30 0.75 0.93;];
% plot the demodulated I-V profiles
if type==1
    l=5.6; r=6;
else
    l=5.8; r=6.2;
end
IV_profile = zeros(13000,30);
t = 16/13000:16/13000:16;
lengend_string = {'','','','0umol/L','','','','','8umol/L','','','','','16umol/L',...
    '','','','','24umol/L','','','','','32umol/L','','','','','40umol/L',...
    '','','',''};
FigInd = FigInd+1;
subplot(2,2,FigInd)
axis([0 16 250 300])
set(gca,'FontName','Arial','FontSize',12,'FontWeight','bold')
xlabel('Time (s)'); ylabel('Sensing current (\muA)')
if type==1
    title('I-V profiles of Urea Acid')
else
    title('I-V profiles of Ascorbic Acid')
end
box on
hold on
    plot([8 8],[250 300],':','Color',[0.1 0.1 0.1])
    hold on
    plot([l l],[250 300],':','Color',[0.1 0.1 0.1])
    hold on
    plot([r r],[250 300],':','Color',[0.1 0.1 0.1])
    hold on
for h = 1:30
    temp = funcCutProfile(s{1,h},0); % trim the demodulated I-V profile
    IV_profile(:,h) = temp;
    plot(t,temp,'color',cl(fix((h-1)/5)+1,:),'LineWidth',0.5)
    legend boxoff
    legend(lengend_string{1:h})
    hold on    
    pause(0.7)
end
if type==1
    annotation('textarrow',[0.23 0.25], [0.85 0.8],'String','peak current', ...
               'FontName','Arial', ...
               'FontSize',10, ...
               'Color','black', ...
               'HeadStyle','cback1', ...
               'HeadWidth',5, ...
               'HeadLength',5);
else
    annotation('textarrow',[0.23 0.25], [0.38 0.33],'String','peak current', ...
           'FontName','Arial', ...
           'FontSize',10, ...
           'Color','black', ...
           'HeadStyle','cback1', ...
           'HeadWidth',5, ...
           'HeadLength',5);
end
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
clc
NumofEstimation = 200;
concentration = 0:8:40;
% current       = p1*concentration+p2
% concentration = (current-p2)/p1
if type==1
    p1 =      0.2045;
    p2 =         274;
    ind = 4601:4800; %the location of peak current for UA
end
if type==2
    p1 =      0.2302;
    p2 =       270.6;
    ind = 4501:4700; %the location of peak current for AA
end
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Estimate concentration value
current = zeros(NumofEstimation,6);
for i = 1:6
    temp = IV_profile(ind,(i-1)*5+1:i*5);    
    current(:,i) = mean(temp,2);
end
for i = 1:6
    y = current(:,i);
    est(:,i) = (y-p2)./p1;
end
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% classification
classification = zeros(NumofEstimation,5);
[n,~] = find(est(:,2)<=10);
classification(n,1) = 1;
[n,~] = find(est(:,2)>10);
classification(n,1) = 2;

[m,~] = find(est(:,3)<=10);
classification(m,2) = 1;
[n,~] = find((est(:,3)>10)&(est(:,3)<=20));
classification(n,2) = 2;
[l,~] = find(est(:,3)>20);
classification(l,2) = 3;

[m,~] = find(est(:,4)<=20);
classification(m,3) = 2;
[n,~] = find(est(:,4)>=20&est(:,4)<=28);
classification(n,3) = 3;
[l,~] = find(est(:,4)>28);
classification(l,3) = 4;

[m,~] = find(est(:,5)<=28);
classification(m,4) = 3;
[n,~] = find(est(:,5)>=28&est(:,5)<=36);
classification(n,4) = 4;
[l,~] = find(est(:,5)>36);
classification(l,4) = 5;

[m,~] = find(est(:,6)<=36);
classification(m,5) = 4;
[n,~] = find(est(:,6)>36);
classification(n,5) = 5;
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Count estimation results and obtain the confusion matrix
% Plot the sensing accuracy confusion matrix
clc
confusion_matrix = zeros(5,5);
xldata = {'L1','L2','L3','L4','L5'};
FigInd = FigInd+1;
subplot(2,2,FigInd)
% set(gca,'Position',[0.25 0.25 0.4 0.4])
% hold on
for i = 1:5
    for j = 1:5
        clear m
        [m,~] = find(classification(:,i)==j);
        confusion_matrix(j,i) = length(m)/NumofEstimation;
        heatmap(xldata,xldata,confusion_matrix.*100,'ColorbarVisible','off','FontName','Arial','FontSize',12)
        pause(0.25)
    end
end
xlabel('Actual level'); ylabel('Estimated level')
if type==1
    title('Sensing accuracy of Urea Acid')
else
    title('Sensing accuracy of Ascorbic Acid')
end


