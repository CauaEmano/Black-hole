#ifndef CAMERA_H
#define CAMERA_H

#include "hit.h"

class Camera {
    public:
        double quadros = 1.0;
        int largura = 100;

        void renderizar(const hitaveis& mundo) {
            inicializar();

            std::cout << "P3\n" << largura << ' ' << altura << "\n255\n";

            for (int j = 0; j < altura; j++) {
                std::clog << "\rScanline Remaining: " << (altura - j) << ' ' << std::flush;
                for (int i = 0; i < largura; i++) {
                    auto pixel_centro = pixel00_local + (i*pixel_delta_u) + (j*pixel_delta_v);
                    auto raio_direcao = pixel_centro - centro;
                    Raio r(centro, raio_direcao);

                    Cor pixel_color = raio_cor(r, mundo);
                    escrever_cor(std::cout, pixel_color);
                }
            }
        }

    private:
        int altura;
        Ponto3d centro;
        Ponto3d pixel00_local;
        Vetor3d pixel_delta_u;
        Vetor3d pixel_delta_v;

        void inicializar() {
            altura = int(largura/quadros);
            altura = (altura < 1) ? 1: altura;
            centro = Ponto3d(0,0,0);

            auto focal_lente = 1.0;
            auto viewport_altura = 2.0;
            auto viewport_largura = viewport_altura * (double(largura)/altura);

            auto viewport_u = Vetor3d(viewport_largura, 0, 0);
            auto viewport_v = Vetor3d(0, -viewport_altura, 0);

            pixel_delta_u = viewport_u/largura;
            pixel_delta_v = viewport_v/altura;

            auto viewport_cima_esquerda = centro - Vetor3d(0,0,focal_lente) - viewport_u/2 - viewport_v/2;
            pixel00_local = viewport_cima_esquerda + 0.5 *(pixel_delta_u + pixel_delta_v);
        }

        Cor raio_cor(const Raio& r, const hitaveis& mundo) {
            recordar_hits rec;
            if (mundo.hit(r, Intervalo(0, infinity), rec)) {
                return 0.5 * (rec.normal + Cor(1,1,1));
            }

            Vetor3d direcao_unidade = vetor_normalizado(r.direcao());
            auto a = 0.5*(direcao_unidade.y() + 1.0);
            return (1.0-a) * Cor(1.0, 1.0, 1.0) + a*Cor(0.5, 0.7, 1.0);
        }
};

#endif