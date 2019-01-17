#include <iostream>
#include <vector>

#include <DataFrame.hpp>

std::vector<int> loadData(std::string path) {
    DataFrame df(path);
    //std::cout << df << std::endl;
    std::vector<int> data = df.get<int>("", [](auto s){ return std::stoi(s); });

    return data;
}

std::vector<double> loadData2(std::string path) {
    DataFrame df(path);
    //std::cout << df << std::endl;
    std::vector<double> data = df.get<double>("", [](auto s){ return std::stoi(s); });

    return data;
}


void saveData(std::vector<int> data, std::string path) {
    DataFrame df;
    df.addColumn("Example Output Data", data, [](int number) {       
	return std::to_string(number);
    });

    df.toCsv("output_data.csv");
}

std::vector<int> doCalculations(std::vector<int> R_wektor, std::vector<double> sygnal) {
    std::vector<int> results;
    std::vector<int> Q_wektor;
    //for (auto number : data)
        //results.push_back(number * 2);
	std::cout<<R_wektor.size() <<std::endl;


	    for (int i=0; i<R_wektor.size(); i++)
    {
        int odl;
        //odleglosc miedzy R
        if (i == 0)
        {
            odl = R_wektor [0];
        }
        else 
        {
            odl = R_wektor [i] - R_wektor[i-1];
        }

        int okno = 0; 
        // szukanie wektora Q

        while (R_wektor[i]-okno-1>=0 && okno<= odl*0.1)
        {
            if (sygnal[R_wektor[i]-okno] < sygnal[R_wektor[i]-okno-1])
                {Q_wektor.push_back(R_wektor[i] - okno); break;}
            okno=okno+1;

        }
   }




    return Q_wektor;
}

int main() {
    std::vector<int> inputData1 = loadData("Rpeaks2.csv");
    std::vector<double> inputData2 = loadData2("sygnal2.csv");
    std::vector<int> outputData = doCalculations(inputData1,inputData2);
    saveData(outputData, "output_data.csv");
}
