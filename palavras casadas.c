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
    int respondido; //pra o programa avisar se a palavra j� foi respondida (0=vazio, 1=preenchido).
} dados;

// se pah a gnt pd so fzr um vetor cm tamanho MTO grande, e falar q tem um
// limite de palavras (tp 10), vamo testar
//pior q acho que 5 palavras ja ta dboa. se nao capaz de nem caber na tela

dados infojogo[N];
int cont = 0, fim; // N vai aumentando(alocacao dinamica q o jo falou)
// funcao de menu
void menu();

// funcao de carregar
void carregando();

void teladefim();

// funcao q entra dados
void entradados(dados v[N]);

void mostradados(dados v[N], int a);

void editadados(dados v[N]);

void imprimirdica(dados v[N]);

void jogada(dados v[N]);

void jogo(dados v[N]);

void iniciar();

void desligar();


int main(void) {
    iniciar();
    menu();
}

void menu() {
    system("cls");
    printf("Bem vindo ao Super Palavras Cruzadas!!!! :)\n\n");
    int opcao;
    printf("Escolha o que deseja fazer:\nOpcao 1: Montar o jogo\nOpcao 2: Jogar\nOpcao 3: Sair do jogo\n");

    scanf("%d", &opcao);
    char c;
    scanf("%c", &c);

    while (opcao != 1 && opcao != 2 && opcao != 3) {
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
        jogo(infojogo);
        teladefim();
        desligar();
        abort();
    }
    if (opcao == 3) {
        system("color 6");
        printf("Voce saiu do jogo.");
        desligar();
        abort();
    }
    return;
}

void iniciar(){
    printf("Iniciando o Windows .....");
    system("color 1");
    Beep(622, 350);
    Beep(311, 100);
    system("color 6");
    Beep(466, 350);
    Beep(311, 100);
    system("color 2");
    Beep(415, 400);
    Beep(311, 250);
    Beep(622, 400);
    system("color 4");
    Beep(466, 750);
    system("color 7");
}

void desligar(){
    system("cls");
    printf("Desligando o Windows .....");
    system("color 4");
    Beep(840, 200);
    system("color 2");
    Beep(620, 200);
    system("color 6");
    Beep(420, 200);
    system("color 1");
    Beep(460, 800);
    system("cls");
    system("color 7");
}

// falta matriz apoio
void entradados(dados v[N]) {
    int igual;
    char c;
    char numero[] = "0123456789";
    printf("Voce esta entrando suas palavras!\n");
    do {
        cont++;
        printf("Entre os dados da palavra %d!\n", cont);
        printf("Palavra: ");
        while(strlen(v[cont].palavra)<=1||igual==0||strpbrk(v[cont].palavra, numero)!=NULL){
            fgets(v[cont].palavra, sizeof(v[cont].palavra), stdin);
            strtok(v[cont].palavra, "\n");
            for(int i=1; i<cont; i++){
                igual=strcasecmp(v[cont].palavra, v[i].palavra);
                if(igual==0)break;
            }
            if(strpbrk(v[cont].palavra, numero)!=NULL){
                system("color 6");
                Sleep(500);
                printf("Nao insira numeros nas palavras >:(\nInsira uma palavra valida:\n");
                system("color 7");
            }
            else if(strlen(v[cont].palavra)<=1){
                system("color 6");
                Sleep(500);
                printf("Por favor, insira uma palavra com mais de uma letra:\n");
                system("color 7");
            }
            if(igual==0){
                system("color 6");
                Sleep(500);
                printf("Essa palavra ja esta no jogo!\nDigite outra palavra:\n");
                system("color 7");
            }
        }
        printf("Dica: ");
        fgets(v[cont].dica, sizeof(v[cont].dica), stdin);
        strtok(v[cont].dica, "\n");

        printf("Voce inseriu a palavra %d\n\n",cont);
        v[cont].respondido=0;
        printf("Deseja inserir mais? s para outra palavra e n para sair ");
        scanf("%c",&c);
        char y;
        scanf("%c",&y);
    } while(c=='s' || c=='S');
    fim=cont;
    carregando();
    editadados(infojogo);
}

