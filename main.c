/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:  Arquivo principal do campo minado.
 *
 *        Version:  1.0
 *        Created:  20-01-2009 14:39:31
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Psycho Mantys (P.M.), psycho.mantys(.AT,)gmail dot com
 *
 * =====================================================================================
 */
/** 
* @file main.c
* @brief Um jogo de campo minado feito para o terminal.
* @author Psycho Mantys
* @date 2009-01-23
*/

/* #####   HEADER FILE INCLUDES   ################################################### */
#include "Campo_Minado.h"
#include <stdio.h>
#include <stdlib.h>

/* #####   MACROS  -  LOCAL TO THIS SOURCE FILE   ################################### */
#ifdef __win32__
	#define CLEAR "cls"
#else
	#define CLEAR "clear"
#endif

/* #####   PROTOTYPES  -  LOCAL TO THIS SOURCE FILE   ############################### */
void display_game( cm_t* jogo , char *coluna );

int main ( int argc, char *argv[] ){
	int x,y, qtdBombas , opcao ;

	/* Cria um jogo */
	cm_t *jogo;

	system(CLEAR);
	do{
		printf("Bem vindo ao jogo do campo minado!!\nDigite o tamanho do seu jogo e a quantidade de bombas:(x y qtdBombas):\n");
		scanf("%d %d %d",&x,&y,&qtdBombas);

		jogo = cm_create_game( x , y , qtdBombas );
		system(CLEAR);
		if ( ! jogo )
			printf("Erro ao criar jogo. Passe valores certos!\n");
	}
	while ( ! jogo ) ;

	cm_make_field( jogo );

	while ( ! cm_isEnd(jogo) ){
		system(CLEAR);
		display_game(jogo, " | " );

		printf("Escolha a sua ação:\n1 ) Arriscar um campo.\n2 ) Colocar Bandeira.\n3 ) Sair\n4 ) Reiniciar o jogo\n");
		scanf("%d", &opcao);

		switch (opcao){
			case 1 :
				printf("Qual o campo que você quer arriscar? ( x y )\n");
				scanf("%d %d",&x,&y);
				cm_play(jogo,x-1,y-1);
			break;
			case 2 :
				printf("Qual o campo que você quer colocar a bandeira? ( x y )\n");
				scanf("%d %d",&x,&y);
				cm_add_flag(jogo,x-1,y-1);
			break;
			case 3 :
				cm_end_game(jogo);
				return EXIT_SUCCESS;
			break;
			case 4 :
				cm_make_field(jogo);
			break;

		}
	}

	system(CLEAR);
	display_game(jogo , " | " );

	if ( cm_isWinner(jogo) ){
		printf("Parabens, você ganhou!!\n");
	}else{
		printf("Você perdeu, tente de novo ;).\n");
	}

	cm_end_game(jogo);
	return EXIT_SUCCESS;
}	/* ----------  end of function main  ---------- */

/* #####   FUNCTION DEFINITIONS  -  LOCAL TO THIS SOURCE FILE   ##################### */
/** 
* @brief Função que mostra na tela do console o campo.
* 
* @param jogo	O jogo que você deseja mostrar
*
* @param coluna	Uma string que sera colocada entre as colunas do campo.
* Serve como separador.
*/
void display_game( cm_t* jogo , char* coluna ){
	int i,j;
	
	printf("   %s",coluna);
	for ( i=0 ; i<jogo->Xmax ; ++i ){
		printf("%2d %s",i+1,coluna);
	}
	printf("\n");
	for ( i=0 ; i<jogo->Ymax ; ++i ){
		printf("%2d %s", i+1 , coluna );
		for ( j=0 ; j<jogo->Xmax ; ++j ){
			printf(" %c %s", jogo->display[i][j] , coluna );
		}
		printf("\n");
	}
}

