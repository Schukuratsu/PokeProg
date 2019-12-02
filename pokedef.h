// evita duplicação
#ifndef POKEDEF
#define POKEDEF

// includes padrão
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<math.h>

// configurações de arquivos de dados
#define QTD_TIPO 18
#define QTD_CLIMA 7
#define TIPOS_POR_CLIMA 3
#define QTD_ATAQUE_RAPIDO 30
#define QTD_ATAQUE_CARREGADO 129
#define QTD_POKEMON 151
// configurações do jogo
#define QTD_POKEMON_POR_JOGADOR 3
#define QTD_JOGADOR 2
#define QTD_ESCUDO 2
#define NIVEL_PASSO 0.5
#define NIVEL_MIN 0
#define NIVEL_MAX 40
// coisas aleatórias
#define TAM_STRING 50

struct tipo_struct
{
char nome[TAM_STRING];
float eficacia[QTD_TIPO];
};
typedef struct tipo_struct tipo_struct;

struct clima_struct
{
char nome[TAM_STRING];
int tipo[TIPOS_POR_CLIMA];
};
typedef struct clima_struct clima_struct;

struct ataque_struct
{
char nome[TAM_STRING];
float dano;
int tipo;
float energia;
};
typedef struct ataque_struct ataque_struct;

struct pokemon_struct
{
char nome[TAM_STRING];
float ataque;
float defesa;
float velocidade;
float stamina;
int tipo1;
int tipo2;
};
typedef struct pokemon_struct pokemon_struct;

struct pokemon_selecionado_struct
{
struct pokemon_struct *base; //pokemon selelcionado
struct ataque_struct *ataque_rapido; //ataque rapido selecionado
struct ataque_struct *ataque_carregado; //ataque carregado selecionado
float ps; //pontos de saude atuais
float nivel; //nivel do pokemon
float energia; //energia do pokemon
};
typedef struct pokemon_selecionado_struct pokemon_selecionado_struct;

#endif