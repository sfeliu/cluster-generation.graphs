#include "include/grafo.hpp"


Grafo::Grafo(){
}


Grafo::~Grafo(){
	for(int i =0; i < vertices.size(); i++){
		for(int j=0;j < vertices[i].size(); j++)
			delete vertices[i][j];		
	}
}

void Grafo::new_node(){
	std::vector<node*> v;
	vertices.push_back(v);
}


void Grafo::new_node(int n){
	for(int i = 0; i < n; i++){
		std::vector<node*> v;
		vertices.push_back(v);
	}
}


bool Grafo::existe(int u, int v){
	std::vector<node*> it = vertices[u];
	bool yaExiste = false;
	for(int i=0; i<it.size(); i++){
		if(it[i]->id == v){
			return true;
		}
	}
	return yaExiste;
}

void Grafo::borrar_edge(int u, int v){
	if(u > vertices.size()-1 || v > vertices.size()-1){
		return;
	}
	vertices[u].erase(vertices[u].begin()+v);
	vertices[v].erase(vertices[v].begin()+u);

}

void Grafo::add_edge(int u, int v, double w){
	if(u > vertices.size()-1 || v > vertices.size()-1 || existe(u,v)){
		return;
	}
	node* nuevo_1 = new node;
	nuevo_1->id = v;
	nuevo_1->weight = w;
	(vertices[u]).push_back(nuevo_1);

	node* nuevo_2 = new node;
	nuevo_2->id = u;
	nuevo_2->weight = w;
	(vertices[v]).push_back(nuevo_2);
}

void Grafo::imprimir(){
	std::cout<< std::endl << "imprimiendo grafo..."<< std::endl;
	for(int i = 0;i < vertices.size();i++){
		std::vector<node*> it = vertices[i];
		for(int j = 0; j< it.size(); j++){
			std::cout<< "(" << i << "-->" << it[j]->id << ") ";
		}
		std::cout << std::endl;
	}
}


//TODO mandar a privado
bool porPeso(std::tuple<int,int,double> a, std::tuple<int,int,double> b){
	return (std::get<2>(a) < std::get<2>(b));
}


void Grafo::init_kruskal(){
	for(int i = 0; i<(vertices).size(); i++){
		padre.push_back(i);
		altura.push_back(1);
	}
}

int Grafo::find(int id){
	if(padre[id] != id){
		return find(padre[id]);
	}
	return padre[id];
}

void Grafo::conjunction(int u, int v){
	int x = find(u);
	int y = find(v);
	if(altura[x] < altura[y]){
		padre[x] = y;
	}else{
		padre[y] = x;
	}
	if(altura[x] == altura[y]){
		altura[x] = altura[x]+1;
	}
}

listAristas Grafo::kruskal(){
	init_kruskal();
	listAristas aristas;
	listAristas agm;
	for(int i = vertices.size()-1; i >= 0; i--){
		for(int j = vertices[i].size()-1; j >= 0; j--){
			vertices[i].erase(vertices[i].begin() + j);
			aristas.push_back(std::tuple<int,int,double>(i,(vertices[i][j])->id,(vertices[i][j])->weight));
		}
	}
	sort(aristas.begin(),aristas.end(), porPeso);
	for(int j = 0; j < aristas.size(); j++){
		if( find(std::get<0>(aristas[j])) != find(std::get<1>(aristas[j])) ){
			agm.push_back(aristas[j]);
			conjunction(std::get<0>(aristas[j]),std::get<1>(aristas[j]));
		}
	}
	return agm;
}

/*listAristas grafo::kruskal(){
	init_kruskal();
	listAristas aristas;
	listAristas agm;
	for(int i = 0; i<vertices.size(); i++){
		for(int j = 0; j<vertices[i].size(); j++){
			aristas.push_back(tuple<int,int,double>(i,(vertices[i][j])->id,(vertices[i][j])->weight));
			// if(i == 10){
			// 	cout << get<2>(aristas[j]) << endl;	
			// }
		}
	}
	sort(aristas.begin(),aristas.end(), porPeso);
	for(int j = 0; j<aristas.size(); j++){
		if( find(get<0>(aristas[j])) != find(get<1>(aristas[j])) ){
			agm.push_back(aristas[j]);
			conjunction(get<0>(aristas[j]),get<1>(aristas[j]));
		}
	}
	return agm;
}*/

/*bool esAlcanzable(listAristas l, int u, int i, int diametro, double &suma, int &pasos){

}*/

