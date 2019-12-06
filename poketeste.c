#include "pokedef.h"

void testePokemon(pokemon_selecionado_struct *p){
	printf("\n\n\nnomepoke: %s\natr: %s\natc: %s\nnv: %.2f\nps: %.2f",
		p->base->nome,
		p->ataque_rapido->nome,
		p->ataque_carregado->nome,
		p->nivel,
		p->ps
    );
}

void testeTipo(tipo_struct p[QTD_TIPO]){
	for(int i = 0; i <= QTD_TIPO; i++){
		printf("\nidtipo: %d - nometipo: %s",i, p[i].nome);
	}
}