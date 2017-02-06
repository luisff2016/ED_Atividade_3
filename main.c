#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <string.h>

//Declaração das estruturas
typedef struct taxi Taxi;
typedef struct lista Lista;

struct taxi{
    Taxi* first;
};

struct lista{
    char motorista[31];
    char *placa[8];
    double x, y;
    Taxi* prox;
};

FILE *arquivo;//Criação do arquivo

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
void inserirCarro(Taxi* c, char *motorista, char *p, double x, double y){
    arquivo = fopen("..\\ex\\arquivo\\lista.db", "a+b");
    Lista* ant = NULL;
    Lista* varrer = c->first;

    while(varrer != NULL && strcmp(varrer->placa, p) == 0){
        ant = varrer;
        varrer = varrer->prox;
    }

    Lista* novo = (Lista*) malloc(sizeof(Lista));
    int i;
    for(i=0;i<30;i++){
        motorista[i] = toupper(motorista[i]);
        novo->motorista[i] = motorista[i];
    }
    for(i=0;i<8;i++){
        p[i] = toupper(p[i]);
        novo->placa[i] = p[i];
    }
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
    fwrite(c, sizeof(novo), 1, arquivo);
    fclose(arquivo);
}

//Exibir elementos da lista
int mostrarLista(Taxi* c){
    Lista* cars = c;

    if(arquivo == NULL){
        printf("\aLista vazia.\n");
		return 1;
    }

    long int tamanho = sizeof(cars);
    fseek(arquivo,0,0);

    do{
        fread(&cars,tamanho,1,arquivo);
        if(feof(arquivo))
            printf("Motorista: %s | Placa: %s | Posicao: (%i, %i)\n",
                   cars->motorista, cars->placa, cars->x, cars->y);
    }while(!feof(arquivo));

return 0;
}

//Remover carros que estão na lista
Taxi* removerCarro(Taxi* c, char *placa){
    if(placa == -1){
        printf("\aNao ha carros proximos.\n");
        return c;
    }

    else{
		Lista* ant = NULL; //ponteiro para o primeiro elemento da lista
	    Lista* aux = c->first;   //ponteiro para percorrer a lista

	    while(aux != NULL && (strcmp(aux->placa, placa)==1)) {
	        ant = aux;
	        aux = aux->prox;
	    }

	    if (aux != NULL){
	        if(ant == NULL) {
	            c->first = aux->prox;
	            printf("\nO motorista %s, com carro de placa %s vem te buscar.\n", aux->motorista, placa);
	        }else{
	            ant->prox = aux->prox;
	            printf("\nO motorista %s, com carro de placa %s vem te buscar.\n", aux->motorista, placa);
	        }
	    }
	    free(aux);
	    return c;
	}
}

//Procurando por uma identificação já cadastrada
int procurarID(Taxi* c, char *placa){
    Lista* cars;

    for(cars = c->first; cars !=  NULL; cars = cars->prox){
      //  cars->placa = toupper(cars->placa);
        if(strcmp(cars->placa, placa)==0)
            return 1;
    }
    return -1;
}

//Procurando carro em uma distância próxima
char procurarTaxi(Taxi* c, double x, double y){
    Lista* cars;

    double res = 0.0;
    char placa[8];
    int i;

    for(cars = c->first; cars != NULL; cars = cars->prox){
        fflush(stdin); //limpar buffer
        //calcula a distancia entre dois pontos
        res = sqrt(pow(x - cars->x, 2)+ pow(y - cars->y, 2));
        if(!(res > 13.1)){
            for(i=0; i<8; i++)
                 placa[i] = cars->placa[i];
            return placa;
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


//Funcao para reinicializar as opcoes do menu
void voltarAoMenu(Taxi* c){
    printf("\n\n");
    printf("\t\t\t\tPresssione qualquer tecla para voltar ao MENU PRINCIPAL");
      fflush(stdin);
        getch();
      system("cls");
    menu(c);
}

//permitir ou nao a insercao de um novo taxi
char validarCarro(){
   char operador;
       do{
          printf("\n\n\t\tDeseja adicionar um novo carro? [S - sim; N - n%co]", 198);
                fflush(stdin);
                operador = toupper(getchar());
          printf("\n" );
       }while (operador != 'S' && operador != 'N');

return operador;
}

//Adicionar novo carro
void addCar(Taxi* c){

    char operador = 'S';
    char motorista[31], placa[8];
    double x, y;

    while(operador == 'S'){
        printf("Entre com o nome do motorista: ");
            scanf("%30s", motorista);
        printf("Entre com a placa do carro: ");
            scanf("%7s", placa);
/*
        if(procurarID(c, id) == 1){
            printf("Identificacao ja cadastrada. Tente novamente.\n");
            continue;
        }
*/
        while(1){
            printf("Insira a posicao inicial do carro (x,y): ");
                scanf("%lf %lf", &x, &y);

            if((x < 0.0 || x > 50.0) || ((y < 0.0 || y > 50.0)))
                printf("Coordenadas invalidas. Tente valores entre 0.0 e 50.0.\n");
            else
                break;
        }
        operador = validarCarro();

    inserirCarro(c, motorista, placa, x, y);
    }
    voltarAoMenu(c);
}

//Solicitar um taxi (remover da lista)
void pedirTaxi(Taxi* c){

    if(emptyList(c) == -1){
        printf("\aNao ha carros disponiveis.\n");
        voltarAoMenu(c);
    }else{
        double x, y;
        printf("Digite a sua posicao (x, y): ");
            scanf("%lf %lf", &x, &y);

        removerCarro(c, procurarTaxi(c, x, y));
        voltarAoMenu(c);
    }
}

//Interface com o usuario
void menu(Taxi* c){

    printf("\t\t=======================\n");
    printf("\t\t\tTaxi\n");
    printf("\t\t=======================\n\n");

    printf("1 - Pedir um taxi\n");
    printf("2 - Mostrar taxis disponiveis\n\n");
    printf("3 - Adicionar um novo taxi\n");
    printf("4 - Liberar toda a lista\n");
    printf("\n\n0 - SAIR\n");
    printf("\t\t\tSelecione uma das opcoes acima: ");

    int op;
        scanf("%d", &op);
    switch(op){
        case 0:
            exit(0);

        case 1:
            system("cls");
            printf("\t\t============================\n");
            printf("\t\t\tPedir Taxi\n");
            printf("\t\t============================\n\n");

            pedirTaxi(c);
            break;
        case 2:
            system("cls");
            printf("\t\t============================\n");
            printf("\t\t\tCarros Disponiveis\n");
            printf("\t\t============================\n\n");

            mostrarLista(c);
            voltarAoMenu(c);
            break;
        case 3:
            system("cls");
            printf("\t\t===============================\n");
            printf("\t\t\tAdicionar Novos Carros\n");
            printf("\t\t===============================\n\n");

            addCar(c);
            break;
        case 4:
            liberarCarros(c);
                system("cls");
				printf("\aLista liberada.\n");

            voltarAoMenu(c);
            break;
        default:
            printf("\aOpcao invalida.");
            system("cls");
            menu(c);
            break;
    }
}


int main(){
    Lista* c = criarLista();
/*
    inserirCarro(c, 26, 8.8, 17.5);
    inserirCarro(c, 78, 33.0, 10.1);
    inserirCarro(c, 65, 0.0, 46.4);
    inserirCarro(c, 16, 17.2, 14.3);
*/
    menu(c);

return 0;
}
