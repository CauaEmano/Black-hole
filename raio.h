#ifndef RAIO_H
#define RAIO_H

#include "vetor3d.h"

class Raio {
    private:
        Ponto3d origin;
        Vetor3d direction;

    public:
        Raio() {}

        Raio(Ponto3d orig, Vetor3d dir): origin(orig), direction(dir) {}

        const Ponto3d origem() const { return origin; }
        const Vetor3d direcao() const { return direction; }

        Ponto3d at(double t) const {
            return origin + (t*direction);
        }
};

#endif