//TODO mandar a privado?
void sumaCamino(listAristas l, int u, int v, double &suma, int &pasos, int &vecinos){
	if (pasos == 0){
		return;
	} else {
		for(int i = 0; i < l.size(); i++){
			if((std::get<0>(l[i]) == u && std::get<1>(l[i]) != v)){
				suma = suma + std::get<2>(l[i]);
				pasos--;
				vecinos++;
				sumaCamino(l, std::get<1>(l[i]), std::get<0>(l[i]), suma, pasos, vecinos);
				pasos++;
			}
			if((std::get<1>(l[i]) == u && std::get<0>(l[i]) != v)){
				suma = suma + std::get<2>(l[i]);
				pasos--;
				vecinos++;
				sumaCamino(l, std::get<0>(l[i]), std::get<1>(l[i]), suma, pasos, vecinos);
				pasos++;
			}
		}
	}
}

//TODO mandar a privado?
double promedio_vecinos(listAristas l, int u, int v, int diametro){
	double suma = 0;
	int pasos = diametro;
	int vecinos = 0;
	sumaCamino(l,u,v,suma,pasos,vecinos);
	// pasos = diametro;
	// sumaCamino(l,v,u,suma,pasos,vecinos);

	suma = suma/(vecinos);
	return suma;
}

//TODO mandar a privado?
void varianza_vecinos(listAristas l, int u, int v, double &suma, int &pasos, int &vecinos, double promedio){
	if (pasos == 0){
		return;
	} else {
		for(int i = 0; i < l.size(); i++){
			if((std::get<0>(l[i]) == u && std::get<1>(l[i]) != v)){
				suma = suma + pow(std::get<2>(l[i])-promedio,2);
				pasos--;
				vecinos++;
				sumaCamino(l, std::get<1>(l[i]), std::get<0>(l[i]), suma, pasos, vecinos);
				pasos++;
			}
			if((std::get<1>(l[i]) == u && std::get<0>(l[i]) != v)){
				suma = suma + pow(std::get<2>(l[i])-promedio,2);
				pasos--;
				vecinos++;
				sumaCamino(l, std::get<0>(l[i]), std::get<1>(l[i]), suma, pasos, vecinos);
				pasos++;
			}
		}
	}					
}

//TODO mandar a privado?
double desvio_estandard(listAristas l, int u, int v, int diametro, double promedio){
	double suma = 0;
	int pasos = diametro;
	int vecinos = 0;
	varianza_vecinos(l,u,v,suma,pasos,vecinos, promedio);
	suma = sqrt(suma/vecinos);
	return suma;

}

//TODO mandar a privado?
listAristas remover_inconsistentes(listAristas l, int diametro){
	listAristas res = l;
	for(int i = 0; i < res.size(); i++){
		int u = std::get<0>(res[i]);
		int v = std::get<1>(res[i]);
		double promedio_u = promedio_vecinos(res,u,v,diametro);
		double promedio_v = promedio_vecinos(res,v,u,diametro);
		double peso = std::get<2>(res[i]);
		double desvio_u = desvio_estandard(res,u,v,diametro,promedio_u);
		double desvio_v = desvio_estandard(res,v,u,diametro,promedio_v);

		// cout<< "promedio: " << promedio << "; peso: " << peso << endl;

		bool pesoMayorPromedioU = peso > 3*promedio_u;
		bool pesoMayorPromedioV = peso > 3*promedio_v;
		bool pesoPromedioMayorDesvioU = (peso - promedio_u) > desvio_u*3;
		bool pesoPromedioMayorDesvioV = (peso - promedio_v) > desvio_v*3;
		if(pesoMayorPromedioU && pesoMayorPromedioV && pesoPromedioMayorDesvioU && pesoPromedioMayorDesvioV){
			res.erase(res.begin()+i);
			i--;
		}
	}
	return res;
}


void imprimir_agm(listAristas l){

	std::cout<< std::endl << "imprimiendo arbol generador minimo..."<< std::endl;
	for(int j = 0; j< l.size(); j++){
		std::cout<< "(" << std::get<0>(l[j]) << "-->" << std::get<1>(l[j]) << " ;peso: " << std::get<2>(l[j]) << ") " << std::endl;
	}
	std::cout << std::endl;
}

void Grafo::imprimir_pos(){
	std::cout<< "imprimiendo cordenadas..."<<std::endl;
	std::cout<< "{ ";
	for(int i = 0; i< puntos.size(); i++){
		std::cout<<"("<< puntos[i]->x << ", "<< puntos[i]->y << ") ";
	}
	std::cout << "}" <<std::endl;
}

/*double grafo::promedio_vecinos(int u, int v, int tam){
	double promedio;
	double cant_vecinos_u = (vertices[u].size()<tam) ? vertices[u].size() : tam;
	double cant_vecinos_v = (vertices[v].size()<tam) ? vertices[v].size() : tam;
	for(int i = 0; i<cant_vecinos_u; i++){
		promedio = promedio + vertices[u][i]->weight;
	}
	for(int j = 0; j< cant_vecinos_v; j++){
		promedio = promedio + vertices[v][j]->weight;
	}
	promedio = promedio/(cant_vecinos_v+cant_vecinos_u);
	return promedio;
}*/


