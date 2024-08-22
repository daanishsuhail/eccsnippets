%%%%%%%% ENCODER: Uses an encoding matrix to encode a 4 bit message into a
%%%%%%%% 7 long code ~ FALL 2022

A=[0 1 1 0]; %Initial message

B=[1 1 1 0 0 0 0; 1 0 0 1 1 0 0; 0 1 0 1 0 1 0; 1 1 0 1 0 0 1;]; %Encoding matrix
%%%%% 1100110
C=mod(A*B,2); %Applies mod 2 to simulate 'binary adding'

fprintf(1,"Original encoded matrix above\n")
disp(C)
ORIGINALMAT=C
ORIGINALMAT
%%%%%%%% ERROR APPLICATION: Applies noise to the code

finalprob = [];
finaldist = [];

eprob = 0.00; %Designates the error probability

while eprob < 1.00;
X = [];
Y = [];
percent_count = 1;

while percent_count < 11
error_total = 0;
string_pos = 1;
while string_pos < 8
    randomnum = rand;
    randomnum
    if randomnum <= eprob
        if C(1,string_pos) == 1
            C(1,string_pos) = 0;
            fprintf(1,"NEWMATBELOW")
            disp(C)
        else %string_pos == 0
            C(1,string_pos) = 1;
        end
        %C(1,string_pos)=mod(C(1,string_pos)+1,2);
        error_total=error_total+1;
    end
    string_pos=string_pos+1;
end

fprintf(1,"total errors below\n")
disp(error_total)
fprintf(1,"Error matrix below\n")
disp(C)


%%%%%%%% DECODER: Determines the syndrome and corrects a single error

D=[0 0 1; 0 1 0; 0 1 1; 1 0 0; 1 0 1; 1 1 0; 1 1 1;];
SYN=mod(C*D,2);

error_position = SYN(1,1).*4 + SYN(1,2).*2 + SYN(1,3).*1;

if not(error_position == 0)
    C(1,error_position)=mod(C(1,error_position)+1,2);
end
fprintf(1,"Corrected matrix found below.\n")
disp(C)

string_pos=1;
distancefromencoded=0;
while string_pos < 8
    if not(C(1,string_pos)==ORIGINALMAT(1,string_pos))
        distancefromencoded = distancefromencoded + 1;
    end
    string_pos = string_pos + 1;
end

fprintf(1,"Distance from original matrix below.");
disp(distancefromencoded);

X(end+1) = eprob;
Y(end+1) = distancefromencoded;
percent_count = percent_count + 1;
end
finalprob(end+1)=mean(X);
finaldist(end+1)=mean(Y);
finalprob;
finaldist;
X
Y
clear X;
clear Y;
eprob = eprob + 0.01;
end

%%%%%%%% PLOTTER: Plots the points that correspond to error probability and
%%%%%%%% distance from original message.
%X
%Y

%plot(X,Y,'+');
finalprob;
finaldist;
plot(finalprob,finaldist,'+')
