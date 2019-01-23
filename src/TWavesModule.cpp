#include<iostream> 
#include<cmath> 
#include<vector> 
#include<algorithm> 
#include<TWavesModule.hpp> 

TWavesModule::TWavesModule(EcgBaselineModuleBase& ecgBaselineModule, WavesModuleBase& wavesModule) :
    
    ecgBaselineModule{ ecgBaselineModule }, wavesModule{ wavesModule } {
        
        ecgBaselineModule.attach(this);
        wavesModule.attach(this);

    }
    
    
    void TWavesModule::runTWaves() {

	    auto ecgData = ecgBaselineModule.getResults();
	    auto wavesData = wavesModule.getResults();
	    
		auto T = wavesData.T_wektor;
        auto ecg = ecgData.samples;
	    
        //std::cout << "ecg.size() " << ecg.size() << "\n";

        //std::cout << "T.size() " << T.size() << "\n";

        int tlength = T.size();

        double tVal[tlength];
		int tPos[tlength];


    	for (int ti=0; ti<tlength; ti++){
            tPos[ti] = T[ti];
            tVal[ti] = ecg[tPos[ti]];
        }

        double fc = 360; // :(

		// Iterators and parameters
	    int beats = 16;     		// amount of Tpeaks analysed at a time 
	    double maxTWaves=0;    		// maximum value of detected TWaves (0 for no TWaves detected)
	    std::vector<int> resPos; 	// positions of T-waves containing TWaves (relative to ecg)
	    
	    
	    // ECG window analysing
	    int tValLength = sizeof(tVal)/sizeof(*tVal);
	    int limit = std::floor(tValLength/beats);
	    int iBegin, iEnd, t, ki, z, i=0;
	    double TWaves;
	    std::vector<double> TWavesve;
			
	  // Heart rate measuring
        double l = tValLength + 0.00001;     	
	    double time=(1.0/fc)*ecg.size(); 
		double HR=60.0*l/time;
        

	    while (i<limit){
            TWavesve.clear();
			
	        iBegin=(i*beats);
	        iEnd=std::min((i+1)*beats, tValLength+1)-1;
        
            for(ki=iBegin+1; ki<=iEnd; ki=ki+2){
	            TWavesve.push_back( tVal[ki]-tVal[ki-1] ); // difference between odd and even T waves
	        }
	
			// TWaves detection
	        z=0;  // amount of zero-crossings
	        for (int k=0; k<TWavesve.size(); k++){
	            if ( TWavesve[k]/(TWavesve[k+1]+0.000000000000001)<0 ){
	                z=z+1;
	            }
	        }

	        if (z<0.4*TWavesve.size() & HR>65 & HR<190){ 	// searching for TWaves
	        	
				    double  minresult = *std::min_element(TWavesve.begin(), TWavesve.end());
				    double  maxresult = *std::max_element(TWavesve.begin(), TWavesve.end());
				    TWaves = 1*  std::max(std::abs(minresult), maxresult);
	        	
				    maxTWaves=std::max(maxTWaves, TWaves);
				
				    for (int r=iBegin; r<=iEnd; r++){
					      resPos.push_back(tPos[r]);
				    }
				
            }
	        else{
	            TWaves=0;
	        }
	        
	        i=i+1;
		}


	    //results = {
	        results.maxTWA = maxTWaves,
	    	results.resultTWA = resPos;
		//};
	
	
	  validateResults();
    
}
    
    
    TWavesData TWavesModule::getResults() {
    
        if (!resultsValid()) {
            runTWaves();
        }

        return results;
    }
    
