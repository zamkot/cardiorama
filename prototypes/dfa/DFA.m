function [m,F] = DFA(sygnal)

tachogram = sygnal(sygnal<2);


%% podzia³ na bloki -> 4<=deltam<=64, wyznaczenie krzywej i wyznaczenie wektora fluktuakcji
K = length(tachogram);
m = 4:2:64;
for i = 1:length(m)
    
    tachogram = tachogram(1:length(tachogram) - mod(length(tachogram), m(i)));
    [x, y] = calka(tachogram);
	[x1, y1] = podzial(x, y, m(i));
    [p] = my_poly( x1, y1 );
    y_p = zeros(size(y1));
    
    for ii = 1:size(y1, 1)
        y_p(ii,:) = polyval(p(ii,:), x1(ii,:));
        
    end 
    y_p = y_p';
    y_p = y_p(:);
    F(i) = sqrt(1/K*sum((y_p-y).^2)); 
end
tachogram3 = 0.001*tachogram;
X(1) =  tachogram3(1);
suma =  X(1);
for j = 2: length(tachogram3)
    for k = 2: j
        X(j) = (suma+ tachogram3(k));
        suma = X(j);
    end
end
end

