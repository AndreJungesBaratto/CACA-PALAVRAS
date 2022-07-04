#include <stdbool.h> //eventualemente a gnt pd usar um true ou false
#include <stdio.h>
#include <stdlib.h>
#include <string.h> //funcoes de string
#include <conio.h>
#include <windows.h>

#define N 100
#define BLACK   "\e[0;30m"
#define RED     "\e[0;31m"
#define REDSUB  "\e[4;31m"
#define GREEN   "\e[0;32m"
#define YELLOW  "\e[0;33m"
#define BLUE    "\e[0;34m"
#define MAGENTA "\e[0;35m"
#define CYAN    "\e[0;36m"
#define RESET   "\e[0;0m"

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
void iniciar();
void desligar();
void surpresa();

// Funções da matriz:
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
    //iniciar();
    menu();
}


void menu() {
    volta:
    system("cls");
    printf("Bem vindo ao Super Palavras Cruzadas!!!! \e[0;33m:)"RESET"\n\n");
    int opcao;
    printf("Escolha o que deseja fazer:\nOpcao 1: Montar o jogo\nOpcao 2: Jogar\nOpcao 3: Sair do jogo\n");

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
        printf("Voce saiu do jogo.");
        getchar();
        //desligar();
        surpresa();
        return;
    }
    return;
}


void iniciar(){
    printf("Iniciando o Windows .....");
    system("color 1");
    Beep(622, 450);
    system("color 6");
    Beep(466, 450);
    system("color 2");
    Beep(415, 350);
    Beep(311, 250);
    Beep(622, 350);
    system("color 4");
    Beep(466, 500);
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
    Beep(470, 600);
    system("cls");
    system("color 7");
}


