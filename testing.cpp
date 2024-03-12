#include <bits/stdc++.h>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <bits/stdc++.h>
#include <unistd.h>

using namespace std;

class statistics{
    public:
    int staticSensorsCount;
    int possibleSoujournLocationsCount;
    bool isPossibleToCover;
    double maxDeadline;
    int numberOfWCVsrequired;
    double distanceTravelledbyWCV;
    double chargingRange;
};

vector<pair<int,int>> generateStaticSensors(int num, int maxX, int maxY){
    // Assumes the num is divisible by either 10 or 50
    if(num%50==0){
        int gap = maxX/10;
        int gap2 = maxY/5;
        int noInsideBox = num/50;
        vector<pair<int,int>> ans;
        for(int i=0;i<maxX;i+=gap){
            for(int j=0;j<maxY;j+=gap2){
                int cnt = noInsideBox;
                while(cnt--){
                    int lb = i;
                    int ub = i+gap;
                    int x = (rand() % (ub - lb + 1)) + lb;
                    lb = j;
                    ub = j+gap2;
                    int y = (rand() % (ub - lb + 1)) + lb;
                    ans.push_back({x,y});
                }
            }
        }
        return ans;
    }
    else{
        int gap = maxX/5;
        int gap2 = maxY/2;
        int noInsideBox = num/10;
        vector<pair<int,int>> ans;
        for(int i=0;i<maxX;i+=gap){
            for(int j=0;j<maxY;j+=gap2){
                int cnt = noInsideBox;
                while(cnt--){
                    int lb = i;
                    int ub = i+gap;
                    int x = (rand() % (ub - lb + 1)) + lb;
                    lb = j;
                    ub = j+gap2;
                    int y = (rand() % (ub - lb + 1)) + lb;
                    ans.push_back({x,y});
                }
            }
        }
        return ans;
    }
    
}

vector<float> staticSensorsCharacteristics(){
    // $b_{i}$ &nbsp; $S.O.C_{i}$ &nbsp; $C_r$ &nbsp; $D_r$
    // battery capacity, `S.O.C` - state of charge, `Cr` - Charging rate of $SS_i$, `Dr` - Discharging rate of $SS_i$.
    float batteryCapacity = (rand()%100) + 1;
    float LO = 0.4, HI = 1.0;
    float stateOfCharge = LO + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(HI-LO)));
    float Cr = (rand()%5) + 1;
    LO = 0.1, HI = 1.5;
    float Dr = LO + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(HI-LO)));
    return vector<float>{batteryCapacity,stateOfCharge,Cr,Dr};

}

void generateInput(int staticSensorsCount, double chargingRange) {
    std::ofstream inputFile(".\\input4.txt");
    if (!inputFile.is_open()) {
        std::cerr << "Error opening input.txt for writing." << std::endl;
        exit(EXIT_FAILURE);
    }
    inputFile << staticSensorsCount << " " << chargingRange << endl;
    vector<pair<int,int>> staticSensorsLocations = generateStaticSensors(staticSensorsCount,100,100);

    for(auto t:staticSensorsLocations){
        vector<float> sensor = staticSensorsCharacteristics();
        inputFile << t.first << " " << t.second << " ";
        for(auto x:sensor) inputFile << x << " ";
        inputFile << "\n";
    }
    inputFile << "150 5 5\n50 50\n";
    inputFile.close();
}

void writeStatistics(vector<statistics> stats, double chargingRange) {
    std::ofstream inputFile(".\\./Statistics/finalstats_v1.txt");
    if (!inputFile.is_open()) {
        std::cerr << "Error opening input.txt for writing." << std::endl;
        exit(EXIT_FAILURE);
    }
    inputFile << stats.size() << " " << chargingRange << endl;
    for(auto t:stats){
        inputFile << fixed << setprecision(6);
        inputFile << t.staticSensorsCount << " ";
        inputFile << t.chargingRange << " ";
        inputFile << t.possibleSoujournLocationsCount << " ";
        inputFile << t.isPossibleToCover << " ";
        inputFile << t.maxDeadline << " ";
        inputFile << t.numberOfWCVsrequired << " ";
        inputFile << t.distanceTravelledbyWCV << " ";
        inputFile << endl;
    }

    inputFile.close();
}
void writeStatisticsForConstantStaticSensors(vector<statistics> stats, int numberOfSensors) {
    std::ofstream inputFile(".\\./Statistics/finalstats_v2.txt");
    if (!inputFile.is_open()) {
        std::cerr << "Error opening input.txt for writing." << std::endl;
        exit(EXIT_FAILURE);
    }
    inputFile << stats.size() << " " << numberOfSensors << endl;
    for(auto t:stats){
        inputFile << fixed << setprecision(6);
        inputFile << t.staticSensorsCount << " ";
        inputFile << t.chargingRange << " ";
        inputFile << t.possibleSoujournLocationsCount << " ";
        inputFile << t.isPossibleToCover << " ";
        inputFile << t.maxDeadline << " ";
        inputFile << t.numberOfWCVsrequired << " ";
        inputFile << t.distanceTravelledbyWCV << " ";
        inputFile << endl;
    }

    inputFile.close();
}


