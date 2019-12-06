
#include<stdio.h>
#include<stdlib.h>
#include<string.h>


struct ataque_misto_struct
{
char tipo[30];
char modo[30];
char nome[30];
float dano;
float energia;
int novoid;
};
typedef struct ataque_misto_struct ataque_misto_struct;

struct lista_struct
{
int num_atk[7];
};
typedef struct lista_struct lista_struct;


int main(){

    ataque_misto_struct ataque_misto[208];
    int vetor[208];
    lista_struct lista[150];
    int i, j;
    int contar = 0;
    int contac = 0;
    int idatk, id;
    int mew[39];

    FILE *arq1 = fopen ("golpes","r");
    if(arq1 == NULL)
    {
        printf("ERRO nos golpes");
        return -1;
    }

    for(i=0;i<208;i++){
        fscanf(arq1,"%s %s",ataque_misto[i].tipo,ataque_misto[i].modo);
        fgets(ataque_misto[i].nome,18,arq1);
        fscanf(arq1,"%f %f",&ataque_misto[i].dano,&ataque_misto[i].energia);
    }
    fclose(arq1);

    FILE *arq2 = fopen("movimentos.txt", "r");
    if(arq2==NULL)
    {
        printf("Erro ao abrir o arquivo de movimentos");
        return -1;
    }
   
    for(i=0;i<150;i++)
    {
        fscanf(arq2, "%d %d %d %d %d %d %d", &lista[i].num_atk[0], &lista[i].num_atk[1], &lista[i].num_atk[2], &lista[i].num_atk[3], &lista[i].num_atk[4], &lista[i].num_atk[5], &lista[i].num_atk[6]);
    }
    for(i=0;i<39;i++)
    {
        fscanf(arq2, "%d", &mew[i]);
    }
    fclose(arq2);





    const char nome_ar[] = "ataque_rapido.txt";
    FILE *ar = fopen(nome_ar, "w+");
    const char nome_ac[] = "ataque_carregado.txt";
    FILE *ac = fopen(nome_ac, "w+");
    if (ar != NULL && ac != NULL){
        for(i=0;i<208;i++){
            if(strcmp(ataque_misto[i].modo,"rapido") == 0){
                ataque_misto[i].novoid = contar++;
                fprintf(ar,"%s %s                  %.2f %.2f\n",ataque_misto[i].tipo, ataque_misto[i].nome,ataque_misto[i].dano,ataque_misto[i].energia);
            }
            else if(strcmp(ataque_misto[i].modo,"carregado") == 0){
                ataque_misto[i].novoid = contac++;
                fprintf(ac,"%s %s                  %.2f %.2f\n",ataque_misto[i].tipo, ataque_misto[i].nome,ataque_misto[i].dano,ataque_misto[i].energia);
            }
        }
        fclose(ar);
        fclose(ac);
    }
    else{
        printf("Erro ao escrever golpes");
        return -1;
    }


    const char nome_lr[] = "lista_rapido.txt";
    FILE *lr = fopen(nome_lr, "w+");
    const char nome_lc[] = "lista_carregado.txt";
    FILE *lc = fopen(nome_lc, "w+");
    if (lr != NULL && lc != NULL){
        for(i=0;i<150;i++){
            contar = 0;
            contac = 0;
            for(j=0;j<7;j++){
                idatk = lista[i].num_atk[j];
                if(idatk > 208 || idatk < 0) printf("POBREMA AQUI: LISTA: %d ATAQUE: %d\n", i, idatk);
                if(strcmp(ataque_misto[idatk].modo,"rapido") == 0){
                    contar++;
                    id = ataque_misto[idatk].novoid;
                    if(idatk == 208) id = -1;
                    fprintf(lr,"%d ",id);
                }
                else if(strcmp(ataque_misto[idatk].modo,"carregado") == 0){
                    contac++;
                    id = ataque_misto[idatk].novoid;
                    if(idatk == 208) id = -1;
                    fprintf(lc,"%d ",id);
                }
            }
            for (contar = contar; contar < 14; contar++){
                fprintf(lr,"%d ",-1);
            }
            fprintf(lr,"\n");
            for (contac = contac; contac < 25; contac++){
                fprintf(lc,"%d ",-1);
            }
            fprintf(lc,"\n");
        }
        contar = 0;
        contac = 0;
        for(i=0;i<39;i++)
        {
            idatk = mew[i];
            if(idatk > 208 || idatk < 0) printf("POBREMA AQUI: LISTA: %d ATAQUE: %d\n", i, idatk);
            if(strcmp(ataque_misto[idatk].modo,"rapido") == 0){
                contar++;
                id = ataque_misto[idatk].novoid;
                if(idatk == 208) id = -1;
                fprintf(lr,"%d ",id);
            }
            else if(strcmp(ataque_misto[idatk].modo,"carregado") == 0){
                contac++;
                id = ataque_misto[idatk].novoid;
                if(idatk == 208) id = -1;
                fprintf(lc,"%d ",id);
            }
        }
        for (contar = contar; contar < 14; contar++){
            fprintf(lr,"%d ",-1);
        }
        for (contac = contac; contac < 25; contac++){
            fprintf(lc,"%d ",-1);
        }
        fclose(lr);
        fclose(lc);
    }
    else{
        printf("Erro ao escrever listas");
        return -1;
    }





    return 0;
}