clc; clear; close all;
% ECG Baseline Drift Removal Using Discrete Wavelet Transform
% Vega-Mart�nez G., Alvarado-Serrano C. and Leija-Salas L.
%% Przygotowanie danych
addpath('./ekg_zasoby');

load('100_V5.dat');
x = X100_V5;
fs = 360;

%% Szukanie cz�stotliwo�ci �rodkowej 

delta = 1/fs;
amax = 10;
a = 2.^[1:amax];  % wektor zawieraj�cy pot�gi 2

F = scal2frq(a,'db4',delta); % wyznacza 

for i = 1: length(a)
    if (F(i) < 1)
        level = i;
        break;
    end
end

%% DWT
y = x(:)'; 
c = []; % wektor, w kt�rym znajduj� si� informacje dotycz�ce detali i ostatniej aproksymacji
l = zeros(1, level+2); %wektor zawieraj�cy w sobie informacje dotycz�ce d�ugo�ci sygna��w
l(end) = length(y); % zapisuje informacj� na temat d�ugo�ci sygna�u

% l = [l1, l2, ..., ;ln]
% ln - d�ugo�� sygna�u, l(n-1) - dlugosc sygnalu po pierwszej dekompozycji,
% l(1) - dlugosc sygnalu po n-tej dekompozycji

for i = 1:level
    [y,d] = dwt(y,'db4');
    c = [d c]; % zapisywana informacje o wsp�czynniku detali - detale s� zapisywane w 
               % kolejno�ci od ostatniej dekompozycji do pierwszej
    l(end-i) = length(d); % zapisywana dlugosc sygnalu po dekompozycji
end

% Ostatnia dekompozycja sygna�u: 
c = [y c];  %finalny wektor: x wsp�czynnik�w Aproksymacji poziomu level
            % 1-level wsp�czynnik�w detali
l(1) = length(y);

%% Usuni�cie wsp�czynnika detali
% usuni�cie detali ostatniej dekompozycji - zast�pienie pierwszych l(1)
% element�w warto�ci� 0 

c(1:l(1)) = zeros(l(1),1);

%% Transformata odwrotna
% dokonujemy iDWT sygna�u korzystaj�c z wyznaczonych wcze�niej detali,
% gdzie ostatni wektor detali zosta� usuni�ty (zast�piony warto�ci� 0)
% iDWT wykonujemy level razy

a = c(1:l(1));  % aproksymacja poziomu level

od = l(1)+1; % pocz�tek wsp�czynnik�w detali dla zadanego poziomu

for i = 1:level
    do = od + l(i+1) - 1; % koniec wsp�czynnik�w detali dla zadanego poziomu
    a = idwt(a, c(od:do), 'db4', l(i+2));
    od = do + 1;

end
s = a; %sygna� EKG z usuni�t� lini� izoelektryczn� 

figure()
subplot(2, 1, 1)
plot(x(1:1000), 'r')
title('Oryginalny sygna� EKG')
subplot(2,1,2)
plot(s(1:1000))
title('Sygna� po usuni�ciu linii izoelektrycznej')



