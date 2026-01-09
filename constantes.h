#ifndef CONSTANTES_H
#define CONSTANTES_H

#include <cmath>
#include <random>
#include <iostream>
#include <limits>
#include <memory>

using std::make_shared;
using std::shared_ptr;

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

inline double degrees_to_radians(double degrees) {
    return degrees * pi / 180.0;
    
}

inline double random_double() {
    static std::uniform_real_distribution<double> distribuicao(0.0, 1.0);
    static std::mt19937 gerador;
    return distribuicao(gerador);
}

inline double random_double(double min, double max) {
    return min + (max-min)*random_double();
}

#include "intervalo.h"
#include "cor.h"
#include "raio.h"
#include "vetor3d.h"

#endif