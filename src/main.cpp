#include "include/grafo.hpp"
#include "include/misc.hpp"

int main(int argc, char** argv){
    int mode = atoi(argv[1]);
    if(mode==0) {
        std::cout << "ingrese cantidad de puntos y sus cordenadas:" << std::endl;
        int n;
        std::cin >> n;
        double x, y;
        std::vector<Coordenadas> coordenadas;
        for (int i = 0; i < n; i++) {
            std::cin >> x >> y;
            Coordenadas cor = Coordenadas();
            cor.x = x;
            cor.y = y;
            coordenadas.push_back(cor);
        }
        Grafo g(coordenadas);
        listAristas particionado = g.prim();

        Grafo agm = Grafo(particionado, n);
        listAristas res = remover_inconsistentes(particionado, agm, 2, 2, 14, 3);
        std::vector<int> colores = descubrirConexo(res, n);
        for(int v=0; v<n; v++){
            std::cout<<colores[v]<<std::endl;
        }
    }else{
        std::vector<std::vector<double>> pesos;
        int n;
        std::cin >> n;
        for(int i = 0; i < n; i++){
            std::vector<double> nodo_i;
            pesos.push_back(nodo_i);
            for(int j = 0; j < n; j++){
                double peso;
                std::cin >> peso;
                pesos[i].push_back(peso);
            }
        }
        Grafo g(pesos);
        g.logPesos();
        if(atoi(argv[2]) == 0){
            g.cicloNegativoBF();
        }else{
            g.cicloNegativoFW();
        }
    }

	return 0;
}
