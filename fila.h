/**Carros são salvos na lista com duas infomações: uma identificação(int) e coordenadas(x,y) que vão de 0.0 a 50.0.
 * A saída dos carros é baseada na distância entre os seus pontos(x,y) e as coordenadas do passageiro.
 * Se a distância entre o carro e o passageiro for menor ou igual a 13 o primeiro carro encontrado é retirado da lista.
 * */

#include <math.h>//uso da função pow() e sqrt()
#include <stdio.h>
#include <stdlib.h>

//Declaração das estruturas
typedef struct taxi Taxi;
typedef struct lista Lista;

struct taxi{
    Taxi* first;
};

struct lista{
    int idCarro;
    double x, y;
    Taxi* prox;
};

//Criar lista vazia
Taxi* criarLista(void){
    Taxi* c = (Taxi*) malloc(sizeof(Taxi));
    c->first = NULL;
    return c;
};

//Verificar se a lista está vazia
int emptyList(Taxi* c){
    if(c->first == NULL)
        return -1;
    else
        return 1;
}

//Inserção ordenada dos carros
void inserirCarro(Taxi* c, int carID, double x, double y){
    Lista* ant = NULL;
    Lista* varrer = c->first;

    while(varrer != NULL && varrer->idCarro < carID){
        ant = varrer;
        varrer = varrer->prox;
    }

    Lista* novo = (Lista*) malloc(sizeof(Lista));
    novo->idCarro = carID;
    novo->x = x;
    novo->y = y;
    novo->prox = c->first;

    if(ant == NULL){
        novo->prox = c->first;
        c->first = novo;
    }else{
        novo->prox = ant->prox;
        ant->prox = novo;
    }
}

//Exibir elementos da lista
int mostrarLista(Taxi* c){
    Lista* cars = c;

    if(c->first == NULL){
        printf("\aLista vazia.\n");
		return 1;
    }
    for(cars = c->first; cars !=  NULL; cars = cars->prox)
        printf("Identificacao do carro: %d  |  Posicao(%.1f, %.1f)\n",
               cars->idCarro, cars->x, cars->y);

return 0;
}

//Remover carros que estão na lista
Taxi* removerCarro(Taxi* c, int carID){
    if(carID == -1){
        printf("\aNao ha carros proximos.\n");
        return c;
    }

    else{
		Lista* ant = NULL; //ponteiro para o primeiro elemento da lista
	    Lista* aux = c->first;   //ponteiro para percorrer a lista

	    while(aux != NULL && aux->idCarro != carID) {
	        ant = aux;
	        aux = aux->prox;
	    }

	    if (aux != NULL){
	        if(ant == NULL) {
	            c->first = aux->prox;
	            printf("\nO carro %d vem te buscar.\n", carID);
	        }else{
	            ant->prox = aux->prox;
	            printf("\nO carro %d vem te buscar.\n", carID);
	        }
	    }
	    free(aux);
	    return c;
	}
}

//Procurando por uma identificação já cadastrada
int procurarID(Taxi* c, int carID){
    Lista* cars;

    for(cars = c->first; cars !=  NULL; cars = cars->prox)
        if(cars->idCarro == carID)
            return 1;

    return -1;
}

//Procurando carro em uma distância próxima
int procurarTaxi(Taxi* c, double x, double y){
    Lista* cars;

    double res = 0.0;
    int carID = 0;

   for(cars = c->first; cars != NULL; cars = cars->prox){
        fflush(stdin); //limpar buffer
        //calcula a distancia entre dois pontos
        res = sqrt(pow(x - cars->x, 2)+ pow(y - cars->y, 2));
        if(!(res > 13.1)){
            carID = cars->idCarro;
            return carID;
        }else if(res >= 13.1 || res < 20.0)
            printf("Procurando carro mais  proximo...\n");
	}
    return -1;//elemento nao encontrado
}

//Zerar uma lista criada
void liberarCarros(Taxi* c){
    Lista* t = c->first, *u;

    while(t !=  NULL){
        u = t;
        t = t->prox;
        free(t);
    }
    c->first = NULL;
}
