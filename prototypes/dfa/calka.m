function [ x, y ] = calka(s)

%s - sygna³
%x, y - wspó³rzêdne wyjœciowe
  z = mean(s);
  y = cumsum(s-z);
  x = cumsum(s);
end


