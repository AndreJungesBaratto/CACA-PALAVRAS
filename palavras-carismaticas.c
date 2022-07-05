#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include "colors.h"

#define N 100


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
void surpresa();

// Funcoes de matriz:
void montamatriz();
char** RSTmatriz();
void imprimirmatriz();
void freematriz(char** arr);
void addpalavra(char** arr, int p, int q, int offset);
int redlin(int p);
int redcol(int p);
char tabuleiro();
void imprimirtabuleiro();


dados infojogo[N];
int cont = 0, fim;


int m, n;           // Dimensões da matriz
char** mat;         // Matriz montanda (answer key)
char** tab;         // Matriz tabuleiro do jogo (visual)

char alfabeto[26] = {"ABCDEFGHIJKLMNOPQRSTUVWXYZ"};


int main() {
    titulo();
    menu();
    freematriz(mat);
    freematriz(tab);
    return 1;
}


void menu() {
    volta:
    system("cls");
    printf(BWHT "Bem vindo ao Super Palavras Cruzadas!!!! "YEL":)"RST"\n\n");
    int opcao;
    printf(BLU "Escolha o que deseja fazer:\n\n" RST);
    printf("1. [Montar o jogo]\n");
    printf("2. [Jogar]\n");
    printf("3. [Sair]\n\n");

    scanf("%d", &opcao);
    getchar();

    while(opcao != 1 && opcao != 2 && opcao != 3) {
        printf(URED "Digite uma opcao valida!!! >:-(" RST "\n");
        scanf("%d", &opcao);
        getchar();
    }

    if(opcao == 1) {
        system("cls");
        carregando();
        entradados(infojogo);
        carregando();
        menu();
    }
    if(opcao == 2) {
        system("cls");
        carregando();
        jogo(infojogo);
        teladefim();
        surpresa();
        return;
    }
    if(opcao == 3) {
        system("color 6");
        printf(URED "Voce saiu do jogo." RST);
        Sleep(2000);
        system("color 7");
        system("cls");
        surpresa();
        getchar();
        getchar();
        return;
    }
    return;
}


