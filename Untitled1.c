#include <stdbool.h> //eventualemente a gnt pd usar um true ou false
#include <stdio.h>
#include <stdlib.h>
#include <string.h> //funcoes de string
#include <conio.h>
#include <windows.h>

#define N 100
#define BLACK     "\e[0;30m"
#define RED       "\e[0;31m"
#define REDSUB    "\e[4;31m"
#define GREEN     "\e[0;32m"
#define GREENHIGH "\e[0;92m"
#define YELLOW    "\e[0;33m"
#define BLUE      "\e[0;34m"
#define BLUEHIGH  "\e[0;94m"
#define MAGENTA   "\e[0;35m"
#define CYAN      "\e[0;36m"
#define RESET     "\e[0;0m"

typedef struct {
    char palavra[50];
    char dica[100];
    int orientacao; // 1 - Horizontal // 2 - Vertical
    int x;
    int y;
    int respondido; //0 - Vazio //1 - Preenchido).
} dados;

void menu();
void carregando();
void teladefim();
void entradados(dados v[N]);
void mostradados(dados v[N], int a);
void editadados(dados v[N]);
void imprimirdica(dados v[N]);
void jogada(dados v[N]);
void jogo(dados v[N]);
void titulo();
//void desligar();
void surpresa();

// Fun��es da matriz:
void montamatriz();
char** resetmatriz();
void imprimirmatriz();
void freematriz();
void addpalavra(int p, int q);
int redlin(int p);
int redcol(int p);


dados infojogo[N];
int cont = 0, fim;


int m, n;
char** mat;
char alfabeto[26] = {"ABCDEFGHIJKLMNOPQRSTUVWXYZ"};



int main(void) {
    titulo();
    menu();
}


void menu() {
    volta:
    system("cls");
    printf("\e[0;97mBem vindo ao Super Palavras Cruzadas!!!! "YELLOW":)"RESET"\n\n");
    int opcao;
    printf(BLUEHIGH"Escolha o que deseja fazer:"RESET"\nOpcao 1: Montar o jogo\nOpcao 2: Jogar\nOpcao 3: Sair do jogo\n");

    scanf("%d", &opcao);
    getchar();

    while (opcao != 1 && opcao != 2 && opcao != 3) {
        printf(REDSUB "Digite uma opcao valida!!! >:-(" RESET "\n");
        scanf("%d", &opcao);
        getchar();
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
        //desligar();
        surpresa();
        return;
    }
    if (opcao == 3) {
        system("color 6");
        printf("\e[4;31mVoce saiu do jogo.");
        getchar();
        //desligar();
        surpresa();
        return;
    }
    return;
}


