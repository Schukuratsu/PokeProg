#include "pokedef.h"

int carregaTipo(tipo_struct tipo[QTD_TIPO]){
    const char nome_arq[] = "tipo.txt";
    FILE *arq = fopen(nome_arq, "r");
    int n = 0;
    if (arq != NULL){
        while (!feof(arq)){ // lê linha
            tipo_struct p;
            fscanf(arq, "%s", p.nome);
            // printf("%s, ", p.nome);
            for(int i = 0; i < QTD_TIPO; i++){
                fscanf(arq, "%f", &p.eficacia[i]);
                // printf("%.2f, ", p.eficacia[i]);
            }
            tipo[n] = p;
            n++;
        }
        fclose(arq);
    }
    else{
        perror(nome_arq); // qual o erro?
    }
    return n;
}

int pegaIdTipo(char tipo_pokemon[TAM_STRING], tipo_struct tipo[QTD_TIPO], int linha, const char nome_arq[TAM_STRING]){
    if(strcmp(tipo_pokemon, "null") == 0){
        return -1;
    }
    for(int i = 0; i < QTD_TIPO; i++){
        if(strcmp(tipo_pokemon, tipo[i].nome) == 0){
            return i;
        }
    }
    printf("Tipo invalido na linha %d do arquivo %s\n", linha+1, nome_arq);
    exit(1);
}

int carregaClima(clima_struct clima[QTD_CLIMA], tipo_struct tipo[QTD_TIPO]){
    const char nome_arq[TAM_STRING] = "clima.txt";
    FILE *arq = fopen(nome_arq, "r");
    int n = 0;
    if (arq != NULL){
        char clima_tipo[TAM_STRING];
        while (!feof(arq)){ // lê linha
            clima_struct p;
            fscanf(arq, "%s", p.nome);
            // printf("\n%s ", p.nome);
            for(int i = 0; i < TIPOS_POR_CLIMA; i++){
                fscanf(arq, "%s", clima_tipo);
                // printf("%s ", clima_tipo);
                p.tipo[i] = pegaIdTipo(clima_tipo, tipo, n, nome_arq);
                // printf("%d ", p.tipo[i]);
            }
            clima[n] = p;
            n++;
        }
        fclose(arq);
    }
    else{
        perror(nome_arq); // qual o erro?
    }
    return n;
}

int carregaAtaque(ataque_struct *ataque, tipo_struct tipo[QTD_TIPO], const char nome_arq[]){
    FILE *arq = fopen(nome_arq, "r");
    int n = 0;
    if (arq != NULL){
        char ataque_tipo[TAM_STRING];
        while (!feof(arq)){ // lê linha
            ataque_struct p;
            fscanf(arq, "%s %f %s %f", p.nome, &p.dano, ataque_tipo, &p.energia);
            p.tipo = pegaIdTipo(ataque_tipo, tipo, n, nome_arq);
            // printf("\n%s %.2f %s %d %.2f\n", p.nome, p.dano, ataque_tipo, p.tipo, p.energia);
            ataque[n] = p;
            n++;
        }
        fclose(arq);
    }
    else{
        perror(nome_arq); // qual o erro?
    }
    return n;
}

int carregaAtaqueRapido(ataque_struct *ataque, tipo_struct tipo[QTD_TIPO]){
    const char nome_arq[] = "ataque_rapido.txt";
    return carregaAtaque(ataque, tipo, nome_arq);
}

int carregaAtaqueCarregado(ataque_struct *ataque, tipo_struct tipo[QTD_TIPO]){
    const char nome_arq[] = "ataque_carregado.txt";
    return carregaAtaque(ataque, tipo, nome_arq);
}

int carregaPokemon(pokemon_struct pokemon[QTD_POKEMON], tipo_struct tipo[QTD_TIPO]){
    const char nome_arq[] = "pokemon.txt";
    FILE *arq = fopen(nome_arq, "r");
    int n = 0;
    if (arq != NULL){
        char tipo1[TAM_STRING], tipo2[TAM_STRING];
        while (!feof(arq)){ // lê linha
            pokemon_struct p;
            fscanf(arq, "%s %f %f %f %f %s %s", p.nome, &p.ataque, &p.defesa, &p.velocidade, &p.stamina, tipo1, tipo2);
            p.tipo1 = pegaIdTipo(tipo1, tipo, n, nome_arq);
            p.tipo2 = pegaIdTipo(tipo2, tipo, n, nome_arq);
            // printf("\n%s %.2f %.2f %.2f %.2f %s %d %s %d", p.nome, p.ataque, p.defesa, p.velocidade, p.stamina, tipo1, p.tipo1, tipo2, p.tipo2);
            pokemon[n] = p;
            n++;
        }
        fclose(arq);
    }
    else{
        perror(nome_arq); // qual o erro?
    }
    return n;
}
