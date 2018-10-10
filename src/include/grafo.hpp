
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


struct Cordenadas
	{
	// public:
		double x;
		double y;	
	};

typedef std::vector< std::tuple <int,int,double> > listAristas;

class Grafo
{
	struct node
	{
		double weight;
		int id;
	};

	

	public:
		std::vector<Cordenadas>& puntos();
		Grafo();
		~Grafo();
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
		std::vector<int> padre;
		std::vector<int> altura;
		std::vector< std::vector<node*> > vertices;

		std::vector<Cordenadas> _puntos;

};

#endif