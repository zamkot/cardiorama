#include <iostream>
#include <armadillo>

#include <iostream>
#include <string>
#include <IOModule.hpp>
#define PRINT(x) std::cout<<x<<std::endl


using namespace std;
using namespace arma;

void ioUsageExample() {
    std::string record_name = "/home/xavier/Desktop/repos/cardiorama/data/123"; //set absolute path to record

    Physionet object(record_name);
    CardioRecordHeader header = object.getHeader(); //read header
    PRINT(header.nSamp);
    PRINT(header.nLeads);
    PRINT(header.leadsNames[0]);
    PRINT(header.leadsNames[1]);

    CardioDataFrame dataFrame = object.getDataFrame();  //get main dataFrame struct with signal information and header inside
    for(int i = 0; i < 200; i++) {
        PRINT(dataFrame.dataFrame[1].signal[i]);   //print 200 samples from channel 2
    }

    CardioRPeaks rPeaks = object.getRPeaks();  //get annotations positions marked by Physionet team, use to test ;)
    for(int i = 0; i < 200; i++) {
        PRINT(rPeaks.rPeaks[i]);   //print 200 positions
    }

    CardioAnnotaions annotaions = object.getAnnotations();  //get annotations symbols marked by Physionet team, use to test ;)
    for(int i = 0; i < 200; i++) {
        PRINT(annotaions.annotations[i]);   //print 200 annotations
    }
};

int main() {
    mat A = randu<mat>(4,5);
    mat B = randu<mat>(4,5);

    cout << A*B.t() << endl;

    ioUsageExample();
}