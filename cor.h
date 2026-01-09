#ifndef COR_H
#define COR_H

#include "vetor3d.h"

using Cor = Vetor3d;

inline double linear_para_gama(double linear_componente) {
    if (linear_componente > 0) {
        return std::sqrt(linear_componente);
    }
    return 0;
}

void escrever_cor(std::ostream& out, const Cor& pixel_color) {
    auto r = pixel_color.x();
    auto g = pixel_color.y();
    auto b = pixel_color.z();

    r = linear_para_gama(r);
    g = linear_para_gama(g);
    b = linear_para_gama(b);

    static const Intervalo intensidade(0.000, 0.999);
    int rbyte = int(256 * intensidade.clamp(r));
    int gbyte = int(256 * intensidade.clamp(g));
    int bbyte = int(256 * intensidade.clamp(b));

    out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
}

#endif