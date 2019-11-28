// sequência lógica:

// carregar lista de pokemons
    // padrão: nome,ataque,defesa,velocidade,energia,tipo1,tipo2(pode ser vazio) //dados base
// foreach player
    // for i < 3
        // seleciona pokemon
        // seleciona golpes

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

#define QTD_ATAQUE_RAPIDO 10 //CHANGEME
#define QTD_ATAQUE_CARREGADO 10 //CHANGEME
#define QTD_POKEMON 151
#define QTD_POKEMON_POR_JOGADOR 3

struct ataque_rapido_struct
{
char nome[50];
float ataque;
float defesa;
float velocidade;
float energia;
};

struct ataque_carregado_struct
{
char nome[50];
float ataque;
float defesa;
float velocidade;
float energia;
};

struct pokemon_struct
{
char nome[50];
float ataque;
float defesa;
float velocidade;
float energia;
};

struct selected_pokemon_struct
{
struct pokemon_struct *pokemon;
struct ataque_rapido_struct *ataque_rapido;
struct ataque_carregado_struct *ataque_carregado;
};


// função para ler do arquivo
// recebe o vetor que ela irá preencher
// retorna a quantidade de elementos preenchidos
int carregaAtaqueRapido(struct ataque_rapido_struct aux_ataque_rapido[QTD_ATAQUE_RAPIDO]){
	// abre o arquivo para leitura
	FILE * arq = fopen("ataque_rapido.txt", "r");

	if(arq != NULL)
	{
		int indice = 0;
		while(1)
		{
			struct ataque_rapido_struct p;

			// fread ler os dados
			// retorna a quantidade de elementos lidos com sucesso
			size_t r = fread(&p, sizeof(struct ataque_rapido_struct), 1, arq);

			// se retorno for menor que o count, então sai do loop
			if(r < 1)
				break;
			else
				aux_ataque_rapido[indice++] = p;
                printf("%s\n",p.nome);
		}
		fclose(arq); // fecha o arquivo
		return indice;
	}
	else
	{
		printf("\nErro ao abrir o arquivo para leitura!\n");
		exit(1); // aborta o programa
	}
}

// função para ler do arquivo
// recebe o vetor que ela irá preencher
// retorna a quantidade de elementos preenchidos
int carregaAtaqueCarregado(struct ataque_carregado_struct aux_ataque_carregado[QTD_ATAQUE_CARREGADO]){
	// abre o arquivo para leitura
	FILE * arq = fopen("ataque_carregado.txt", "r");

	if(arq != NULL)
	{
		int indice = 0;
		while(1)
		{
			struct ataque_carregado_struct p;

			// fread ler os dados
			// retorna a quantidade de elementos lidos com sucesso
			size_t r = fread(&p, sizeof(struct ataque_carregado_struct), 1, arq);

			// se retorno for menor que o count, então sai do loop
			if(r < 1)
				break;
			else
				aux_ataque_carregado[indice++] = p;
                printf("%s\n",p.nome);
		}
		fclose(arq); // fecha o arquivo
		return indice;
	}
	else
	{
		printf("\nErro ao abrir o arquivo para leitura!\n");
		exit(1); // aborta o programa
	}
}

// função para ler do arquivo
// recebe o vetor que ela irá preencher
// retorna a quantidade de elementos preenchidos
int carregaPokemon(struct pokemon_struct aux_pokemon[QTD_POKEMON]){
	// abre o arquivo para leitura
	FILE * arq = fopen("pokemon.txt", "r");

	if(arq != NULL)
	{
		int indice = 0;
		while(1)
		{
			struct pokemon_struct p;

			// fread ler os dados
			// retorna a quantidade de elementos lidos com sucesso
			size_t r = fread(&p, sizeof(struct pokemon_struct), 1, arq);

			// se retorno for menor que o count, então sai do loop
			if(r < 1)
				break;
			else
				aux_pokemon[indice++] = p;
                printf("%s\n",p.nome);
		}
		fclose(arq); // fecha o arquivo
		return indice;
	}
	else
	{
		printf("\nErro ao abrir o arquivo para leitura!\n");
		exit(1); // aborta o programa
	}
}

// função para escrever os elementos de uma struct no arquivo
void salvaPokemon(struct pokemon_struct aux_pokemon[])
{
	int i;
	int len_vet = sizeof(struct pokemon_struct) - 1; // tamanho do vetor
	FILE * arq;

	// abre o arquivo para escrita no modo append (adiciona ao final)
	arq = fopen("pokemon.txt", "a+");

	if(arq != NULL)
	{
		for(i = 0; i < len_vet; i++)
			// escreve cada elemento do vetor no arquivo
			fwrite(&aux_pokemon[i], sizeof(struct pokemon_struct), 1, arq);
		fclose(arq); // aborta o programa
	}
	else
	{
		printf("\nErro ao abrir o arquivo para leitura!\n");
		exit(1); // aborta o programa
	}
}

int main(){
    // declaração dos vetores a serem carregados
    struct ataque_rapido_struct ataque_rapido[QTD_ATAQUE_RAPIDO];
    struct ataque_carregado_struct ataque_carregado[QTD_ATAQUE_CARREGADO];
    struct pokemon_struct pokemon[QTD_POKEMON];
    struct selected_pokemon_struct jogador1[QTD_POKEMON_POR_JOGADOR];
    //teste salvar dados
    struct pokemon_struct pokemon1;
    strcpy(pokemon1.nome,"Zubat");
    pokemon1.ataque = 1;
    pokemon1.defesa = 1;
    pokemon1.velocidade = 1;
    pokemon1.energia = 1;
    salvaPokemon(&pokemon1);
    // carregamento dos vetores
    carregaPokemon(pokemon);
    // carregaAtaqueRapido(ataque_rapido);
    // carregaAtaqueCarregado(ataque_carregado);
    getchar();
    return 0;
}