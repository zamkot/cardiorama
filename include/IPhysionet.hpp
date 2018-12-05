#pragma once
#include <iostream>
#include <vector>

typedef std::vector<std::vector<int>> CardioSignal;

struct CardioRecordHeader {
    std::string                       recordName;     // Path to record
    std::vector<std::string>          leadsNames;     // Leads names
    int                               nLeads;         // Number of leads in record
    int                               freq;           // Frequency value
    int                               baseline;	      // ADC output given 0 physical units input
    unsigned long                     nSamp;	      // Number of samples (0: unspecified)
    double                            adcGain;        // Units are adus per physical unit
    int                               adcResolution;  // ADC reolution in bits
};

struct CardioChannelHeader {
    std::string                       recordName;     // Path to record
    std::string                       leadName;       // Lead name
    int                               freq;           // Frequency value
    int                               baseline;	      // ADC output given 0 physical units input
    unsigned long                     nSamp;	      // Number of samples (0: unspecified)
    double                            adcGain;        // Units are adus per physical unit
    int                               adcResolution;  // ADC reolution in bits

    CardioChannelHeader(){};
    CardioChannelHeader(CardioRecordHeader header, int channelNumber) :
            recordName(header.recordName),
            leadName(header.leadsNames[channelNumber]),
            freq(header.freq),
            baseline(header.baseline),
            nSamp(header.nSamp),
            adcGain(header.adcGain),
            adcResolution(header.adcResolution)
    {}
};

struct CardioChannel {
    CardioChannelHeader               header;    // Container containing information from header
    std::vector<int>                  signal;    // Vector containing signals samples from one channel
};

struct CardioDataFrame {
    std::vector<CardioChannel>        dataFrame;   // Container containing: nLeads x (header and signal structures)
};

struct CardioRPeaks {
    std::vector<int>                  rPeaks;      // Position of R peaks (samples)
};

struct CardioAnnotaions {
    std::vector<std::string>          annotations;  // Annotations Marks
};

class IPhysionet {
public:
    virtual CardioRecordHeader getHeader() = 0;
    virtual CardioDataFrame getDataFrame() = 0;
    virtual CardioRPeaks getRPeaks() = 0;
    virtual CardioAnnotaions getAnnotations() = 0;
    virtual void readAnnotations() = 0;
};
