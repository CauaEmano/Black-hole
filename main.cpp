#include "constantes.h"
#include "camera.h"
#include "hit.h"
#include "hit_lista.h"
#include "esfera.h"


using namespace std;

int main() {

    hitaveis_lista mundo;

    mundo.add(make_shared<Esfera>(Ponto3d(0,0,-1), 0.5));
    mundo.add(make_shared<Esfera>(Ponto3d(0,-100.5, -1), 100));

    Camera cam;

    cam.quadros = 16.0 / 9.0;
    cam.largura = 400;

    cam.renderizar(mundo);
    return 0;
}