void editadados(dados v[N]){
    system("cls");
    char c='s';
    do{
        system("cls");
        printf("Agora vamos revisar os dados!\n");
        for(int l=1;l<=cont;l++){
            mostradados(v,l);
            printf("\n");
        }
        printf("Deseja editar alguma palavra? (s para sim e n para nao) ");
        scanf("%c",&c);
        char l;
        scanf("%c",&l);
        if(c=='s' || c=='S'){
            char o;
            int edita;
            printf("\nDiga o numero da palavra que voce quer editar\n");
            scanf("%d", &edita);
            char h;
            scanf("%c",&h);
            while(edita<=0||edita>cont){
                printf("Digite uma palavra valida! >:(\n");
                scanf("%d", &edita);
                scanf("%c",&h);
            }

            printf("Entre os novos dados da palavra %d\n", edita);
            printf("Palavra: ");
            int igual;
            char numero[]="0123456789";
            do{
                fgets(v[edita].palavra, sizeof(v[edita].palavra), stdin);
                strtok(v[edita].palavra, "\n");
                    for(int i=1; i<=cont; i++){
                        if(i!=edita){
                        igual=strcasecmp(v[edita].palavra, v[i].palavra);
                        if(igual==0)break;
                        }
                    }
                    if(strpbrk(v[edita].palavra, numero)!=NULL){
                        system("color 6");
                        Sleep(500);
                        printf("Nao insira numeros nas palavras >:(\nInsira uma palavra valida:\n");
                        system("color 7");
                    }
                    else if(strlen(v[edita].palavra)<=1){
                        system("color 6");
                        Sleep(500);
                        printf("Por favor, insira uma palavra com mais de uma letra:\n");
                        system("color 7");
                    }
                    if(igual==0){
                        system("color 6");
                        Sleep(500);
                        printf("Essa palavra ja esta no jogo!\nDigite outra palavra:\n");
                        system("color 7");
                    }
            }while(strlen(v[edita].palavra)<=1|| igual==0||strpbrk(v[edita].palavra, numero)!=NULL);

            printf("Dica: ");
            fgets(v[edita].dica, sizeof(v[edita].dica), stdin);
            strtok(v[edita].dica, "\n");

            printf("Voce editou a palavra %d\n\n",edita);
            getch();
        }
    }while(c=='s' || c=='S');
    system("cls");
}

// ok
void mostradados(dados v[N], int a) {
    printf("Dados da palavra %d\n", a);
    printf("Palavra: %s\nDica: %s\nOrientacao: %s\n", v[a].palavra, v[a].dica,v[a].orientacao);
}

//ok
void imprimirdica(dados v[N]){
    for (int i=1; i<=cont; i++) {
        if(v[i].respondido==0){
            printf("Dica da palavra %d: ", i);
            puts(v[i].dica);
            printf("Orientacao da palavra %d: ", i);
            puts(v[i].orientacao);
            printf("\n");
        }
  }
}

//ok
void carregando(){
    system("cls");
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

void teladefim(){
    for(int b=0;b<1;b++){
        char vitc[13];
        memset(vitc,'-',12);
        vitc[0]='o';
        system("color 6");
        puts(vitc);printf("    \\[^^]\\    \n");printf("Voce venceu!\n");puts(vitc);
        for(int i=1;i<12;i++){
            system("cls");
            vitc[i]='o';
            vitc[i-1]='-';
            puts(vitc);
            if(i%2==1){
                system("color 9");
                printf("   /[^^]/    \n");
            }else{
                system("color 6");
                printf("   \\[^^]\\    \n");
            }
            printf("Voce venceu!\n");puts(vitc);
            Sleep(125);
        }
        for(int i=10;i>=0;i--){
            system("cls");
            vitc[i]='o';
            vitc[i+1]='-';
            puts(vitc);
            if(i%2==1){
                system("color 9");
                printf("   /[^^]/    \n");
            }else{
                system("color 6");
                printf("   \\[^^]\\   \n");
            }
            printf("Voce venceu!\n");puts(vitc);
            Sleep(125);
        }
        system("cls");
        system("color 7");
    }
    printf("Aperte qualquer botao para sair\n");
    getch();
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
        int teste=strcasecmp(v[t].palavra, resp);
            if(teste==0){
                system("color 2");
                printf("Resposta correta! XD\n");
                v[t].respondido=1;
                fim--;
                getch();
                system("cls");
                system("color 7");
            }
            else {
            system("color 4");
            printf("Resposta incorreta ;-;\n");
            getch();
            system("cls");
            system("color 7");
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
