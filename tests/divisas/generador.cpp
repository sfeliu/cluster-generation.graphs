#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <algorithm>
#include <string>
#include <math.h>

#include <chrono>
#include <time.h>
using namespace std;

void generarMatriz(int N, int inicio_del_ciclo, int longitud_ciclo){
	cout << N << " "<< inicio_del_ciclo << " "<< longitud_ciclo << " "<< endl;
	int k = inicio_del_ciclo;

	vector< vector <double> > matrix(N,vector<double> (N, 0.01));
	int i = 1;
	
	while(i < longitud_ciclo){
		matrix[k][k+1] = 2;
		i++;
		k++;
	}
	matrix[k][inicio_del_ciclo] = 2;
	
	cout << "Inicio generacion de grafos: " << endl;
	ofstream grafo (to_string(N)+to_string(inicio_del_ciclo)+to_string(longitud_ciclo)+".csv");
	grafo << N<<endl;
	for(size_t fil = 0; fil < N; fil++)
	{
		grafo << matrix[fil][0];
		for(size_t col = 1; col < N; col++)
		{
			grafo << ",";
			grafo << matrix[fil][col];
		}
		grafo << endl;
	}
	
	cout << "Termino generacion de grafos: " << endl;
}

int main()
{	
	int inicio_del_ciclo = 0;
	int cantidad_de_nodos = 5;
	int longitud_ciclo = 1;
	for (int j = 1; j < cantidad_de_nodos; j++)
	{
		for(int h = inicio_del_ciclo ; h <= j; h++)
		{
			for(int l = longitud_ciclo; l <= j-h ; l++)
			{
				cout << "asd: "<< j-h<<endl;
				generarMatriz(j,h,l);
			}	
		}
	}
	return 0;
}