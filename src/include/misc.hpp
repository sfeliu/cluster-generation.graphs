#ifndef _MISC_HPP_
#define _MISC_HPP_

#include "grafo.hpp"

void imprimir_agm(listAristas l);
listAristas remover_inconsistentes(listAristas l, Grafo g, double ds, double f, double diametro, int mod);
void descubrirConexoAux(int u, listAristas res, int& contador, std::vector<bool> &visitado, int& i, std::vector<int> &comp_conex);
std::vector<int> descubrirConexo(listAristas l, int n);
listAristas diff(listAristas& l1, listAristas& l2);

#endif