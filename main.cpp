#include <iostream>
#include <string>
#include <vector>
#include <filesystem>
#include <sstream>
#include <fstream>

namespace fs = std::filesystem;
using namespace std;

void printProcs(string pid){
    const string path = "/proc/"+pid+"/stat";
    int size = filesystem::file_size(path);
    string content(size, '\0');

    ifstream in(path, ios::binary);
    in.read(content.data(), size);
    cout<< content << endl;
}

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
        printProcs(pid);
    }
}

int main() {
    listProcess();
    return 0;
}
