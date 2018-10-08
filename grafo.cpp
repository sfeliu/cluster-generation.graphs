#include <stdlib.h>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <tuple>
#include <cstdio>
#include <cstdlib>
#include <math.h>



using namespace std;

class cordenadas
	{
	public:
		double x;
		double y;	
	};

typedef vector< tuple <int,int,double> > listAristas;
class grafo
{
	struct node
	{
		double weight;
		int id;
	};

	

	vector<int> padre;
	vector<int> altura;
	vector< vector<node*> > vertices;
	public:
		vector<cordenadas*> puntos;
		grafo();
		~grafo();
		bool existe(int u, int v);
		void imprimir();
		void new_node();
		void new_node(int n);
		void borrar_edge(int u, int v);
		void add_edge(int u, int v, double weight);
		void conjunction(int u, int v);
		int find(int id);
		void init_kruskal();
		void imprimir_pos();
		listAristas kruskal();
		// listAristas remover_inconsistentes(listAristas l, int diametro);
		// double promedio_vecinos(int u, int v, int tam);
		// double promedio_vecinos(listAristas l, int u, int v, int diametro);

};

grafo::grafo(){
}


grafo::~grafo(){
	for(int i =0; i<vertices.size(); i++){
		for(int j=0;j<vertices[i].size(); j++)
			delete vertices[i][j];		
	}
}

void grafo::new_node(){
	vector<node*> v;
	vertices.push_back(v);
}


void grafo::new_node(int n){
	for(int i = 0; i<n; i++){
		vector<node*> v;
		vertices.push_back(v);
	}
}


bool grafo::existe(int u, int v){
	vector<node*> it = vertices[u];
	bool yaExiste = false;
	for(int i=0; i<it.size(); i++){
		if(it[i]->id == v){
			yaExiste = true;
			break;
		}
	}
	return yaExiste;
}

void grafo::borrar_edge(int u, int v){
	if(u>vertices.size()-1 || v>vertices.size()-1){
		return;
	}
	vertices[u].erase(vertices[u].begin()+v);
	vertices[v].erase(vertices[v].begin()+u);

}

void grafo::add_edge(int u, int v, double w){
	if(u>vertices.size()-1 || v>vertices.size()-1 || existe(u,v)){
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

void grafo::imprimir(){
	cout<< endl << "imprimiendo grafo..."<< endl;
	for(int i = 0;i<vertices.size();i++){
		vector<node*> it = vertices[i];
		for(int j = 0; j< it.size(); j++){
			cout<< "(" << i << "-->" << it[j]->id << ") ";
		}
		cout << endl;
	}
}


bool porPeso(tuple<int,int,double> a, tuple<int,int,double> b){
	return (get<2>(a) < get<2>(b));
}


void grafo::init_kruskal(){
	for(int i = 0; i<(vertices).size(); i++){
		padre.push_back(i);
		altura.push_back(1);
	}
}

int grafo::find(int id){
	if(padre[id] != id){
		return find(padre[id]);
	}
	return padre[id];
}

void grafo::conjunction(int u, int v){
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

listAristas grafo::kruskal(){
	init_kruskal();
	listAristas aristas;
	listAristas agm;
	for(int i = vertices.size()-1; i>=0; i--){
		for(int j = vertices[i].size()-1; j>=0; j--){
			vertices[i].erase(vertices[i].begin()+j);
			aristas.push_back(tuple<int,int,double>(i,(vertices[i][j])->id,(vertices[i][j])->weight));
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

void sumaCamino(listAristas l, int u, int v, double &suma, int &pasos, int &vecinos){
	if(pasos == 0){
		return;
	}else{
		for(int i = 0; i<l.size(); i++){
			if((get<0>(l[i]) == u && get<1>(l[i]) != v)){
				suma = suma + get<2>(l[i]);
				pasos--;
				vecinos++;
				sumaCamino(l, get<1>(l[i]), get<0>(l[i]), suma, pasos, vecinos);
				pasos++;
			}
			if((get<1>(l[i]) == u && get<0>(l[i]) != v)){
				suma = suma + get<2>(l[i]);
				pasos--;
				vecinos++;
				sumaCamino(l, get<0>(l[i]), get<1>(l[i]), suma, pasos, vecinos);
				pasos++;
			}
		}
	}
}

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

listAristas remover_inconsistentes(listAristas l, int diametro){
	listAristas res = l;
	for(int i = 0; i < res.size(); i++){
		int u = get<0>(res[i]);
		int v = get<1>(res[i]);
		double promedio_u = promedio_vecinos(res,u,v,diametro);
		double promedio_v = promedio_vecinos(res,v,u,diametro);
		double peso = get<2>(res[i]);
		// cout<< "promedio: " << promedio << "; peso: " << peso << endl;
		if(peso > 3*promedio_u && peso > 3*promedio_v){
			res.erase(res.begin()+i);
			i--;
		}
	}
	return res;
}


void imprimir_agm(listAristas l){

	cout<< endl << "imprimiendo arbol generador minimo..."<< endl;
	for(int j = 0; j< l.size(); j++){
		cout<< "(" << get<0>(l[j]) << "-->" << get<1>(l[j]) << " ;peso: " << get<2>(l[j]) << ") " << endl;
	}
	cout << endl;
}

void grafo::imprimir_pos(){
	cout<< "imprimiendo cordenadas..."<<endl;
	cout<< "{ ";
	for(int i = 0; i< puntos.size(); i++){
		cout<<"("<< puntos[i]->x << ", "<< puntos[i]->y << ") ";
	}
	cout << "}" <<endl;
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



int main(){
	cout << "ingrese cantidad de puntos y sus cordenadas:" << endl; 
	int n;
	cin >> n;
	double x,y;
	grafo g;
	g.new_node(n);
	for(int i = 0; i<n ; i++){
		cin >> x >> y;
		cordenadas* cor = new cordenadas;
		cor->x = x;
		cor->y = y;
		(g.puntos).push_back(cor);
	}
	for(int i = 0; i<n ; i++){
		for(int j = 0; j<n; j++){
			if(i != j ){
				double diff_x = abs(g.puntos[i]->x)-abs(g.puntos[j]->x);
				double diff_y = abs(g.puntos[i]->y)-abs(g.puntos[j]->y);
				double peso = sqrt(diff_x*diff_x + diff_y*diff_y);
				g.add_edge(i,j,peso);
			}
		}
	}
	//g.imprimir();
	listAristas particionado = g.kruskal();
	imprimir_agm(particionado);
	listAristas res = remover_inconsistentes(particionado, 1); 
	imprimir_agm(res);
	g.imprimir_pos();
	// g.new_node(3);
	// g.add_edge(0,2,1);
	// g.add_edge(0,1,7);
	// g.add_edge(1,2,5);
	// g.imprimir();
	// imprimir_agm(g.kruskal());

	// cat grafo1.csv | ./ejec

	return 0;
}
