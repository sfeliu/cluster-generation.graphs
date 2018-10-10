
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


struct Coordenadas
	{
	// public:
		double x;
		double y;	
	};

typedef std::vector< std::tuple <int,int,double> > listAristas;

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

	private:
		std::vector<int> _padre;
		std::vector<int> _altura;
		std::vector< std::vector<Node> > _vertices;
		std::vector<Coordenadas> _puntos;

		// bool porPeso(std::tuple<int,int,double> a, std::tuple<int,int,double> b);

};

#endif