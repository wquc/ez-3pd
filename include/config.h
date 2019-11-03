#ifndef CONFIG_H
#define CONFIG_H

#include <string>
#include <vector>

struct Config {
    unsigned short ncomp;
    std::vector<double> chiVec;
    std::vector<double> volVec;
    double gridsize;
    std::string outpref;
};

bool read_config(const std::string& inp_name, Config& config);

#endif