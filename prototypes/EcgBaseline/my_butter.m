clc; clear; close all;

%%
addpath('./ekg_zasoby');

load('100_V5.dat');
s = X100_V5;
subplot(2, 1, 1);
plot(s(1:1000), 'r')
title('Sygnal z linia izoelektryczna')

% tworzenie wspó³czynników A(z) i B(Z)
% filtr Butterworth, 2 rzêdowy, górnoprzepostowy

fc = 0.5; % czêstotliwoœæ odciêcia
fs = 360;   % czêstotliwoœæ próbkowania
Wn = (fc/fs)/2; % czêstotliwoœæ odciêcia znormalizowana
n = 2;      % rz¹d filtru

[b,a] = butter(n, Wn, 'high');  % tworzenie filtra
H       = tf(b,a);              % wyznaczenie transmitancji

%% stworzenie macierzy sos

[sos,g] = tf2sos(b,a);          % tworzenie macierzy


%% filtracja w fazie zerowej

y = filtfilt(sos, g, s);
subplot(2,1,2);
plot(y(1:1000), 'b');
title('sygnal bez linii izoelektrycznej po filtracji butter')

