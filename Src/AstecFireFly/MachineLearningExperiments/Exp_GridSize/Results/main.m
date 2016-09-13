A = xlsread('gridSize_results.xlsx', '5', 'E1:F974');
size(A)

B = xlsread('gridSize_results.xlsx','5','F1:G974');
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
    if(norm(p1-p0) == 0)
        v1 = [0, 0];
    else
        v1 = (p1 - p0)/norm(p1-p0);
    end
    if(norm(p1-p2) == 0)
        v2 = [0, 0];
    else
        v2 = (p1 - p2)/norm(p1-p2);
    end
    
    newangle = v2 - v1;
    newangle
    angle = [angle; newangle];
end
size(angle)

angle


%[status, message] = xlswrite('results.xlsx', angle, 'Sheet2', 'I2:I964');

%status 
%message