void titulo(){
int i=0;
    while(!kbhit()){
   // for(int i=0; i<4; i++){
        system("color 6");
        system("cls");
        if(i%4==0){
        printf("\n");
        printf("                   $$\\                                                  \n");
        printf("                   $$ |                                                  \n");
        printf("  $$$$$$\\  $$$$$$\\ $$ |$$$$$$\\$$\\    $$\\ $$$$$$\\ $$$$$$\\  $$$$$$$\\       \n");
        printf(" $$  __$$\\ \\____$$\\$$ |\\____$$\\$$\\  $$  $$  __$$\\\\____$$\\$$  _____|      \n");
        printf(" $$ /  $$ |$$$$$$$ $$ |$$$$$$$ \\$$\\$$  /$$ |  \\__$$$$$$$ \\$$$$$$\\        \n");
        printf(" $$ |  $$ $$  __$$ $$ $$  __$$ |\\$$$  / $$ |    $$  __$$ |\\____$$\\       \n");
        printf(" $$$$$$$  \\$$$$$$$ $$ \\$$$$$$$ | \\$  /  $$ |    \\$$$$$$$ $$$$$$$  |      \n");
        printf(" $$  ____/ \\_______\\__|\\_______|  \\_/   \\__|     \\_______\\_______/       \n");
        printf(" $$ |                                              $$\\                   \n");
        printf(" $$ |                                              $$ |                  \n");
        printf(" \\$$$$$$$\\ $$$$$$\\ $$\\   $$\\$$$$$$$$\\$$$$$$\\  $$$$$$$ |$$$$$$\\  $$$$$$$\\ \n");
        printf(" $$  _____$$  __$$\\$$ |  $$ \\____$$  \\____$$\\$$  __$$ |\\____$$\\$$  _____|\n");
        printf(" $$ /     $$ |  \\__$$ |  $$ | $$$$ _/$$$$$$$ $$ /  $$ |$$$$$$$ \\$$$$$$\\  \n");
        printf(" $$ |     $$ |     $$ |  $$ |$$  _/ $$  __$$ $$ |  $$ $$  __$$ |\\____$$\\ \n");
        printf(" \\$$$$$$$\\$$ |     \\$$$$$$  $$$$$$$$\\$$$$$$$ \\$$$$$$$ \\$$$$$$$ $$$$$$$  |\n");
        printf("  \\_______\\__|      \\______/\\________\\_______|\\_______|\\_______\\_______/ \n");
        printf("\n");
        }

        if(i%4==1){
        printf("\n");
        printf("                    /$$                                                   \n");
        printf("                   | $$                                                   \n");
        printf("   /$$$$$$  /$$$$$$| $$ /$$$$$$ /$$    /$$/$$$$$$ /$$$$$$  /$$$$$$$       \n");
        printf("  /$$__  $$|____  $| $$|____  $|  $$  /$$/$$__  $|____  $$/$$_____/       \n");
        printf(" | $$  \\ $$ /$$$$$$| $$ /$$$$$$$\\  $$/$$| $$  \\__//$$$$$$|  $$$$$$        \n");
        printf(" | $$  | $$/$$__  $| $$/$$__  $$ \\  $$$/| $$     /$$__  $$\\____  $$       \n");
        printf(" | $$$$$$$|  $$$$$$| $|  $$$$$$$  \\  $/ | $$    |  $$$$$$$/$$$$$$$/       \n");
        printf(" | $$____/ \\_______|__/\\_______/   \\_/  |__/     \\_______|_______/        \n");
        printf(" | $$                                                /$$                  \n");
        printf(" | $$                                               | $$                  \n");
        printf(" |_/$$$$$$$ /$$$$$$ /$$   /$$/$$$$$$$$ /$$$$$$  /$$$$$$$ /$$$$$$  /$$$$$$$\n");
        printf("  /$$_____//$$__  $| $$  | $|____ /$$/|____  $$/$$__  $$|____  $$/$$_____/\n");
        printf(" | $$     | $$  \\__| $$  | $$  /$$$$/  /$$$$$$| $$  | $$ /$$$$$$|  $$$$$$ \n");
        printf(" | $$     | $$     | $$  | $$ /$$__/  /$$__  $| $$  | $$/$$__  $$\\____  $$\n");
        printf(" |  $$$$$$| $$     |  $$$$$$//$$$$$$$|  $$$$$$|  $$$$$$|  $$$$$$$/$$$$$$$/\n");
        printf("  \\_______|__/      \\______/|________/\\_______/\\_______/\\_______|_______/ \n");
        printf("\n");
        }

        if(i%4==2){
        printf("                    __                                                   \n");
        printf("                   |  \\                                                  \n");
        printf("   ______   ______ | $$ ______ __     __  ______  ______   _______       \n");
        printf("  /      \\ |      \\| $$|      |  \\   /  \\/      \\|      \\ /       \\      \n");
        printf(" |  $$$$$$\\ \\$$$$$$| $$ \\$$$$$$\\$$\\ /  $|  $$$$$$\\\\$$$$$$|  $$$$$$$      \n");
        printf(" | $$  | $$/      $| $$/      $$\\$$\\  $$| $$   \\$/      $$\\$$    \\       \n");
        printf(" | $$__/ $|  $$$$$$| $|  $$$$$$$ \\$$ $$ | $$    |  $$$$$$$_\\$$$$$$\\      \n");
        printf(" | $$    $$\\$$    $| $$\\$$    $$  \\$$$  | $$     \\$$    $|       $$      \n");
        printf(" | $$$$$$$  \\$$$$$$$\\$$ \\$$$$$$$   \\$    \\$$      \\$$$$$$$\\$$$$$$$       \n");
        printf(" | $$                                               __                   \n");
        printf(" \\ $$                                              |  \\                  \n");
        printf("   _______  ______  __    __ ________ ______   ____| $$ ______   _______ \n");
        printf("  /       \\/      \\|  \\  |  |        |      \\ /      $$|      \\ /       \\\n");
        printf(" |  $$$$$$|  $$$$$$| $$  | $$\\$$$$$$$$\\$$$$$$|  $$$$$$$ \\$$$$$$|  $$$$$$$\n");
        printf(" | $$     | $$   \\$| $$  | $$ /    $$/      $| $$  | $$/      $$\\$$    \\ \n");
        printf(" | $$_____| $$     | $$__/ $$/  $$$$|  $$$$$$| $$__| $$  $$$$$$$_\\$$$$$$\\\n");
        printf("  \\$$     | $$      \\$$    $|  $$    \\$$    $$\\$$    $$\\$$    $|       $$\n");
        printf("   \\$$$$$$$\\$$       \\$$$$$$ \\$$$$$$$$\\$$$$$$$ \\$$$$$$$ \\$$$$$$$\\$$$$$$$ \n");
        }

        if(i%4==3){
        printf("                    __                                                   \n");
        printf("                   /  |                                                    \n");
        printf("   ______   ______ $$ | ______  __     __ ______  ______   _______         \n");
        printf("  /      \\ /      \\$$ |/      \\/  \\   /  /      \\/      \\ /       |        \n");
        printf(" /$$$$$$  |$$$$$$  $$ |$$$$$$  $$  \\ /$$/$$$$$$  $$$$$$  /$$$$$$$/         \n");
        printf(" $$ |  $$ |/    $$ $$ |/    $$ |$$  /$$/$$ |  $$//    $$ $$      \\         \n");
        printf(" $$ |__$$ /$$$$$$$ $$ /$$$$$$$ | $$ $$/ $$ |    /$$$$$$$ |$$$$$$  |        \n");
        printf(" $$    $$/$$    $$ $$ $$    $$ |  $$$/  $$ |    $$    $$ /     $$/         \n");
        printf(" $$$$$$$/  $$$$$$$/$$/ $$$$$$$/    $/   $$/      $$$$$$$/$$$$$$$/          \n");
        printf(" $$ |                                                __                    \n");
        printf(" $$ |                                               /  |                   \n");
        printf(" $$_______  ______  __    __ ________  ______   ____$$ | ______   _______  \n");
        printf("  /       |/      \\/  |  /  /        |/      \\ /    $$ |/      \\ /       | \n");
        printf(" /$$$$$$$//$$$$$$  $$ |  $$ $$$$$$$$/ $$$$$$  /$$$$$$$ |$$$$$$  /$$$$$$$/  \n");
        printf(" $$ |     $$ |  $$/$$ |  $$ | /  $$/  /    $$ $$ |  $$ |/    $$ $$      \\  \n");
        printf(" $$ \\_____$$ |     $$ \\__$$ |/$$$$/__/$$$$$$$ $$ \\__$$ /$$$$$$$ |$$$$$$  | \n");
        printf(" $$       $$ |     $$    $$//$$      $$    $$ $$    $$ $$    $$ /     $$/  \n");
        printf("  $$$$$$$/$$/       $$$$$$/ $$$$$$$$/ $$$$$$$/ $$$$$$$/ $$$$$$$/$$$$$$$/   \n");
        }
        if(i<4){printf("\n\n\n");}
        if(i>=4){
        printf("\n                     - Aperte enter para comecar -                    \n\n");
        }
        Sleep(1000);
        i++;
    }
    system("cls");
    system("color 7");
    getchar();
}

/*void desligar(){

    system("cls");
    printf("Desligando o Windows .....");
    system("color 4");
    Beep(840, 200);
    system("color 2");
    Beep(620, 200);
    system("color 6");
    Beep(420, 200);
    system("color 1");
    Beep(470, 600);
    system("cls");
    system("color 7");
}*/


void entradados(dados v[N]) {
    int igual;
    int c;
    char numero[] = "0123456789";
    printf(BLUE "Voce esta entrando suas palavras!" RESET "\n");
    mais:
        cont++;
        printf(GREEN"Entre os dados da palavra %d!"RESET"\n", cont);
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
                printf("\e[1;31mNao insira numeros nas palavras"RED" >:("RESET"\nInsira uma palavra valida:\n");
                system("color 7");
            }
            else if(strlen(v[cont].palavra)<=1){
                system("color 6");
                Sleep(500);
                printf("\e[1;33mPor favor, insira uma palavra com mais de uma letra:"RESET"\n");
                system("color 7");
            }
            if(igual==0){
                system("color 6");
                Sleep(500);
                printf(YELLOW"Essa palavra ja esta no jogo!"RESET"\nDigite outra palavra:\n");
                system("color 7");
            }
        }
        printf("Dica: ");
        fgets(v[cont].dica, sizeof(v[cont].dica), stdin);
        strtok(v[cont].dica, "\n");
        printf(GREEN "Voce inseriu a palavra %d"RESET"\n\n",cont);
        v[cont].respondido=0;
        repete:
        printf(YELLOW"Deseja inserir mais?"RESET"\n");
        printf("1. [Sim]\n2. [Nao]\n");
        scanf("%d",&c);
        getchar();
        if(c==1){
            system("cls");
            goto mais;
        }
        if(c!=1&&c!=2){
            system("color 6");
            printf(RED"Digite uma opcao valida >:("RESET"\n");
            Sleep(500);
            system("color 7");
            goto repete;
        }
    fim=cont;
    carregando();
    editadados(infojogo);
}


