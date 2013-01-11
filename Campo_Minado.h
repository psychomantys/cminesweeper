/*
 * =====================================================================================
 *
 *       Filename:  Campo_Minado.h
 *
 *    Description:  Header que contem funções uteis para gerar o campo.
 *
 *        Version:  1.0
 *        Created:  20-01-2009 14:42:08
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Psycho Mantys (P.M.), psycho.mantys(.AT,)gmail dot com
 *
 * =====================================================================================
 */
/** 
* @file Campo_Minado.h
* @brief Funções uteis e gerais do campo minado.
* @author Psycho Mantys
* @date 2009-01-21
*/
#ifndef _CAMPO_MINADO_H
#define _CAMPO_MINADO_H
/* #####   HEADER FILE INCLUDES   ################################################### */
#include <stdbool.h>

/* #####   EXPORTED MACROS   ######################################################## */
/**
 * \brief Macro que representa o espaço de uma bomba.
 */ 
#define BOMB		'*'
/**
 * \brief Macro que representa o espaço vazio no campo.
 */ 
#define BLANK_FIELD	'0'
/**
 * \brief Macro que representa o espaço vazio no display.
 */ 
#define BLANK_DISPLAY	' '
/**
 * \brief Macro que representa uma flag no campo.
 */ 
#define FLAG_DISPLAY	'F'

/* #####   EXPORTED TYPE DEFINITIONS   ############################################## */
typedef struct cm_t cm_t;

/* #####   EXPORTED DATA TYPES   #################################################### */
/** 
* @brief Esse é o jogo de um campo minado. Todas as informações sobre o jogo atual
* estão em uma dessa estrutura.
*/
struct cm_t {
	/** 
	* @brief Vetor que contem o estado atual do campo. Esse vetor é util para exibição.
	*/
	char **display;	
	/** 
	* @brief Numero de bombas no jogo atual.
	*/
	unsigned int bombas;
	/** 
	* @brief Tamanho no eixo X do campo
	*/
	int Xmax;
	/** 
	* @brief Tamanho no eixo Y do campo
	*/
	int Ymax;
	/** 
	* @brief Quantas casas do jogo já foram preenchidas.
	*/
	unsigned int step;
	/** 
	* @brief Variavel que define se o jogo foi perdido, caso ela seja diferente de
	* 'true' ( condição  "! lose" ). Caso ela seja 'false', o jogo ainda não esta
	* perdido.
	*/
	bool lose;
	/** 
	* @brief Variavel que contem a quantidade maxima de campos no jogo.
	*/
	unsigned long int max_steps;
	/** 
	* @brief Vetor que contem o endereço da matriz de 2 dimensões que contem o campo.
	*/
	char **campo;
};
/* #####   EXPORTED FUNCTION DECLARATIONS   ######################################### */
/** 
* @brief Cria um jogo. Essa função deve ser chamada toda vez que você quiser criar
* um jogo. Para terminar o jogo, use \a end_game
* @param	x		O \a "x" maximo do campo.
* @param	y		O \a "y" maximo do campo.
* @param	qtdBombas	Quantidade de bombas que o campo vai ter.
*
* @return	Retorna o jogo criado. Ele ainda precisa ser preenchido o campo.
*/
cm_t* cm_create_game( const unsigned int x , const unsigned int y , const unsigned int qtdBombas ) ;

/** 
* @brief Função que faz uma jogada em um campo vazio ou com bandeira.
* 
* @param jogo	O jogo no qual que você quer jogar.
* @param x	A coordenada \a "x" da posição que você quer jogar.
* @param y	A coordenada \a "y" da posição que você quer jogar.
*
* @return	Retorna o mesmo endereço do jogo. Retorna NULL se um erro ocorreu.
*/
cm_t* cm_play( cm_t *jogo , const unsigned int x , const unsigned int y );

/** 
* @brief Finaliza o jogo.
*
* @param	jogo	A variavel que contem o jogo que você esta encerrando.
*/
void cm_end_game( cm_t* jogo );

/** 
* @brief 
* Essa função preenche o campo do jogo campo minado que esta sendo passado.
* Essa função inicializa o vetor display e campo, ignorando qualquer coisa que esteja
* no vetor antes. Também inicializa os membros do jogo, setando para os valores de inicio
* de jogo.
*
* @param jogo	O jogo atual que você quer gerar um campo.
* 
* @return	Retorna o mesmo endereço do jogo. Retorna NULL se um erro ocorreu.
*/
cm_t* cm_make_field( cm_t *jogo );

/** 
* @brief Função que indica se o jogo acabou ou não.
* 
* @param jogo	O jogo que você quer saber o resultado.
* 
* @return	Retorna 'false' se o jogo ainda não acabou, ou 'true' caso
* contrario. ex:. "if ( cm_isEnd(jogo) )".
*/
bool cm_isEnd( cm_t *jogo );

/** 
* @brief Função que indica se o jogo foi vencido ou não.
* 
* @param jogo	O jogo que você quer saber o resultado.
* 
* @return	Retorna 'false' se o jogo ainda não acabou, ou 'true' caso
* contrario. ex:. "if ( cm_isEnd(jogo) )".
*/
bool cm_isWinner( cm_t *jogo );

/** 
* @brief Função que adiciona uma bandeira em um lugar do campo.
* 
* @param jogo	O jogo que você quer adicionar a bandeira.
*
* @param x	A coordenada \a "x" de onde você quer adicionar a bandeira.
*
* @param y	A coordenada \a "y" de onde você quer adicionar a bandeira.
* 
* @return	Retorna o jogo. Caso a operação não tenha sido feita, retorna NULL.
*/
cm_t *cm_add_flag( cm_t *jogo , const unsigned int x , const unsigned int y );

#endif /* _CAMPO_MINADO_H */

