
clear; clc; close all
FigInd = 0;

figure('color','w')
pause(2)
load data_UA_tag_AS.mat
type = 1; %UA=1,AA=2
main

load data_AA_tag_AS.mat
type = 2; %UA=1,AA=2
main