#include<iostream> 
#include<cmath> 
#include<vector> 
#include<algorithm> 

TWAModule::TWAModule(EcgBaselineModuleBase& EcgBaselineModule, WavesModuleBase& WavesModule) :
    
    EcgBaselineModule{ EcgBaselineModule }, WavesModule{ WavesModule } {
        
        EcgBaselineModule.attach(this);
        WavesModule.attach(this);

    }
    
    
    void TWAModule::runTWA() {

	  auto ecg = EcgBaselineModule.getResults();
	  auto wavesData = WavesModule.getResults();
	    
		auto Tonset = wavesData.tOnset;
		auto Tend = wavesData.tEnd;
	    
	
	    
		int minlength = std::min(Tonset.size(), Tend.size());
		double tVal[minlength], localMaxVal;
		int tPos[minlength], localMaxPos;
		
	
		// Finding positions and values of T-peaks based on T-onset and T-end from WAVES
	  for (int ti=0; ti<minlength; ti++){
	    	
	      localMaxPos=Tonset[ti];
	    	localMaxVal=std::abs(ecg[localMaxPos]);
	    			
	    	for (int s=Tonset[ti]+1; s<= Tend[ti]; s++){ 
            if (std::abs(ecg[s]>localMaxVal)){
	    			    localMaxPos = s;
	    			    localMaxVal = std::abs(ecg[s]);
	    		  }
	    	}
	 
	    	tPos[ti]= localMaxPos;
	    	tVal[ti]= localMaxVal;
    }
	
		// Iterators and parameters
	  int beats = 16;     		// amount of Tpeaks analysed at a time 
	  double maxTWA=0;    		// maximum value of detected TWA (0 for no TWA detected)
	  std::vector<int> resPos; 	// positions of T-waves containing TWA (relative to ecg)
	    
	    
	  // ECG window analysing
	  int tValLength = sizeof(tVal)/sizeof(*tVal);
	  int limit = std::floor(tValLength/beats);
	  int iBegin, iEnd, t, ki, z, i=0;
	  double twa;
	  std::vector<double> tWave;
				
			
	  // Heart rate measuring     	
	  double time=(1.0/fc)*ecg.size(); 
		double HR=60.0*tValLength/time;
		
	    
	  while (i<limit){
        tWave.clear();
			
	      iBegin=(i*beats);
	      iEnd=std::min((i+1)*beats, tValLength+1)-1;
        
        for(ki=iBegin+1; ki<=iEnd; ki=ki+2){
	          tWave.push_back( tVal[ki]-tVal[ki-1] ); // difference between odd and even T waves
	      }
	
			  // TWA detection
	      z=0;  // amount of zero-crossings
	      for (int k=0; k<tWave.size(); k++){
	          if ( tWave[k]/(tWave[k+1]+0.000000000000001)<0 ){
	              z=z+1;
	          }
	      }
	
	      if (z<0.3*tWave.size() & HR>65 & HR<190){ 	// searching for TWA
	        	
				    double  minresult = *std::min_element(tWave.begin(), tWave.end());
				    double  maxresult = *std::max_element(tWave.begin(), tWave.end());
				    twa = 1000*  std::max(std::abs(minresult), maxresult);
	        	
				    maxTWA=std::max(maxTWA, twa);
				
				    for (int r=iBegin; r<=iEnd; r++){
					      resPos.push_back(tPos[r]);
				    }
				
         }
	       else{
	            twa=0;
	       }
	        
	       i=i+1;
		}


	  results = {
	      results.maxTWA = maxTWA;
	    	results.resultTWA = resPos;
		};
	
	
	  validateResults();
    
}
    
    
    TWAData TWAModule::getResults() {
    
        if (!resultsValid()) {
            runTWA();
        }

        return results;
    }
    