void editadados(dados v[N]){
    system("cls");
    char c='s';
    do{
        system("cls");
        printf(BLUE"Agora vamos revisar os dados!"RESET"\n");
        for(int l=1;l<=cont;l++){
            mostradados(v,l);
            printf("\n");
        }
        repete:
        printf(YELLOW"Deseja editar alguma palavra?"RESET"\n1. [Sim]\n2. [Nao]\n");
        scanf("%d",&c);
        if(c!=1&&c!=2){
            system("color 6");
            printf(RED"Digite uma opcao valida >:("RESET"\n");
            Sleep(500);
            system("color 7");
            goto repete;
        }
        if(c==1){
            char o;
            int edita;
            printf("\n"YELLOW"Diga o numero da palavra que voce quer editar"RESET"\n");
            scanf("%d", &edita);
            getchar();
            while(edita<=0||edita>cont){
                system("color 6");
                printf(RED"Digite uma palavra valida! >:("RESET"\n");
                Sleep(500);
                system("color 7");
                scanf("%d", &edita);
                getchar();
            }

            printf(YELLOW"Entre os novos dados da palavra %d"RESET"\n", edita);
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
                        printf(RED"Nao insira numeros nas palavras >:("RESET"\nInsira uma palavra valida:\n");
                        system("color 7");
                    }
                    else if(strlen(v[edita].palavra)<=1){
                        system("color 6");
                        Sleep(500);
                        printf(RED"Por favor, insira uma palavra com mais de uma letra:"RESET"\n");
                        system("color 7");
                    }
                    if(igual==0){
                        system("color 6");
                        Sleep(500);
                        printf(RED"Essa palavra ja esta no jogo!\nDigite outra palavra:"RESET"\n");
                        system("color 7");
                    }
            }while(strlen(v[edita].palavra)<=1|| igual==0||strpbrk(v[edita].palavra, numero)!=NULL);

            printf("Dica: ");
            fgets(v[edita].dica, sizeof(v[edita].dica), stdin);
            strtok(v[edita].dica, "\n");

            printf(GREEN"Voce editou a palavra %d"RESET"\n\n",edita);
            getchar();
        }
    }while(c==1);
    system("cls");
    montamatriz();
}


void mostradados(dados v[N], int a) {
    printf("Dados da palavra %d\n", a);
    printf("Palavra: %s\nDica: %s\n", v[a].palavra, v[a].dica);
}


void imprimirdica(dados v[N]){
    for (int i=1; i<=cont; i++) {
        if(v[i].respondido==0){
            printf("Dica da palavra %d: ", i);
            puts(v[i].dica);
            /*printf("Orientacao da palavra %d: ", i);
            puts(v[i].orientacao);*/
            printf("\n");
        }
  }
}


void carregando(){
    system("cls");
    char carr[10];
    int cor;
    for(int i=0; i<10; i++){
        carr[i]=("%c%c%c"RESET, 177);
        printf("%c", carr[i]);
    }
    for(cor=0; cor<6; cor++){
        system("cls");
        printf("Carregando\n");
        for(int e=0; e<10; e++){
            if(e<2*cor){
                printf(GREEN"%c"RESET, carr[e]);
            }
            else printf("%c"RESET, carr[e]);
        }
                    printf("\n");
        Sleep(300);
    }
    system("cls");
}



void teladefim(){
    while(!kbhit()){
        for(int i=0; i<4; i++){
            system("cls");
               for(int e=1; e<15; e++){
                    if(e<=2*i+1||e>=14-2*i){
                        printf(GREEN"%c"RESET, 205);
                    }
                    else printf("%c"RESET, 205);
               }
                            printf("\n");

            if(i==0||i==4){
                printf(GREEN"  %c%c%c%c%c%c%c"RESET"\n", 192, 91, 94, 45, 94, 218, 93);
            }
            if(i==1||i==3||i==5){
                printf(GREEN"   %c%c%c%c%c%c%c"RESET"\n", 192, 91, 94, 250, 94, 93, 217);
            }
            if(i==2||i==6){
                printf(GREEN"    %c%c%c%c%c%c%c"RESET"\n", 91, 191, 94, 45, 94, 93, 217);
            }

            printf(GREENHIGH"Voce venceu!!"RESET "\n");

            for(int e=1; e<15; e++){
                if(e<=2*i+1||e>=14-2*i){
                    printf(GREEN"%c"RESET, 205);
                }
                else printf("%c"RESET, 205);
            }
            printf("\n\n\n");
            Sleep(300);

        }
        system("cls");
    }
    getchar();
    system("cls");
    printf(BLUE"Voce saiu do jogo"RESET"\n");
    getchar();
}


void jogada(dados v[N]){
    char resp[50];
    int t;
    printf(GREEN"Escolha a palavra que deseja tentar:"RESET"\n");
            scanf("%d", &t);
            getchar();
        while(t>cont||t<=0||v[t].respondido==1){
            if(t>cont||t<=0){
                printf(YELLOW"Nao existe palavra com esse numero. Escolha uma palavra valida:"RESET"\n");
            }
            if(v[t].respondido==1){
                printf(YELLOW"Essa palavra ja foi respondida!"RESET" Escolha outra palavra:\n");
            }
            scanf("%d", &t);
            getchar();
        }
        printf(CYAN"Voce escolheu a palavra: %d"RESET"\nInsira sua resposta:\n", t);
        fgets(resp, sizeof(resp), stdin);
        strtok(resp, "\n");
        int teste=strcasecmp(v[t].palavra, resp);
            if(teste==0){
                system("color 2");
                printf(GREENHIGH"Resposta correta! XD"RESET"\n");
                v[t].respondido=1;
                fim--;
                getchar();
                system("cls");
                system("color 7");
            }
            else {
            system("color 4");
            printf("\e[0;91MResposta incorreta ;-;"RESET"\n");
            getchar();
            system("cls");
            system("color 7");
            }
}


void jogo(dados v[N]) {
  system("cls");
  char resp[50];
  int t;
  if(cont==0){
    system("color 4");
    printf("Nenhuma palavra foi inserida ainda!\nPressione qualquer tecla para voltar ao menu! :)");
    getchar();
    system("color 7");
    menu();
  }
  else{
    printf(MAGENTA"Bom jogo!!!!! :)"RESET"\n");
    while(1){
        imprimirdica(infojogo);
        jogada(infojogo);
        if(fim==0) break;
        system("cls");
    }
    return;
    }
}

