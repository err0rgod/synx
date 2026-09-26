#include <iostream>
#include <string>
#include <vector>
#include <filesystem>
#include <sstream>


namespace fs = std::filesystem;
using namespace std;


bool validPid(string directory) {
    // check if the directry is a valid pid or not
    stringstream ss(directory);
    int num;
    return (ss >> num) && (ss >> ws).eof();
}
vector<string> parseProc() {
    // open ./proc and read all the directories that are numbers
    string procPath = "/proc";
    vector<string> procs;

    // collect only those directories that are numbers
    for( const auto& entry : fs::directory_iterator(procPath)){
        if(entry.is_directory() && validPid(entry.path().filename().string()) ){
            procs.push_back(entry.path().filename().string());
        }
    }
    return procs;
}

void listProcess() {
    // Function implementation goes here
    vector<string> procs;

    procs = parseProc();
    for(const string &pid : procs){
        cout<< pid<< endl;
    }
}

int main() {
    listProcess();
    return 0;
}
