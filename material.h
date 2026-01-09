#ifndef MATERIAL_H
#define MATERIAL_H

#include "hit.h"

class Material {

    public:
        virtual ~Material() = default;

        virtual bool espalhar(
            const Raio& r, const recordar_hits& rec, Cor& atenuacao, Raio& espalhado) const {
                return false;
            }

};

class Lambertian : public Material {

    public:
        Lambertian(const Cor& albedo) : albedo(albedo) {}

        bool espalhar(const Raio& r, const recordar_hits& rec, Cor& atenuacao, Raio& espalhado) const override {
            auto espalhar_direcao = rec.normal + random_unit_vector();

            if (espalhar_direcao.proximo_zero())
                espalhar_direcao = rec.normal;

            espalhado = Raio(rec.p, espalhar_direcao);
            atenuacao = albedo;
            return true;
        }
    private:
        Cor albedo;
};

class Metal : public Material {
    public: 
        Metal(const Cor& albedo, double fuzz) : albedo(albedo), fuzz(fuzz<1? fuzz:1) {}

        bool espalhar(const Raio& r, const recordar_hits& rec, Cor& atenuacao, Raio& espalhado) const override {
            Vetor3d refletido = refletir(r.direcao(), rec.normal);
            refletido = vetor_normalizado(refletido) + (fuzz*random_unit_vector());
            espalhado = Raio(rec.p, refletido);
            atenuacao = albedo;
            return (dot(espalhado.direcao(), rec.normal) > 0);
        }     
        
    private:
        Cor albedo;
        double fuzz;
};

#endif