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
        //g.imprimir();
        //listAristas aristas = g.convert();
        listAristas particionado = g.prim();

        //imprimir_agm(particionado);
        Grafo agm = Grafo(particionado, n);
        listAristas res = remover_inconsistentes(particionado, agm, 2, 2, 14, 3);
        std::vector<int> colores = descubrirConexo(res, n);
        for(int v=0; v<n; v++){
            std::cout<<colores[v]<<std::endl;
        }


        //agm.imprimir();
        //std::ofstream file_1("/Users/pablo2martin/Downloads/algo3TP2/build/grafo2_clu_d4_f2_desvio3.csv");
        //file_1<< "x_1, " << "y_1," << "x_2, " << "y_2" << endl;
        // for(int i = 0; i < res.size(); i++){
        // 	file_1 << (g.puntos()[std::get<0>(res[i])]).x << ", "<< (g.puntos()[std::get<0>(res[i])]).y <<", " << (g.puntos()[std::get<1>(res[i])]).x << ", "<< (g.puntos()[std::get<1>(res[i])]).y << std::endl;
        // }

        /*std::ofstream file_1("/home/santiago/Documents/algo_3/algo3TP2/tests/grafos/grafo11_nodos.csv");
        for(int i = 0; i < g.puntos().size(); i++){
            file_1 << (g.puntos()[i]).x << ", " << (g.puntos()[i]).y << std::endl;
        }
        std::ofstream file_2("/home/santiago/Documents/algo_3/algo3TP2/tests/grafos/grafo11_agm.csv");
        for(int i = 0; i <particionado.size(); i++){
            file_2 << std::get<0>(particionado[i]) << ", " << std::get<1>(particionado[i]) << std::endl;
        }*/
        // imprimir_agm(res);
        //g.imprimir_pos();
        // g.new_node(3);
        // g.add_edge(0,2,1);
        // g.add_edge(0,1,7);
        // g.add_edge(1,2,5);
        // g.imprimir();
        // imprimir_agm(g.kruskal());

        // cat grafo1.csv | ./ejec
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