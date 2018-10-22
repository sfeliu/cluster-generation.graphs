#include "include/grafo.hpp"


Grafo::Grafo(){
}

void Grafo::new_node(){
	std::vector<Node>v;
	_vertices.push_back(v);
}


Grafo::Grafo(std::vector<Coordenadas> puntos) {
    unsigned long n = puntos.size();
    this->new_node(n);
    for(int i = 0; i<n ; i++){
        for(int j = 0; j<n; j++){
            if(i != j ){
                double diff_x = abs(puntos[i].x)-abs(puntos[j].x);
                double diff_y = abs(puntos[i].y)-abs(puntos[j].y);
                double peso = sqrt(diff_x*diff_x + diff_y*diff_y);
                this->add_edge(i,j,peso);
            }
        }
        _puntos[i] = puntos[i];
    }
}


Grafo::Grafo(std::vector<std::vector<double>> pesos) {
    unsigned long n = pesos.size();
    this->new_node(n);
    for(int i = 0; i<n ; i++){
        for(int j = 0; j<n; j++){
            this->add_directional_edge(i,j,pesos[i][j]);
        }
    }
}


void Grafo::new_node(int n){
	for(int i = 0; i < n; i++){
		std::vector<Node> v;
		_vertices.push_back(v);
	}
}


bool Grafo::existe(int u, int v){
	bool yaExiste = false;
	for(int i=0; i <  _vertices[u].size(); i++){
		if(_vertices[u][i].id == v){
			return true;
		}
	}
	return yaExiste;
}

void Grafo::borrar_edge(int u, int v){
	if(u > _vertices.size()-1 || v > _vertices.size()-1){
		return;
	}
	_vertices[u].erase(_vertices[u].begin()+v);
	_vertices[v].erase(_vertices[v].begin()+u);

}

void Grafo::add_directional_edge(int u, int v, double w){
	if(u > _vertices.size()-1 || v > _vertices.size()-1 || existe(u,v)){
		return;
	}
	Node nuevo_1 = Node();
	nuevo_1.id = v;
	nuevo_1.weight = w;
	(_vertices[u]).push_back(nuevo_1);
}

void Grafo::add_edge(int u, int v, double w){
	if(u > _vertices.size()-1 || v > _vertices.size()-1 || existe(u,v)){
		return;
	}
	Node nuevo_1 = Node();
	nuevo_1.id = v;
	nuevo_1.weight = w;
	(_vertices[u]).push_back(nuevo_1);

	Node nuevo_2 = Node();
	nuevo_2.id = u;
	nuevo_2.weight = w;
	(_vertices[v]).push_back(nuevo_2);
}

void Grafo::imprimir(){
	std::cout<< std::endl << "imprimiendo grafo..."<< std::endl;
	for(int i = 0; i < _vertices.size();i++){
		for(int j = 0; j< _vertices[i].size(); j++){
			std::cout<< "(" << i << "-" << _vertices[i][j].weight << "->" << _vertices[i][j].id << ") ";
		}
		std::cout << std::endl;
	}
}


//TODO mandar a privado
bool porPeso(std::tuple<int,int,double> a, std::tuple<int,int,double> b){
	return (std::get<2>(a) < std::get<2>(b));
}


void Grafo::init_kruskal_pc(){
	for(int i = 0; i<(_vertices).size(); i++){
		_padre.push_back(i);
		_altura.push_back(1);
	}
}

int Grafo::find_pc(int id){
	if(_padre[id] != id){
		_padre[id] = find(_padre[id]);
	}
	return _padre[id];
}

void Grafo::conjunction_pc(int u, int v){
	int x = find(u);
	int y = find(v);
	if(_altura[x] < _altura[y]){
		_padre[x] = y;
	}else{
		_padre[y] = x;
	}
	if(_altura[x] == _altura[y]){
		_altura[x] = _altura[x]+1;
	}
}

listAristas Grafo::convert(){
	listAristas aristas;
	for(int i = _vertices.size()-1; i >= 0; i--){
		for(int j = _vertices[i].size()-1; j >= 0; j--){
			_vertices[i].erase(_vertices[i].begin() + j);
			aristas.push_back(std::tuple<int,int,double>(i,(_vertices[i][j]).id,(_vertices[i][j]).weight));
		}
	}
	return aristas;

}