void entradados(dados v[N]) {
    int igual;
    int c;
    char numero[] = "0123456789";
    printf(BLUE "Voce esta entrando suas palavras!" RESET "\n");
    mais:
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
            printf("Digite uma opcao valida >:(\n");
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
        printf("Agora vamos revisar os dados!\n");
        for(int l=1;l<=cont;l++){
            mostradados(v,l);
            printf("\n");
        }
        repete:
        printf("Deseja editar alguma palavra?\n1. [Sim]\n2. [Nao]\n");
        scanf("%d",&c);
        if(c!=1&&c!=2){
            system("color 6");
            printf("Digite uma opcao valida >:(\n");
            Sleep(500);
            system("color 7");
            goto repete;
        }
        if(c==1){
            char o;
            int edita;
            printf("\nDiga o numero da palavra que voce quer editar\n");
            scanf("%d", &edita);
            getchar();
            while(edita<=0||edita>cont){
                system("color 6");
                printf("Digite uma palavra valida! >:(\n");
                Sleep(500);
                system("color 7");
                scanf("%d", &edita);
                getchar();
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
    /*system("cls");
    for (int i = 0; i < 1; i++) {
        char a[10];
        printf("Carregando");
        for (int j = 0; j < 5; j++) {
            printf(".");
            Sleep(400);
            sprintf(a, "color %d", j+3);
            system(a);
        }
        printf("\r");
        for (int j = 0; j < 20; j++) {
            printf(" "); // apaga a linha anterior
        }
        printf("\r");
    }
    system("color 7");*/
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
    for(int b=0;b<1;b++){
        char vitc[13];
        memset(vitc,'-',12);
        vitc[0]='o';
        system("color 6");
        puts(vitc);printf("    \\[^^]\\    \n");printf(GREEN"Voce venceu!"RESET"\n");puts(vitc);
        for(int i=1;i<6;i++){
            system("cls");
            vitc[2*i]='o';
            vitc[2*(i-1)]='-';
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
        for(int i=5;i>=0;i--){
            system("cls");
            vitc[2*i]='o';

            if(i<=4){
            vitc[2*(i+1)]='-';
            }
            puts(vitc);
            if(i%2==1){
                system("color 9");
                printf("   /[^^]/    \n");
            }else{
                system("color 6");
                printf("   \\[^^]\\   \n");
            }
            printf("Voce venceu!\n");puts(vitc);
            Sleep(150);
            vitc[10]='-';
        }
        system("cls");
        system("color 7");
    }
    printf("Aperte qualquer botao para sair\n");
    getchar();
}


void jogada(dados v[N]){
    char resp[50];
    int t;
    printf("Escolha a palavra que deseja tentar:\n");
            scanf("%d", &t);
            getchar();
        while(t>cont||t<=0||v[t].respondido==1){
            if(t>cont||t<=0){
                printf("Nao existe palavra com esse numero. Escolha uma palavra valida:\n");
            }
            if(v[t].respondido==1){
                printf("Essa palavra ja foi respondida! Escolha outra palavra:\n");
            }
            scanf("%d", &t);
            getchar();
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
                getchar();
                system("cls");
                system("color 7");
            }
            else {
            system("color 4");
            printf("Resposta incorreta ;-;\n");
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

// Incrimentos a fazer
void montamatriz() {

    /*
    A fazer:
    - Testar se haverá sobreposição de letras distintas
    - Impedir que letra estravaze limite da matriz
    - Limitar tamanho máximo tabuleiro (lin < )
    - Testar se coordenada y é uma letra

    */

    infojogo[1].x = 0;
    infojogo[1].y = 0;

    orientacao1:

    printf("Qual a orientacao da palavra \"%s\"?:\n\n", infojogo[1].palavra);
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
        system("color 6");
        Sleep(500);
        system("color 7");
        goto orientacao1;
    }
    system("cls");

	mat = resetmatriz(m, n, mat);
    imprimirmatriz(m, n, mat);


    system("cls");

    addpalavra(1, 1);


    for(int p = 2; p <= cont; p++) {
        orientacao:

        printf("Qual a orientacao da palavra \"%s\"?:\n\n", infojogo[p].palavra);
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
            printf("Opcao incorreta!\n");
            system("color 6");
            Sleep(500);
            system("color 7");
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
        printf("Entre as coordenadas da palavra \"%s\": ", infojogo[p].palavra);
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
                printf("Coordenadas invalidas, tente novamente!\n");
                system("color 6");
                Sleep(500);
                system("color 7");
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
    system("color 2");
    printf("Tabuleiro de jogo montado!\n");
    Sleep(500);
    system("color 7");
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
    printf(GREEN"           .:!!!!!!#####################################"YELLOW"!!:!!!:::!!!!!!.......:::::::::!!!!!!!!#!################!!!####!!!!!!!!!!!!!##############!####################!!!!!!!!!!!!!!!!!!!##@@"BLACK"@#!!"GREEN":!!!!!!!!!!!!!!!!!!!!!!!!!#!!:::::!!!!!!!!");
    printf(GREEN"           .:!!!!!!!####################################"YELLOW"!!!!!!!!!!!!!!:.....::::::::!!!!!!!!###!!##@@@@@@@@##############!!!!!!!!!!!!!###################@@@@@@@@#####@#####!!!!!!!!!!!!!!!!####"BLACK"!!##"GREEN"##!!!!!!!!!!!!!!!!!!!!!!!!!:::::!!!!!!!!");
    printf(GREEN"           .:!!!!!!!####################################"YELLOW"!!!!!!!!!::!!::.....:::::::!!!!##!!##!!!!!##@@@@@@################!!!!!!!!!!!!!##################@@@@@@@@##!###########!!!!!!!!!!!!!######"BLACK"####"GREEN"##!!!!!!!!!!!!!!!!!!!!!!!::::::!!!!!!!!");
    printf(GREEN"          ..:!!!!!!!!###################################"YELLOW"!!!!!!!!!!!!::.......::::::::::::::::!!!!!!!######################!!!!::::::!!!!###############################!!!!!!!!!!!:!::::!!!!#####"BLACK"#####"GREEN"##!!!!!!!!!!!!!!!!!!!!!!!::::::!!!!!!!!");
    printf(GREEN"          ..:!!!!!!!!!###################################"YELLOW"!!!!!!:::!::.  ............::::::::::!!!!!!!!!!!!!!!!!!!!!!##!!!!!!!::::::::!!!!#######!!!!!!!!!!!!!!!!!!!!!!!!!!::::::::::::::!!!!!!##!!!"BLACK"####"GREEN"#!!!!!!!!!!!!!!!!!!!!!!!::::::!!!!!!!!");
    printf(GREEN"          ..:!!!!!!!!!###################################"YELLOW"!!!!!::!!!!::    ........:::::::::::::!!!!!!!!!!!!!!!!!!!!!!!!!!!!:::::..::::!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!:::::::::::::::::::!!!!#!!!!"BLACK"###"GREEN"!!!!!!!!!!!!!!!!!!!!!!!!::::::!!!!!!!!");
    printf(GREEN"          .::!!!!!!!!!!##################################"YELLOW"!!!!!:!!!!!!:. ........:::::::::::::::::::!!!!!!!!!!!!!!!!!!!!!!:::::::..:::::!!!!!!!!!!!!!!!!!!!!!!!!!!!!!::::::::::::::::::::::::!!###!!!"BLACK"##"GREEN"######!!!!!############!!::::::!!!!!!!!");
    printf(GREEN"          .::!!!!!!!!!!!#################################"YELLOW"!!!!!:!!!!!!:.......:::::::::::::::::::::::::!!!:!!!!!:::!!:::::::::::...:::::!!!!!!!!!!!!!!!!!!!!!!:::::::::::::::::::::::::::::::!!!#!!!!!"BLACK"#"GREEN"#####@@###@@@@@@@@@@@@@@!!::::!!!!!!!!!");
    printf(GREEN"...      ..::!!!!!!!!!!!##################################"YELLOW"!!::!!!!!!!:......::::::::::::::::::::::::::::::::::::::::::::::::::.....:::::::::::::::::::::::::::::::::::::::::::::::::::::!!!!!!####!!!"GREEN"!!!!!!!#!!##@@@@@@@@@@@@@!!::::!!!!!!!!!");
    printf(GREEN".::........::!!!!!!!!!!!!##################################"YELLOW"!:::!!!!!!:......:::::::::::::::::::::::!!!!!!!!!!!!!!!!!:::::::::::....::::::!!!!!!!!!!!!!!!!!!!:::::::::::::::::!!!!:!!!!!!!!!!!!####!!!"GREEN"##@@@@@@@####@@@@@@@@@@@@!!::::!!!!!!!!!");
    printf(GREEN"::::......:::!!!!!!!!!!!!##################################"YELLOW"!!::::!!!!:.:..::::::::::::::!!!!!!!!!!!!!!!!!!!!#!!!!!!!!!!::::::::::::::::::!!!!!!:!!!!!!##!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!##!!!!!"GREEN"##@@@@@@#####@@@@@@@@@@@#!:::::!!!!!!!!!");
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
