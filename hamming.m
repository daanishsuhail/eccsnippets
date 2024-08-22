%---------------
%Creates initial string of n length ~ FALL 2022

prompt = "initial message\n";

message=input(prompt,'s');

parsedMessage=zeros(1,strlength(message),"int16");

for n=1:strlength(message)
    parsedMessage(n)=str2num(message(n));
end

g=sprintf('%d',parsedMessage);
fprintf('\n%s\n', g);

%------------------
%Generates a hamming(7,4) based on the values
syms x;
rVal = solve(x+1==strlength(message),x); %computes the r-value
blocklength=(2.^rVal)-1;

fprintf("Hamming(%d,%d)\n",blocklength,strlength(message));

newHamming=zeros(1,blocklength,"int16");
parityCheck=zeros(1,rVal,"int16");