listAristas Grafo::kruskal_pc(listAristas aristas){
	init_kruskal_pc();
	listAristas agm;
	sort(aristas.begin(),aristas.end(), porPeso);
	for(int j = 0; j < aristas.size(); j++){
		if( find_pc(std::get<0>(aristas[j])) != find_pc(std::get<1>(aristas[j])) ){
			agm.push_back(aristas[j]);
			conjunction_pc(std::get<0>(aristas[j]),std::get<1>(aristas[j]));
		}
	}
	return agm;
}


void Grafo::init_kruskal(){
	for(int i = 0; i<(_vertices).size(); i++){
		_padre.push_back(i);
	}
}

int Grafo::find(int id){
	if(_padre[id] != id){
		return find(_padre[id]);
	}
	return _padre[id];
}

void Grafo::conjunction(int u, int v){
	_padre[find(u)] = _padre[find(v)];
}


listAristas Grafo::kruskal(listAristas aristas){
	init_kruskal();
	listAristas agm;
	sort(aristas.begin(),aristas.end(), porPeso);
	for(int j = 0; j < aristas.size(); j++){
		if( find(std::get<0>(aristas[j])) != find(std::get<1>(aristas[j])) ){
			agm.push_back(aristas[j]);
			conjunction(std::get<0>(aristas[j]),std::get<1>(aristas[j]));
		}
	}
	return agm;
}

listAristas Grafo::prim(){
	listAristas padre;
	std::vector<double> distancia;
	std::vector<bool> visitado;

	for(int i = 0; i < _vertices.size(); i++){
		padre.push_back(std::tuple<int,int,double>());
		distancia.push_back(10000000);
		visitado.push_back(false);
	}

	distancia[0] = 0;
	std::priority_queue <std::tuple<int,double>, std::vector<std::tuple<int,double>>, Comparador> pq;
	pq.push(std::tuple<int,double>(0, distancia[0]));
	while(!pq.empty()){
		std::tuple <int,double> t = pq.top();
		pq.pop();
		int t_1 = std::get<0>(t);
		if(!visitado[t_1]){
			visitado[t_1] = true;
			for(int j = 0; j < _vertices[t_1].size(); j++){
				int t_2 = _vertices[t_1][j].id;
				if(!visitado[t_2] && (distancia[t_2] > _vertices[t_1][j].weight)){
					distancia[t_2] = _vertices[t_1][j].weight;
					padre[t_2] = std::tuple<int,int,double>(t_1,t_2,distancia[t_2]);
					t = std::tuple<int,double>(t_2, distancia[t_2]);
					pq.push(t);
				}
			}
		}
	}
	return padre;
}

/*
std::string Grafo::bellmanFord(){
	std::vector<double> distancia;
	bool cambios = false;
	int i = 0;
	for (int i = 0; i < _vertices.size(); ++i)
	{
		//falta importar #include <limits> 
		//(para poder usar inf, que es como inicializa el algoritmo las distancias)
		//distancia[i] = inf;
	}
	i = 0;
	while( i < _vertices.size() && cambios)
	{	
		for (int j = 0; j < _vertices.size(); ++j)
		{	
			int min = distancia[j];
			for (int k = 0; k < _vertices.size(); ++k)
			{
				if (min > distancia[k]+ _vertices[k][0])
				{
					min = distancia[k]+ _vertices[k][0];
				}
			}
			distancia[j] = min;
		}
			i++;
	}
	if(i == n){
		return "SI";
	}
	return "NO";
}

std::string Grafo::floyWarshall(){
	for (int k = 0; k < _vertices.size(); ++k)
	{
		for (int i = 0; i < _vertices.size(); ++i)
		{
			for (int j = 0; j < count; ++j)
			{
				_vertices[i][j].weight = min(_vertices[i][j].weight,_vertices[i][k].weight+_vertices[k][i].weight);
			}
		}
	}
	for (int i = 0; i < _vertices.size(); ++i)
	{
		if (_vertices[i][i] < 0)
		{
			return return "SI";
		}
	}
	return "NO";
}
*/

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
	if(vecinos != 0){
		suma = suma/(vecinos);
	}else{
		suma = 10000000;
	}
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
	if(vecinos != 0){
		suma = suma/(vecinos);
	}else{
		suma = 10000000;
	}
	suma = sqrt(suma);
	return suma;

}