void titulo(){
int i=0;
    while(!kbhit()){
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

void entradados(dados v[N]) {
    int igual;
    int c;
    char numero[] = "0123456789";
    printf(BLU "Voce esta entrando suas palavras!\n\n" RST);

    mais:

    cont++;
    printf(BWHT "Entre os dados da palavra %d."RST"\n", cont);
    printf("Palavra: ");

    while(strlen(v[cont].palavra)<=1||igual==0||strpbrk(v[cont].palavra, numero)!=NULL){
        fgets(v[cont].palavra, sizeof(v[cont].palavra), stdin);
        strtok(v[cont].palavra, "\n");

        for(int i=1; i<cont; i++) {
            igual=strcasecmp(v[cont].palavra, v[i].palavra);
            if(igual==0)break;
        }

        if(strpbrk(v[cont].palavra, numero) != NULL){
            system("color 6");
            Sleep(500);
            system("color 7");
            system("cls");
            printf(BRED "Nao insira numeros nas palavras"RED" >:(\n\n"RST"Insira uma palavra valida: ");

        }
        else if(strlen(v[cont].palavra) <= 1){
            system("color 6");
            Sleep(500);
            system("color 7");
            system("cls");
            printf("Por favor, insira uma palavra com mais de uma letra: ");
        }
        if(igual == 0){
            system("color 6");
            Sleep(500);
            system("color 7");
            system("cls");
            printf(YEL"Essa palavra ja esta no jogo!\n\n"RST"Digite outra palavra: ");
        }
    }
    printf("Dica: ");
    fgets(v[cont].dica, sizeof(v[cont].dica), stdin);
    strtok(v[cont].dica, "\n");

    printf(GRN "Voce inseriu a palavra %d"RST"\n\n",cont);
    v[cont].respondido=0;

    repete1:

    printf(YEL"Deseja inserir mais?"RST"\n");
    printf("1. [Sim]\n2. [Nao]\n");

    scanf("%d",&c);
    getchar();

    if(c == 1){
        system("cls");
        goto mais;
    }
    if(c != 1 && c != 2){
        system("color 6");
        Sleep(500);
        system("color 7");
        system("cls");
        printf(RED "Digite uma opcao valida >:(\n\n"RST);
        goto repete1;
    }
    fim = cont;
    carregando();
    editadados(infojogo);
}


void editadados(dados v[N]){
    system("cls");
    char c = 's';
    do {
        system("cls");
        printf(BBLU "Agora vamos revisar os dados!\n\n" RST);

        for (int l=1; l<=cont; l++){
            mostradados(v,l);
            printf("\n");
        }

        repete2:

        printf(YEL"Deseja editar alguma palavra?"RST"\n1. [Sim]\n2. [Nao]\n");
        scanf("%d",&c);
        if(c != 1 && c !=2 ){
            system("color 6");
            printf(RED "Digite uma opcao valida >:("RST"\n");
            Sleep(500);
            system("color 7");
            goto repete2;
        }
        if(c==1){
            char o;
            int edita;

            printf("\n"YEL"Diga o numero da palavra que voce quer editar: " RST);
            scanf("%d", &edita);
            getchar();

            while(edita <=0 || edita > cont) {
                printf(RED "Digite uma palavra valida! >:("RST"\n");
                scanf("%d", &edita);
                getchar();
            }

            printf(BWHT "Entre os novos dados da palavra %d"RST"\n", edita);
            printf("Palavra: ");

            int igual;
            char numero[]="0123456789";

            do {
                fgets(v[edita].palavra, sizeof(v[edita].palavra), stdin);
                strtok(v[edita].palavra, "\n");

                for(int i = 1; i <= cont; i++){
                    if(i != edita) {
                        igual=strcasecmp(v[edita].palavra, v[i].palavra);
                        if(igual == 0) break;
                    }
                }
                if(strpbrk(v[edita].palavra, numero) != NULL) {
                    system("color 6");
                    Sleep(500);
                    system("color 7");
                    system("cls");
                    printf(BRED "Nao insira numeros nas palavras"RED" >:(\n\n"RST"Insira uma palavra valida: ");
                }
                else if(strlen(v[edita].palavra) <= 1){
                    system("color 6");
                    Sleep(500);
                    system("color 7");
                    system("cls");
                    printf("Por favor, insira uma palavra com mais de uma letra: ");
                }
                if(igual == 0){
                    system("color 6");
                    Sleep(500);
                    system("color 7");
                    system("cls");
                    printf(YEL"Essa palavra ja esta no jogo!\n\n"RST"Digite outra palavra: ");
                }
            } while(strlen(v[edita].palavra) <=1 || igual == 0||strpbrk(v[edita].palavra, numero) != NULL);

            printf("Dica: ");
            fgets(v[edita].dica, sizeof(v[edita].dica), stdin);
            strtok(v[edita].dica, "\n");

            printf(GRN"Voce editou a palavra %d"RST"\n\n",edita);
            getchar();
        }
    } while(c == 1);
    system("cls");
    montamatriz();
}


void mostradados(dados v[N], int a) {
    printf("Dados da palavra %d\n", a);
    printf("Palavra: %s\nDica: %s\n", v[a].palavra, v[a].dica);
}


void imprimirdica(dados v[N]){
    printf(BBLU "DICAS\n\n" RST);
    for (int i = 1; i <= cont; i++) {
        if(v[i].respondido == 0){
            printf(BWHT "Palavra %d: " WHT, i);
            puts(v[i].dica);
            printf("\n" RST);
        }
    }
}


void carregando(){
    system("cls");
    char carr[10];

    for (int i = 0; i < 10; i++) {
        carr[i]=("%c%c%c"RST, 177);
        printf("%c", carr[i]);
    }
    for (int cor = 0; cor < 6; cor++) {
        system("cls");
        printf("Carregando\n");

        for(int e = 0; e < 10; e++){
            if(e < 2*cor) {
                printf(GRN"%c"RST, carr[e]);
            }
            else printf("%c"RST, carr[e]);
        }
        printf("\n");
        Sleep(300);
    }
    system("cls");
}



void teladefim(){
    while(!kbhit()){
        for (int i = 0; i < 4; i++) {
            system("cls");
            for (int e = 1; e < 15; e++){
                if(e <= 2*i + 1 || e >= 14 - 2*i){
                    printf(GRN"%c"RST, 205);
                }
                else printf("%c"RST, 205);
            }
            printf("\n");

            if(i==0||i==4){
                printf(GRN"  %c%c%c%c%c%c%c"RST"\n", 192, 91, 94, 45, 94, 218, 93);
            }
            if(i==1||i==3||i==5){
                printf(GRN"   %c%c%c%c%c%c%c"RST"\n", 192, 91, 94, 250, 94, 93, 217);
            }
            if(i==2||i==6){
                printf(GRN"    %c%c%c%c%c%c%c"RST"\n", 91, 191, 94, 45, 94, 93, 217);
            }

            printf(HGRN"Voce venceu!!"RST "\n");

            for(int e=1; e<15; e++){
                if(e<=2*i+1||e>=14-2*i){
                    printf(GRN"%c"RST, 205);
                }
                else printf("%c"RST, 205);
            }
            printf("\n\n\n");
            Sleep(300);

        }
        system("cls");
    }
    getchar();
    system("cls");
    printf(UWHT "Voce saiu do jogo."RST"\n");
    getchar();
}


void jogada(dados v[N]){
    char resp[50];
    int t;
    imprimirtabuleiro();
    imprimirdica(infojogo);

    printf("\n");
    printf("Escolha a palavra que deseja tentar: ");
    scanf("%d", &t);
    getchar();

    while(t > cont||t <= 0||v[t].respondido == 1){
        system("cls");
        if(t > cont || t <= 0) {
            printf(BWHT "Nao existe palavra com esse numero.\n\n" RST);
        }
        if(v[t].respondido==1) {
            printf(BWHT "Essa palavra ja foi respondida.\n\n" RST);
        }
        imprimirtabuleiro();
        imprimirdica(infojogo);
        printf("\n");
        printf("Escolha outra palavra: ");

        scanf("%d", &t);
        getchar();
    }
    printf("\n");
    printf("Insira sua resposta: ");
    fgets(resp, sizeof(resp), stdin);
    strtok(resp, "\n");

    int teste = strcasecmp(v[t].palavra, resp);

    if(teste == 0){
        system("color 2");
        Sleep(300);
        system("cls");
        system("color 7");
        v[t].respondido = 1;
        fim--;
        addpalavra(tab, t, t, 1);
        system("cls");
        printf(BGRN "Resposta correta! XD\n\n" RST);
    }
    else {
        system("color 4");
        Sleep(300);
        system("cls");
        system("color 7");
        printf(BRED "Resposta incorreta ;-;\n\n" RST);
    }
}


void jogo(dados v[N]) {
    system("cls");
    tabuleiro(); // Inicializa o tabuleiro de jogo
    char resp[50];
    int t;
    if(cont == 0) {
        system("color 4");
        printf("Nenhuma palavra foi inserida ainda!\nPressione qualquer tecla para voltar ao menu! :)");
        getchar();
        system("color 7");
        menu();
    }
    else {
        printf(BWHT "--- Bom jogo! ---\n\n" RST);
        while(1) {
            jogada(infojogo);
            if(fim == 0) {
                Sleep(500);
                break;
            }
        }
        return;
    }
}

// Incrimentos a fazer
void montamatriz() {

    /*
    A fazer:
    - Testar se havera sobreposicao de letras distintas
    - Impedir que letra estravaze limite da matriz
    - Limitar tamanho maximo tabuleiro
    - Testar se coordenada y e uma letra
    */

    infojogo[1].x = 0;
    infojogo[1].y = 0;

    orientacao1:

    printf(CYN "Qual a orientacao da palavra \"%s\"?:\n\n" RST, infojogo[1].palavra);
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
        printf("Opcao incorreta!\n");
        goto orientacao1;
    }
    system("cls");

	mat = RSTmatriz(m, n, mat);
    imprimirmatriz(m, n, mat);


    system("cls");

    addpalavra(mat, 1, 1, 0);


    for(int p = 2; p <= cont; p++) {
        orientacao:

        printf(CYN "Qual a orientacao da palavra \"%s\"?:\n\n" RST, infojogo[p].palavra);
        printf("1. [Horizontal]\n");
        printf("2. [Vertical]\n\n");
        scanf(" %d", &infojogo[p].orientacao);

        if (infojogo[p].orientacao == 1) {
            n += 2*strlen(infojogo[p].palavra);
        }
        else if (infojogo[p].orientacao == 2) {
            m += 2*strlen(infojogo[p].palavra);
        }
        else {
            system("cls");
            printf(RED "Opcao incorreta!\n" RST);
            goto orientacao;
        }

        RSTmatriz(m, n, mat);
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
            addpalavra(mat, i, p, 0);
        }

		coordenadas:

        imprimirmatriz();

		char letra;
        printf(CYN "Entre as coordenadas da palavra \"%s\": " RST, infojogo[p].palavra);
        scanf(" %c %d", &letra, &infojogo[p].x);
        letra = toupper(letra);

        for (int i = 0; i < 26; i++) {
            if (letra == alfabeto[i]) {
                infojogo[p].y = i;
            }
        }
        if (infojogo[p].y > n-1 || infojogo[p].x > m-1) {
            system("cls");
            printf(YEL "Coordenadas invalidas, tente novamente!\n" RST);
            goto coordenadas;
        }

        system("cls");
        addpalavra(mat, p, p, 0);

        int m_ = redlin(p);
        int n_ = redcol(p);

        freematriz(mat);
        m = m_;
        n = n_;
        mat = RSTmatriz();

        for (int i = 1; i <= p; i++) {
            system("cls");
            addpalavra(mat, i, p+1, 0);
        }

        system("cls");
        imprimirmatriz();
   }

    Sleep(500);
    printf(GRN "Tabuleiro de jogo montado!\n" RST);
    getchar();
    printf("Aperte enter para continuar.\n");
    getchar();
}


