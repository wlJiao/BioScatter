function Data_Norm = funcNormDivSeg(Data, n)
Data_len = length(Data);
if(Data_len<n)
    error("Too few data points")
end

Data_Norm = zeros([1,Data_len]);
for i = 1:n
    Data_Norm(floor(1+(i-1)*Data_len/n:floor(i*Data_len/n))) = normalize(Data(floor(1+(i-1)*Data_len/n:floor(i*Data_len/n))),'scale','mad');
    Data_Norm(floor(1+(i-1)*Data_len/n:floor(i*Data_len/n))) = normalize(Data_Norm(floor(1+(i-1)*Data_len/n:floor(i*Data_len/n))),'range');
end

end




