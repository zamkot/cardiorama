function [ p] = polyfit_function( x, y )
        
    p = zeros(size(y, 1), 2);
    
    for ii = 1:size(y, 1)
        p(ii,:) = polyfit(x(ii,:), y(ii,:), 1);
    end
    
end

