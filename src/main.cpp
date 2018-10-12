#include "include/grafo.hpp"
#include "include/misc.hpp"

int main(){
	std::cout << "ingrese cantidad de puntos y sus cordenadas:" << std::endl; 
	int n;
	std::cin >> n;
	double x,y;
	Grafo g; 
	g.new_node(n);
	for(int i = 0; i<n ; i++){
		std::cin >> x >> y; 
		Coordenadas cor = Coordenadas();
		cor.x = x;
		cor.y = y;
		(g.puntos()).push_back(cor);
	}
	for(int i = 0; i<n ; i++){
		for(int j = 0; j<n; j++){
			if(i != j ){
				double diff_x = abs(g.puntos()[i].x)-abs(g.puntos()[j].x);
				double diff_y = abs(g.puntos()[i].y)-abs(g.puntos()[j].y);
				double peso = sqrt(diff_x*diff_x + diff_y*diff_y);
				g.add_edge(i,j,peso);
			}
		}
	}
	//g.imprimir();
	listAristas aristas = g.convert();
	listAristas particionado = g.kruskal(aristas);
	imprimir_agm(particionado);
	listAristas res = remover_inconsistentes(particionado, 1);
	//std::ofstream file_1("/Users/pablo2martin/Downloads/algo3TP2/build/grafo2_clu_d4_f2_desvio3.csv");
	//file_1<< "x_1, " << "y_1," << "x_2, " << "y_2" << endl;
	// for(int i = 0; i < res.size(); i++){
	// 	file_1 << (g.puntos()[std::get<0>(res[i])]).x << ", "<< (g.puntos()[std::get<0>(res[i])]).y <<", " << (g.puntos()[std::get<1>(res[i])]).x << ", "<< (g.puntos()[std::get<1>(res[i])]).y << std::endl;
	// }
	imprimir_agm(res);
	//g.imprimir_pos();
	// g.new_node(3);
	// g.add_edge(0,2,1);
	// g.add_edge(0,1,7);
	// g.add_edge(1,2,5);
	// g.imprimir();
	// imprimir_agm(g.kruskal());

	// cat grafo1.csv | ./ejec

	return 0;
}