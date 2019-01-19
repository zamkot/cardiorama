clc; clear; close all;

%%
addpath('./ekg_zasoby');

load('100_V5.dat');
s = X100_V5;
subplot(2, 1, 1);
plot(s(1:1000), 'r')
title('Sygnal z linia izoelektryczna')

% tworzenie wsp�czynnik�w A(z) i B(Z)
% filtr Butterworth, 2 rz�dowy, g�rnoprzepostowy

fc = 0.5; % cz�stotliwo�� odci�cia
fs = 360;   % cz�stotliwo�� pr�bkowania
Wn = (fc/fs)/2; % cz�stotliwo�� odci�cia znormalizowana
n = 2;      % rz�d filtru

[b,a] = butter(n, Wn, 'high');  % tworzenie filtra
H       = tf(b,a);              % wyznaczenie transmitancji

%% stworzenie macierzy sos

%[sos,g] = tf2sos(b,a);          % tworzenie macierzy


%% filtracja w fazie zerowej

y1 = filter(b, a, s);

for i=0:length(y1)-1
   y2(i+1) = y1(end-i); 
end

 y3 = filter(b,a,y2);

for i=0:length(y3)-1
   y(i+1) = y3(end-i); 
end

subplot(2,1,2);
plot(y(1:1000), 'b');
title('sygnal bez linii izoelektrycznej po filtracji butter')

