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
//pior q acho que 5 palavras j� ta dboa. se n�o capaz de nem caber na tela

dados infojogo[N];
int cont = 0; // N vai aumentando(alocacao dinamica q o jo falou)

// funcao de menu
void menu();

// funcao de carregar
void carregando();

// funcao q entra dados
void entradados(dados v[N]);

void mostradados(dados v[N], int a);

void checadados();

void imprimirdica(dados v[N]);

int jogo();


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
        carregando();
        entradados(infojogo);
        carregando();
        menu();
    }
    if (opcao == 2) {
        system("cls");
        carregando();
        checadados();
        carregando();
        menu();
    }
    if (opcao == 3) {
        system("cls");
        carregando();
        jogo();
        carregando();
        menu();
        // funcao de jogo EU VOU ME MATAR
    }


    if (opcao == 4) {
        printf("Voce saiu do jogo.");
        abort();
    }
    return;
}

// ok
void entradados(dados v[N]) {
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
}



// ok
void mostradados(dados v[N], int a) {
    printf("Dados da palavra %d\n", a);
    printf("Palavra: %sDica: %sOrientacao: %s\n", v[a].palavra, v[a].dica,v[a].orientacao);
}



void checadados(){
    system("cls");
    char c='s';
    printf("Voce esta checando suas palavras!\n");
    if(cont==0){
        printf("Nenhuma palavra foi inserida ainda!\nPressione qualquer tecla para voltar ao menu! :)");
        getch();
        carregando();
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

void imprimirdica(dados v[N]){
    for (int i=1; i<=cont; i++) {
        printf("Dica da palavra %d: \n", i);
        puts(v[i].dica);
        printf("Orientacao da palavra %d:\n", i);
        puts(v[i].orientacao);
        printf("\n");
  }
}
void carregando(){
   for(int k=0;k<1;k++){
        char carr[7];
        memset(carr,'-',6);
        carr[0]='o';
        printf("  ");puts(carr);printf("carregando\n  ");puts(carr);
        for(int i=1;i<6;i++){
            system("cls");
            carr[i]='o';
            carr[i-1]='-';
            printf("  ");puts(carr);printf("carregando\n  ");puts(carr);
            Sleep(100);
        }
        for(int i=4;i>=0;i--){
            system("cls");
            carr[i]='o';
            carr[i+1]='-';
            printf("  ");puts(carr);printf("carregando\n  ");puts(carr);
            Sleep(100);
        }
        system("cls");
    }
    system("cls");
}

int jogo() {
  system("cls");
  char resp;
  int t;
  // string resp; //� assim que usa string? ou da pra deixar como char mesmo?
  printf("Bom jogo!!!!! :)\n");
  if(cont==0){
    printf("Nenhuma palavra foi inserida ainda!\nPressione qualquer tecla para voltar ao menu! :)");
    getch();
    carregando();
    menu();
  }
  else{
    imprimirdica(infojogo);
    getch();
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