// Incrimentos a fazer
void montamatriz() {

    /*
    A fazer:
    - Testar se haver� sobreposi��o de letras distintas
    - Impedir que letra estravaze limite da matriz
    - Limitar tamanho m�ximo tabuleiro (lin < )
    - Testar se coordenada y � uma letra

    */

    infojogo[1].x = 0;
    infojogo[1].y = 0;

    orientacao1:

    printf(CYAN"Qual a orientacao da palavra \"%s\"?:"RESET"\n\n", infojogo[1].palavra);
    printf("1. [Horizontal]\n");
    printf("2. [Vertical]\n\n");
    scanf(" %d", &infojogo[1].orientacao);

    if (infojogo[1].orientacao == 1) {
        m = 1;
        n = strlen(infojogo[1].palavra);
    }
    else if (infojogo[1].orientacao == 2) {
        m = strlen(infojogo[1].palavra);
        n = 1;
    }
    else {
        system("cls");
        printf(RED"Opcao incorreta!"RESET"\n");
        goto orientacao1;
    }
    system("cls");

	mat = resetmatriz(m, n, mat);
    imprimirmatriz(m, n, mat);


    system("cls");

    addpalavra(1, 1);


    for(int p = 2; p <= cont; p++) {
        orientacao:

        printf(YELLOW"Qual a orientacao da palavra \"%s\"?:"RESET"\n\n", infojogo[p].palavra);
        printf("1. [Horizontal]\n");
        printf("2. [Vertical]\n\n");
        scanf(" %d", &infojogo[p].orientacao);
        getchar();

        if (infojogo[p].orientacao == 1) {
            n += 2*strlen(infojogo[p].palavra);
        }
        else if (infojogo[p].orientacao == 2) {
            m += 2*strlen(infojogo[p].palavra);
        }
        else {
            system("cls");
            printf(RED"Opcao incorreta!"RESET"\n");
            goto orientacao;
        }

        resetmatriz(m, n, mat);
        system("cls");

        // palavra i

        for (int i = 1; i < p; i++) {

            if (infojogo[p].orientacao == 1) {
                infojogo[i].y += (int) strlen(infojogo[p].palavra);
            }
            else if (infojogo[p].orientacao == 2) {
                infojogo[i].x += (int) strlen(infojogo[p].palavra);
            }

            system("cls");
            addpalavra(i, p);
        }

		coordenadas:

        imprimirmatriz();

		char letra;
        printf(GREEN"Entre as coordenadas da palavra \"%s\": "RESET, infojogo[p].palavra);
        scanf(" %c %d", &letra, &infojogo[p].x);
        getchar();
            letra = toupper(letra);

            for (int i = 0; i < 26; i++) {
                if(letra == alfabeto[i]) {
                    infojogo[p].y = i;
                }
            }
            if (infojogo[p].y > n-1 || infojogo[p].x > m-1) {
                system("cls");
                printf(YELLOW"Coordenadas invalidas, tente novamente!"RESET"\n");
                goto coordenadas;
            }

        system("cls");
        addpalavra(p, p);

        int m_ = redlin(p);
        int n_ = redcol(p);

        freematriz(m, n, mat);
        m = m_;
        n = n_;
        mat = resetmatriz();

        for (int i = 1; i <= p; i++) {
            system("cls");
            addpalavra(i, p+1);
        }

        system("cls");
        imprimirmatriz();
   }

    Sleep(500);
    printf(GREEN"Tabuleiro de jogo montado!"RESET"\n");
    getchar();
    printf("Aperte enter para continuar.\n");
    getchar();
}


