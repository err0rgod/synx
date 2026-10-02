#include <iostream>
#include <string>
#include <vector>
#include "ps.cpp"
#include "CLI11.hpp"

using namespace std;

// argc and argv are the ways to pass to pass arguements in the main func, argc is the count of parameters passed in the 
// parameters and char **argv is the char array containing those sub commands where argv[0] = file location and argv[argc-1] = null pointer always to define the end of the subcommnds
int main(int argc, char **argv) {

    // initialises the CLI11 so that we can use the arguements
    CLI::App app{"Synx: Your daily linux driver."};
    
    app.set_version_flag("-V, --version","0.1.0");

    auto* ps = app.add_subcommand("ps", "List Processes");

    CLI11_PARSE(app, argc, argv);

    if(*ps){
        listProcess();
    }
    
    return 0;
}
