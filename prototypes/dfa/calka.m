function [ x, y ] = calka(s)

%s - sygna�
%x, y - wsp�rz�dne wyj�ciowe
  z = mean(s);
  y = cumsum(s-z);
  x = cumsum(s);
end


