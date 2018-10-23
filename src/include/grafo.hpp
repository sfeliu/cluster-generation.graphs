
#ifndef _GRAFO_HPP_
#define _GRAFO_HPP_


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
#include <queue>
#include <chrono>
#include <limits> //Inf


#define INF std::numeric_limits<double>::infinity()

struct Coordenadas
	{
	// public:
		double x;
		double y;	
	};

typedef std::vector< std::tuple <int,int,double> > listAristas;

class Comparador 
{
public:
	int operator()(std::tuple<int,double> t ,std::tuple<int,double> s){
		return std::get<1>(t) > std::get<1>(s);
	}
};

class Grafo
{
	struct Node
	{
		double weight;
		int id;
	};

	

	public:
		std::vector<Coordenadas>& puntos();
		Grafo();
		Grafo(std::vector<Coordenadas> puntos); // constructor de grafo Kn con coordenadas
		Grafo(std::vector<std::vector<double>> pesos); // constructor de grafo Kn con matriz de pesos
		Grafo(listAristas l, int cantNodos); // Contructor con listaAristas.
		bool existe(int u, int v);
		void imprimir();
		void new_node();
		void new_node(int n);
		void borrar_edge(int u, int v);
		void add_edge(int u, int v, double weight);
		void add_directional_edge(int u, int v, double weight);
		void conjunction_pc(int u, int v);
		int find_pc(int id);
		void init_kruskal_pc();
		void imprimir_pos();
		int find(int id);
		void init_kruskal();
		void conjunction(int u, int v);
		listAristas obtener_vecinos(int u, int v, double cant_vecinos);
		listAristas kruskal(listAristas aristas);
		listAristas kruskal_pc(listAristas aristas);
		listAristas prim();
		listAristas convert();

		void cicloNegativoFW();
		void cicloNegativoBF();

        void logPesos();
		// bool floydWarshall(); 
		/*
		std::string floyWarshall();
		std::string bellmanFord();
		*/
		// listAristas remover_inconsistentes(listAristas l, int diametro);
		// double promedio_vecinos(int u, int v, int tam);
		// double promedio_vecinos(listAristas l, int u, int v, int diametro);

	private:
		std::vector<int> _padre;
		std::vector<int> _altura;
		std::vector< std::vector<Node> > _vertices;
		std::vector<Coordenadas> _puntos;

		double& peso(int u, int v);
		int floydWarshall(std::vector< std::vector<int> > &distancias);
		int bellmanFord(std::vector< std::vector<int> > &distancias);
		// bool porPeso(std::tuple<int,int,double> a, std::tuple<int,int,double> b);

};

#endif