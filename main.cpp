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
    // fetch only valuable data 
    /*
        State Table
        R	Running or runnable (on the run queue)
        S	Sleeping in an interruptible wait (most processes)
        D	Uninterruptible sleep (usually disk I/O) — cannot be killed
        Z	Zombie — terminated, waiting for parent to wait()
        T	Stopped by a signal (SIGSTOP/SIGTSTP), or traced
        t	Tracing stop (Linux 2.6.33+)
        I	Idle kernel thread (Linux 4.14+)
        X / x	Dead (should never be seen)
        P	Parked (Linux 3.9+)
        W	Paging (only pre-2.6.0; now means "waking" in old ranges)
        K	Wakekill (2.6.33 – 3.13)
    */
    vector<string> tempStat;
    string bits = "";
    int counter = 3;
    for(auto &it: content){
        if(counter == 0) break;
        if(it == ' '){
            tempStat.push_back(bits);
            bits = "";
            counter--;
        }
        bits += it;
    }
    // tempStat -> 0 = pid 1 = name 2 = state
    int proccessId = stoi(tempStat[0]);
    string procName = tempStat[1];
    string procState = tempStat[2];
    cout << proccessId << " " << procName << " " << procState << endl;

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
