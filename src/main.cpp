#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include "../include/define.h"
#include "../include/config.h"
#include "../include/fh.h"
// #include "../include/util.h"

int main(int argc, char* argv[]) {
    std::ios_base::sync_with_stdio(false);
    std::cout << "EZNPD> ***********************************************" << std::endl
              << "EZNPD> N-dimensional Phase Digrams"  << std::endl
              << "EZNPD> version 1.0, September 2019." << std::endl
              << "EZNPD> ***********************************************" << std::endl;
    if(argc!=2) {
        std::cerr << "ERROR> Missing input file!" << std::endl;
        return EXIT_FAILURE;
    }
    /* 1. read input */
    STR inp_name = argv[1];
    Config config;
    if(!read_config(inp_name, config)) {
        return EXIT_FAILURE;
    }
    
    /* 2. Compute phase diagram */
    init_pd(config.ncomp, config.gridsize);
    calc_pd(config.chiVec, config.volVec, config.gridsize);
    /* 3. write output */
    // std::string out_name = config.job_name + std::string("_nma_data_cutoff") + 
    //                        real2str(config.r_cutoff) + std::string(".dat");
    // write_data(out_name, config.n_modes, config.tol);
    write_pd(config.outpref);
    std::cout << "EZNPD> Normal termination of the program." << std::endl;
    return EXIT_SUCCESS;
}