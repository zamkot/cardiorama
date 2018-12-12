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
    explicit Physionet(std::string recordName);
    void readFile(const std::string& file_name) {}; // Trzeba wczytać jakoś te pliki

    CardioRecordHeader getHeader() override;
    CardioDataFrame getDataFrame() override;
    CardioRPeaks getRPeaks() override;
    CardioAnnotaions getAnnotations() override;

    ~Physionet();
};