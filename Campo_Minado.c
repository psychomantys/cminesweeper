/*
 * =====================================================================================
 *
 *       Filename:  Campo_Minado.c
 *
 *    Description:  Implementação das funções uteis do campo minado.
 *
 *        Version:  1.0
 *        Created:  20-01-2009 15:10:58
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Psycho Mantys (P.M.), psycho.mantys(.AT,)gmail dot com
 *
 * =====================================================================================
 */
/** 
* @file Campo_Minado.c
* @brief Implementações da das funções uteis do campo minado.
* @author Psycho Mantys
* @date 2009-01-22
*/

/* #####   HEADER FILE INCLUDES   ################################################### */
#include "Campo_Minado.h"
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

/* #####   PROTOTYPES  -  LOCAL TO THIS SOURCE FILE   ############################### */
/** 
* @brief Funções que preenche o jogo com bombas e tambem deixa os campos ao lado certos.
* 
* @param jogo	O jogo que você quer preencher.
* 
* @return 	O jogo ja processado.
*/
cm_t* fill_field_with_bombs( cm_t* jogo );

/** 
* @brief Funação recursiva que libera campos vazio no display do jogo. Caso seja um 
* BLANK_FIELD, ele atualiza a matriz que contem o front-end do jogo e atualiza o numero
* de casas jogadas(cm_t->step++). Depois, se o range for valido, lan?a ela mesma para
* as casas ao lado.
* 
* @param jogo	Jogo atual.
*
* @param x	A cordenada "x" do ponto que você quer liberar. Tem que ser uma
* coordenada valida(não negativa e menor que INT_MAX da stdlib.h).
*
* @param y	A cordenada "y" do ponto que você quer liberar. Tem que ser uma
* coordenada valida(não negativa e menor que INT_MAX da stdlib.h).
*
* @return	O jogo que você passou. Em caso de erro, retorna NULL.
*/
void recursive_blank_test( cm_t* jogo , int x , int y );

/* #####   FUNCTION DEFINITIONS  -  EXPORTED FUNCTIONS   ############################ */
cm_t* cm_create_game( const unsigned int x , const unsigned int y , const unsigned int qtdBombas ){
	unsigned int i;

	/* Checagem de bombas a mais que o campo pode aguentar */
	if ( x*y < qtdBombas ){
		return NULL;
	}

	cm_t* jogo = (cm_t* )malloc( sizeof(cm_t) );
	jogo->Xmax = x ;
	jogo->Ymax = y ;
	jogo->bombas = qtdBombas ;
	jogo->lose = false ;

	/* Alloca memoria para o campo e display */
	jogo->campo = (char **)malloc( sizeof(char*)*y );
	jogo->display = (char **)malloc( sizeof(char*)*y );
	for ( i=0 ; i<y ; ++i ){
		jogo->campo[i] =  (char *)malloc(sizeof(char)*x);
		jogo->display[i] = (char *)malloc(sizeof(char)*x);
	}
	return jogo;
}

cm_t *cm_add_flag( cm_t *jogo , const unsigned int x , const unsigned int y ){
	/* testa se é uma jogada valida */
	if ( x >= jogo->Xmax || y >= jogo->Ymax )
		return NULL;

	if ( jogo->display[y][x] == BLANK_DISPLAY ){
		jogo->display[y][x] = FLAG_DISPLAY ;
		jogo->step++;
	}else{
		return NULL ;
	}
	return jogo ;
}

cm_t* cm_play( cm_t *jogo , const unsigned int x , const unsigned int y ){
	/* testa se é uma jogada valida */
	if ( x >= jogo->Xmax || y >= jogo->Ymax )
		return NULL;

	/* Testa se você jogou em uma bomba. Caso sim, você perdeu */
	if ( jogo->campo[y][x] == BOMB ){
		jogo->lose = true ;
		jogo->display[y][x] = jogo->campo[y][x] ;
	}
	if ( jogo->display[y][x] == BLANK_DISPLAY ){
		switch ( jogo->campo[y][x] ) {
			case BLANK_FIELD :
				recursive_blank_test( jogo , x , y );
			break;
			case '1' :
			case '2' :
			case '3' :
			case '4' :
			case '5' :
			case '6' :
			case '7' :
			case '8' :
				/* E um numero, revelar ele no vetor display */
				jogo->display[y][x] = jogo->campo[y][x];
				jogo->step++ ;
			break ;

		}
	}else{
		return NULL;
	}
	return jogo;
}

void cm_end_game( cm_t* jogo ){
	unsigned int i;
	/* desaloca matriz do campo */
	for ( i=0 ; i<jogo->Ymax ; ++i ){
		free( jogo->campo[i] );
		free( jogo->display[i] );
	}
	free(jogo->campo);
	free(jogo->display);
	free(jogo);
}

