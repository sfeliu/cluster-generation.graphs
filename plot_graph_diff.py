import csv
import matplotlib.pyplot as plt
import networkx as nx
from itertools import count
from random import randint


with open('grafo2_nodos.csv', 'r') as csvfile:
	nodos = []
	for row in csv.reader(csvfile, delimiter = ','):
		nodos.append((float(row[0]),float(row[1])))

#with open('grafo2_agm.csv', 'r') as csvfile:
#	mylist = []
#	for row in csv.reader(csvfile, delimiter = ','):
#		mylist.append((int(row[0]),int(row[1])))


with open('grafo2_clu_11_f9.000000_ds9.000000_diff.csv', 'r') as csvfile:
	mylist_diff = []
	for row in csv.reader(csvfile, delimiter = ','):
		mylist_diff.append((int(row[0]),int(row[1])))

with open('grafo2_clu_11_f9.000000_ds9.000000_diff1.csv', 'r') as csvfile:
	mylist_diff1 = []
	for row in csv.reader(csvfile, delimiter = ','):
		mylist_diff1.append((int(row[0]),int(row[1])))


with open('grafo2_clu_11_f9.000000_ds9.000000_diff2.csv', 'r') as csvfile:
	mylist_diff2 = []
	for row in csv.reader(csvfile, delimiter = ','):
		mylist_diff2.append((int(row[0]),int(row[1])))


G = nx.Graph()

for index in range(len(nodos)):
	G.add_node(index, pos = nodos[index])

#for index in range(len(mylist)):
#	G.add_edge(mylist[index][0], mylist[index][1], color = 'b')



for index in range(len(mylist_diff)):
	G.add_edge(mylist_diff[index][0], mylist_diff[index][1], color = 'g')

for index in range(len(mylist_diff1)):
	G.add_edge(mylist_diff1[index][0], mylist_diff1[index][1], color = 'b')

for index in range(len(mylist_diff2)):
	G.add_edge(mylist_diff2[index][0], mylist_diff2[index][1], color = 'r')

edges = G.edges()
colors = [G[u][v]['color'] for u,v in edges]

color_map = []
for n in G:
	color_map.append('black')


pos=nx.get_node_attributes(G,'pos')
#nx.draw(G, pos, node_size = 15, node_color = color_map, alpha = 0.9, width = 1)

nx.draw(G, pos, node_size = 10, edge_color = colors, node_color = color_map, alpha = 0.9, width = 3)
#nx.draw(G, pos, node_size = 300, edge_color = colors, node_color = color_map, alpha = 0.9, width = 3, with_labels = True, font_color = 'y', font_weight = 'heavy')

plt.show()

