A = xlsread('hovering_results.xlsx', '1', 'E2:F961');
size(A)

B = xlsread('hovering_results.xlsx','1','F2:G961');
size(B)

if (size(A) ~= size(B))
    disp 'array sizes do not match'
    exit;
end;

angle = [];
for count = 1 : size(A) - 1
    p0 = [0 0];
    p1 = [A(count) B(count)];
    p2 = [A(count+1) B(count+1)];
    v1 = p1 - p0;
    v2 = p1 - p2;
    if (norm(v1) == 0 || norm(v2) == 0)
        newangle = 0;
    else
        newangle = acos(dot(v2,v1)/ (norm(v1) * norm(v2)));
    end
    angle = [angle; newangle];
end
size(angle)

angle


%[status, message] = xlswrite('results.xlsx', angle, 'Sheet2', 'I2:I964');

%status 
%message