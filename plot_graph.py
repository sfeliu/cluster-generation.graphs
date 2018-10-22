import csv
import matplotlib.pyplot as plt
import networkx as nx
from itertools import count
from random import randint


with open('grafo2_nodos.csv', 'r') as csvfile:
	nodos = []
	for row in csv.reader(csvfile, delimiter = ','):
		nodos.append((float(row[0]),float(row[1])))

with open('grafo2_clu_11_7.000000_7.000000.csv', 'r') as csvfile:
	aristas = []
	for row in csv.reader(csvfile, delimiter = ','):
		aristas.append((int(row[0]),int(row[1])))

with open('grafo2_padres_11_7.000000_7.000000.csv', 'r') as csvfile:
	padre = []
	for row in csv.reader(csvfile, delimiter = ','):
		padre.append(int(row[0]))

colors = []
for i in range(max(padre)+1):
	colors.append("#%06X" % randint(0, 0xFFFFFF))

G = nx.Graph()

for index in range(len(nodos)):
	G.add_node(index, pos = nodos[index])

for index in range(len(aristas)):
	G.add_edge(aristas[index][0], aristas[index][1])

color_map = []
for n in G:
	color_map.append(colors[padre[int(n)]])


pos=nx.get_node_attributes(G,'pos')
nx.draw(G, pos,node_size = 50, node_color = color_map)
plt.show()