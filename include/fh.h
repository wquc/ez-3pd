#ifndef FH_H
#define FH_H

#include <vector>

struct Coor2D {
    double x;
    double y;
    Coor2D () {}
    Coor2D (double x, double y):x(x), y(y) {}
};

struct Comp3D {
    double x;
    double y;
    double z;
    Comp3D () {}
    Comp3D (double x, double y, double z):x(x), y(y), z(z) {}
    REALVEC vec() {
        return REALVEC{this->x, this->y, this->z};
    }
    friend Comp3D operator + (const Comp3D &vec1, const Comp3D &vec2) {
        return Comp3D(vec1.x+vec2.x, vec1.y+vec2.y, vec1.z+vec2.z);
    }
    friend Comp3D operator - (const Comp3D &vec1, const Comp3D &vec2) {
        return Comp3D(vec1.x-vec2.x, vec1.y-vec2.y, vec1.z-vec2.z);
    }
};

// convert 3D composition to 2D coordinate
Coor2D comp2coor2d(const Comp3D& comp3d);

REAL freeEnergyFH(const REALVEC& phiVec, const REALVEC& volVec, const REALVEC& chiVec);
// REAL freeEnergyOA(const REALVEC& targVec, const REALVEC& phiVec, const REALVEC& chiVec, const REALVEC& volVec);

bool check_stablility(REAL dG_trial, REAL dG_real);

void init_pd(unsigned short int ncomp, double gridsize);

void calc_pd(const REALVEC& volVec, const REALVEC& chiVec, REAL gridsize);

void write_pd(const STR& out_name);

#endif