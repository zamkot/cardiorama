function [maxTWA, resBegin, resEnd] = TWAfunctionENG(ecg, Tonset, Tend, fc)
    
    % INFO: T-wave alternans (TWA) detection and measurment
    % INPUTS:
    % > ecg         - ecg signal with removed baseline
    % > Tonset      - positions of T-onsets
    % > Tend        - positions of T-ends
    % > fc          - sampling rate of signal
    % OUTPUTS:
    % > maxTWA      - maximum value of detected TWA (0 for no TWA detected)
    % > resBegin    - beging positions of signal containing TWA
    % > resEnd      - end positions of signal containing TWA 
    % DEPENDENCIES:
    % > ECG_BASELINE
    % > WAVES
    % COMMENTS:
    % > Tested on R2018a
    
    %% To be replaced !! with ecg = signal from ECG_BASELINE
    ecg = wavelet_function(ecg);

    %% To be replaced !! with T-peaks counted using T-onset and T-end from WAVES
    [tVal, tPos] = t_finder(ecg);
    
%     for ti=1:min(length(Tonset), length(Tend))
%          [tVal(ti), tPos(ti)] = (max(abs(ecg(Tonset(ti):Tend(ti)))));
%     end

    %% To be replaced !! with proper fc
    fc = 500;

    %% Iterators and helpful parameters
    
    beats = 16;     % amount of Tpeaks analised at a time
    flag=0;         % 0=no TWA; 1=TWA detected
    i=0;            % index of ECG signal
    j=0;            % index of result arrays
    maxTWA=0;       % maximum value of detected TWA (0 for no TWA detected)
    resBegin=0;     % beging positions of signal containing TWA
    resEnd=0;       % end positions of signal containing TWA
    
    %% ECG window analisyng
    
    while i<=floor(length(tVal)/beats)

        iBegin=(i*beats)+1;
        iEnd=min((i+1)*beats, length(tVal));

        % TWA detection
        t=tVal(iBegin:iEnd);
        
        tOdd = t(1:2:end-1);    % division into odd and even T waves
        tEven = t(2:2:end); 

        tWave = tOdd-tEven;     

        z=0;                    % amount of zero-crossings
        for k=1:length(tWave)-1
            if tWave(k)/(tWave(k+1)+eps)<0
                z=z+1;
            end
        end

        % heart rate detection
        R = length(tVal);       
        time=length(ecg)*(1/fc);
        HR=60*R/time;


        if z<0.5*length(tWave) & HR>65 & HR<190 	% searching for TWA
            twa = 1000*max(abs(tWave(3:end-2)));
        else
            twa=0;
        end

        if (twa ~= 0)       % save to results if TWA is found
            flag =1;
            j=j+1;
            resBegin(j)=tPos(iBegin);
            resEnd(j)=tPos(iEnd);           
            maxTWA=max(maxTWA, twa);
        end
        i=i+1;


    end

%% Wisualizising results: can be used in GUI 

% 	if (flag ~=0)
%         figure;
%         plot(ecg);
%         hold on;
%         for y=1:length(resBegin)
%             plot (resBegin(y):resEnd(y), ecg(resBegin(y):resEnd(y)), 'r');
%         end
%         hold off;
% 	end


end

