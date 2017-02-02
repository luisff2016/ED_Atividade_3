#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>   //uso da função pow() e sqrt()


/* EDI_2016_2_TURMA_2_Atividade_3*/
/** Componentes:
* Julio Antonio Gomes Oliveira
* Luis Fernando Feitosa
* Résmony Silva Muniz
**/

/* Atividade 3 - Lista linear e arquivo binario */

//Declaração das estruturas
typedef struct taxi Taxi;
typedef struct lista Lista;
typedef struct ponto Ponto;

struct taxi{
    Taxi *first;
};
struct lista{
    int idCarro;
    float x, y;
    Taxi *prox;
};
struct ponto{
    float x, y;
};

float* tarifa;
Ponto p;

//Funcões Auxiliares:
Taxi* criarLista(void);
int emptyList(Taxi* c);
void inserirCarro(Taxi* c, int carID, float x, float y);
int mostrarLista(Taxi* c);
Taxi* removerCarro(Taxi* c, int carID);
int procurarID(Taxi* c, int carID);
int procurarTaxi(Taxi* c, float x, float y);
void telaMenuPrincipal();
void menuPrincipal(Taxi* c);
void tituloAdm();
void telaAdministracao();
void menuAdministracao(Taxi* c);
void tituloMot();
void telaMotorista();
void menuMotorista(Taxi* c);
void tituloMenu();
void telaMenu();
void menu(Taxi* c);
void liberarCarros(Taxi* c);
void voltarAoMenu(Taxi* c);
char validarCarro();
void addCar(Taxi* c);
void pedirTaxi(Taxi* c);
void carroDisponivel(Taxi* c);
void liberarLista(Taxi* c);
void relatorioViagens(Taxi* c);
void relatorioFinanceiro(Taxi* c);
void cadMotorista(Taxi* c);
void listarMotorista(Taxi* c);
void alterarMotorista(Taxi* c);
void excluirMotorista(Taxi* c);
int validarID(Taxi *c);
int validarCoordenada(Taxi *c);


/*
void valorViagem(Taxi* c);
float calculaDistancia(Taxi*c,float x,float y);
*/

/** Empresa de Taxi. Carros são salvos na lista com duas infomações: uma identificação(int) e coordenadas(x,y) que vão de 0.0 a 50.0.
 * A saída dos carros é baseada na distância entre os seus pontos(x,y) e as coordenadas do passageiro.
 * Se a distância entre o carro e o passageiro for menor ou igual a 13 o primeiro carro encontrado é retirado da lista.
 * */

int main(){
    Taxi *c = criarLista();
    //valores inseridos para testes
    inserirCarro(c, 26, 0.0, 25.0);
    inserirCarro(c, 42, 25.0, 50.0);
    inserirCarro(c, 65, 0.0, 50.0);
    inserirCarro(c, 16, 50.0, 0.0);
    inserirCarro(c, 12, 0.0, 10.0);
    inserirCarro(c, 55, 33.2, 12.8);
    menuPrincipal(c);
    free(c);
return 0;
}

void telaMenuPrincipal(){
    system("cls");
    printf("\t\t=======================\n");
    printf("\t\t Empresa de Taxi\n");
    printf("\t\t=======================\n\n");
    printf("1 - Administracao. \n\n");
    printf("2 - Motorista. \n\n");
    printf("3 - Usuario. \n\n");
    printf("\n\n0 - SAIR\n\n");
    printf("\t\t\tSelecione uma das opcoes acima: ");
}

void menuPrincipal(Taxi* c){
    telaMenuPrincipal();
    int op;
        scanf("%d", &op);
    switch(op){
        case 0:
            exit(0);
        case 1:
            menuAdministracao(c);
            break;
        case 2:
            menuMotorista(c);
            break;
        case 3:
            menu(c);
            break;
        default:
            printf("\aOpcao invalida.");
            system("cls");
            menuPrincipal(c);
            break;
    }
}

void tituloAdm(){
    system("cls");
    printf("\t\t=======================\n");
    printf("\t\t Administracao \n");
    printf("\t\t=======================\n\n");
}

void telaAdministracao(){
    tituloAdm();
    printf("1 - Relatorio de viagens. \n\n");
    printf("2 - Relatorio Financeiro. \n\n");
    printf("3 - Adicionar carro. \n\n");
    printf("4 - Mostrar lista. \n\n");
    printf("5 - Liberar lista. \n\n");
    printf("6 - Valor da tarifa por Km. \n\n");
    printf("\n\n0 - Voltar ao menu anterior.\n\n");
    printf("\t\t\tSelecione uma das opcoes acima: ");
}

