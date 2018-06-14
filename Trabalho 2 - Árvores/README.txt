INF 213 - Trabalho 2
Nome: Rodrigo Eduardo de Oliveira Bauer Chichorro
Matrícula: 92535

Fontes de consulta:
	Código antigo de INF 112 para implementar o insertionSort

1) Ordem de complexidade:
	Árvore: o programa calcula o número de movimentos através de uma versão modificada
do método insert. Ao comparar a versão modificada do método com a versão original, as operações adicionais realizadas pela versão modificada estão dentro de laços/loops que já existiam a versão original. Logo, a ordem de complexidade do método insert() continua sendo log(n). Como fazemos n inserções na árvore, a ordem de complexidade é n*log(n).
	Ordenar: Como é apenas uma versão ligeiramente modificada do insertionSort, a orden=m de complexidade é a mesma do insertionSort: n^2 (n ao quadrado).

2) Tempo de processamento de várias entradas aleatórias:
	Criei um programa simples que utiliza a função rand() para gerar uma sequência de números
para aos testes.

	Método		ARVORE 			ORDENAR
	Tamanho	  
		 
	500		62578			62578
			real    0m0.005s	real    0m0.005s
			user    0m0.005s	user    0m0.001s
			sys     0m0.000s 	sys     0m0.004s

	1000		250787			250787
			real    0m0.006s	real    0m0.007s
			user    0m0.006s	user    0m0.004s
			sys     0m0.000s	sys     0m0.003s
	
	2000	 	958054			958054
			real    0m0.006s	real    0m0.009s
			user    0m0.006s	user    0m0.009s
			sys     0m0.000s	sys     0m0.000s

	100000		2492262209		2492262209
			real    0m0.050s	real    0m5.574s
			user    0m0.046s	user    0m5.575s
			sys     0m0.004s	sys     0m0.000s

	2000000		1000028784054		não foi testado.
			real    0m2.311s
			user    0m2.283s
			sys     0m0.028s


3) Conclusão: Concluímos que árvores, assim como outras estruturas de dados, possuem diversas aplicações inusitadas. É interessante também notar que podemos tirar conclusões sobre um uso do insertionSort mesmo sem ordenar o vetor. 

















