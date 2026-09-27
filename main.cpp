#include <iostream>
#include <string>
#include <vector>
#include <filesystem>
#include <sstream>
#include <fstream>
#include <iterator>


namespace fs = std::filesystem;
using namespace std;

void printProcs(string pid){
    const string path = "/proc/"+pid+"/stat";

    ifstream in(path, ios::binary);
    if(!in){
        cout<< "File not Found"<< endl;
    }

    string content(
        (istreambuf_iterator<char>(in)),
        istreambuf_iterator<char>()
    );
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
