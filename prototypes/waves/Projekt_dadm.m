%clear all 
close all

clear Ponset_wektor
clear Pend_wektor
%%
%filtracja sygnalu
%clc; clear; close all;

%%
%addpath('./ekg_zasoby');

load('100_MLII.dat');
s = X100_MLII;


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

plot(y(1:1000));
title('sygnal bez linii izoelektrycznej po filtracji butter')

%%
%dane
sygnal=y;
%load R_wektor;
%load('100_attr.dat');
R_wektor=VarName1;

czestotliwosc=360;

% szukane
%Q_wektor;
%S_wektor;
%ORSonset_wektor;

%Szukanie zalamka Q


okno=0;
	
for i=1: length(R_wektor) 
    Q_wektor(i)=0; %gdyby za³amek Q dla tego R nie zosta³ odnalezionych z jakiœ przyczyn
	okno=0;
    miejsce=0;
		
	while R_wektor(i)-okno>=0 && okno<=100 %okno 100 probek - > do zmiany!
		
			if sygnal(R_wektor(i)-okno) < sygnal(R_wektor(i)-(okno+1)) 
			
				Q_wektor(i)=R_wektor(i)-okno; %wpisanie znalezionej pozycji do tablicy
				break
            end
            miejsce=miejsce+1;
			okno=okno+1; %przesuwanie siê wzd³u¿ okna
    end   
    
    % QRS onset
   
    okno=0;
    while R_wektor(i)-miejsce>=1 && okno/czestotliwosc<=0.04 %okno 100 probek - > do zmiany!
		
			if sygnal(R_wektor(i)-miejsce) > sygnal(R_wektor(i)-(miejsce+1)) && sygnal(R_wektor(i)-miejsce) < 0.2 &&  sygnal(R_wektor(i)-miejsce) > -0.2 
			
				QRSonset_wektor(i)=R_wektor(i)-miejsce; %wpisanie znalezionej pozycji do tablicy
				break
            end
            miejsce=miejsce+1;
			okno=okno+1; %przesuwanie siê wzd³u¿ okna
    end   
    
    
    
       % Pend_wektor;
   
    okno=0;
    while R_wektor(i)-miejsce>=1  && okno/czestotliwosc<=0.1 %okno 100 probek - > do zmiany!
		
			if sygnal(R_wektor(i)-miejsce) < sygnal(R_wektor(i)-(miejsce+1)) && sygnal(R_wektor(i)-miejsce) > 0.5 && okno/czestotliwosc>=0.04 
			
				Pend_wektor(i)=R_wektor(i)-miejsce; %wpisanie znalezionej pozycji do tablicy
				break
            end
            miejsce=miejsce+1;
			okno=okno+1; %przesuwanie siê wzd³u¿ okna
    end  
    
    
         % Ponset_wektor;
   
    okno=0;
    while R_wektor(i)-miejsce>=1  && okno/czestotliwosc<=0.16 %okno 
		
			if sygnal(R_wektor(i)-miejsce) > sygnal(R_wektor(i)-(miejsce+1)) && sygnal(R_wektor(i)-miejsce) < 0.2 &&  sygnal(R_wektor(i)-miejsce) > -0.2 && okno/czestotliwosc>=0.02 
			
				Ponset_wektor(i)=R_wektor(i)-miejsce; %wpisanie znalezionej pozycji do tablicy
				break
            end
            miejsce=miejsce+1;
			okno=okno+1; %przesuwanie siê wzd³u¿ okna
    end  
    
    
    % S_wektor
    
    S_wektor(i)=0; %gdyby za³amek Q dla tego R nie zosta³ odnalezionych z jakiœ przyczyn
		okno=0;
		miejsce=0;
		while R_wektor(i)+okno< length(sygnal) && okno<=100 %okno 100 probek - > do zmiany!
		
			if sygnal(R_wektor(i)+okno) < sygnal(R_wektor(i)+(okno+1))
			
				S_wektor(i)=R_wektor(i)+okno; %wpisanie znalezionej pozycji do tablicy
				break
            end
			okno=okno+1; %przesuwanie siê wzd³u¿ okna
			miejsce=miejsce+1;
        end
    
       
   % Tonset_wektor;
   
    okno=0;
    while  R_wektor(i)+miejsce< length(sygnal)  && okno/czestotliwosc<=0.12 %okno 
		
			if sygnal(R_wektor(i)+miejsce) < sygnal(R_wektor(i)+(miejsce+1)) && sygnal(R_wektor(i)+miejsce) > 0.2  && okno/czestotliwosc>=0.02 
			
				Tonset_wektor(i)=R_wektor(i)+miejsce; %wpisanie znalezionej pozycji do tablicy
				break
            end
            miejsce=miejsce+1;
			okno=okno+1; %przesuwanie siê wzd³u¿ okna
    end  
    
    
       % Tend_wektor;
   

    
    
    
    
    
    
    
    
end



for i=1:4
 hold on   
plot(QRSonset_wektor(i), sygnal(QRSonset_wektor(i)),'*')

end


for i=1:4
 hold on   
plot(Ponset_wektor(i)-9, sygnal(Ponset_wektor(i)-9),'*') %% uwaga oszukane!

end



