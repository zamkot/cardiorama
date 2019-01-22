#pragma once
#include <iostream>
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <armadillo>
#include "heartClassBase.hpp"
#include "heartClassModule.hpp"

class Descriptor{
    public:
    Descriptor(std::vector <int>,std::vector<int>,int);
    //Mat<int> cutSignal (std::vector<int>,std::vector<int>,int);
    Mat<int> cutSignalVec;
    
    
};
