#include <iostream>
#include <cstdio>
#include <wfdb.h>

#include <IOModule.hpp>

/* VERSION: ALPHA
 * allows to read signal's samples and information such as fs, adc gain etc. -> (most wanted usability)
 * also allows to read annotations made by Physionet team
 * TODO: (version 1.0)
 * specific header for every channel
 * annotaions translator from subtypes to types (we need only 3 'main' types of annotations -> N, V, SV)
 * some other cool features!
 * */

// ------------------------ PRIVATE:

char* Physionet::convertRecordName(std::string recordName) {
    auto* newName = new char[recordName.size() + 1];
    std::move(recordName.begin(), recordName.end(), newName);
    newName[recordName.size()] = '\0';
    return newName;
}

void Physionet::setRecord(std::string recordName) {
    mRecordPath = convertRecordName(recordName);
};

void Physionet::setHeader() {
    auto nLeads = isigopen(mRecordPath, nullptr, 0);             // Get nLeads information

    WFDB_Siginfo *s;
    s = (WFDB_Siginfo *) malloc(nLeads * sizeof(WFDB_Siginfo)); // Prepare signal's info structure
    isigopen(mRecordPath, s, nLeads);                            // Unpack signal info to structure s

    mHeader.nLeads        = nLeads;
    mHeader.baseline      = s->baseline;
    mHeader.adcGain       = s->gain;
    mHeader.adcResolution = s->adcres;
    mHeader.recordName    = mRecordPath;
    mHeader.nSamp         = (unsigned long) s->nsamp;
    mHeader.freq          = (int) sampfreq(mRecordPath);

    for(int i = 0; i < nLeads; i++){
        mHeader.leadsNames.emplace_back(s[i].desc);
    }
};

CardioSignal Physionet::readSamples() {
    CardioSignal signal(mHeader.nLeads, std::vector<int>(mHeader.nSamp));

    WFDB_Sample *v;
    v = (WFDB_Sample *) malloc(mHeader.nLeads * sizeof(WFDB_Sample));
    for (int i = 0; i < mHeader.nSamp; i++) {
        if (getvec(v) < 0) {
            break;
        }
        for (int j = 0; j < mHeader.nLeads; j++) {
            signal[j][i] = v[j];
        }
    }
    return signal;
};

void Physionet::notReadedAnnotationHandling() {
    std::cout<<"Method readAnnotations() not called before. Reading annotations..."<<std::endl;
    readAnnotations();
}
// ------------------------ PUBLIC:

Physionet::Physionet(std::string recordName) {
    setRecord(recordName);
    setHeader();
};

void Physionet::readAnnotations() {

    WFDB_Anninfo an;
    WFDB_Annotation annot;

    an.name = convertRecordName("atr");
    an.stat = WFDB_READ;

    if (annopen(mRecordPath, &an, 1) < 0) exit(2);

    while (getann(0, &annot) == 0) {
        mRPeaks.rPeaks.emplace_back(annot.time);
        mAnnotations.annotations.emplace_back(std::string(annstr(annot.anntyp)));    // :(
    }

    annotationsReadedFlag = true;
};

CardioRecordHeader Physionet::getHeader() {
    return mHeader;
}

CardioDataFrame Physionet::getDataFrame() {
    CardioDataFrame dataFrame;
    CardioSignal signal(mHeader.nLeads, std::vector<int>(mHeader.nSamp));
    signal = readSamples();

    for(int i = 0; i <mHeader.nLeads; i++) {
        CardioChannel channel;
        channel.header = mHeader;
        channel.signal = signal[i];
        dataFrame.dataFrame.emplace_back(channel);
    }
    return dataFrame;
};


CardioRPeaks Physionet::getRPeaks() {
    if(!annotationsReadedFlag)
        notReadedAnnotationHandling();  // nie wiem czy taki handling jest okej
    return mRPeaks;
};

CardioAnnotaions Physionet::getAnnotations() {
    if(!annotationsReadedFlag)
        notReadedAnnotationHandling();
    return mAnnotations;
};

Physionet::~Physionet() {
    //TODO: uzupełnić destruktor
};