//TODO mandar a privado?
listAristas remover_inconsistentes(listAristas l, int ds, double f, double diametro, int mod){
	listAristas res = l;
	for(int i = 0; i < res.size(); i++){
		int u = std::get<0>(res[i]);
		int v = std::get<1>(res[i]);
		if(u == v){
			res.erase(res.begin()+i);
			i--;
		}else{
			double promedio_u = promedio_vecinos(res,u,v,diametro);
			double promedio_v = promedio_vecinos(res,v,u,diametro);
			double peso = std::get<2>(res[i]);
			double desvio_u = desvio_estandard(res,u,v,diametro,promedio_u);
			double desvio_v = desvio_estandard(res,v,u,diametro,promedio_v);

			// cout<< "promedio: " << promedio << "; peso: " << peso << endl;

			bool pesoMayorPromedioU = peso > f*promedio_u;
			bool pesoMayorPromedioV = peso > f*promedio_v;
			bool pesoPromedioMayorDesvioU = (peso - promedio_u) > desvio_u*ds;
			bool pesoPromedioMayorDesvioV = (peso - promedio_v) > desvio_v*ds;
			if(mod == 1){
				if(pesoMayorPromedioU && pesoMayorPromedioV){
					res.erase(res.begin()+i);
					i--;
				}
			}
			if(mod == 2){
				if(pesoPromedioMayorDesvioU && pesoPromedioMayorDesvioV){
					res.erase(res.begin()+i);
					i--;
				}
			}
			if(mod == 3){
				if((pesoMayorPromedioU && pesoMayorPromedioV) || (pesoPromedioMayorDesvioU && pesoPromedioMayorDesvioV)){
					res.erase(res.begin()+i);
					i--;
				}
			}
			if(mod == 4){
				if(pesoMayorPromedioU && pesoMayorPromedioV && pesoPromedioMayorDesvioU && pesoPromedioMayorDesvioV){
					res.erase(res.begin()+i);
					i--;
				}
			}			
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
	for(int i = 0; i< puntos().size(); i++){
		std::cout<<"("<< puntos()[i].x << ", "<< puntos()[i].y << ") ";
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

std::vector<Coordenadas>& Grafo::puntos(){
	return _puntos;
}

double& Grafo::peso(int u, int v){
	return _vertices[u][v].weight;
}

void Grafo::logPesos(){
	int n = _vertices.size();
	for (int u = 0; u < n; u++){
		for (int v = 0; v < n; v++){
			peso(u,v) = - log10(peso(u,v));
		}
	}
}

void Grafo::cicloNegativoFW(){
	int n = _vertices.size();
	std::vector <int> filaSiguiente(n,-1);
	std::vector <std::vector<int> > siguiente (n,filaSiguiente);

	int hayCicloNegativo = floydWarshall(siguiente);

	if (hayCicloNegativo != -1){
		std::cout << "SI ";
		std::vector<int> recorrido;
		recorrido.push_back(hayCicloNegativo);
		int v = hayCicloNegativo;
		int u = siguiente[v][v];
			while (v != u){
				recorrido.push_back(u);
				u = siguiente[u][v];
			}
			recorrido.push_back(hayCicloNegativo);
			for (int i = 0; i < recorrido.size(); i++){
				std::cout << recorrido[i] << " ";
			}
	} else {
		std::cout << "NO";
	}
}

int Grafo::floydWarshall(std::vector< std::vector<int> > &siguiente){
	int n = _vertices.size();
	std::vector <double> filaDistancias(n,INF);

	std::vector <std::vector<double> > distancias (n,filaDistancias);

	for (int u = 0; u < n; u++){
		for(int v = 0; v < n; v++){
			distancias[u][v] = peso(u,v);
			siguiente[u][v] = v;
		}
	}

	for (int k = 0; k < n; k++){
		for (int i = 0; i < n; i++){
			for (int j = 0; j < n; j++){
				if (distancias[i][j] > distancias[i][k] + distancias[k][j]){
					distancias[i][j] = distancias[i][k] + distancias[k][j];
					siguiente[i][j] = siguiente[i][k];
				}
			}
		}
	}

    for (int i = 0; i < n; i++) 
        if (distancias[i][i] < 0) 
            return i; 
    return -1;  
}

void Grafo::cicloNegativoBF(){
    //imprimir();
    int n = _vertices.size();
    std::vector <int> pred(n,-1);
    std::vector <double> distancias(n,INF);
    std::vector <double> copia;
    distancias[0] = 0;

	// std::vector <std::vector<double> > distancias (n,filaDistancias);
	int i = 0;
	bool cambio = true;
	while(i < n && cambio){	
		copia = distancias;
		cambio = false;
		for (int u = 0; u < n; ++u){
			for (int v = 0; v < n; ++v){
				if(copia[u] != INF) {
                    if ( copia[v] == INF || copia[v] > copia[u] + peso(u, v)){
                        //std::cout << copia[v] << " > " << copia[u] << " + " << peso(u, v) << std::endl;
                        distancias[v] = copia[u] + peso(u, v);
                        pred[v] = u;
                        cambio = true;
                        //std::cout << u << " <- " << pred[v] << std::endl;
                    }
                }
			}
		}
		i++;
	}
	    //std::cout << "Encontre que hay ciclo"<< std::endl;
        //for(int x = 0; x<pred.size(); x++){
        //    std::cout << pred[x] << std::endl;
        //}
    bool hayCiclo = false;
    for (int v = 0; v < n; v++) {
        //std::cout << "copia" << copia[v] << "| real " << distancias[v] << std::endl;
        if (copia[v] != distancias[v]){
            hayCiclo = true;
            std::cout << "SI ";
            int h = pred[v];
            std::vector<int> recorrido;
            recorrido.push_back(v);
            while (h != v) {
                recorrido.push_back(h);
                h = pred[h];
                //std::cout << h << std::endl;
            }
            for (int j = recorrido.size()-1; j >= 0; j--) {
                std::cout << recorrido[j] << " ";
            }
            std::cout << recorrido[recorrido.size()-1] << std::endl;
            break;
        }
    }
    if(!hayCiclo){
        std::cout<< "NO";
    }
}

void descubrirConexoAux(int u, listAristas res, int& contador, std::vector<bool> &visitado, int& i, std::vector<int> &comp_conex){
	comp_conex[u] = contador;
	comp_conex[std::get<1>(res[i])] = contador;
	visitado[u] = true;
	for(int j = 0; j<res.size(); j++){
		if(i != j ){
			if(std::get<0>(res[j]) == u){
				descubrirConexoAux(std::get<1>(res[j]), res, contador, visitado, j, comp_conex);
			}
			if( std::get<1>(res[j]) == u){
				descubrirConexoAux(std::get<0>(res[j]), res, contador, visitado, j, comp_conex);
			}
		}else{
			if(!visitado[std::get<1>(res[j])]){
				descubrirConexoAux(std::get<1>(res[j]), res, contador, visitado, j, comp_conex);
			}
		}
	}
}


std::vector<int> descubrirConexo(listAristas l, int n){
	std::vector<int> comp_conex;
	int contador = 0;
	std::vector<bool> visitado;
	for(int i = 0; i < n; i++){
		comp_conex.push_back(0);
		visitado.push_back(false);	
	}
	for(int i = 0; i < l.size(); i++){
		if(!visitado[std::get<0>(l[i])]){
			descubrirConexoAux(std::get<0>(l[i]), l, contador, visitado,i,comp_conex);	
			contador++;
		}
	}
	return comp_conex;
}

listAristas diff(listAristas& l1, listAristas& l2){
	listAristas res;
	for(int i = 0; i < l1.size(); i++){
		bool pertenece = false;
		for(int j = 0; j< l2.size(); j++){
			bool igualesInv = (std::get<0>(l1[i]) == std::get<1>(l2[j])) && (std::get<1>(l1[i]) == std::get<0>(l2[j]));
			bool iguales = (std::get<0>(l1[i]) == std::get<0>(l2[j])) && (std::get<1>(l1[i]) == std::get<1>(l2[j]));
			if(iguales || (igualesInv)){
				pertenece = true;
				res.push_back(l1[i]);
				l2.erase(l2.begin()+j);
				l1.erase(l1.begin()+i);
				i--;
				break;
			}
		}
		// if(!pertenece){
		// }
	}
	return res;
}
