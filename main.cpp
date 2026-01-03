#include "vetor3d.h"
#include "cor.h"

#include <iostream>

using namespace std;

int main() {

    int largura = 256;
    int altura = 256; //Tamanho da imagem

    cout << "P3\n" << largura << ' ' << altura << "\n255\n";  //Formatação principal, arquivo ppm
    for (int i = 0; i < altura; i++){
        clog << "\rLinhas remanescentes: " << (altura - i) << ' ' << std::flush;
        for (int j = 0; j < largura; j++){
            auto pixel_color = Cor(double(j)/(largura-1), double(i)/(altura-1), 0);
            escrever_cor(cout, pixel_color);
        }
    }
    clog << "\rDone.               \n";

    return 0;
}