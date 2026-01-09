#include "constantes.h"
#include "camera.h"
#include "hit.h"
#include "hit_lista.h"
#include "material.h"
#include "esfera.h"

using namespace std;

int main() {

    hitaveis_lista mundo;

    auto material_chao = make_shared<Lambertian>(Cor(0.8,0.8,0.0));
    auto material_centro = make_shared<Lambertian>(Cor(0.1, 0.2, 0.5));
    auto material_esquerda = make_shared<Metal>(Cor(0.8, 0.8, 0.8), 0.3);
    auto material_direita = make_shared<Metal>(Cor(0.8, 0.6, 0.2), 1.0);

    mundo.add(make_shared<Esfera>(Ponto3d(0,0,-1.2), 0.5, material_centro));
    mundo.add(make_shared<Esfera>(Ponto3d(0,-100.5, -1.0), 100, material_chao));
    mundo.add(make_shared<Esfera>(Ponto3d(-1.0, 0.0, -1.0), 0.5, material_esquerda));
    mundo.add(make_shared<Esfera>(Ponto3d(1.0, 0.0, -1.0), 0.5, material_direita));

    Camera cam;

    cam.quadros = 16.0 / 9.0;
    cam.largura = 400;
    cam.samples_por_pixel = 100;
    cam.max_recursao = 50;

    cam.renderizar(mundo);
    return 0;
}