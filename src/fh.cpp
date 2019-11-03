#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cmath>
#include <algorithm>
#include <iomanip>
#include <utility>
#include <cmath>
#include "../include/define.h"
#include "../include/fh.h"

static std::vector<Comp3D> composition3d;
static std::vector<bool>   is_unstable;
static std::vector<REAL>   alphaArr; 

Coor2D comp2coor2d(const Comp3D& comp3d) {
    return Coor2D(comp3d.x+0.5*comp3d.z, COEFF2*comp3d.z);
}

REAL freeEnergyFH(const REALVEC& phiVec, const REALVEC& chiVec, const REALVEC& volVec) {
    REAL entropyFH  = phiVec[0]*log(phiVec[0])/volVec[0] + 
                      phiVec[1]*log(phiVec[1])/volVec[1] +
                      phiVec[2]*log(phiVec[2])/volVec[2];
    REAL enthalpyFH = phiVec[0]*phiVec[1]*chiVec[0] + 
                      phiVec[1]*phiVec[2]*chiVec[2] + 
                      phiVec[0]*phiVec[2]*chiVec[1];
    return entropyFH + enthalpyFH;
}

bool check_stablility(REAL dG_trial, REAL dG_real) {
    return dG_trial < dG_real ? 0:1;
}

void init_pd(unsigned short int ncomp, double gridsize) {
    std::cout << "CalcPhaseDiag> Initializing phase diagram ..."
              << std::endl;
    if(3==ncomp) {
        const INT Ngrid = static_cast<INT>(1/gridsize);
        for(INT i=1; i<Ngrid; ++i)
            for (INT j=1; j<Ngrid; ++j) {
                if ((i+j)< Ngrid) {
                    INT k = Ngrid-(i+j);
                    composition3d.push_back(Comp3D(i*gridsize, j*gridsize, k*gridsize));
                }
            }
        is_unstable.resize(composition3d.size());
        std::fill(is_unstable.begin(), is_unstable.end(), false);
        std::cout << "CalcPhaseDiag> After initialization, (" 
                  << composition3d.size() 
                  << ") compositions will be examined."
                  << std::endl;
                  
        std::cout << "CalcPhaseDiag> Initializing angle array ..."
                  << std::endl;
        const REAL dalpha = MATHPI / Ngrid;
        for (INT ialpha=1; ialpha<Ngrid; ++ialpha) {
            alphaArr.push_back(ialpha*dalpha);
        }
        std::cout << "CalcPhaseDiag> Done."
                  << std::endl;
    }
}

void calc_pd(const REALVEC& volVec, const REALVEC& chiVec, REAL gridsize) {
    std::cout << "CalcPhaseDiag> Estimating unstable region ..."
              << std::endl;
    const INT Ncomp = composition3d.size();
    const REAL halfgrid = 0.5*gridsize;

#pragma omp parallel for
    for (INT icomp=0; icomp<Ncomp; ++icomp) {
        auto comp = composition3d[icomp];
        auto dG_fh = freeEnergyFH(comp.vec(), volVec, chiVec);
        INT stability_indicator = 1;
        bool skip_composition = false;
        for (const auto& alpha: alphaArr) {
            auto dphiVec = Comp3D(halfgrid*( cos(alpha)-COEFF1*sin(alpha)),
                                  halfgrid*(-cos(alpha)-COEFF1*sin(alpha)),
                                  halfgrid*(COEFF2*sin(alpha)));
            auto dG1 = freeEnergyFH((comp+dphiVec).vec(), volVec, chiVec);
            auto dG2 = freeEnergyFH((comp-dphiVec).vec(), volVec, chiVec);
            stability_indicator *= check_stablility(0.5*(dG1+dG2), dG_fh);
            if (0==stability_indicator) {
                is_unstable[icomp] = true;
                skip_composition = true;
                break;
            }
        }
        if (skip_composition) continue;
    }
}

void write_pd(const STR& out_name) {
    std::cout << "WritePhaseDiag> Wrting data ..."
              << std::endl;
    std::ofstream out_file(out_name+".dat");
    const INT Ncomp = composition3d.size();
    for (INT icomp=0; icomp<Ncomp; ++icomp) {
        if (is_unstable[icomp]) {
            auto ucomp = composition3d[icomp];
            // Permute order to keep consistency with Bergfeldt's paper.
            out_file << ucomp.z << " "
                     << ucomp.x << " " 
                     << ucomp.y << std::endl;
        }
    }
    std::cout << "WritePhaseDiag> Done ..."
              << std::endl;
}