void imprimirmatriz() {
    printf("%7s", "");
		for (int j = 0; j < n; j++) {
			printf("%c ", alfabeto[j]);
	    }
		printf("\n");
		printf("%4s%c", "", 218);
		for (int j = 0; j < n+1; j++) {
			printf("%c%c", 196, 196);
	    }
		printf("\n");


    for(int i = 0; i < m ; i++) {

        if (i < 10) {printf("  %d %c ", i, 179);}   // 179 corresponde ao caracter "│"
		else {printf(" %d %c ", i, 179);}

        for(int j = 0; j < n; j++) {
            if (mat[i][j] == '.') {
                printf(BWHT " %c" RST, 250);      // 250 corresponde a '·'
            }
            else {
                printf(BWHT " %c" RST, mat[i][j]);
            }
        }
        printf("\n");
    }
    printf("\n");
}


char** RSTmatriz() {
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


void freematriz(char** arr) {
    for (int k = 0; k < m; k++) {
		free(arr[k]);
	}
	free(arr);
}


void addpalavra(char** arr, int p, int q, int offset) {

    if (infojogo[p].orientacao == 1) {
        for (int i = 0; i < strlen(infojogo[p].palavra); i++) {
            arr[infojogo[p].x + offset][infojogo[p].y + i + offset] = (char) infojogo[p].palavra[i];

            if (p == q) {
                system("cls");
                if (arr == mat) {
                    imprimirmatriz();
                }
                else {
                    printf("\n\n");
                    imprimirtabuleiro();
                }
                Sleep(100);
            }
        }
    }
    else if (infojogo[p].orientacao == 2) {
        for (int i = 0; i < strlen(infojogo[p].palavra); i++) {
            arr[infojogo[p].x + i + offset][infojogo[p].y + offset] = (char) infojogo[p].palavra[i];

            if (p == q) {
                system("cls");
                if (arr == mat) {
                    imprimirmatriz();
                }
                else {
                    printf("\n\n");
                    imprimirtabuleiro();
                }
                Sleep(100);
            }
        }
    }

}


int redlin(int p) {
    int m_ = m;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if(mat[i][j] != '.') {

                m_ -= i;
                for (int q = 1; q <= p; q++) {
                    infojogo[q].x -=i;
                }

                for (int k = 0; k < m; k ++) {
                    for (int l = 0; l < n; l++) {
                        if(mat[m-k-1][n-l-1] != '.') {
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

char tabuleiro() {
    tab = (char**) calloc(m+2, sizeof(char*));
	for (int k = 0; k < m+2; k++) {
		tab[k] = calloc(n+2, sizeof(char));
	}

    for (int i = 0; i < m+2; i++) {
        for (int j = 0; j < n+2; j++) {
            tab[i][j] = '.';
        }
    }

    for (int i = 1; i < m+1; i++) {
        for (int j = 1; j < n+1; j++) {
            if (mat[i-1][j-1] != '.'){
                tab[i][j] = ' ';
            }
        }
    }

    for (int p = 1; p <= cont; p++) {
        tab[infojogo[p].x+1][infojogo[p].y+1] = (char) p + '0';
    }
}

void imprimirtabuleiro() {
    for (int i = 0; i < m+2; i++) {
        for (int j = 0; j < n+2; j++) {
            if (tab[i][j] == ' ' && (i+j) % 2 == 0){
                printf(BLUB "   " RST);
            }
            else if (tab[i][j] == ' ' && (i+j) % 2 == 1){
                printf(INV BBLK "   " RST);
            }
            else if (tab[i][j] == '.') {
                printf("   ");
            }
            else if ((i+j) % 2 == 0) {
                printf(BLUB BWHT " %c " RST, tab[i][j]);
            }
            else if ((i+j) % 2 == 1) {
                printf(INV BBLK " %c " RST, tab[i][j]);
            }
            else {
                printf(" X ");
            }
        }
        printf("\n");
    }
    printf("\n");
}


void surpresa(){
    system("color F7");
    printf(GRN":!!::!!!:::::::!!!!!!!!!!!####################################################################################################@@#####!!!!#######!!!!!!!####!!!!!!!!#####################@@@#########@########@############@########!!!!!!####");
    printf(GRN"!!!::!!::!!!!!!!!################################################################################################################!:.....::!!##!!!!:::::!##:::::::::!!###################@@@##################@#####################!!!!!!####");
    printf(GRN"!!!:!!!!!################################################@@@@@@@@@@@@@@@@@@@@@@@@@######@@@@@@@@@@@@@@@@@##@@@@@@################!:::!:..:!!#!!!!::::::!##::.......:!!!!!!!!############@@@###############################@#########!!!!!####");
    printf(GRN"::!!!!::!################@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@####!!###!!!!!!!!:::!:.::!!!!:::::.:::!##:........:!:::!!!!!!!!!!:!!###@@@########################################!!!!!!####");
    printf(GRN"::!!:!!!!!############@@@@###@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@#######!!!#############!!!:!!##!!!!::::::::!##:..    ..::::::!!!!!!!!::!!!!###########################################!!!!!!!####");
    printf(GRN"!:!!:::!!!############@@@@##@@##@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@######!!!!"BLK"#########@@@@@@@@@@##@@@@@@@@@######"GRN"!!!##!:........:!::::!!!!!!!!!::!!!####!!!!!!!##@##!#####@#####################!!!!!#####");
    printf(GRN"!!!!::::!!########################@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@#########"BLK"####@@###@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@#@@#@##"GRN"!!!:::....:!:::::!!!!::::::!!!####!:::!:!!!#!!!!####################!!###!!!!!!#####");
    printf(GRN"!!!!:!!!!!#########################@@@@@@@@@@@@@@#######@@#@@@@@@@@@@@@@@@@@@@@@@@@@@@@#############"BLK"###@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@###########"GRN"!!!!!:::::!!!!:!::::!!!!###!!::!:!!!!!:::!!##@###############!!###!!!!!!#####");
    printf(GRN"!!!!:!!!!!########################@@@@@@@@@@###########@@@@@@@@@##@@@@##@@@@@@####@@@@##!!######"BLK"#####@@@@@@@@#@@@@@@@@#@@@@@@@@@@@@@@@@@@@@@@@@@@@@####@@@@@@@@@@####"GRN"!!!!!!!!!::::::!!!####!:::::!!!!!::::!!#############@###!!###!!!!!!#####");
    printf(GRN"!!::::!!!!#####################@@@@@@@@##############@#@@@@####!!!!###!!#@@@@##!##@@@@#######"BLK"#######@##@@@@@@@@@@@###@@@@@@@######@@@@@@@@@@@####@@@@@@@@@@@@@@@@@@##########"GRN"!!!::::!!!####!!:::::!!#!::::!!###!!!!!##########!###!!!!!!#####");
    printf(GRN"!:!!:!!!!!#######################@@#################!!!!####@@#!::!##!!!#@@@@##!#######"BLK"##@@@@@####@@@@@@@@@@@@###@@@@@@#######################@@@@@@@@@@@@@@@@@@@@@@@@@#########"GRN"!!:!!!!#@##!:::::!!!!!::::!!!#!!!!::::!!#####!!##!!!!!!!#####");
    printf(GRN"!:!!!!!::!##########################################!!!!####@@#!!!!###!!#@@@@##!!##"BLK"##@@#@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@######################@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@######"GRN"!!!!!#@##!!:::::!!!!:::::!##!!!!!!!:::!########!!!!!!######");
    printf(GRN"!::!:!!::!!####################!####################!!!!#######!!!!##!!!#@@@@##!#"BLK"##@##@#@@####@@#@@@@@@@@@@@@################################@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@#####"GRN"!!!!!#@##!::::::!!!!:::::!##!!!!!!:::!!#!!!!!!#!!!#!!!#####");
    printf(GRN"!::!::!!:!!#################!!!!####################!!!!!######!::!##!#!##@@##"BLK"######@@@@@@##@@@@@#######@#############"YEL"!!!!!!!!!!!!!!!!!!!!"BLK"##############@@@@@@@@@@@@@@@@@@@@@@@@@@###"GRN"!!#@##!:::!!!!!!!::::!!##!!!::!::::!#!!::::!!!!#!!######");
    printf(GRN"!!!!!!!:!!!#########################################!!!!!######!::!!#!!!#####"BLK"#####@@@##@@###@@##########"YEL"!!!!!!!!!!!!!!:::::::::::::::::::!!!!!!!!!!!!!!!!!!"BLK"#########@@@@@@@@@@@@@@@@###"GRN"#@##!:::!!!!#!!::::!!###!!::::::!!#!!:::::.::!!!######");
    printf(GRN":!!!!!!:!!!###########!!!!##!!######################!!!!!######!:!!#!!!!###"BLK"#######@@@@@@@@####"YEL"!!!!!#!!!!!!!!!!!:::::::::::.................:::::::::::::::::::!!!!!!"BLK"#####@@@@@@@@@@@@###"GRN"@#!!:::!!!!!!!::::!!###!!::::::!!#!!::::::..:::!#####");
    printf(GRN":!!!!!!:!!!########!!!!!!!!!!!!!!###################!!!!!######!:!!#!!!!#"BLK"#########@@@@#####"YEL"!!!!!!!!:!!!!!:::::::...::............................:::::::::::::::::::!!!!"BLK"####@@@@@@@@@@@#@#"GRN"!!:::!!!!!!!::::!!##!!!::!:::!!#!!:::::..:::::!!###");
    printf(GRN":!!!!!!:!!!######!!!!!!!!!!!!!!!!!!#################!!!!!######!:!!#!!!!"BLK"########@@@@#####"YEL"!!!!::::::::::::::::::::...:..................::........::::::::::::::::::::::!!!!!"BLK"###@@@@@@@@@@##"GRN"!:::!!!!#!!::::!!##!!!::!!::!!#!!:.::::::::::!::!!");
    printf(GRN":!!!::!!!!!##!!!!!!!!!!!!!!!!!!!!!!#################!!!!!######!:!!!!!"BLK"#########@@@####"YEL"!!!!:::......::::::::::::::::::::::::::::::::::::::.::::::::::::::::::::::::::::::::::!!!"BLK"##@@@@@@@@##"GRN"!:::!!!!#!!:::::!##!!!::!!!!!!#!::.::::::::::!!:::");
    printf(GRN"!!!:!!:::!!!!::!!!!!!!!!!!!!!!!!!!!!!###############!!!!!######!::!!!"BLK"#########@####"YEL"!!!:::........::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::!!"BLK"###@@@@@@##"GRN":::!!!!#!!:::::!##!!:::!!!!!!#!::.:::.::::::!!:::");
    printf(GRN"!::!!:!!!::::!!!!!!!!!!!!!!!!!!!!!!!!!!#############!!!!!######!:!!##"BLK"########@@###"YEL"!:::......::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::!!"BLK"###@@@@@@#"GRN"!::!!!!#!!::.::!##!!:::!!!!!!#!!::::::::::::!!:::");
    printf(GRN"!::!:!::  .:::!!!!!!!!!!!!!!!!!!!!!!!!##############!!!!!######!::!##"BLK"############"YEL"!::......::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::!!!!!!!!!!!!!!!!!!:::::::::!!"BLK"###@@@@@@#"GRN"!!!!!!#!!::.::!##!!:::!!!:!!#!!::::::::::::!!:::");
    printf(GRN":!!:::.   .:::!!!!!!!!!!!!!!!!!!!!!!!!!!#!!!########!!!!!######!:.:!"BLK"##@@@@#####"YEL"!!::.....:::::::::::::::::::::::::::::::::::::::::::::::::::!!:!!!!!!!!!!!!!!!!!!!!!!!!!!!::::::::!!!"BLK"###@@@@@##"GRN"!!!!!#!!::::!!##!!!!!!!:!!!#!::::::::::::!!!:::");
    printf(GRN"!:::.     .::::!!!!!!!!!!!!!!!!!!!!!!!!!!!########!!!!!!!!#####!:::!"BLK"##@@@#####"YEL"!!::.....:::::::::::::::::::::::::::::!!!!!!::::!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!::!!!!!"BLK"####@@@@#"GRN"!!!!!#!!!:::!!#!!!!!!!!:!!!#!!:::::::::::!!!:::");
    printf(GRN"::.       .:::::!!!!!!!!!!!!!!!!!!!!!!!!!!######!!!!!!:!!!#####::.:!"BLK"#@@@####"YEL"!!:::.....::::::::::::::::::::::::::::::::::::::::::::::::::::::!!:::::!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"BLK"######@@##"GRN"!!!!#!!::::!!#!!!!!:::::!!#!!:::::::::::!!!:::");
    printf(GRN".         .:::::!!!!!!!!!!!!!!!!!!!!!!!!!!#####!!!!!!:::!!!####!:::!"BLK"#@@###"YEL"!!!:::.....:::::::::::::::::::::::::::::::....::::::::::::::::::::::::::::::::::::!!!!!!!!!!!!!!!!!!!!!!!!!"BLK"#######@##"GRN"!:::!::.....:!!!::::::::!!#!!!!!::::::::!!!:::");
    printf(GRN"          .:::::!!!!!!!!!!!!!!!!!!!!!!!!!!#####!!!!!!:::!!!####!:::#"BLK"####"YEL"!!!!:::.....::::::::::::::::::::::::::::.....::::::::::::::::::::::...::::::::::::::::::::::::::!!!!!!!!!!!!!"BLK"##########"GRN"!...:........!!!!!!!!!!!!!##!!!!!:::::::!!!:::");
    printf(GRN"          .:::::::!!!!!!!!!!!!!!!!!!!!!!!!#!###!!!!!!:::!!!####!::!"BLK"####"YEL"!!!!!::.....:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::!!!!!!!!!!!!!!!"BLK"##########"GRN"!...:........!!!!!:::::!!##!!!::::::::::!!!::!");
    printf(GRN"          .:!::::::!!!!!!!!!!!!!!!!!!!!!!!#####!!!!!!:::!!!!###!::"BLK"#####"YEL"!!!!::......:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::!!!::!!!!!!:::::::::::::::::::!!!!!!!!!"BLK"###########"GRN"!::!:::..:::#!!::::::::!!#!!::::::::::!!!:::!");
    printf(GRN"          .:!:::::::!!!!!!!!!!!!!!#############!!!!!!:::!!!!####@@"BLK"####"YEL"!!!:........::::::::::::::::::::::::::::!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!::::::::::::::!!!!!!!!"BLK"####@@@@##"GRN"#!!#!!::::!!#!!:::::!!!!##!!::::::::::!!!:::!");
    printf(GRN"          ..::::::::!!!!!!!!!!!!!!##############!!!!!!!:!!!!##@##"BLK"#####"YEL"!!:..............::::::!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!:::::!!!!!!!!!"BLK"####@@@##"GRN"##!#!!::::!!#!!!!!!!!!!!!!!!!!!:::::::!!!:::!");
    printf(GRN"          ..!:::!:::::::::::::::::!!!!!!!!!!!!!!!!!!!::::!!!!#####"BLK"###"YEL"!!:..............:::::!!!!!!!!!!!!######!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!#############!!!!!!!!!!!!!!!!!!!!!!!"BLK"###@@###"GRN"!:::::.::::::::::::::::::::::::::::::!!!!!!!");
    printf(GRN"           .!:!!!!:...........................................:::!"BLK"###"YEL"!!:...........::::!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!##################!!!!!!!!!!!!!!!!!!!!!!!!"BLK"##@@###"GRN"!::::::::::::::::::::::::::::::::::::!!!!!!!");
    printf(GRN"          ..!!!!!#####!!!!!!!!!!!!!!::::::::::::::::::::::::::::!!"BLK"###"YEL"!!.........::::::!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!################!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"BLK"###@@@##"GRN"!!!!!!!!!!!!!!!##!##########!!::::::!!!!!!!");
    printf(GRN"          ..!!!!!!########################################"YEL"!::::!!"BLK"####"YEL"!!........::::::::::::!!!!!!!!!!!!!!!!!!!!!####!!!!!!!!!!!!!!!!#################!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"BLK"#@@@@##"GRN"#!!!!!!!!!#!!!!!!!!!#######!!!:::::!!!!!!!!");
    printf(GRN"           .:!!!!!!#####################################"YEL"!!:!!!:::!!!!!!.......:::::::::!!!!!!!!#!################!!!####!!!!!!!!!!!!!##############!####################!!!!!!!!!!!!!!!!!!!"BLK"##@@@#"GRN"!!:!!!!!!!!!!!!!!!!!!!!!!!!!#!!:::::!!!!!!!!");
    printf(GRN"           .:!!!!!!!####################################"YEL"!!!!!!!!!!!!!!:.....::::::::!!!!!!!!###!!##@@@@@@@@##############!!!!!!!!!!!!!###################@@@@@@@@#####@#####!!!!!!!!!!!!!!!!"BLK"####!"GRN"!####!!!!!!!!!!!!!!!!!!!!!!!!!:::::!!!!!!!!");
    printf(GRN"           .:!!!!!!!####################################"YEL"!!!!!!!!!::!!::.....:::::::!!!!##!!##!!!!!##@@@@@@################!!!!!!!!!!!!!##################@@@@@@@@##!###########!!!!!!!!!!!!!"BLK"######"GRN"######!!!!!!!!!!!!!!!!!!!!!!!::::::!!!!!!!!");
    printf(GRN"          ..:!!!!!!!!###################################"YEL"!!!!!!!!!!!!::.......::::::::::::::::!!!!!!!######################!!!!::::::!!!!###############################!!!!!!!!!!!:!::::!!!!"BLK"######"GRN"######!!!!!!!!!!!!!!!!!!!!!!!::::::!!!!!!!!");
    printf(GRN"          ..:!!!!!!!!!###################################"YEL"!!!!!!:::!::.  ............::::::::::!!!!!!!!!!!!!!!!!!!!!!##!!!!!!!::::::::!!!!#######!!!!!!!!!!!!!!!!!!!!!!!!!!::::::::::::::!!!!!"BLK"!##"YEL"!!!"GRN"#####!!!!!!!!!!!!!!!!!!!!!!!::::::!!!!!!!!");
    printf(GRN"          ..:!!!!!!!!!###################################"YEL"!!!!!::!!!!::    ........:::::::::::::!!!!!!!!!!!!!!!!!!!!!!!!!!!!:::::..::::!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!:::::::::::::::::::!!!"BLK"!#"YEL"!!!!"GRN"###!!!!!!!!!!!!!!!!!!!!!!!!::::::!!!!!!!!");
    printf(GRN"          .::!!!!!!!!!!##################################"YEL"!!!!!:!!!!!!:. ........:::::::::::::::::::!!!!!!!!!!!!!!!!!!!!!!:::::::..:::::!!!!!!!!!!!!!!!!!!!!!!!!!!!!!::::::::::::::::::::::::!!"BLK"###"YEL"!!!"GRN"########!!!!!############!!::::::!!!!!!!!");
    printf(GRN"          .::!!!!!!!!!!!#################################"YEL"!!!!!:!!!!!!:.......:::::::::::::::::::::::::!!!:!!!!!:::!!:::::::::::...:::::!!!!!!!!!!!!!!!!!!!!!!:::::::::::::::::::::::::::::::!!!"BLK"#"YEL"!!!!!"GRN"######@@###@@@@@@@@@@@@@@!!::::!!!!!!!!!");
    printf(GRN"...      ..::!!!!!!!!!!!##################################"YEL"!!::!!!!!!!:......::::::::::::::::::::::::::::::::::::::::::::::::::.....:::::::::::::::::::::::::::::::::::::::::::::::::::::!!!!!!"BLK"###"YEL"#!!!"GRN"!!!!!!!#!!##@@@@@@@@@@@@@!!::::!!!!!!!!!");
    printf(GRN".::........::!!!!!!!!!!!!##################################"YEL"!:::!!!!!!:......:::::::::::::::::::::::!!!!!!!!!!!!!!!!!:::::::::::....::::::!!!!!!!!!!!!!!!!!!!:::::::::::::::::!!!!:!!!!!!!!!!!!"BLK"##"YEL"##!!!"GRN"##@@@@@@@####@@@@@@@@@@@@!!::::!!!!!!!!!");
    printf(GRN"::::......:::!!!!!!!!!!!!##################################"YEL"!!::::!!!!:.:..::::::::::::::!!!!!!!!!!!!!!!!!!!!#!!!!!!!!!!::::::::::::::::::!!!!!!:!!!!!!##!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"BLK"#"YEL"#!!!!!"GRN"##@@@@@@#####@@@@@@@@@@@#!:::::!!!!!!!!!");
    printf(GRN".:::::....:::!!!!!!!!!!!!!##################################"YEL"!:!!!::!::...::::::::!!!!!!!!!!!!!!!!!!!!!!#####!!!!:::::::::::::::::::::::::!:::::::::!!!#######!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"GRN"#@@!!###!!####@@@@@@@@@@#!::::!!!!!!!!!!");
    printf(GRN".:::::::::::!!!!!!!!!!!!!!!#################################"YEL"!::!!!::::::::::::!!!!!!!!!!!!!!!!!!!!!#########!!!!::::::::::::!!!!!!!!!!!!!!!!!::::!!!!!##########!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!#!!!"GRN"##@#!!#########@@@@@@@@@@#!::::!!!!!!!!!!");
    printf(GRN".:::::::::::!!!!!!!!!!!!!!!!!################################"YEL"!::::::::::::::!!!!!!!!!!!!!!!!!!!!!!#######!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!###!###########!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"GRN"#@@#!!########@@@@@@@@@@@#!:::!!!!!!!!!!!");
    printf(GRN"::::::::::::!!!!!!!!!!!!!!!!!#################################"YEL"!:::.::.::::!!!!!!!!!!!!!!!!!!!!!!########!!!!!!!!#######!!!!!!!!!!!!!!!###############!!!!!##########!!!!!!!!!###!!!!!!!!!!!!!!!:!!!"GRN"##@@#!!#@########@@@@@@@@@#!::!!!!!!!!!!!!");
    printf(GRN"::::::::::::!!!!!!!!!!!!!!!!!!#################################"YEL"!:..::::::!!!!!!!!!!!!!!!!!!!!!#######!!!!!!!!!!!!##############!#####################!!!!!!!##########!!!!!!######!!##!!!!!!!!:!!!!"GRN"#@@@#!!#######@####@@@@@@@#!!::!!!!!!!!!!!");
    printf(GRN".:::::...:::!!!!!!!!!!!!!!!!!!!#################################"YEL"!!!:::::::!!!!!!!!!!!!!!!!!!!#####!!!!!!!!!!!!!!!!!!##############################!!!!!!!!!!####!#######!!!#########!!!!!!!!!!!!!"GRN"##@!!::!!!!!!!!!!!!!!!!::!!!!!!!:!!!!!!!!!!!");
    printf(GRN":.........::!!!!!!!!!!!!!!!!!!!!######################################"YEL"!::::!!!!!!!!!!!!!!!!!!#####!!!!!!!!!!!!!!!!!!!!!!#########################!!!!!!!!!!!########!!!!!!#######!!!##!!!!!!"GRN"#####@@@#::::::::::::!!!!!!!!!!!::::!:!!!!!!!!!!!");
    printf(GRN":.........::!!!!!!!!!!!!!!!!!!!#############################@@@@###!!!!:"YEL":::!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!###########################################!!!!!!!!!!##!!!!##!!##!!"GRN"##@@@@@@@#!::::::::::::!!!!!!!!!!!::!!!!!!!!!!!!!!");
    printf(GRN"..........::!!!!!!!!!!!!!!!!!!!!##################################!!!!!:::"YEL"::!!!!!!!!!!!!!!!!!!!!!!!!#############################################################!!!!!!!!!!!!!!!!!!!!!!!!!"GRN"##@@@@@##!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
    printf(GRN"..........::!!!!!!!!!!!!!!::!!!!!!!!!!!!!!!!!!!!!!!!!!!!#######!!:::::::::::"YEL"!!!!!!!!!!!!!!!!!!!!!!!######@@@@@#######!!!!!!!!!!!!###!!!!!##############@@@@@####!!!!!!!!!!!!!!!!!!!!!!!!!!!"GRN":::::!!!!!!!!!!!!!!!!!!!!!!!!!####!!!!!!!!!!!!!!!!");
    printf(GRN"..:::.....::!!!!!!!!!!!!!!!::::::::::::::::::::::!!!!!!!!!!!!!!!::.........::"YEL"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!###########!!#############################@@@#####!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"GRN":::::!!!!!!!!!!#############@@@@@@#!!!!!!!!!!!!!!!!");
    printf(GRN"....::....::!!!!!!!####!!!!!!!!!!!!!!!!!!:::::::::::::::::::::::::.........::"YEL"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!###!######!###############!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"GRN"::::!!!!#####@@@@@@@@@@@@@@@@@@@@@@#!!!!!!!!!!!!!!!!");
    printf(GRN"....::::::::!!!!!!!#################!!!!!!!!!!!!!!!!!!!:::::::::::::::::::::::"YEL"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"GRN"######################@@@@@@@@@@@@@@###!!!!!!!!!!!!!!!!");
    printf(GRN".....:::::::!!!!!!!!###############################!!!!!!!!!!!!!!!!!!!!!!!!!!!::"YEL"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!#######!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"GRN"###@@@######@@######################@@@@#!!!!!!!!!!!!!!!!");
    printf(GRN"::::::::::::!!!!!!!!!###########################@@@@@############!!!!!!!!!!!!!!!"YEL"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!####################!!!!!!!!!!!!!!!!!!!!!!!!#####!!"GRN"###############@#!!!!!!!!###!##########@@#!!!!!!!!!!!!!!!!");
    printf(GRN"::::::::::::!!!!!!!!!##############################@########@@@@@@@@@@@@@########"YEL"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!##########################!!!!!!!!!!!!!!!!!!!!!!#####!!"GRN"#######################!####!#############@@#!!!!!!!!!!!!!!!!");
    printf(GRN"::::::::::::!!!!!!!!!!#################################@########@@@@@@@@@@@@@@@#@@##"YEL"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!###!!!####!!!!!!!!!!!!!!!!!!!!!!!!!!!########"GRN"################!!##!!!!!##!####!#########@@#!!!!!!!!!!!!!!!!");
    printf(GRN"::::::::::::!!!!!!!!!!!##############################@@@#######@@@@#########@####!!!!!!"YEL"!!!!!!!!!!!!!!!::::::::!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!###########"GRN"#################!!!!!!!!!##!!################!!!!!!!!!!!!!!!!");
    printf(GRN".....:::::::!!!!!!!!!!!!##############################################!!!!!!!!###!!!!!"RST"##"YEL"!:!!!!!!!!!!!!!!!:::::::::::!:::!!!!!!!!!!!!!!!!:::::::::::!!!!!!!!!!!!!!###########"RST"@@@@###"GRN"!!!!########!!!!####!!###!!!!#!!!!!!!!!##!!!!!!!!!!!!!!!!!");
    printf(GRN"::::::::::::!!!!!!!!!!!!##################################!!!!!!!!!!!!!#####!!!!!!!!"RST"###@"YEL"!::::!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!##############"RST"@@@@@#########"GRN"!!!!!:::::::::::::::::::!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
    printf(GRN"::::::::::::!!!!!!!!!!!!!######################!!!:::::::!!!!!!!!#######!!!!!!!!!!!"RST"##@@@"YEL"!::::!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!##############!!!!#"RST"@@@@@@@##############"GRN"!!!!!::::::::::::::::::::::!!!!!!!!!!!!!!!!!");
    printf(GRN"!!::::::::::!!!!!!!!!!!!!!###########!!!!!:::::::!!!!!!!#######!!!!!!!!!#!!!!####!!"RST"#@@@@"YEL"!:::!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!###########################"RST"@@@@@@@@@#####################"GRN"!!!!!!!!!!!:::::::!!!!!!!!!!!!!!!!!");
    printf(GRN"##!!::::::::!!!!!!!!!!!!!!!!!!!!!::::::::!!!!!!!#########!!!!!!!!!######!!!"RST"#########@@@@"YEL"!!:!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!##!!!!#######################################"RST"@@@@@@@@@@@@#############################"GRN"!!!!!!!!!!!!!!!!!!!!!!!!");
    printf(GRN"###!!:::::::!!!!!!!!!!!!!:::::::::!!!!!!!#########!!!!!!!!"RST"#####################!!###@@@@#"YEL"!!!!!!!!!!!!!!!!!!!!!!!!!!########################################################"RST"@@@@@@@@@@@@@@##################@@@@@@@@######"GRN"!!!!!!!!!!!!!!!!!!!!");
    printf(GRN"#####!!:::::!!!!!!!!::::::::!!!!!!!!!!####!!!!!!!"RST"####!##########################!###@@@@@#"YEL"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!#################################"RST"@@@@@@@@@@@@@@@@@@@################@@@@@@@@@@######"GRN"!!!!!!!!!!!!!!!!");
    printf(GRN"!######!!::::::::::::!!!!!!!!!!!!!!!!!!!!!"RST"#########################################@@@@@@##"YEL"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!#############################"RST"@@@@@@@@@@@@@@@@@@@@@@@#############@@@@@@@@@@@@@@##########"GRN"!!!!!!!");
    printf(GRN"########!!!::::!!!!!!!!!!!!!!!!!!!!!"RST"############@@@@@@@@@@@@@@@@@@@#@@@@###########@@@@@@@##"YEL"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!##########################"RST"@@@@@@@@@@@@@@@@@@@@@@@@@@@@##############@@@@@@@@@@#######"GRN"!!!!!!!##");
    printf(GRN"!!!!!!!#######!!!!!!!!!!!"RST"##########@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@########@@@@@@@@###"YEL"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!#######################"RST"@@@@@@@@@@@@@@@@@@@@@@@@##########################@@@@@@@###########"GRN"!!");
    printf(RST"!!!####################@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@########@@@@@@@@@###"YEL"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!########################"RST"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@#####################################");
    printf(RST"######@@@@@@@@###########@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@######@@@@@@@@@@@###"YEL"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!#######################"RST"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@############################@@");
    printf(RST"@@######################################@#@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@####@@@@@@@@@@@@@@####"YEL"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!######################"RST"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@#######@@@@");
    printf(RST"##################################################################@@@@@@@@@@@@@@###@@@@@@@@@@@@@@#######"YEL"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!#####################"RST"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");
    printf(RST"###################################################################@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@######"YEL"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!####################"RST"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");
    printf(RST"##############@@@@@@@##############################################@@@@@@@@@@@@@@@@#@@@@@@@@@@@@@@@@@@########"YEL"!!!!!!!!!!!!!!!!!!!!!!!!!####################"RST"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@##############################@@@@@@@@#@@@@@@");
    printf(RST"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@####################################@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@########"YEL"!!!!!!!!!!!!!!!!!!!!!!!!###!##########"RST"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@##############################@@@@@@@@@@@@@####");
    printf(RST"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@###############@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@#########"YEL"!!!!!!!!!!!!!!!!!!!!!!!!########"RST"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@##########################@@@@@@@@@@@@@@@@@@@@");
    printf(RST"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@###########"YEL"!!!!!!!!!!!!!!!########"RST"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@########################@@@@@@@@@@@@@@@@@@@@@@@");
}

