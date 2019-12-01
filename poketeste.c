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