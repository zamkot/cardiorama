function [window,Fluctuation] = DFA(signal)


%% podzia³ na bloki -> 4<=deltam<=64, wyznaczenie krzywej i wyznaczenie wektora fluktuakcji
K = length(tachogram);
window = 4:2:64;
for i = 1:length(window)
    
    tachogram = tachogram(1:length(tachogram) - mod(length(tachogram), window(i)));
    [x, y] = integration(tachogram);
	[x1, y1] = share_signal(x, y, window(i));
    [p] = polyfit_function( x1, y1 );
    y_p = zeros(size(y1));
    
    for ii = 1:size(y1, 1)
        y_p(ii,:) = polyval(p(ii,:), x1(ii,:));
        
    end 
    y_p = y_p';
    y_p = y_p(:);
    Fluctuation(i) = sqrt(1/K*sum((y_p-y).^2)); 
end
end