void imprimirmatriz() {
    printf("%5s", "");
		for (int j = 0; j < n; j++) {
			printf("%c ", alfabeto[j]);
	    }
		printf("\n");
		printf("%4s", "");
		for (int j = 0; j < n; j++) {
			printf("__");
	    }
		printf("\n");


    for(int i = 0; i < m ; i++) {

        if (i < 10) {printf("  %d| ", i);}
		else {printf(" %d| ", i);}

        for(int j = 0; j < n; j++) {
            printf("%c ", mat[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}


char** resetmatriz() {
  mat = (char**) calloc(m, sizeof(char*));
	for (int k = 0; k < m; k++) {
		mat[k] = calloc(n, sizeof(char));
	}

	for(int i = 0; i < m ; i++) {
        for(int j = 0; j < n; j++) {
            mat[i][j] = (char) '.';
        }
	}

	return mat;
}


void freematriz() {
    for (int k = 0; k < m; k++) {
		free(mat[k]);
	}
	free(mat);
}


void addpalavra(int p, int q) {

    if (infojogo[p].orientacao == 1) {
        for (int i = 0; i < strlen(infojogo[p].palavra); i++) {
            mat[infojogo[p].x][infojogo[p].y + i] = (char) infojogo[p].palavra[i];

            if (p == q) {
                system("cls");
                imprimirmatriz();
                Sleep(100);
            }
        }
    }
    else if (infojogo[p].orientacao == 2) {
        for (int i = 0; i < strlen(infojogo[p].palavra); i++) {
            mat[infojogo[p].x + i][infojogo[p].y] = (char) infojogo[p].palavra[i];

            if (p == q) {
                system("cls");
                imprimirmatriz();
                Sleep(100);
            }
        }
    }

}


int redlin(int p) {
    int m_ = m;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (mat[i][j] != '.') {

                m_ -= i;
                for (int q = 1; q <= p; q++) {
                    infojogo[q].x -=i;
                }

                for (int k = 0; k < m; k ++) {
                    for (int l = 0; l < n; l++) {
                        if (mat[m-k-1][n-l-1] != '.') {
                            m_ -= k;
                            return m_;
                        }
                    }
                }

            }
        }
    }
}


int redcol(int p) {
    int n_ = n;
    for (int j = 0; j < n; j++) {
        for (int i = 0; i < m; i++) {
            if (mat[i][j] != '.') {

                n_ -= j;
                for (int q = 1; q <= p; q++) {
                    infojogo[q].y -=j;
                }

                for (int l = 0; l < n; l++) {
                    for (int k = 0; k < m; k ++) {
                        if (mat[m-k-1][n-l-1] != '.') {
                            n_ -= l;
                            return n_;
                        }
                    }
                }

            }
        }
    }
}


void surpresa(){
    system("color F7");
    printf(GREEN":!!::!!!:::::::!!!!!!!!!!!####################################################################################################@@#####!!!!#######!!!!!!!####!!!!!!!!#####################@@@#########@########@############@########!!!!!!####");
    printf(GREEN"!!!::!!::!!!!!!!!################################################################################################################!:.....::!!##!!!!:::::!##:::::::::!!###################@@@##################@#####################!!!!!!####");
    printf(GREEN"!!!:!!!!!################################################@@@@@@@@@@@@@@@@@@@@@@@@@######@@@@@@@@@@@@@@@@@##@@@@@@################!:::!:..:!!#!!!!::::::!##::.......:!!!!!!!!############@@@###############################@#########!!!!!####");
    printf(GREEN"::!!!!::!################@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@####!!###!!!!!!!!:::!:.::!!!!:::::.:::!##:........:!:::!!!!!!!!!!:!!###@@@########################################!!!!!!####");
    printf(GREEN"::!!:!!!!!############@@@@###@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@#######!!!#############!!!:!!##!!!!::::::::!##:..    ..::::::!!!!!!!!::!!!!###########################################!!!!!!!####");
    printf(GREEN"!:!!:::!!!############@@@@##@@##@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@######!!!!"BLACK"#########@@@@@@@@@@##@@@@@@@@@######"GREEN"!!!##!:........:!::::!!!!!!!!!::!!!####!!!!!!!##@##!#####@#####################!!!!!#####");
    printf(GREEN"!!!!::::!!########################@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@#########"BLACK"####@@###@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@#@@#@##"GREEN"!!!:::....:!:::::!!!!::::::!!!####!:::!:!!!#!!!!####################!!###!!!!!!#####");
    printf(GREEN"!!!!:!!!!!#########################@@@@@@@@@@@@@@#######@@#@@@@@@@@@@@@@@@@@@@@@@@@@@@@#############"BLACK"###@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@###########"GREEN"!!!!!:::::!!!!:!::::!!!!###!!::!:!!!!!:::!!##@###############!!###!!!!!!#####");
    printf(GREEN"!!!!:!!!!!########################@@@@@@@@@@###########@@@@@@@@@##@@@@##@@@@@@####@@@@##!!######"BLACK"#####@@@@@@@@#@@@@@@@@#@@@@@@@@@@@@@@@@@@@@@@@@@@@@####@@@@@@@@@@####"GREEN"!!!!!!!!!::::::!!!####!:::::!!!!!::::!!#############@###!!###!!!!!!#####");
    printf(GREEN"!!::::!!!!#####################@@@@@@@@##############@#@@@@####!!!!###!!#@@@@##!##@@@@#######"BLACK"#######@##@@@@@@@@@@@###@@@@@@@######@@@@@@@@@@@####@@@@@@@@@@@@@@@@@@##########"GREEN"!!!::::!!!####!!:::::!!#!::::!!###!!!!!##########!###!!!!!!#####");
    printf(GREEN"!:!!:!!!!!#######################@@#################!!!!####@@#!::!##!!!#@@@@##!#######"BLACK"##@@@@@####@@@@@@@@@@@@###@@@@@@#######################@@@@@@@@@@@@@@@@@@@@@@@@@#########"GREEN"!!:!!!!#@##!:::::!!!!!::::!!!#!!!!::::!!#####!!##!!!!!!!#####");
    printf(GREEN"!:!!!!!::!##########################################!!!!####@@#!!!!###!!#@@@@##!!##"BLACK"##@@#@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@######################@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@######"GREEN"!!!!!#@##!!:::::!!!!:::::!##!!!!!!!:::!########!!!!!!######");
    printf(GREEN"!::!:!!::!!####################!####################!!!!#######!!!!##!!!#@@@@##!#"BLACK"##@##@#@@####@@#@@@@@@@@@@@@################################@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@#####"GREEN"!!!!!#@##!::::::!!!!:::::!##!!!!!!:::!!#!!!!!!#!!!#!!!#####");
    printf(GREEN"!::!::!!:!!#################!!!!####################!!!!!######!::!##!#!##@@##"BLACK"######@@@@@@##@@@@@#######@#############"YELLOW"!!!!!!!!!!!!!!!!!!!!"BLACK"##############@@@@@@@@@@@@@@@@@@@@@@@@@@###"GREEN"!!#@##!:::!!!!!!!::::!!##!!!::!::::!#!!::::!!!!#!!######");
    printf(GREEN"!!!!!!!:!!!#########################################!!!!!######!::!!#!!!#####"BLACK"#####@@@##@@###@@##########"YELLOW"!!!!!!!!!!!!!!:::::::::::::::::::!!!!!!!!!!!!!!!!!!"BLACK"#########@@@@@@@@@@@@@@@@###"GREEN"#@##!:::!!!!#!!::::!!###!!::::::!!#!!:::::.::!!!######");
    printf(GREEN":!!!!!!:!!!###########!!!!##!!######################!!!!!######!:!!#!!!!###"BLACK"#######@@@@@@@@####"YELLOW"!!!!!#!!!!!!!!!!!:::::::::::.................:::::::::::::::::::!!!!!!"BLACK"#####@@@@@@@@@@@@###"GREEN"@#!!:::!!!!!!!::::!!###!!::::::!!#!!::::::..:::!#####");
    printf(GREEN":!!!!!!:!!!########!!!!!!!!!!!!!!###################!!!!!######!:!!#!!!!#"BLACK"#########@@@@#####"YELLOW"!!!!!!!!:!!!!!:::::::...::............................:::::::::::::::::::!!!!"BLACK"####@@@@@@@@@@@#@#"GREEN"!!:::!!!!!!!::::!!##!!!::!:::!!#!!:::::..:::::!!###");
    printf(GREEN":!!!!!!:!!!######!!!!!!!!!!!!!!!!!!#################!!!!!######!:!!#!!!!"BLACK"########@@@@#####"YELLOW"!!!!::::::::::::::::::::...:..................::........::::::::::::::::::::::!!!!!"BLACK"###@@@@@@@@@@##"GREEN"!:::!!!!#!!::::!!##!!!::!!::!!#!!:.::::::::::!::!!");
    printf(GREEN":!!!::!!!!!##!!!!!!!!!!!!!!!!!!!!!!#################!!!!!######!:!!!!!"BLACK"#########@@@####"YELLOW"!!!!:::......::::::::::::::::::::::::::::::::::::::.::::::::::::::::::::::::::::::::::!!!"BLACK"##@@@@@@@@##"GREEN"!:::!!!!#!!:::::!##!!!::!!!!!!#!::.::::::::::!!:::");
    printf(GREEN"!!!:!!:::!!!!::!!!!!!!!!!!!!!!!!!!!!!###############!!!!!######!::!!!"BLACK"#########@####"YELLOW"!!!:::........::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::!!"BLACK"###@@@@@@##"GREEN":::!!!!#!!:::::!##!!:::!!!!!!#!::.:::.::::::!!:::");
    printf(GREEN"!::!!:!!!::::!!!!!!!!!!!!!!!!!!!!!!!!!!#############!!!!!######!:!!##"BLACK"########@@###"YELLOW"!:::......::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::!!"BLACK"###@@@@@@#"GREEN"!::!!!!#!!::.::!##!!:::!!!!!!#!!::::::::::::!!:::");
    printf(GREEN"!::!:!::  .:::!!!!!!!!!!!!!!!!!!!!!!!!##############!!!!!######!::!##"BLACK"############"YELLOW"!::......::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::!!!!!!!!!!!!!!!!!!:::::::::!!"BLACK"###@@@@@@#"GREEN"!!!!!!#!!::.::!##!!:::!!!:!!#!!::::::::::::!!:::");
    printf(GREEN":!!:::.   .:::!!!!!!!!!!!!!!!!!!!!!!!!!!#!!!########!!!!!######!:.:!"BLACK"##@@@@#####"YELLOW"!!::.....:::::::::::::::::::::::::::::::::::::::::::::::::::!!:!!!!!!!!!!!!!!!!!!!!!!!!!!!::::::::!!!"BLACK"###@@@@@##"GREEN"!!!!!#!!::::!!##!!!!!!!:!!!#!::::::::::::!!!:::");
    printf(GREEN"!:::.     .::::!!!!!!!!!!!!!!!!!!!!!!!!!!!########!!!!!!!!#####!:::!"BLACK"##@@@#####"YELLOW"!!::.....:::::::::::::::::::::::::::::!!!!!!::::!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!::!!!!!"BLACK"####@@@@#"GREEN"!!!!!#!!!:::!!#!!!!!!!!:!!!#!!:::::::::::!!!:::");
    printf(GREEN"::.       .:::::!!!!!!!!!!!!!!!!!!!!!!!!!!######!!!!!!:!!!#####::.:!"BLACK"#@@@####"YELLOW"!!:::.....::::::::::::::::::::::::::::::::::::::::::::::::::::::!!:::::!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"BLACK"######@@##"GREEN"!!!!#!!::::!!#!!!!!:::::!!#!!:::::::::::!!!:::");
    printf(GREEN".         .:::::!!!!!!!!!!!!!!!!!!!!!!!!!!#####!!!!!!:::!!!####!:::!"BLACK"#@@###"YELLOW"!!!:::.....:::::::::::::::::::::::::::::::....::::::::::::::::::::::::::::::::::::!!!!!!!!!!!!!!!!!!!!!!!!!"BLACK"#######@##"GREEN"!:::!::.....:!!!::::::::!!#!!!!!::::::::!!!:::");
    printf(GREEN"          .:::::!!!!!!!!!!!!!!!!!!!!!!!!!!#####!!!!!!:::!!!####!:::#"BLACK"####"YELLOW"!!!!:::.....::::::::::::::::::::::::::::.....::::::::::::::::::::::...::::::::::::::::::::::::::!!!!!!!!!!!!!"BLACK"##########"GREEN"!...:........!!!!!!!!!!!!!##!!!!!:::::::!!!:::");
    printf(GREEN"          .:::::::!!!!!!!!!!!!!!!!!!!!!!!!#!###!!!!!!:::!!!####!::!"BLACK"####"YELLOW"!!!!!::.....:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::!!!!!!!!!!!!!!!"BLACK"##########"GREEN"!...:........!!!!!:::::!!##!!!::::::::::!!!::!");
    printf(GREEN"          .:!::::::!!!!!!!!!!!!!!!!!!!!!!!#####!!!!!!:::!!!!###!::"BLACK"#####"YELLOW"!!!!::......:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::!!!::!!!!!!:::::::::::::::::::!!!!!!!!!"BLACK"###########"GREEN"!::!:::..:::#!!::::::::!!#!!::::::::::!!!:::!");
    printf(GREEN"          .:!:::::::!!!!!!!!!!!!!!#############!!!!!!:::!!!!####@@"BLACK"####"YELLOW"!!!:........::::::::::::::::::::::::::::!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!::::::::::::::!!!!!!!!"BLACK"####@@@@##"GREEN"#!!#!!::::!!#!!:::::!!!!##!!::::::::::!!!:::!");
    printf(GREEN"          ..::::::::!!!!!!!!!!!!!!##############!!!!!!!:!!!!##@##"BLACK"#####"YELLOW"!!:..............::::::!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!:::::!!!!!!!!!"BLACK"####@@@##"GREEN"##!#!!::::!!#!!!!!!!!!!!!!!!!!!:::::::!!!:::!");
    printf(GREEN"          ..!:::!:::::::::::::::::!!!!!!!!!!!!!!!!!!!::::!!!!#####"BLACK"###"YELLOW"!!:..............:::::!!!!!!!!!!!!######!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!#############!!!!!!!!!!!!!!!!!!!!!!!"BLACK"###@@###"GREEN"!:::::.::::::::::::::::::::::::::::::!!!!!!!");
    printf(GREEN"           .!:!!!!:...........................................:::!"BLACK"###"YELLOW"!!:...........::::!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!##################!!!!!!!!!!!!!!!!!!!!!!!!"BLACK"##@@###"GREEN"!::::::::::::::::::::::::::::::::::::!!!!!!!");
    printf(GREEN"          ..!!!!!#####!!!!!!!!!!!!!!::::::::::::::::::::::::::::!!"BLACK"###"YELLOW"!!.........::::::!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!################!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"BLACK"###@@@##"GREEN"!!!!!!!!!!!!!!!##!##########!!::::::!!!!!!!");
    printf(GREEN"          ..!!!!!!########################################"YELLOW"!::::!!"BLACK"####"YELLOW"!!........::::::::::::!!!!!!!!!!!!!!!!!!!!!####!!!!!!!!!!!!!!!!#################!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"BLACK"#@@@@##"GREEN"#!!!!!!!!!#!!!!!!!!!#######!!!:::::!!!!!!!!");
    printf(GREEN"           .:!!!!!!#####################################"YELLOW"!!:!!!:::!!!!!!.......:::::::::!!!!!!!!#!################!!!####!!!!!!!!!!!!!##############!####################!!!!!!!!!!!!!!!!!!!"BLACK"##@@@#"GREEN"!!:!!!!!!!!!!!!!!!!!!!!!!!!!#!!:::::!!!!!!!!");
    printf(GREEN"           .:!!!!!!!####################################"YELLOW"!!!!!!!!!!!!!!:.....::::::::!!!!!!!!###!!##@@@@@@@@##############!!!!!!!!!!!!!###################@@@@@@@@#####@#####!!!!!!!!!!!!!!!!"BLACK"####!"GREEN"!####!!!!!!!!!!!!!!!!!!!!!!!!!:::::!!!!!!!!");
    printf(GREEN"           .:!!!!!!!####################################"YELLOW"!!!!!!!!!::!!::.....:::::::!!!!##!!##!!!!!##@@@@@@################!!!!!!!!!!!!!##################@@@@@@@@##!###########!!!!!!!!!!!!!"BLACK"######"GREEN"######!!!!!!!!!!!!!!!!!!!!!!!::::::!!!!!!!!");
    printf(GREEN"          ..:!!!!!!!!###################################"YELLOW"!!!!!!!!!!!!::.......::::::::::::::::!!!!!!!######################!!!!::::::!!!!###############################!!!!!!!!!!!:!::::!!!!"BLACK"######"GREEN"######!!!!!!!!!!!!!!!!!!!!!!!::::::!!!!!!!!");
    printf(GREEN"          ..:!!!!!!!!!###################################"YELLOW"!!!!!!:::!::.  ............::::::::::!!!!!!!!!!!!!!!!!!!!!!##!!!!!!!::::::::!!!!#######!!!!!!!!!!!!!!!!!!!!!!!!!!::::::::::::::!!!!!"BLACK"!##"YELLOW"!!!"GREEN"#####!!!!!!!!!!!!!!!!!!!!!!!::::::!!!!!!!!");
    printf(GREEN"          ..:!!!!!!!!!###################################"YELLOW"!!!!!::!!!!::    ........:::::::::::::!!!!!!!!!!!!!!!!!!!!!!!!!!!!:::::..::::!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!:::::::::::::::::::!!!"BLACK"!#"YELLOW"!!!!"GREEN"###!!!!!!!!!!!!!!!!!!!!!!!!::::::!!!!!!!!");
    printf(GREEN"          .::!!!!!!!!!!##################################"YELLOW"!!!!!:!!!!!!:. ........:::::::::::::::::::!!!!!!!!!!!!!!!!!!!!!!:::::::..:::::!!!!!!!!!!!!!!!!!!!!!!!!!!!!!::::::::::::::::::::::::!!"BLACK"###"YELLOW"!!!"GREEN"########!!!!!############!!::::::!!!!!!!!");
    printf(GREEN"          .::!!!!!!!!!!!#################################"YELLOW"!!!!!:!!!!!!:.......:::::::::::::::::::::::::!!!:!!!!!:::!!:::::::::::...:::::!!!!!!!!!!!!!!!!!!!!!!:::::::::::::::::::::::::::::::!!!"BLACK"#"YELLOW"!!!!!"GREEN"######@@###@@@@@@@@@@@@@@!!::::!!!!!!!!!");
    printf(GREEN"...      ..::!!!!!!!!!!!##################################"YELLOW"!!::!!!!!!!:......::::::::::::::::::::::::::::::::::::::::::::::::::.....:::::::::::::::::::::::::::::::::::::::::::::::::::::!!!!!!"BLACK"###"YELLOW"#!!!"GREEN"!!!!!!!#!!##@@@@@@@@@@@@@!!::::!!!!!!!!!");
    printf(GREEN".::........::!!!!!!!!!!!!##################################"YELLOW"!:::!!!!!!:......:::::::::::::::::::::::!!!!!!!!!!!!!!!!!:::::::::::....::::::!!!!!!!!!!!!!!!!!!!:::::::::::::::::!!!!:!!!!!!!!!!!!"BLACK"##"YELLOW"##!!!"GREEN"##@@@@@@@####@@@@@@@@@@@@!!::::!!!!!!!!!");
    printf(GREEN"::::......:::!!!!!!!!!!!!##################################"YELLOW"!!::::!!!!:.:..::::::::::::::!!!!!!!!!!!!!!!!!!!!#!!!!!!!!!!::::::::::::::::::!!!!!!:!!!!!!##!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"BLACK"#"YELLOW"#!!!!!"GREEN"##@@@@@@#####@@@@@@@@@@@#!:::::!!!!!!!!!");
    printf(GREEN".:::::....:::!!!!!!!!!!!!!##################################"YELLOW"!:!!!::!::...::::::::!!!!!!!!!!!!!!!!!!!!!!#####!!!!:::::::::::::::::::::::::!:::::::::!!!#######!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"GREEN"#@@!!###!!####@@@@@@@@@@#!::::!!!!!!!!!!");
    printf(GREEN".:::::::::::!!!!!!!!!!!!!!!#################################"YELLOW"!::!!!::::::::::::!!!!!!!!!!!!!!!!!!!!!#########!!!!::::::::::::!!!!!!!!!!!!!!!!!::::!!!!!##########!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!#!!!"GREEN"##@#!!#########@@@@@@@@@@#!::::!!!!!!!!!!");
    printf(GREEN".:::::::::::!!!!!!!!!!!!!!!!!################################"YELLOW"!::::::::::::::!!!!!!!!!!!!!!!!!!!!!!#######!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!###!###########!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"GREEN"#@@#!!########@@@@@@@@@@@#!:::!!!!!!!!!!!");
    printf(GREEN"::::::::::::!!!!!!!!!!!!!!!!!#################################"YELLOW"!:::.::.::::!!!!!!!!!!!!!!!!!!!!!!########!!!!!!!!#######!!!!!!!!!!!!!!!###############!!!!!##########!!!!!!!!!###!!!!!!!!!!!!!!!:!!!"GREEN"##@@#!!#@########@@@@@@@@@#!::!!!!!!!!!!!!");
    printf(GREEN"::::::::::::!!!!!!!!!!!!!!!!!!#################################"YELLOW"!:..::::::!!!!!!!!!!!!!!!!!!!!!#######!!!!!!!!!!!!##############!#####################!!!!!!!##########!!!!!!######!!##!!!!!!!!:!!!!"GREEN"#@@@#!!#######@####@@@@@@@#!!::!!!!!!!!!!!");
    printf(GREEN".:::::...:::!!!!!!!!!!!!!!!!!!!#################################"YELLOW"!!!:::::::!!!!!!!!!!!!!!!!!!!#####!!!!!!!!!!!!!!!!!!##############################!!!!!!!!!!####!#######!!!#########!!!!!!!!!!!!!"GREEN"##@!!::!!!!!!!!!!!!!!!!::!!!!!!!:!!!!!!!!!!!");
    printf(GREEN":.........::!!!!!!!!!!!!!!!!!!!!######################################"YELLOW"!::::!!!!!!!!!!!!!!!!!!#####!!!!!!!!!!!!!!!!!!!!!!#########################!!!!!!!!!!!########!!!!!!#######!!!##!!!!!!"GREEN"#####@@@#::::::::::::!!!!!!!!!!!::::!:!!!!!!!!!!!");
    printf(GREEN":.........::!!!!!!!!!!!!!!!!!!!#############################@@@@###!!!!:"YELLOW":::!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!###########################################!!!!!!!!!!##!!!!##!!##!!"GREEN"##@@@@@@@#!::::::::::::!!!!!!!!!!!::!!!!!!!!!!!!!!");
    printf(GREEN"..........::!!!!!!!!!!!!!!!!!!!!##################################!!!!!:::"YELLOW"::!!!!!!!!!!!!!!!!!!!!!!!!#############################################################!!!!!!!!!!!!!!!!!!!!!!!!!"GREEN"##@@@@@##!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
    printf(GREEN"..........::!!!!!!!!!!!!!!::!!!!!!!!!!!!!!!!!!!!!!!!!!!!#######!!:::::::::::"YELLOW"!!!!!!!!!!!!!!!!!!!!!!!######@@@@@#######!!!!!!!!!!!!###!!!!!##############@@@@@####!!!!!!!!!!!!!!!!!!!!!!!!!!!"GREEN":::::!!!!!!!!!!!!!!!!!!!!!!!!!####!!!!!!!!!!!!!!!!");
    printf(GREEN"..:::.....::!!!!!!!!!!!!!!!::::::::::::::::::::::!!!!!!!!!!!!!!!::.........::"YELLOW"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!###########!!#############################@@@#####!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"GREEN":::::!!!!!!!!!!#############@@@@@@#!!!!!!!!!!!!!!!!");
    printf(GREEN"....::....::!!!!!!!####!!!!!!!!!!!!!!!!!!:::::::::::::::::::::::::.........::"YELLOW"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!###!######!###############!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"GREEN"::::!!!!#####@@@@@@@@@@@@@@@@@@@@@@#!!!!!!!!!!!!!!!!");
    printf(GREEN"....::::::::!!!!!!!#################!!!!!!!!!!!!!!!!!!!:::::::::::::::::::::::"YELLOW"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"GREEN"######################@@@@@@@@@@@@@@###!!!!!!!!!!!!!!!!");
    printf(GREEN".....:::::::!!!!!!!!###############################!!!!!!!!!!!!!!!!!!!!!!!!!!!::"YELLOW"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!#######!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"GREEN"###@@@######@@######################@@@@#!!!!!!!!!!!!!!!!");
    printf(GREEN"::::::::::::!!!!!!!!!###########################@@@@@############!!!!!!!!!!!!!!!"YELLOW"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!####################!!!!!!!!!!!!!!!!!!!!!!!!#####!!"GREEN"###############@#!!!!!!!!###!##########@@#!!!!!!!!!!!!!!!!");
    printf(GREEN"::::::::::::!!!!!!!!!##############################@########@@@@@@@@@@@@@########"YELLOW"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!##########################!!!!!!!!!!!!!!!!!!!!!!#####!!"GREEN"#######################!####!#############@@#!!!!!!!!!!!!!!!!");
    printf(GREEN"::::::::::::!!!!!!!!!!#################################@########@@@@@@@@@@@@@@@#@@##"YELLOW"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!###!!!####!!!!!!!!!!!!!!!!!!!!!!!!!!!########"GREEN"################!!##!!!!!##!####!#########@@#!!!!!!!!!!!!!!!!");
    printf(GREEN"::::::::::::!!!!!!!!!!!##############################@@@#######@@@@#########@####!!!!!!"YELLOW"!!!!!!!!!!!!!!!::::::::!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!###########"GREEN"#################!!!!!!!!!##!!################!!!!!!!!!!!!!!!!");
    printf(GREEN".....:::::::!!!!!!!!!!!!##############################################!!!!!!!!###!!!!!"RESET"##"YELLOW"!:!!!!!!!!!!!!!!!:::::::::::!:::!!!!!!!!!!!!!!!!:::::::::::!!!!!!!!!!!!!!###########"RESET"@@@@###"GREEN"!!!!########!!!!####!!###!!!!#!!!!!!!!!##!!!!!!!!!!!!!!!!!");
    printf(GREEN"::::::::::::!!!!!!!!!!!!##################################!!!!!!!!!!!!!#####!!!!!!!!"RESET"###@"YELLOW"!::::!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!##############"RESET"@@@@@#########"GREEN"!!!!!:::::::::::::::::::!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
    printf(GREEN"::::::::::::!!!!!!!!!!!!!######################!!!:::::::!!!!!!!!#######!!!!!!!!!!!"RESET"##@@@"YELLOW"!::::!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!##############!!!!#"RESET"@@@@@@@##############"GREEN"!!!!!::::::::::::::::::::::!!!!!!!!!!!!!!!!!");
    printf(GREEN"!!::::::::::!!!!!!!!!!!!!!###########!!!!!:::::::!!!!!!!#######!!!!!!!!!#!!!!####!!"RESET"#@@@@"YELLOW"!:::!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!###########################"RESET"@@@@@@@@@#####################"GREEN"!!!!!!!!!!!:::::::!!!!!!!!!!!!!!!!!");
    printf(GREEN"##!!::::::::!!!!!!!!!!!!!!!!!!!!!::::::::!!!!!!!#########!!!!!!!!!######!!!"RESET"#########@@@@"YELLOW"!!:!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!##!!!!#######################################"RESET"@@@@@@@@@@@@#############################"GREEN"!!!!!!!!!!!!!!!!!!!!!!!!");
    printf(GREEN"###!!:::::::!!!!!!!!!!!!!:::::::::!!!!!!!#########!!!!!!!!"RESET"#####################!!###@@@@#"YELLOW"!!!!!!!!!!!!!!!!!!!!!!!!!!########################################################"RESET"@@@@@@@@@@@@@@##################@@@@@@@@######"GREEN"!!!!!!!!!!!!!!!!!!!!");
    printf(GREEN"#####!!:::::!!!!!!!!::::::::!!!!!!!!!!####!!!!!!!"RESET"####!##########################!###@@@@@#"YELLOW"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!#################################"RESET"@@@@@@@@@@@@@@@@@@@################@@@@@@@@@@######"GREEN"!!!!!!!!!!!!!!!!");
    printf(GREEN"!######!!::::::::::::!!!!!!!!!!!!!!!!!!!!!"RESET"#########################################@@@@@@##"YELLOW"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!#############################"RESET"@@@@@@@@@@@@@@@@@@@@@@@#############@@@@@@@@@@@@@@##########"GREEN"!!!!!!!");
    printf(GREEN"########!!!::::!!!!!!!!!!!!!!!!!!!!!"RESET"############@@@@@@@@@@@@@@@@@@@#@@@@###########@@@@@@@##"YELLOW"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!##########################"RESET"@@@@@@@@@@@@@@@@@@@@@@@@@@@@##############@@@@@@@@@@#######"GREEN"!!!!!!!##");
    printf(GREEN"!!!!!!!#######!!!!!!!!!!!"RESET"##########@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@########@@@@@@@@###"YELLOW"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!#######################"RESET"@@@@@@@@@@@@@@@@@@@@@@@@##########################@@@@@@@###########"GREEN"!!");
    printf(RESET"!!!####################@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@########@@@@@@@@@###"YELLOW"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!########################"RESET"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@#####################################");
    printf(RESET"######@@@@@@@@###########@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@######@@@@@@@@@@@###"YELLOW"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!#######################"RESET"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@############################@@");
    printf(RESET"@@######################################@#@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@####@@@@@@@@@@@@@@####"YELLOW"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!######################"RESET"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@#######@@@@");
    printf(RESET"##################################################################@@@@@@@@@@@@@@###@@@@@@@@@@@@@@#######"YELLOW"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!#####################"RESET"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");
    printf(RESET"###################################################################@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@######"YELLOW"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!####################"RESET"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");
    printf(RESET"##############@@@@@@@##############################################@@@@@@@@@@@@@@@@#@@@@@@@@@@@@@@@@@@########"YELLOW"!!!!!!!!!!!!!!!!!!!!!!!!!####################"RESET"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@##############################@@@@@@@@#@@@@@@");
    printf(RESET"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@####################################@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@########"YELLOW"!!!!!!!!!!!!!!!!!!!!!!!!###!##########"RESET"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@##############################@@@@@@@@@@@@@####");
    printf(RESET"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@###############@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@#########"YELLOW"!!!!!!!!!!!!!!!!!!!!!!!!########"RESET"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@##########################@@@@@@@@@@@@@@@@@@@@");
    printf(RESET"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@###########"YELLOW"!!!!!!!!!!!!!!!########"RESET"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@########################@@@@@@@@@@@@@@@@@@@@@@@");
}
