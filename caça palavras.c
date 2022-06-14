#include <stdbool.h> //eventualemente a gnt pd usar um true ou false
#include <stdio.h>
#include <stdlib.h>
#include <windows.h> //da a funcao sleep
#include <string.h> //funcoes de string
#define N 100

typedef struct {
    int numero;
    char palavra[50];
    char dica[100];      // pode aumentar
    char orientacao[30]; // vertical ou horizontal (por 0 ou 1 pra facilitar)
} dados;

// se pah a gnt pd so fzr um vetor cm tamanho MTO grande, e falar q tem um
// limite de palavras (tp 10), vamo testar
//pior q acho que 5 palavras já ta dboa. se não capaz de nem caber na tela

dados infojogo[N];
int cont = 0; // N vai aumentando(alocacao dinamica q o jo falou)

// funcao de menu
void menu();

// funcao q entra dados
int entradados(dados v[N], int cont);

void mostradados(dados v[N], int a);

void checadados(int cont);

void imprimir (dados v[N]);

int jogo(dados v[N], int cont);


int main(void) {
    menu();
}

void menu() {
    system("cls");
    printf("Bem vindo ao Super Palavras Cruzadas!!!! :)\n\n");
    int opcao;
    printf("Escolha o que deseja fazer:\nOpcao 1: Montar o jogo (inserir palavras)\nOpcao 2: Checar palavras\nOpcao 3: Jogar\nOpcao 4: Sair do jogo\n");

    scanf("%d", &opcao);
    char c;
    scanf("%c", &c);

    while (opcao != 1 && opcao != 2 && opcao != 3 && opcao != 4) {
        printf("Digite uma opcao valida!!! >:-(\n");
        scanf("%d", &opcao);
    }

    if (opcao == 1) {
        system("cls");
        cont=entradados(infojogo, cont);
        Sleep(2000);
        menu();
    }
    if (opcao == 2) {
        checadados(cont);
        Sleep(2000);
        menu();
    }
    if (opcao == 3) {
        jogo(infojogo, cont);
        // funcao de jogo EU VOU ME MATAR
    }


    if (opcao == '4') {
        printf("Voce saiu do jogo.");
        abort();
    }
    return;
}

// ok
int entradados(dados v[N], int cont) {
    char c='s';
    printf("Voce esta entrando suas palavras!\n");
    do {
        cont++;
        printf("Entre os dados da palavra %d!\n", cont);
        printf("Palavra: ");
        fgets(v[cont].palavra, sizeof(v[cont].palavra), stdin);
        printf("Dica: ");
        fgets(v[cont].dica, sizeof(v[cont].dica), stdin);
        printf("Orientacao: ");
        fgets(v[cont].orientacao, sizeof(v[cont].orientacao), stdin);

        printf("Parabens! voce inseriu a palavra %d\n\n",cont);
        v[cont].numero = cont;


        printf("Deseja inserir mais? S para outra palavra e N para sair ");
        scanf("%c",&c);
        char k;
        scanf("%c",&k);


    } while(c=='s' || c=='S');
    printf("\nVoce montou seu jogo\n");
    return cont;
}



// ok
void mostradados(dados v[N], int a) {
    printf("Dados da palavra %d\n", a);
    printf("Palavra: %sDica: %sOrientacao: %s\n", v[a].palavra, v[a].dica,v[a].orientacao);
}



void checadados(int cont){
    system("cls");
    char c='s';
    printf("Voce esta checando suas palavras!\n");
    if(cont==0){
        printf("Nenhuma palavra foi inserida ainda! :/\n");
        Sleep(2000);
        menu();
    }
    do {
        int k=0;
        printf("\nDiga o numero da palavra que voce quer checar\n");
        scanf("%d", &k);
        while(k<cont||k>cont){
        printf("Digite uma palavra valida! >:(\n");
        scanf("%d", &k);
        }

        char h;
        scanf("%c",&h);
        mostradados(infojogo, k);
        printf("Deseja checar outro dado? (S para sim e N para nao) ");
        scanf("%c",&c);
        char j;
        scanf("%c",&j);
    } while(c=='s' || c=='S');
    printf("Voce realizou a checagem");
}

void imprimir(dados v[N]){
    for (int i=0; i<=cont; i++) {
        printf("Dica da palavra %d: \n", i);
        puts(v[i].dica);
        printf("Orientacao da palavra %d:\n", i);
        puts(v[i].orientacao);
        printf("\n");
  }
}


int jogo(dados v[N], int cont) {
  char resp;
  int t;
  // string resp; //é assim que usa string? ou da pra deixar como char mesmo?
  printf("Bom jogo!!!!! :)\n");
  if(cont==0){
    printf("Nenhuma palavra foi inserida ainda!");
    Sleep(2000);
    menu();
  }
  else{
    imprimir(infojogo);
  }
  //printf("Escolha a palavra que deseja tentar:\n");
  //  scanf("%d", &t);
  //printf("Voce escolheu a palavra: %d\nInsira sua resposta:\n", t);
   //fgets(resp, sizeof(resp) stdin); //usar fgets
//strcmp(resp, v[t-1].palavra)
   //scanf("%s", &resp); //achei, era aqui
  // if(resp==v[t-1].palavra){

  //}
}
