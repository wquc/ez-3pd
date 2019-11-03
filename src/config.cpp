#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <sstream>
#include "../include/config.h"
#include "../include/util.h"

bool read_config(const std::string& inp_name, Config& config) {
    std::ifstream inp_file(inp_name);
    /* check if input file exists. */
    if(!inp_file.is_open()) {
        std::cout << "ERROR> Cannot open file [" 
                  << inp_name << "]." 
                  << std::endl;
        return false;
    } else {
        std::cout << "ReadConfig> Reading input from file [" 
                  << inp_name 
                  << "]" 
                  << std::endl;
    }
    /* now read configuration */
    std::string each_line;
    std::stringstream each_stream;
    std::string buff;
    double each_chi, each_vol;
    auto is_space = [](char c) {return std::isspace(c);};
    while(getline(inp_file, each_line)) {
        /* filter out comment lines, empty lines and lines of spaces */
        if(0==each_line.substr(0,1).compare("#") ||
            std::all_of(each_line.begin(),each_line.end(),is_space))
            continue;
        each_stream.str(each_line);
        each_stream >> buff;
        if(0==buff.compare("dim")) {
            each_stream >> config.ncomp;
        } else if (0==each_line.substr(0,1).compare("x")) {
            each_stream >> each_chi;
            config.chiVec.push_back(each_chi);
        } else if (0==each_line.substr(0,1).compare("n")) {
            each_stream >> each_vol;
            config.volVec.push_back(each_vol);
        } else if (0==buff.compare("gridsize") ) {
            each_stream >> config.gridsize;
            if (config.gridsize >= 1.0) {
                std::cerr << "ERROR> Resolution must be in range (0, 1) !" 
                          << std::endl;
                return false;
            }
        } else if (0==buff.compare("outpref")) {
            each_stream >> config.outpref;
        } else {
            std::cout << "ERROR> Unrecognized parameter: "
                      << buff 
                      << std::endl;
        }
        each_stream.clear();
    }
    std::cout << "ReadConfig> Done." 
              << std::endl;
    return true;
}