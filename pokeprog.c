// sequência lógica:

// carregar lista de pokemons
    // padrão: nome,ataque,defesa,velocidade,energia,tipo1,tipo2(pode ser vazio) //dados base
// carregar lista de ataques rapidos
    // padrão: nome,dano,tipo,ganho_de_energia //dados base
// carregar lista de ataques carregados
    // padrão: nome,dano,tipo,perda_de_energia //dados base
// carregar lista de elementos
    // padrão: normal,fight,2 ,poison,ground,rock,bug,ghost,steel,fire,water,grass,electr,psychic,ice,dragon,dark,17 //dados base
// carregar lista de climas
    // padrão: sunny //dados base

// foreach player
    // for i < 3
        // seleciona pokemon
			// entrada: id da pokedex
        // seleciona golpes
			//entrada: id do golpe

// include de funções
#include "pokedef.h"
#include "pokecarregamento.c"
#include "pokeselecao.c"
#include "pokebatalha.c"
#include "poketeste.c"

//////////////////////MAIN//////////////////////


int main(){
	// para o fator aleatorio
	srand(time(NULL));
    // declaração dos vetores a serem carregados
	tipo_struct tipo[QTD_TIPO];
	ataque_struct ataque_rapido[QTD_ATAQUE_RAPIDO];
	ataque_struct ataque_carregado[QTD_ATAQUE_CARREGADO];
	pokemon_struct pokemon[QTD_POKEMON];
	pokemon_selecionado_struct pokemon_selecionado[QTD_JOGADOR][QTD_POKEMON_POR_JOGADOR];
	clima_struct clima[QTD_CLIMA];
	int clima_selecionado;
    // carregamento dos dados
    carregaTipo(tipo);
    carregaClima(clima, tipo);
    carregaAtaqueRapido(ataque_rapido, tipo);
    carregaAtaqueCarregado(ataque_carregado, tipo);
    carregaPokemon(pokemon, tipo);
    carregaListaRapido(pokemon);
    carregaListaCarregado(pokemon);
	// processo de seleção
	selecionaPokemons(pokemon_selecionado, pokemon, ataque_rapido, ataque_carregado, clima, tipo);
	selecionaClima(&clima_selecionado, clima, tipo);
	// batalha
	iniciaBatalha(pokemon_selecionado, &clima[clima_selecionado], tipo);
	// // teste
	// testePokemon(&pokemon_selecionado[0][0]);
	// espera no fim
    // getchar();
    return 0;
}