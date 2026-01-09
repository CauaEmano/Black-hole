#ifndef CAMERA_H
#define CAMERA_H

#include "hit.h"
#include "material.h"

class Camera {
    public:
        double quadros = 1.0;
        int largura = 100;
        int samples_por_pixel = 10;
        int max_recursao = 10;

        void renderizar(const hitaveis& mundo) {
            inicializar();

            std::cout << "P3\n" << largura << ' ' << altura << "\n255\n";

            for (int j = 0; j < altura; j++) {
                std::clog << "\rScanline Remaining: " << (altura - j) << ' ' << std::flush;
                for (int i = 0; i < largura; i++) {
                    Cor pixel_color(0,0,0);
                    for (int sample = 0; sample < samples_por_pixel; sample++) {
                        Raio r = get_raio(i,j);
                        pixel_color += raio_cor(r, max_recursao, mundo);
                    }
                    escrever_cor(std::cout, pixel_samples_scale * pixel_color);
                }
            }
        }

    private:
        int altura;
        Ponto3d centro;
        double pixel_samples_scale;
        Ponto3d pixel00_local;
        Vetor3d pixel_delta_u;
        Vetor3d pixel_delta_v;

        void inicializar() {
            altura = int(largura/quadros);
            altura = (altura < 1) ? 1: altura;
            pixel_samples_scale = 1.0/samples_por_pixel;
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

        Raio get_raio(int i, int j) const {
            auto offset = sample_square();
            auto pixel_sample = pixel00_local + ((i+offset.x()) * pixel_delta_u) + ((j + offset.y()) * pixel_delta_v);
            auto raio_origem = centro;
            auto raio_direcao = pixel_sample - raio_origem;

            return Raio(raio_origem, raio_direcao);
        }

        Vetor3d sample_square() const {
            return Vetor3d(random_double() - 0.5, random_double() - 0.5, 0);
        }

        Cor raio_cor(const Raio& r, int depth, const hitaveis& mundo) {
            if (depth <= 0) {
                return Cor(0,0,0);
            }
            
            recordar_hits rec;
            if (mundo.hit(r, Intervalo(0.001, infinity), rec)) {
                Raio espalhado;
                Cor atenuacao;
                if (rec.mat->espalhar(r, rec, atenuacao, espalhado)){
                    return atenuacao * raio_cor(espalhado, depth-1, mundo);
                return Cor(0,0,0);
                }
            }

            Vetor3d direcao_unidade = vetor_normalizado(r.direcao());
            auto a = 0.5*(direcao_unidade.y() + 1.0);
            return (1.0-a) * Cor(1.0, 1.0, 1.0) + a*Cor(0.5, 0.7, 1.0);
        }
};

#endif