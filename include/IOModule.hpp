#pragma once
#include <IPhysionet.hpp>

class Physionet : public IPhysionet {
private:
    char* mRecordPath;   // tego wymaga biblioteka wfdb :(
    CardioRecordHeader mHeader;
    CardioRPeaks mRPeaks;
    CardioAnnotaions mAnnotations;

    bool annotationsCached = false;
    char* convertRecordName(std::string recordName);    // :(
    void setRecord(std::string recordName);
    void setHeader();
    void readAnnotations() override ;
    CardioSignal readSamples();

public:
    Physionet(std::string recordName);
    CardioRecordHeader getHeader() override;
    CardioDataFrame getDataFrame() override;
    CardioRPeaks getRPeaks() override;
    CardioAnnotaions getAnnotations() override;

    ~Physionet();
};