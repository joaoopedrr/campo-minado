#include <stdio.h>
#include <stdlib.h>
#include <time.h>





/* 

	eBomba 0 ou 1
	estaAberta 0 ou 1
	vizinhos 0 a 4

*/





typedef struct{
	int eBomba;
	int estaAberta;
	int vizinhos;
} Celula;





// Variáveis globais
Celula jogo[10][10];
int l, c, tam = 10;



// procedimento para inicializar a matriz do jogo
void inicializarJogo(){
		for(l = 0; l < tam; l++){
			for(c = 0; c < tam; c++){
				jogo[l][c].eBomba = 0;
				jogo[l][c].estaAberta = 0;
				jogo[l][c].vizinhos = 0;
			}
		}
}





// procedimento para sortear as bombas
void sortearBombas(int n){
	int i;
	srand(time(NULL));
	for(i = 0; i < n; i++){
		l = rand() % tam;
		c = rand() % tam;
		if (jogo[l][c].eBomba == 0)
			jogo[l][c].eBomba = 1;
		else
			i--;	
	}
}






/*
	Função que diz se um par de coordenadas é válido ou não
	1 - é valido
	0 - não é valido
*/




int coordenadaEhValida(int l, int c){
	if (l >= 0 && l < tam && c >= 0 && c < tam)
		return 1;
	else
		return 0;
}






/*
 função que retorna a quantidade de bombas na vizinhança de l c
 n == quantidade de bombas
*/




int quantBombasVizinhas(int l, int c){
	
	
	/*
	
		l - 1 e c
		l + 1 e c
		l e c + 1
		l e c - 1
		
	*/
	
	
	
	int quantidade = 0;
	
	if (coordenadaEhValida(l - 1, c) && jogo[l - 1][c].eBomba)
		quantidade++;
	if (coordenadaEhValida(l + 1, c) && jogo[l + 1][c].eBomba)
		quantidade++;
	if (coordenadaEhValida(l, c + 1) && jogo[l][c + 1].eBomba)
		quantidade++;
	if (coordenadaEhValida(l, c - 1) && jogo[l][c - 1].eBomba)
		quantidade++;
	return quantidade;
}






// procedimento para contar as bombas vizinhas
void contarBombas(){
	for(l = 0; l < tam; l++){
			for(c = 0; c < tam; c++)
				jogo[l][c].vizinhos = quantBombasVizinhas(l, c);
		}
}







// procedimento para imprimir o jogo
void imprimir(){
	
	
	printf("\n\n\t   ");
	for(l = 0; l < tam; l++)
		printf(" %d  ", l);   // Índices das colunas
	printf("\n\t  -----------------------------------------\n");
	for(l = 0; l < tam; l++){
			printf("\t%d |", l);		
			for(c = 0; c < tam; c++){
				if (jogo[l][c].estaAberta){
					if (jogo[l][c].eBomba)
						printf(" * ");
					else
						printf(" %d ", jogo[l][c].vizinhos);
				}
				else
					printf("   ");
				printf("|");
			}
			printf("\n\t  -----------------------------------------\n");
	}
}







// procedimento para abrir a coordenada digitada pelo usuário
void abrirCelula(int l, int c){
	
	
	if (coordenadaEhValida(l, c) == 1 && jogo[l][c].estaAberta == 0){
		jogo[l][c].estaAberta = 1;
		if(jogo[l][c].vizinhos == 0){
			
			
			/*
			l - 1 e c acima
			l + 1 e c baixo
			l e c + 1 direita
			l e c - 1 esquerda
			*/
			
			
			
			abrirCelula(l - 1, c);
			abrirCelula(l + 1, c);
			abrirCelula(l, c + 1);
			abrirCelula(l, c - 1);
		}
	}
	
}











/*

	Função para verificar vitória
	1- ganhou
	0 - não ganhou ainda

*/




int ganhou(){
	
	int quantidade = 0;
	
	
	for(l = 0; l < tam; l++){
			for(c = 0; c < tam; c++){
				if (jogo[l][c].estaAberta == 0 && jogo[l][c].eBomba == 0)
					quantidade++;
			}
	}
	return quantidade;
}












// procedimento jogar que faz a leitura das coordenadas
void jogar(){
	
	
	int linha, coluna;
	
	do{
		imprimir();
		do{
			printf("\n Digite as coordenadas de linha e coluna:  \n");
			scanf("%d%d", &linha, &coluna);
			
			if (coordenadaEhValida(linha, coluna) == 0 || jogo[linha][coluna].estaAberta == 1){
				printf("\nCoordenada inválida ou já aberta! Digite novamente!\n");
			}
		} while(coordenadaEhValida(linha, coluna) == 0 || jogo[linha][coluna].estaAberta == 1);
		abrirCelula(linha, coluna);
	} while(ganhou() != 0 && jogo[linha][coluna].eBomba == 0);
	
	if (jogo[linha][coluna].eBomba == 1){
		printf("\n\tQue pena! Você perdeu !!\n");
	}
	else
		printf("\n\tPARABÉNS! Você ganhou !!\n");
	imprimir();
}








int main(){
	
	
	
	int opcao;
	
	
	do{
		inicializarJogo();
		sortearBombas(10);
		contarBombas();
		printf("\n\t\t\t CAMPO MINADO\n");
		jogar();
		
		printf("\nDigite 1 para jogar novamente: \n");
		scanf("%d", &opcao);
	} while(opcao == 1);
	
	
	
	
	
	return 0;
}