cm_t* cm_make_field( cm_t *jogo ){

	/* initialize random seed: */
	srand ( time(NULL) );

	{
		unsigned int i,j,x,y;
		char *vetor_aux ;
		x = jogo->Xmax;
		y = jogo->Ymax;
		jogo->step = 0 ;
		jogo->max_steps = x*y ;

		/* Zera o campo */
		for ( i=0 ; i<y ; ++i ){
			vetor_aux = jogo->campo[i];
			for ( j=0 ; j<x ; ++j ){
				vetor_aux[j] = BLANK_FIELD;
			}
		}
		/* Zera o display */
		for ( i=0 ; i<y ; ++i ){
			vetor_aux = jogo->display[i];
			for ( j=0 ; j<x ; ++j ){
				vetor_aux[j] = BLANK_DISPLAY;
			}
		}
	}

	return fill_field_with_bombs( jogo );
}

bool cm_isEnd( cm_t *jogo ){
	return jogo->lose || ( jogo->max_steps==jogo->step ) ;
}

bool cm_isWinner( cm_t *jogo ){
	return ( ! jogo->lose ) && cm_isEnd( jogo ) ;
}

/* #####   FUNCTION DEFINITIONS  -  LOCAL TO THIS SOURCE FILE   ##################### */
void recursive_blank_test( cm_t* jogo , int x , int y ){
	char *vetor_aux = jogo->campo[y] , *vetor_aux2 = jogo->display[y] ;

	if ( vetor_aux2[x]==FLAG_DISPLAY && ( vetor_aux[x]>'0' && '9'>vetor_aux[x] ) ){
		vetor_aux2[x] = vetor_aux[x];
		return;
	}

	if ( vetor_aux[x] == BLANK_FIELD && vetor_aux2[x] != BLANK_FIELD ){
		if ( vetor_aux2[x] != FLAG_DISPLAY ){
			jogo->step++ ;
		}
		vetor_aux2[x] = vetor_aux[x];

		/* checa o meio */
		if ( x > 0 )
			recursive_blank_test( jogo , x-1 , y );
		if ( x < jogo->Xmax-1 )
			recursive_blank_test( jogo , x+1 , y );

		/* Checa embaixo */
		y-- ;
		if ( y >= 0 ){
			recursive_blank_test( jogo , x , y );

			if ( x > 0 )
				recursive_blank_test( jogo , x-1 , y );
			if ( x < jogo->Xmax-1 )
				recursive_blank_test( jogo , x+1 , y );
		}

		/* Checa em cima */
		y+=2 ;
		if ( y <= jogo->Ymax-1 ){
			recursive_blank_test( jogo , x , y );

			if ( x > 0 )
				recursive_blank_test( jogo , x-1 , y );
			if ( x < jogo->Xmax-1 )
				recursive_blank_test( jogo , x+1 , y );
		}
	}else{
		if( vetor_aux2[x]==BLANK_DISPLAY && '0'<vetor_aux[x] && vetor_aux[x]<'9' ){
			jogo->step++ ;
			vetor_aux2[x] = vetor_aux[x];
		}
	}
}

cm_t* fill_field_with_bombs( cm_t* jogo ){
	unsigned int i,x,y,bombas;
	char *vetor_aux , **campo ;
	campo = jogo->campo ;
	bombas = jogo->bombas;
	x = jogo->Xmax;
	y = jogo->Ymax;
	/* Coloca bombas no campo */
	for ( i=0 ; i<bombas ; ++i ){
		int temp1 = random() % y ;
		int temp2 = random() % x ;
		vetor_aux = campo[temp1];
		while( vetor_aux[temp2] != BLANK_FIELD ){
			temp1 = random() % y;
			temp2 = random() % x;
			vetor_aux = campo[temp1];
		}
		vetor_aux[temp2] = BOMB ;
		/* tenta acertar numeros ao redor */
		/* checa o meio */
		if (temp2 > 0 && vetor_aux[temp2-1] != BOMB ){
			vetor_aux[temp2-1]+=1;
		}
		if (temp2 < x-1 && vetor_aux[temp2+1] != BOMB ) {
			vetor_aux[temp2+1]+=1;
		}

		/* Checa embaixo */
		temp1--;
		if ( temp1 >= 0 ){
			vetor_aux =  campo[ temp1 ] ;
			if ( vetor_aux[temp2] != BOMB ){
				vetor_aux[temp2]+=1;
			}
			if (temp2 > 0 && vetor_aux[temp2-1] != BOMB ){
				vetor_aux[temp2-1]+=1;
			}
			if (temp2 < x-1 && vetor_aux[temp2+1] != BOMB ){
				vetor_aux[temp2+1]+=1;
			}
		}

		/* Checa em cima */
		temp1+=2;
		if ( temp1 <= y-1 ){
			vetor_aux =  campo[ temp1 ] ;
			if ( vetor_aux[temp2] != BOMB )
				vetor_aux[temp2]+=1;
			if (temp2 > 0 && vetor_aux[temp2-1] != BOMB )
				vetor_aux[temp2-1]+=1;
			if (temp2 < x-1 && vetor_aux[temp2+1] != BOMB )
				vetor_aux[temp2+1]+=1;
		}
	}
	/* Retorna o jogo */
	return jogo ;
}

