function [ x, M] = share_signal( x1, y1, l )


q = floor(length(x1)/l);
a = 1;
b = l;

for i = 1:q
    M(i, :) = y1(a:b);
    x(i, :) = x1(a:b);
    a = a + l;
    b = b + l;
end

end

