#include "pokedef.h"

ataque_struct* menuAtaque(pokemon_selecionado_struct *pokemon_selecionado, tipo_struct *tipo){
    int ataque_id = 0;
    int valid;
    ataque_struct *ataque_selecionado;
    // listagem
    printf("\nAtaques disponiveis:\n(1) nome: %s\tdano base: %.2f\ttipo: %s",
        pokemon_selecionado->ataque_rapido->nome,
        pokemon_selecionado->ataque_rapido->dano,
        tipo[pokemon_selecionado->ataque_rapido->tipo].nome);
    if(pokemon_selecionado->energia >= pokemon_selecionado->ataque_carregado->energia){
        printf("\n(2) nome: %s\tdano base: %.2f\ttipo: %s",
            pokemon_selecionado->ataque_carregado->nome,
            pokemon_selecionado->ataque_carregado->dano,
            tipo[pokemon_selecionado->ataque_carregado->tipo].nome);
        valid = 2;
    }
    else{
        valid = 1;
    }
    // seleção
    while(ataque_id < 1 || ataque_id > valid){
        printf("\nSelecione um ataque: ");
        scanf("%d",&ataque_id);
    }
    if(ataque_id == 1){
        ataque_selecionado = pokemon_selecionado->ataque_rapido;
    }else{
        ataque_selecionado = pokemon_selecionado->ataque_carregado;
    }
    return ataque_selecionado;
}

float bonusClima(ataque_struct *pokemon_ataque, clima_struct *clima){
    int ataque_tipo = pokemon_ataque->tipo;
    float bonus_clima = 1;
    for(int i = 0; i < TIPOS_POR_CLIMA; i++){
        if(clima->tipo[i] == ataque_tipo){
            printf("\nBonus de clima!");
            bonus_clima = 1.3;
            break;
        }
    }
    return bonus_clima;
}

float fatorAleatorio(){
    // retorna valor entre 0.85 e 1.15
    float fator_aleatorio = (float) (rand() % 30000);
    fator_aleatorio /= 100000;
    fator_aleatorio += 1;
    return fator_aleatorio;
}

float bonusAtaqueMesmoTipo(ataque_struct *ataque, pokemon_selecionado_struct *pokemon_ataque){
    int ataque_tipo = ataque->tipo;
    int pokemon_ataque_tipo1 = pokemon_ataque->base->tipo1;
    int pokemon_ataque_tipo2 = pokemon_ataque->base->tipo2;
    float bonus_ataque;
    if(ataque_tipo == pokemon_ataque_tipo1 || ataque_tipo == pokemon_ataque_tipo2){
        printf("\nBonus de tipo!");
        bonus_ataque = 1.5;
    }else{
        bonus_ataque = 1;
    }
    return bonus_ataque;
}

float eficaciaTipo(ataque_struct *ataque, pokemon_selecionado_struct *pokemon_defesa, tipo_struct *tipo){
    int ataque_tipo = ataque->tipo;
    int pokemon_defesa_tipo1 = pokemon_defesa->base->tipo1;
    int pokemon_defesa_tipo2 = pokemon_defesa->base->tipo2;
    float eficacia_ataque = tipo[ataque_tipo].eficacia[pokemon_defesa_tipo1];
    // printf("\n\n\n%d %d %f \n\n\n",pokemon_defesa_tipo1,pokemon_defesa_tipo2,eficacia_ataque);
    if(pokemon_defesa_tipo2 != -1){
        eficacia_ataque *= tipo[ataque_tipo].eficacia[pokemon_defesa_tipo2];
    }
    // printf("\n\n\n%f %f %f \n\n\n",eficacia_ataque,tipo[ataque_tipo].eficacia[pokemon_defesa_tipo1],tipo[ataque_tipo].eficacia[pokemon_defesa_tipo2]);
    if(eficacia_ataque < 1){
        printf("\nNão foi muito efetivo.");
    }
    else if(eficacia_ataque > 1){
        printf("\nFoi muito efetivo!");
        printf("\nFoi muito efetivo!");
    }
    return eficacia_ataque;
}

float atacaAdversario(ataque_struct *ataque, pokemon_selecionado_struct *pokemon_ataque, pokemon_selecionado_struct *pokemon_defesa, tipo_struct *tipo, clima_struct *clima, int *escudo){
	float dano;
    int carregado;
    // calcula dano
    dano = 2 * pokemon_ataque->nivel / 5 + 2;
	dano *= ataque->dano;
    dano *=  pokemon_ataque->base->ataque;
    dano /=  pokemon_defesa->base->defesa;
	dano /= 50;
	dano += 2;
	dano *= bonusClima(ataque, clima);
	dano *= fatorAleatorio();
	dano *= bonusAtaqueMesmoTipo(ataque, pokemon_ataque);
	dano *= eficaciaTipo(ataque, pokemon_defesa, tipo);
	// aplica dano
    if(ataque == pokemon_ataque->ataque_carregado && *escudo > 0){
        *escudo--;
        pokemon_ataque->energia -= ataque->energia;
        printf("\nO ataque foi bloqueado!");
    }else{
        pokemon_defesa->ps -= dano;
        printf("\nO ataque causou %.2f de dano", dano);
        if(ataque == pokemon_ataque->ataque_carregado){
            pokemon_ataque->energia -= ataque->energia;
        }
        else{
            pokemon_ataque->energia += ataque->energia;
        }
    }
}

void iniciaBatalha(pokemon_selecionado_struct pokemon_selecionado[QTD_JOGADOR][QTD_POKEMON_POR_JOGADOR], clima_struct *clima, tipo_struct *tipo){
    int pokemon_ativo[QTD_JOGADOR] = {0, 0};
    int escudo[QTD_JOGADOR] = {0, 0};
    ataque_struct *ataque_selecionado;
    pokemon_selecionado_struct *atacante, *atacado;
    float dano;
    int jogador2;
    while(pokemon_selecionado[0][QTD_POKEMON_POR_JOGADOR - 1].ps > 0 && pokemon_selecionado[1][QTD_POKEMON_POR_JOGADOR - 1].ps > 0){
        for (int jogador = 0; jogador < QTD_JOGADOR; jogador++){
            jogador2 = 1 - jogador;
            atacante = &pokemon_selecionado[jogador][pokemon_ativo[jogador]];
            atacado = &pokemon_selecionado[jogador2][pokemon_ativo[jogador2]];
            ataque_selecionado = menuAtaque(atacante, tipo);
            atacaAdversario(ataque_selecionado, atacante, atacado, tipo, clima, &escudo[jogador2]);
        }
    }
}
