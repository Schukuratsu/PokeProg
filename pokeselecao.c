#include "pokedef.h"

void listaPokemon(pokemon_struct *pokemon, tipo_struct *tipo){
    int idt2;
    int i;
    char tipo2[TAM_STRING];
    const char tipo_null[TAM_STRING] = "null";
    for(i = 0; i < QTD_POKEMON; i++){
        idt2 = pokemon[i].tipo2;
        if(idt2 >= 0 && idt2 < QTD_TIPO) {
            strcpy(tipo2,tipo[pokemon[i].tipo2].nome);
        }else{
            strcpy(tipo2, tipo_null);
        }
        printf("(%d)\t%s, atk:%.2f, def:%.2f, sta:%.2f, tipo1:%s, tipo2:%s\n", 
            i + 1, 
            pokemon[i].nome, 
            pokemon[i].ataque, 
            pokemon[i].defesa, 
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
    printf("\nPokemon selecionado: %s\n\n", pokemon[id].nome);
    return id;
}

void listaAtaqueRapido(pokemon_struct *pokemon, ataque_struct *ataque, tipo_struct *tipo){
    int id;
    for(int i = 0; i < 14 && pokemon->rapido[i] != -1; i++){
        id = pokemon->rapido[i];
        printf("(%d)\t%s, dano:%.2f, energia:%.2f, tipo:%s\n", 
            i + 1, 
            ataque[id].nome,
            ataque[id].dano,
            ataque[id].energia,
            tipo[ataque[id].tipo].nome
        );
    }
}

void listaAtaqueCarregado(pokemon_struct *pokemon, ataque_struct *ataque, tipo_struct *tipo){
    int id;
    for(int i = 0; i < 25 && pokemon->carregado[i] != -1; i++){
        id = pokemon->carregado[i];
        printf("(%d)\t%s, dano:%.2f, energia:%.2f, tipo:%s\n", 
            i + 1, 
            ataque[id].nome,
            ataque[id].dano,
            ataque[id].energia,
            tipo[ataque[id].tipo].nome
        );
    }
}

int leAtaqueRapido(pokemon_struct *pokemon, ataque_struct *ataque_rapido, tipo_struct *tipo){
    int pass = 0, id, i;
    while(pass == 0){
        printf("\nSelecione um ataque rapido pelo seu ID (0 para listar): ");
        scanf("%d", &id);
        if(id == 0) listaAtaqueRapido(pokemon, ataque_rapido, tipo);
        else{
            if(id <= 14 && id > 0){
                for(i = 0; i < 14 && pokemon->rapido[i] != -1; i++){
                    if(pokemon->rapido[id - 1] != -1) pass = 1;
                }
            }
        }
    }
    id = pokemon->rapido[id - 1];
    printf("\nAtaque rapido selecionado: %s\n\n", ataque_rapido[id].nome);
    return id;
}

int leAtaqueCarregado(pokemon_struct *pokemon, ataque_struct *ataque_carregado, tipo_struct *tipo){
    int pass = 0, id, i;
    while(pass == 0){
        printf("\nSelecione um ataque carregado pelo seu ID (0 para listar): ");
        scanf("%d", &id);
        if(id == 0) listaAtaqueCarregado(pokemon, ataque_carregado, tipo);
        else{
            if(id <= 25 && id > 0){
                for(i = 0; i < 14 && pokemon->carregado[i] != -1; i++){
                    if(pokemon->carregado[id - 1] != -1) pass = 1;
                }
            }
        }
    }
    id = pokemon->carregado[id - 1];
    printf("\nAtaque carregado selecionado: %s\n\n", ataque_carregado[id].nome);
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
        printf("Digite o nivel do pokemon (de 0 a 40): ");
        scanf("%f", &nivel);
    }
    return nivel;
}

float leVelocidade(){
    float velocidade = -1;
    while(velocidade < 0){
        printf("Digite a velocidade do pokemon: ");
        scanf("%f", &velocidade);
    }
    return velocidade;
}

float calculaPS(pokemon_selecionado_struct *pokemon){
    float ps;
    ps = pokemon->base->stamina * 2 * pokemon->nivel / 100;
    ps += pokemon->nivel + 10;
    printf("\nOs pontos de saude do pokemon selecionado sao: %.2f\n\n", ps);
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
    pokemon_atr = leAtaqueRapido(poke_sel->base, ataque_rapido, tipo);
    poke_sel->ataque_rapido = &ataque_rapido[pokemon_atr];
    pokemon_atc = leAtaqueCarregado(poke_sel->base, ataque_carregado, tipo);
    poke_sel->ataque_carregado = &ataque_carregado[pokemon_atc];
    poke_sel->nivel = leNivel();
    poke_sel->velocidade = leVelocidade();
    calculaPS(poke_sel);
}

float selecionaPokemons(pokemon_selecionado_struct pokemon_selecionado[QTD_JOGADOR][QTD_POKEMON_POR_JOGADOR], pokemon_struct *pokemon, ataque_struct *ataque_rapido, ataque_struct *ataque_carregado, clima_struct *clima, tipo_struct *tipo){
    for(int sel = 0; sel < QTD_POKEMON_POR_JOGADOR; sel++){
        for(int jogador = 0; jogador < QTD_JOGADOR; jogador++){
			printf("\nJogador %d, escolha seu pokemon %d.\n", jogador + 1, sel + 1);
            selecionaPokemon(&pokemon_selecionado[jogador][sel], pokemon, ataque_rapido, ataque_carregado, clima, tipo);
		}
	}
}

void listaClima(clima_struct *clima, tipo_struct *tipo){
    char tipo3[TAM_STRING];
    const char tipo_null[TAM_STRING] = "null";
    int idt3;
    for(int i = 0; i < QTD_CLIMA; i++){
        idt3 = clima[i].tipo[2];
        if(idt3 >= 0 && idt3 < QTD_TIPO) {
            strcpy(tipo3,tipo[clima[i].tipo[2]].nome);
        }else{
            strcpy(tipo3, tipo_null);
        }
        printf("(%d)\t%s\tt1:%s\tt2:%s\tt3:%s\n", 
            i + 1, 
            clima[i].nome,
            tipo[clima[i].tipo[0]].nome,
            tipo[clima[i].tipo[1]].nome,
            tipo3
        );
    }
}

int selecionaClima(int *clima_sel, clima_struct *clima, tipo_struct *tipo){
    int id = -1;
    listaClima(clima, tipo);
    while(id < 1 || id > QTD_CLIMA){
        printf("\nSelecione um clima pelo seu ID (0 para listar): ");
        scanf("%d", &id);
        if(id == 0) listaClima(clima, tipo);
    }
    id = id - 1;
    printf("\nClima selecionado: %s\n\n", clima[id].nome);
    *clima_sel = id;
}
