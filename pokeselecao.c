#include "pokedef.h"

void listaPokemon(pokemon_struct *pokemon, tipo_struct *tipo){
    char tipo2[TAM_STRING];
    for(int i = 0; i < QTD_POKEMON; i++){
        if(pokemon[i].tipo2 == -1) 
            strcpy(tipo2,tipo[pokemon[i].tipo2].nome);
        else 
            strcpy(tipo2, "\0");
        printf("id:%d\t%s\ta:%.2f\td:%.2f\tv:%.2f\ts:%.2f\tt1:%s\tt2:%s\n", 
            i + 1, 
            pokemon[i].nome, 
            pokemon[i].ataque, 
            pokemon[i].defesa, 
            pokemon[i].velocidade, 
            pokemon[i].stamina, 
            tipo[pokemon[i].tipo1].nome, 
            tipo2
        );
    }
}

int lePokemonId(pokemon_struct *pokemon, tipo_struct *tipo){
    int id = -1;
    while(id < 1 || id > QTD_POKEMON){
        printf("\nSelecione um pokemon pelo seu ID da pokedex (0 para listar): ");
        scanf("%d", &id);
        if(id == 0) listaPokemon(pokemon, tipo);
    }
    id = id - 1;
    printf("\nPokemon selecionado: %s\n", pokemon[id].nome);
    return id;
}

void listaAtaque(ataque_struct *ataque, int qtd, tipo_struct *tipo){
    for(int i = 0; i < qtd; i++){
        printf("id:%d\t%s\td:%.2f\tt:%s\te:%.2f\n", 
            i + 1, 
            ataque[i].nome,
            ataque[i].dano,
            tipo[ataque[i].tipo].nome,
            ataque[i].energia
        );
    }
}

int leAtaqueRapido(ataque_struct *ataque_rapido, tipo_struct *tipo){
    int id = -1;
    while(id < 1 || id > QTD_ATAQUE_RAPIDO){
        printf("\nSelecione um ataque rapido pelo seu ID (0 para listar): ");
        scanf("%d", &id);
        if(id == 0) listaAtaque(ataque_rapido, QTD_ATAQUE_RAPIDO, tipo);
    }
    id = id - 1;
    printf("\nAtaque rapido selecionado: %s\n", ataque_rapido[id].nome);
    return id;
}

int leAtaqueCarregado(ataque_struct *ataque_carregado, tipo_struct *tipo){
    int id = -1;
    while(id < 1 || id > QTD_ATAQUE_CARREGADO){
        printf("\nSelecione um ataque carregado pelo seu ID (0 para listar): ");
        scanf("%d", &id);
        if(id == 0) listaAtaque(ataque_carregado, QTD_ATAQUE_CARREGADO, tipo);
    }
    id = id - 1;
    printf("\nAtaque carregado selecionado: %s\n", ataque_carregado[id].nome);
    return id;
}

float resto(float dividendo, float divisor){
    float quociente;
    quociente = dividendo - floorf(dividendo/divisor)*divisor;
    return quociente;
}

float leNivel(){
    float nivel = 0.1;
    while(resto(nivel, NIVEL_PASSO) != 0.0 || nivel < NIVEL_MIN || nivel > NIVEL_MAX){
        printf("\nDigite o nivel do pokemon: ");
        scanf("%f", &nivel);
    }
    return nivel;
}

float calculaPS(pokemon_selecionado_struct *pokemon){
    float ps;
    ps = pokemon->base->stamina * 2 * pokemon->nivel / 100;
    ps += pokemon->nivel + 10;
    printf("\nOs pontos de saude do pokemon selecionado sao: %.2f\n", ps);
    pokemon->ps = ps;
}

float selecionaPokemon(pokemon_selecionado_struct *poke_sel, pokemon_struct *pokemon, ataque_struct *ataque_rapido, ataque_struct *ataque_carregado, clima_struct *clima, tipo_struct *tipo){
    int pokemon_id;
    int pokemon_atr;
    int pokemon_atc;
    float pokemon_nivel;
    float pokemon_ps;
    pokemon_id = lePokemonId(pokemon, tipo);
    poke_sel->base = &pokemon[pokemon_id];
    pokemon_atr = leAtaqueRapido(ataque_rapido, tipo);
    poke_sel->ataque_rapido = &ataque_rapido[pokemon_atr];
    pokemon_atc = leAtaqueCarregado(ataque_carregado, tipo);
    poke_sel->ataque_carregado = &ataque_carregado[pokemon_atc];
    poke_sel->nivel = leNivel();
    calculaPS(poke_sel);
}

float selecionaPokemons(pokemon_selecionado_struct pokemon_selecionado[QTD_JOGADOR][QTD_POKEMON_POR_JOGADOR], pokemon_struct *pokemon, ataque_struct *ataque_rapido, ataque_struct *ataque_carregado, clima_struct *clima, tipo_struct *tipo){
    for(int jogador = 0; jogador < QTD_JOGADOR; jogador++){
		for(int sel = 0; sel < QTD_POKEMON_POR_JOGADOR; sel++){
			selecionaPokemon(&pokemon_selecionado[jogador][sel], pokemon, ataque_rapido, ataque_carregado, clima, tipo);
		}
	}
}

void listaClima(clima_struct *clima, tipo_struct *tipo){
    for(int i = 0; i < QTD_CLIMA; i++){
        printf("id:%d\t%s\tt1:%s\tt2:%s\tt3:%s\n", 
            i + 1, 
            clima[i].nome,
            tipo[clima[i].tipo[0]].nome,
            tipo[clima[i].tipo[1]].nome,
            tipo[clima[i].tipo[2]].nome
        );
    }
}

int selecionaClima(int *clima_sel, clima_struct *clima, tipo_struct *tipo){
    int id = -1;
    while(id < 1 || id > QTD_CLIMA){
        printf("\nSelecione um clima pelo seu ID (0 para listar): ");
        scanf("%d", &id);
        if(id == 0) listaClima(clima, tipo);
    }
    id = id - 1;
    printf("\nClima selecionado: %s\n", clima[id].nome);
    *clima_sel = id;
}