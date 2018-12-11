clc; clear; close all;
% ECG Baseline Drift Removal Using Discrete Wavelet Transform
% Vega-Martínez G., Alvarado-Serrano C. and Leija-Salas L.
%% Przygotowanie danych
addpath('./ekg_zasoby');

load('100_V5.dat');
x = X100_V5;
fs = 360;

%% Szukanie czêstotliwoœci œrodkowej 

delta = 1/fs;
amax = 10;
a = 2.^[1:amax];  % wektor zawieraj¹cy potêgi 2

F = scal2frq(a,'db4',delta); % wyznacza 

for i = 1: length(a)
    if (F(i) < 1)
        level = i;
        break;
    end
end

%% DWT
y = x(:)'; 
c = []; % wektor, w którym znajduj¹ siê informacje dotycz¹ce detali i ostatniej aproksymacji
l = zeros(1, level+2); %wektor zawieraj¹cy w sobie informacje dotycz¹ce d³ugoœci sygna³ów
l(end) = length(y); % zapisuje informacjê na temat d³ugoœci sygna³u

% l = [l1, l2, ..., ;ln]
% ln - d³ugoœæ sygna³u, l(n-1) - dlugosc sygnalu po pierwszej dekompozycji,
% l(1) - dlugosc sygnalu po n-tej dekompozycji

for i = 1:level
    [y,d] = dwt(y,'db4');
    c = [d c]; % zapisywana informacje o wspó³czynniku detali - detale s¹ zapisywane w 
               % kolejnoœci od ostatniej dekompozycji do pierwszej
    l(end-i) = length(d); % zapisywana dlugosc sygnalu po dekompozycji
end

% Ostatnia dekompozycja sygna³u: 
c = [y c];  %finalny wektor: x wspó³czynników Aproksymacji poziomu level
            % 1-level wspó³czynników detali
l(1) = length(y);

%% Usuniêcie wspó³czynnika detali
% usuniêcie detali ostatniej dekompozycji - zast¹pienie pierwszych l(1)
% elementów wartoœci¹ 0 

c(1:l(1)) = zeros(l(1),1);

%% Transformata odwrotna
% dokonujemy iDWT sygna³u korzystaj¹c z wyznaczonych wczeœniej detali,
% gdzie ostatni wektor detali zosta³ usuniêty (zast¹piony wartoœci¹ 0)
% iDWT wykonujemy level razy

a = c(1:l(1));  % aproksymacja poziomu level

od = l(1)+1; % pocz¹tek wspó³czynników detali dla zadanego poziomu

for i = 1:level
    do = od + l(i+1) - 1; % koniec wspó³czynników detali dla zadanego poziomu
    a = idwt(a, c(od:do), 'db4', l(i+2));
    od = do + 1;

end
s = a; %sygna³ EKG z usuniêt¹ lini¹ izoelektryczn¹ 

figure()
subplot(2, 1, 1)
plot(x(1:1000), 'r')
title('Oryginalny sygna³ EKG')
subplot(2,1,2)
plot(s(1:1000))
title('Sygna³ po usuniêciu linii izoelektrycznej')



