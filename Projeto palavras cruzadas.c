#include <stdbool.h> //eventualemente a gnt pd usar um true ou false
#include <stdio.h>
#include <stdlib.h>
#include <string.h> //funcoes de string
#include <conio.h>
#include <windows.h>

#define N 100

typedef struct {
    char palavra[50];
    char dica[100];      // pode aumentar
    char orientacao[30]; // vertical ou horizontal (por 0 ou 1 pra facilitar)
    int respondido; //pra o programa avisar se a palavra já foi respondida (0=vazio, 1=preenchido).
} dados;

// se pah a gnt pd so fzr um vetor cm tamanho MTO grande, e falar q tem um
// limite de palavras (tp 10), vamo testar
//pior q acho que 5 palavras j� ta dboa. se n�o capaz de nem caber na tela

dados infojogo[N];
int cont = 0, fim; // N vai aumentando(alocacao dinamica q o jo falou)
// funcao de menu
void menu();

// funcao de carregar
void carregando();

// funcao q entra dados
void entradados(dados v[N]);

void mostradados(dados v[N], int a);

void checadados();

void imprimirdica(dados v[N]);

void jogada(dados v[N]);

void jogo(dados v[N]);


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
        jogo(infojogo);
        carregando();
        menu();
    }
    if (opcao == 4) {
        printf("Voce saiu do jogo.");
        abort();
    }
    return;
}

// ok
void entradados(dados v[N]) {
    char c;
    printf("Voce esta entrando suas palavras!\n");
    do {
        cont++;
        printf("Entre os dados da palavra %d!\n", cont);
        printf("Palavra: ");
        fgets(v[cont].palavra, sizeof(v[cont].palavra), stdin);
        strtok(v[cont].palavra, "\n");
        while(strlen(v[cont].palavra)<=1){
            printf("Por favor, insira uma palavra com mais de uma letra:\n");
            fgets(v[cont].palavra, sizeof(v[cont].palavra), stdin);
            strtok(v[cont].palavra, "\n");
        }
        printf("Dica: ");
        fgets(v[cont].dica, sizeof(v[cont].dica), stdin);
        strtok(v[cont].dica, "\n");
        printf("Orientacao (v ou h): ");
        fgets(v[cont].orientacao, sizeof(v[cont].orientacao), stdin);
        strtok(v[cont].orientacao, "\n");

        printf("Voce inseriu a palavra %d\n\n",cont);
        v[cont].respondido=0;
        printf("Deseja inserir mais? s para outra palavra e n para sair ");
        scanf("%c",&c);
        char k;
        scanf("%c",&k);
    } while(c=='s' || c=='S');
    fim=cont;
    printf("\nVoce montou seu jogo!\n pressione qualquer tecla para voltar ao menu\n");
}

// ok
void mostradados(dados v[N], int a) {
    printf("Dados da palavra %d\n", a);
    printf("Palavra: %s\nDica: %s\nOrientacao: %s\n", v[a].palavra, v[a].dica,v[a].orientacao);
}

//ok
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
        int k;
        printf("\nDiga o numero da palavra que voce quer checar\n");
        scanf("%d", &k);
        char h;
        scanf("%c",&h);
        while(k<=0||k>cont){
        printf("Digite uma palavra valida! >:(\n");
        scanf("%d", &k);
        scanf("%c",&h);
        }

        mostradados(infojogo, k);
        printf("Deseja checar outro dado? (S para sim e N para nao) ");
        scanf("%c",&c);
        char j;
        scanf("%c",&j);
    } while(c=='s' || c=='S');
    printf("Voce realizou a checagem");
}

//ok
void imprimirdica(dados v[N]){
    for (int i=1; i<=cont; i++) {
        printf("Dica da palavra %d: ", i);
        puts(v[i].dica);
        printf("Orientacao da palavra %d: ", i);
        puts(v[i].orientacao);
        printf("\n");
  }
}

//ok
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

void jogada(dados v[N]){
    char resp[50];
    int t;
    printf("Escolha a palavra que deseja tentar:\n");
            scanf("%d", &t);
            char l;
            scanf("%c", &l);
        while(t>cont||t<=0||v[t].respondido==1){
            if(t>cont||t<=0){
                printf("Nao existe palavra com esse numero. Escolha uma palavra valida:\n");
            }
            if(v[t].respondido==1){
                printf("Essa palavra ja foi respondida! Escolha outra palavra:\n");
            }
            scanf("%d", &t);
            char l;
            scanf("%c", &l);
        }
        printf("Voce escolheu a palavra: %d\nInsira sua resposta:\n", t);
        fgets(resp, sizeof(resp), stdin);
        strtok(resp, "\n");
        int teste=strcmp(v[t].palavra, resp);
            if(teste==0){
                printf("Resposta correta! XD\n");
                v[t].respondido=1;
                fim--;
                getch();
            }
            else {
            printf("Resposta incorreta ;-;\n");
            getch();
            }
}

void jogo(dados v[N]) {
  system("cls");
  char resp[50];
  int t;
  if(cont==0){
    printf("Nenhuma palavra foi inserida ainda!\nPressione qualquer tecla para voltar ao menu! :)");
    getch();
    carregando();
    menu();
  }
  else{
    printf("Bom jogo!!!!! :)\n");
    while(1){
        imprimirdica(infojogo);
        jogada(infojogo);
        if(fim==0) break;
        system("cls");
    }
    return;
  }
}
