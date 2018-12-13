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
		
	while R_wektor(i)-okno>=1 && okno<=20 
		
			if sygnal(R_wektor(i)-okno) < sygnal(R_wektor(i)-(okno+1)) 
			
				Q_wektor(i)=R_wektor(i)-okno; %wpisanie znalezionej pozycji do tablicy
				break
            end
            miejsce=miejsce+1;
			okno=okno+1; %przesuwanie siê wzd³u¿ okna
    end   
    
    % QRS onset
   
    okno=0;
    while R_wektor(i)-miejsce>=1 && okno/czestotliwosc<=0.04
		
			if sygnal(R_wektor(i)-miejsce) > sygnal(R_wektor(i)-(miejsce+1)) && sygnal(R_wektor(i)-miejsce) < -0.05 &&  sygnal(R_wektor(i)-miejsce) > -0.1 
			
				QRSonset_wektor(i)=R_wektor(i)-miejsce; %wpisanie znalezionej pozycji do tablicy
				break
            end
            miejsce=miejsce+1;
			okno=okno+1; %przesuwanie siê wzd³u¿ okna
    end   
    
    
    
       % Pend_wektor;
   
    okno=0;
    while R_wektor(i)-miejsce>=1  && okno/czestotliwosc<=0.1 
		
			if sygnal(R_wektor(i)-miejsce) < sygnal(R_wektor(i)-(miejsce+1)) && sygnal(R_wektor(i))>-0.05 && okno/czestotliwosc>=0.04 
			
				Pend_wektor(i)=R_wektor(i)-miejsce; %wpisanie znalezionej pozycji do tablicy
				break
            end
            miejsce=miejsce+1;
			okno=okno+1; %przesuwanie siê wzd³u¿ okna
    end  
    
    
         % Ponset_wektor;
   
    okno=0;
    while R_wektor(i)-miejsce>=1  && okno/czestotliwosc<=0.16 %okno 
		
			if sygnal(R_wektor(i)-miejsce) > sygnal(R_wektor(i)-(miejsce+1)) && sygnal(R_wektor(i)-miejsce) < -0.005 &&  sygnal(R_wektor(i)-miejsce) > -0.15 && okno/czestotliwosc>=0.02 
			
				Ponset_wektor(i)=R_wektor(i)-miejsce; %wpisanie znalezionej pozycji do tablicy
				break
            end
            miejsce=miejsce+1;
			okno=okno+1; %przesuwanie siê wzd³u¿ okna
    end  
    
    
    % S_wektor
    
		okno=3;
		miejsce=0;
		while R_wektor(i)+okno< length(sygnal) && okno<=20
		
			if sygnal(R_wektor(i)+okno) < sygnal(R_wektor(i)+(okno+1))
			
				S_wektor(i)=R_wektor(i)+okno; %wpisanie znalezionej pozycji do tablicy
				break
            end
			okno=okno+1; %przesuwanie siê wzd³u¿ okna
			miejsce=miejsce+1;
        end
    
          % QRS end
   
    okno=0;
    while R_wektor(i)+miejsce< length(sygnal) && okno/czestotliwosc<=0.02
		
			if sygnal(R_wektor(i)+miejsce) < sygnal(R_wektor(i)+(miejsce+1)) && sygnal(R_wektor(i)+miejsce) < -0.05 &&  sygnal(R_wektor(i)+miejsce) > -0.13 
			
				QRSend_wektor(i)=R_wektor(i)+miejsce; %wpisanie znalezionej pozycji do tablicy
				break
            end
            miejsce=miejsce+1;
			okno=okno+1; %przesuwanie siê wzd³u¿ okna
    end   
    
       
   % Tonset_wektor;
   
    okno=0;
    while  R_wektor(i)+miejsce< length(sygnal)  && okno/czestotliwosc<=0.3 %okno 
		
			if sygnal(R_wektor(i)+miejsce) < sygnal(R_wektor(i)+(miejsce+1)) && sygnal(R_wektor(i)+miejsce) > -0.2  && okno/czestotliwosc>=0.23 
			
				Tonset_wektor(i)=R_wektor(i)+miejsce; %wpisanie znalezionej pozycji do tablicy
				break
            end
            miejsce=miejsce+1;
			okno=okno+1; %przesuwanie siê wzd³u¿ okna
    end  
    
    
       % Tend_wektor;
   

    okno=0;
    while  R_wektor(i)+miejsce< length(sygnal)  && okno/czestotliwosc<=0.16 %okno 
		
			if sygnal(R_wektor(i)+miejsce) < sygnal(R_wektor(i)+(miejsce+1)) && sygnal(R_wektor(i)+miejsce) < 0 &&  sygnal(R_wektor(i)+miejsce) > -0.1 && okno/czestotliwosc>=0.12 
			
				Tend_wektor(i)=R_wektor(i)+miejsce; %wpisanie znalezionej pozycji do tablicy
				break
            end
            miejsce=miejsce+1;
			okno=okno+1; %przesuwanie siê wzd³u¿ okna
    end  
    
    
    
    
    
    
    
end

    
    
for i=1:4
 hold on   
plot(Ponset_wektor(i), sygnal(Ponset_wektor(i)),'*')

end