void relatorioViagens(Taxi* c){
    system("cls");
    tituloAdm();
    printf("\n\nEm construção\n\n");
    voltarAoMenu(c);
    menuAdministracao(c);
}

void relatorioFinanceiro(Taxi* c){
    system("cls");
    tituloAdm();
    printf("\n\nEm construção\n\n");
    voltarAoMenu(c);
    menuAdministracao(c);
}
int validarID(Taxi *c){
    int id;
    printf("Entre com uma identificacao para o carro: ");
    scanf("%d", &id);
    if(procurarID(c, id) != 1) return id;
    printf("Identificacao ja cadastrada. Tente novamente.\n");
    validarID(c);
}

int validarCoordenada(Taxi *c){
    printf("Insira a posicao inicial do carro (x,y): \n");
    scanf("%f %f", &p.x, &p.y);
    if (!(p.x <0.0 || p.x>50.0 || p.y<0.0 || p.y>50.0)) return 0;
    printf("Coordenadas invalidas. Tente valores entre 0.0 e 50.0.\n");
    validarCoordenada(c);
}

//Adicionar novo carro
void addCar(Taxi* c){
    system("cls");
    printf("\t\t===============================\n");
    printf("\t\t\tAdicionar Novos Carros\n");
    printf("\t\t===============================\n\n");
    printf("\n Escola uma opcao;\n");
    printf("\n 1 - Adicionar carro;\n");
    printf("\n 0 - Voltar ao menu anterior.\n");
    int op;
    scanf("%d", &op);
    int id;
    switch(op){
        case 0:
            menuAdministracao(c);
            break;
        case 1:
            id = validarID(c);
            validarCoordenada(c);
            inserirCarro(c, id, p.x, p.y);
            voltarAoMenu(c);
            addCar(c);
            break;
        default:
            printf("\aOpcao invalida.");
            voltarAoMenu(c);
            addCar(c);
            break;
        }

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
void liberarLista (Taxi* c){
    liberarCarros(c);
    system("cls");
	tituloAdm();
	printf("\aLista liberada.\n");
    voltarAoMenu(c);
    menuAdministracao(c);
}

void valorTarifa (Taxi* c,float* t){
    system("cls");
	tituloAdm();
	printf("\n Digite o valor da tarifa por km: \n");
    scanf("%f",*t);
    voltarAoMenu(c);
    menuAdministracao(c);
}


void menuAdministracao(Taxi* c){
    telaAdministracao();
    int op;
        scanf("%d", &op);
    switch(op){
        case 0:
            menuPrincipal(c);
        case 1:
            relatorioViagens(c);
            break;
        case 2:
            relatorioFinanceiro(c);
            break;
        case 3:
            addCar(c);
            break;
        case 4:
            carroDisponivel(c);
            break;
        case 5:
            liberarLista(c);
            break;
        case 6:
            valorTarifa(c,tarifa);
            break;
        default:
            printf("\aOpcao invalida.");
            system("cls");
            menuAdministracao(c);
            break;
    }
}

void tituloMot(){
    system("cls");
    printf("\t\t=======================\n");
    printf("\t\t Motorista \n");
    printf("\t\t=======================\n\n");
}

void telaMotorista(){
    tituloMot();
    printf("1 - Cadastro de Motorista. \n\n");
    printf("2 - Listar Motoristas. \n\n");
    printf("3 - Alterar Motoristas. \n\n");
    printf("4 - Excluir Motoristas. \n\n");
    printf("\n\n0 - Voltar ao menu anterior.\n\n");
    printf("\t\t\tSelecione uma das opcoes acima: ");
}

void cadMotorista(Taxi* c){
    system("cls");
    printf("Em construção");
    voltarAoMenu(c);
    menuMotorista(c);
}

void listarMotorista(Taxi* c){
    system("cls");
    printf("Em construção");
    voltarAoMenu(c);
    menuMotorista(c);
}

void alterarMotorista(Taxi* c){
    system("cls");
    printf("Em construção");
    voltarAoMenu(c);
    menuMotorista(c);
}

void excluirMotorista(Taxi* c){
    system("cls");
    printf("Em construção");
    voltarAoMenu(c);
    menuMotorista(c);
}

void menuMotorista(Taxi* c){
    telaMotorista();
    int op;
        scanf("%d", &op);
    switch(op){
        case 0:
            menuPrincipal(c);
        case 1:
            cadMotorista(c);
            break;
        case 2:
            listarMotorista(c);
            break;
        case 3:
            alterarMotorista(c);
            break;
        case 4:
            excluirMotorista(c);
            break;
        default:
            printf("\aOpcao invalida.");
            system("cls");
            menuMotorista(c);
            break;
    }
}

void tituloMenu(){
    system("cls");
    printf("\t\t=======================\n");
    printf("\t\t\t Usuario \n");
    printf("\t\t=======================\n\n");
}

void telaMenu(){
    tituloMenu();
    printf("1 - Pedir um taxi\n\n");
    printf("\n\n0 - Voltar ao menu anterior. \n\n");
    printf("\t\t\tSelecione uma das opcoes acima: ");
}

//Solicitar um taxi (remover da lista)
void pedirTaxi(Taxi* c){

    if(emptyList(c) == -1){
        printf("\a Nao ha carros disponiveis.\n");
        voltarAoMenu(c);
    }else{
        float x, y;
        printf("Digite a sua posicao (x, y): \n");
            scanf("%lf %lf", &x, &y);
        removerCarro(c, procurarTaxi(c, x, y));
        voltarAoMenu(c);
        menu(c);
    }
}

/*
void valorViagem(Taxi* c){
    system("cls");
    printf("\t\t============================\n");
    printf("\t\t\t Valor da viagem \n");
    printf("\t\t============================\n\n");
    float preco,*x,*y;
    preco = calculaDistancia(c,x,y)*tarifa;
    printf("Viagem calculada em: R$ &f",preco);
    voltarAoMenu(c);
    menu(c);
}
*/

void carroDisponivel(Taxi* c){
            system("cls");
            printf("\t\t============================\n");
            printf("\t\t\tCarros Disponiveis\n");
            printf("\t\t============================\n\n");
            mostrarLista(c);
            voltarAoMenu(c);
            menuAdministracao(c);
}

//Interface com o usuario
void menu(Taxi* c){
    telaMenu();
    int op;
        scanf("%d", &op);
    switch(op){
        case 0:
            menuPrincipal(c);
        case 1:
            pedirTaxi(c);
            break;
        /*
        case 2:
            valorViagem(c);
            break;
            */
        default:
            printf("\aOpcao invalida.");
            system("cls");
            menu(c);
            break;
    }
}

//Criar lista vazia
Taxi* criarLista(void){
    Taxi *c = (Taxi*) malloc(sizeof(Taxi));
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
void inserirCarro(Taxi* c, int carID, float x, float y){
    Lista* novo = (Lista*) malloc(sizeof(Lista));
    novo->idCarro = carID;
    novo->x = x;
    novo->y = y;
    Lista* ant = NULL;
    Lista* varrer = c->first;
    while(varrer!=NULL && varrer->idCarro<carID){
                ant = varrer;
                varrer = varrer->prox;
            }
    if(ant == NULL){
        novo->prox = c->first;
        c->first = novo;
    }
    else{
        novo->prox = ant->prox;
        ant->prox = novo;
    }
}

//Exibir elementos da lista
int mostrarLista(Taxi* c){
    if(c->first == NULL){
        printf("\aLista vazia.\n");
		return 1;
    }
    else{
        Lista*cars = NULL;
        for(cars = c->first ; cars != NULL ; cars = cars->prox)
            printf("Identificacao do carro: %d  |  Posicao(%.1f, %.1f)\n",
               cars->idCarro, cars->x, cars->y);
    return 0;
    }
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

    for(cars = c->first; cars !=  NULL; cars = cars->prox){
        if(cars->idCarro == carID){
            return 1;
        }
    }
    return -1;
}

//Procurando carro em uma distância próxima
int procurarTaxi(Taxi* c, float x, float y){
    Lista* cars;

    float res = 0.0;
    int carID = 0;

   for(cars = c->first; cars != NULL; cars = cars->prox){
        fflush(stdin); //limpar buffer
        //calcula a distancia entre dois pontos
        res = sqrt(pow(x - cars->x, 2)+ pow(y - cars->y, 2));
        if((res < 50)){
            carID = cars->idCarro;
            return carID;
        }else
        printf("Procurando carro mais  proximo...\n");
	}
    return -1;//elemento nao encontrado
}

/*
//calcula a distancia entre dois pontos
float calculaDistancia (Taxi *c,Ponto p){
    printf("Digite a sua posicao (x, y): \n");
            scanf("%f %f", &p.x, &p.y);
    float res = 0.0;
    res = sqrt(pow(x - cars->x, 2)+ pow(y - cars->y, 2));
    return res;
}
*/

//Funcao para reinicializar as opcoes do menu
void voltarAoMenu(Taxi* c){
    printf("\n\n");
    printf("\t\t\t\tPresssione qualquer tecla para voltar ao MENU");
      fflush(stdin);
        getch();
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





