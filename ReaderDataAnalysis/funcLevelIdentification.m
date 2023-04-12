
function data = funcLevelIdentification(x,type)
    % type=1 UA; type=2 AA; type=3 Na;
    if type ~=1 && type ~= 2 && type~=3
        disp('Wrong type.')
        return
    end
    if type == 1 || type==2
        if (x<-5)||(x>50)
            data = -1;
        end
        if (x>=-5)&&(x<=12)
            data = 1;
        end
        if (x>12)&&(x<20)
            data = 2;
        end
        if (x>=20)&&(x<28)
            data =3;
        end
        if (x>=28)&&(x<=32)
            data = 4;
        end
        if (x>32)&&(x<=44)
            data = 5;
        end
        if x>44
            data = -1;
        end
    end
    if type == 3
        if (x<-5)||(x>110)
            data = -1;
        end
        if (x>=-5)&&(x<=20)
            data = 1;
        end
        if (x>20)&&(x<40)
            data = 2;
        end
        if (x>=40)&&(x<60)
            data =3;
        end
        if (x>=60)&&(x<=85)
            data = 4;
        end
        if (x>85)&&(x<=105)
            data = 5;
        end
        if x>105
            data = -1;
        end
    end
end