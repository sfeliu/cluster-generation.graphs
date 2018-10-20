import os
import sys
from random import shuffle



grafo_size = int(sys.argv[1])
ciclo_size = int(sys.argv[2])
sarting_index = 1


grafo = [[0.0001 for i in range(0,grafo_size)] for j in range(0,grafo_size)]
ciclo = [1.01 for i in range(0,ciclo_size)]
for index, peso in enumerate(ciclo[1:]):
	#print(str(index))
	#print(str((index +1) % (grafo_size-1)))
	grafo[index][(index +1) % (grafo_size-1)] = peso
grafo[ciclo_size-1][0] = 1.01
#print(grafo)
#indexs = [i for i in range(0,grafo_size)]
#shuffle(indexs)
#grafo2 = grafo
#for ind, new_index in enumerate(indexs):
#	grafo[ind] = grafo2[new_index]
with open('tests/divisas/n' + str(grafo_size) + '_c' + str(ciclo_size) + '.csv', 'w+') as f:
	f.write(str(grafo_size) + '\n')
	for node in grafo:
		f.write(str(node).replace('[', '').replace(']', '').replace(',', '') + '\n')