void runCode(const std::string& codeFile, const std::string& outputFile) {
    std::string command = codeFile;
    system(command.c_str());
}


void constantGamma(){
    // vector<int> testCases = {100,300,600,900,1200,1500,1800,2000};
    vector<int> testCases = {30,50,100,200,250,300,350,400,450,500};
    // vector<int> testCases = {30};
    vector<statistics> stats;
    double chargingRange = 5;
    for(auto t:testCases){
        generateInput(t,chargingRange);
        runCode("main", "correctoutput.txt");
        std::ifstream input(".\\./Statistics/stats.txt");
        statistics s1;
        input >> s1.staticSensorsCount;
        input >> s1.chargingRange;
        input >> s1.possibleSoujournLocationsCount;
        input >> s1.isPossibleToCover;
        input >> s1.maxDeadline;
        input >> s1.numberOfWCVsrequired;
        input >> s1.distanceTravelledbyWCV;
        stats.push_back(s1);
    }
    writeStatistics(stats,chargingRange);
}

void generateInputForConstantStaticSensors(double chargingRange, int numberOfSensors,vector<pair<int,int>> staticSensorsLocations ,vector<vector<float>> sensorsCharacteristics) {
    std::ofstream inputFile(".\\input4.txt");
    if (!inputFile.is_open()) {
        std::cerr << "Error opening input.txt for writing." << std::endl;
        exit(EXIT_FAILURE);
    }
    inputFile << numberOfSensors << " " << chargingRange << endl;
    

    for(int i=0;i<numberOfSensors;i++){
        pair<int,int> t = staticSensorsLocations[i];
        vector<float> sensor = sensorsCharacteristics[i];
        inputFile << t.first << " " << t.second << " ";
        for(auto x:sensor) inputFile << x << " ";
        inputFile << "\n";
    }


    inputFile << "100 5 5\n50 50\n";
    inputFile.close();
}


void constantStaticSensors(){
    vector<double> testCases = {5,6,8,10,12,14,16,18,20};
    int numberOfSensors = 100;
    vector<pair<int,int>> staticSensorsLocations = generateStaticSensors(numberOfSensors,100,100);
    vector<vector<float>> sensorsCharacteristics;
    for(auto t:staticSensorsLocations){
        vector<float> sensor = staticSensorsCharacteristics();
        sensorsCharacteristics.push_back(sensor);
    }
    vector<statistics> stats;
    for(auto t:testCases){
        generateInputForConstantStaticSensors(t,numberOfSensors, staticSensorsLocations,sensorsCharacteristics);
        runCode("main", "correctoutput.txt");
        std::ifstream input(".\\./Statistics/stats.txt");
        statistics s1;
        input >> s1.staticSensorsCount;
        input >> s1.chargingRange;
        input >> s1.possibleSoujournLocationsCount;
        input >> s1.isPossibleToCover;
        input >> s1.maxDeadline;
        input >> s1.numberOfWCVsrequired;
        input >> s1.distanceTravelledbyWCV;
        stats.push_back(s1);
    }
    writeStatisticsForConstantStaticSensors(stats,numberOfSensors);

}


int main(){
    srand(time(0)); 
    const char* compileCommand1 = "g++ main.cpp -o main";
    int result1 = system(compileCommand1);

    if (result1 == 0) {
        std::cout << "Compilation successful!" << std::endl;
    } else {
        std::cerr << "Compilation failed." << std::endl;
    }
    
    
    // constantGamma();
    constantStaticSensors();
  
}