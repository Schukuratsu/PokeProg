#include "pokedef.h"

int verificaPrimeiro(pokemon_selecionado_struct *ps1, pokemon_selecionado_struct *ps2){
    int primeiro;
    if(ps1->velocidade > ps2->velocidade){
        primeiro = 0;
    }
    else{
        primeiro = 1;
    }
    return primeiro;
}

ataque_struct* menuAtaque(pokemon_selecionado_struct *pokemon_selecionado, tipo_struct *tipo){
    int ataque_id = 0;
    int valid;
    ataque_struct *ataque_selecionado;
    // listagem
    printf("\n(1) nome: %s\tdano base: %.2f\ttipo: %s",
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
            printf("Bonus de clima!\n");
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
        printf("Bonus de tipo!\n");
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
    if(eficacia_ataque == 0){
        printf("O golpe nao teve efeito.\n");
    }
    else if(eficacia_ataque == 0.5){
        printf("O golpe foi pouco efetivo.\n");
    }
    else if(eficacia_ataque == 4){
        printf("O golpe foi super efetivo!\n");
    }
    else if(eficacia_ataque == 2){
        printf("O golpe foi muito efetivo!\n");
    }
    return eficacia_ataque;
}

int atacaAdversario(ataque_struct *ataque, pokemon_selecionado_struct *pokemon_ataque, pokemon_selecionado_struct *pokemon_defesa, tipo_struct *tipo, clima_struct *clima, int *escudo){
	float dano;
    int carregado;
    int bloqueado;
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
    if(strcmp(ataque->nome, pokemon_ataque->ataque_carregado->nome) == 0 && *escudo > 0){
        *escudo--;
        pokemon_ataque->energia -= ataque->energia;
        bloqueado = 1;
        printf("O ataque foi bloqueado!\n");
    }else{
        bloqueado = 0;
        pokemon_defesa->ps -= dano;
        printf("O ataque causou %.2f de dano.\n", dano);
        if(ataque == pokemon_ataque->ataque_carregado){
            pokemon_ataque->energia += (dano / 2) - ataque->energia;
        }
        else{
            pokemon_ataque->energia += (dano / 2) + ataque->energia;
        }
    }
    return bloqueado;
}

void escreveLogCabecalho(pokemon_selecionado_struct *p_s1, pokemon_selecionado_struct *p_s2){
    const char nome_arq[] = "log_batalha.csv";
    FILE *arq = fopen(nome_arq, "w+");
    if (arq != NULL){
        fprintf(arq,"turno;atacante;ataque;ps(jogador1);ps(jogador2);energia(jogador1);energia(jogador2)\n");
        printf("\tturno\tatacante\tataque\tps(jogador1)\tps(jogador2)\tps(jogador1)\tps(jogador2)\n");
        fprintf(arq,"0;-;-;%.3f;%.3f;%.3f;%.3f\n", p_s1->ps, p_s2->ps, p_s1->energia, p_s2->energia);
        printf("log: \t0\t-\t\t-\t%.3f\t\t%.3f\t\t%.3f\t\t%.3f\n", p_s1->ps, p_s2->ps, p_s1->energia, p_s2->energia);
        fclose(arq);
    }
    else{
        perror(nome_arq); // qual o erro?
    }
    return;
}

void escreveLog(ataque_struct *ataque_selecionado, pokemon_selecionado_struct *p_s1, pokemon_selecionado_struct *p_s2, int jogador, int bloqueado, int turno){
    const char nome_arq[] = "log_batalha.csv";
    FILE *arq = fopen(nome_arq, "a+");
    char nome_atacante[TAM_STRING];
    char nome_ataque[TAM_STRING];
    if (arq != NULL){
        if(jogador == 0){
            strcpy(nome_atacante, p_s1->base->nome);
        }
        else{
            strcpy(nome_atacante, p_s2->base->nome);
        }
        strcpy(nome_ataque, ataque_selecionado->nome);
        if(bloqueado){
            strcat(nome_ataque, " (block)");
        }
        fprintf(arq,"%d;%s;%s;%.3f;%.3f;%.3f;%.3f\n", turno, nome_atacante, nome_ataque, p_s1->ps, p_s2->ps, p_s1->energia, p_s2->energia);
        printf("log: %d\t%s\t%s\t%.3f\t%.3f\t%.3f\t%.3f\n", turno, nome_atacante, nome_ataque, p_s1->ps, p_s2->ps, p_s1->energia, p_s2->energia);
        fclose(arq);
    }
    else{
        perror(nome_arq); // qual o erro?
    }
    return;
}

void iniciaBatalha(pokemon_selecionado_struct pokemon_selecionado[QTD_JOGADOR][QTD_POKEMON_POR_JOGADOR], clima_struct *clima, tipo_struct *tipo){
    int pokemon_ativo[QTD_JOGADOR] = {0, 0};
    int escudo[QTD_JOGADOR] = {QTD_ESCUDO, QTD_ESCUDO};
    ataque_struct *ataque_selecionado;
    pokemon_selecionado_struct *atacante, *atacado;
    int jogador2;
    int jogador;
    int bloqueado;
    int ultimo_jogador;
    int turno = 0;
    printf("-- BATALHA INICIADA --\n\n");
    escreveLogCabecalho(&pokemon_selecionado[0][pokemon_ativo[0]], &pokemon_selecionado[1][pokemon_ativo[1]]);
    jogador = verificaPrimeiro(&pokemon_selecionado[0][pokemon_ativo[0]],&pokemon_selecionado[1][pokemon_ativo[1]]);
    while(pokemon_selecionado[0][QTD_POKEMON_POR_JOGADOR - 1].ps > 0 && pokemon_selecionado[1][QTD_POKEMON_POR_JOGADOR - 1].ps > 0){
        turno++;
        jogador2 = 1 - jogador;
        atacante = &pokemon_selecionado[jogador][pokemon_ativo[jogador]];
        atacado = &pokemon_selecionado[jogador2][pokemon_ativo[jogador2]];
        printf("\nTurno do jogador %d - \'%s\' ataca \'%s\'.", jogador + 1, atacante->base->nome, atacado->base->nome);
        ataque_selecionado = menuAtaque(atacante, tipo);
        bloqueado = atacaAdversario(ataque_selecionado, atacante, atacado, tipo, clima, &escudo[jogador2]);
        escudo[jogador2] -= bloqueado; 
        escreveLog(ataque_selecionado, &pokemon_selecionado[0][pokemon_ativo[0]], &pokemon_selecionado[1][pokemon_ativo[1]], jogador, bloqueado, turno);
        ultimo_jogador = jogador;
        if(jogador) jogador = 0;
        else jogador = 1;
        // verifica se pokemon foi nocauteado
        if(atacado->ps <= 0){
            printf("O pokemon '%s' desmaiou...\n", atacado->base->nome);
            pokemon_ativo[jogador2]++;
            jogador = verificaPrimeiro(&pokemon_selecionado[0][pokemon_ativo[0]],&pokemon_selecionado[1][pokemon_ativo[1]]);
        }
    }
    printf("\nO vencedor foi o jogador %d", ultimo_jogador + 1);
    return;
}
