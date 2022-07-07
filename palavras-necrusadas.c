#include <stdio.h>    // Ler e escrever no terminal.
#include <stdlib.h>   //
#include <string.h>   // Manipulacao de strings.
#include <conio.h>    //
#include <windows.h>  // Comandos system, entre outros.
#include "colors.h"   // Biblioteca para colorir texto.
#include "graphics.h" // Biblioteca de animacoes.

// Define o limite de palavras na struct.
#define N 30

// Esta struct relaciona cada palavra com sua dica, orientacao, coordenadas na matriz e se ja foi respondida ou nao.
typedef struct {
    char palavra[50];
    char dica[100];
    int orientacao; // 1 - Horizontal // 2 - Vertical
    int x;
    int y;
    int respondido; //0 - Vazio //1 - Preenchido).
} dados;

// Cada funcao sera explicada abaixo.
void menu();
void entradados();
void mostradados(int a);
void editadados();
void imprimirdica();
void jogada();
void jogo();

// Funcoes de matriz:
void montamatriz();
char** resetmatriz();
void imprimirmatriz();
void freematriz(char** arr);
void addpalavra(char** arr, int p, int q, int offset);
int redlin(int p);
int redcol(int p);
char tabuleiro();
void imprimirtabuleiro();


dados infojogo[N];

// A variavel cont armazena quantas e quais palavras o jogo tem na ordem em que foram inseridas.
// A variavel fim armazena quantas palavras faltam ser respondidas para que o jogo acabe.
int cont = 0, fim;


int m, n;           // Dimensões da matriz
char** mat;         // Matriz montanda (answer key)
char** tab;         // Matriz tabuleiro do jogo (visual)

char alfabeto[26] = {"ABCDEFGHIJKLMNOPQRSTUVWXYZ"};

// A funcao main basicamente inicia o programa e chamaa funcao menu, onde todas as outras funcoes serao iniciadas.
// Ao fim do jogo, a matriz e o tabuleiro sao resetadas, a fim de liberar espaco.
int main() {
    titulo();
    menu();
    freematriz(mat);
    freematriz(tab);
    return 0;
}

// A funcao menu chama as duas funcoes principais, "entradados" e "jogo", dependendo da escolha do jogador.
void menu() {
    system("cls");
    printf(BWHT "Bem vindo ao Super Palavras Cruzadas!!!! "YEL":)"RST"\n\n");
    int opcao;

    // Aqui sao definidas opcoes.
    printf(HBLU "Escolha o que deseja fazer:\n\n" RST);
    printf("1. [Montar o jogo]\n");
    printf("2. [Jogar]\n");
    printf("3. [Sair]\n\n");

    // Aqui o jogador insere a opcao que deseja e o programa a escaneia.
    scanf("%d", &opcao);
    getchar();

    // Enquanto a resposta do jogador nao se enquadrar em uma das tres opcoes, este loop informa que a resposta nao eh valida e pede que o jogador responda novamente.
    while(opcao != 1 && opcao != 2 && opcao != 3) {
        printf(URED "Digite uma opcao valida!!! >:-(" RST "\n");
        scanf("%d", &opcao);
        getchar();
    }

    // Caso a opcao escolhida seja a 1, o programa chama a funcao entradados.
    if(opcao == 1) {
        system("cls");
        carregando();
        entradados(infojogo);
        carregando();

        // Ao retornar da funcao iniciada, o programa volta para o inicio do menu, para que o jogador escolha o que deseja fazer em seguida.
        menu();
    }

    // Caso a opcao escolhida seja a 2, o programa chama a funcao jogo.
    if(opcao == 2) {
        system("cls");
        carregando();
        jogo(infojogo);
	getchar();
	    
        // Ao retornar, o programa roda uma animacao parabenizando o jogador e volta novamente para o menu, para que o jogador escolha o que deseja fazer.
        teladefim();
        menu();
        return;
    }

    // Caso a opcao escolhida seja a 3, o programa eh finalizado.
    if(opcao == 3) {
        system("color 6");
        printf(URED "Voce saiu do jogo." RST);
        Sleep(2000);
        system("color 7");
        system("cls");
        jo();
        getchar();
        getchar();
        return;
    }
    return;
}

// Nesta funcao o jogador insere as palavras e suas respectivas dicas.
void entradados() {
    int igual;
    int c;

    // Este vetor com todos os algarismos sera usado para verificar se ha algum algarismo nas palavras inseridas.
    char numero[] = "0123456789";

    printf(HBLU "Voce esta entrando suas palavras!\n\n" RST);

    // Este marcador de retorno sera usado mais tarde
    mais:

    // A cada palavra que eh inserida, o contador de palavras aumenta em 1.
    cont++;

    // O programa, entao, pede que o jogador insira uma palavra.
    printf(BGRN "Entre os dados da palavra %d."RST"\n", cont);
    printf("Palavra: ");

    // Caso a palavra inserida pelo jogador nao seja valida por algum motivo, o programa informa o problema e pede que o jogador insira novamente.
    do {
        fgets(infojogo[cont].palavra, sizeof(infojogo[cont].palavra), stdin);
        strtok(infojogo[cont].palavra, "\n");

        // Easteregg...
        if (strcasecmp(infojogo[cont].palavra, "jo ueyama") == 0) {

            system("color 4");
            Sleep(1000);
            system("color F4");
            Sleep(500);
            system("cls");
            system("color 17");
            Sleep(100);

            printf("A problem has been detected and Windows has been shut down to prevent damage\nto your computer.\n\nA process or thread crucial to system operation has unexpectedly exited or been\nterminated.\nIf this is the first time you've seen this Stop error screen,\nrestart your computer. if this screen appears again, follow these steps:\n\nCheck to make sure any new hardware or software is properly installed.\nIf this is a new installation, ask your hardware or software manufacturer\nfor and Windows updates you might need.\n\nIf problems continue, disable or remove any newly installed hardware.\nDisable BIOS memory options such as caching or shadowing.\nIf you need to use Safe Mode to remove or disable components, restart\nyour computer, press F8 to select Advanced Startup Options, and then\nselect Safe Mode.\n\nTechnical information:\n\n*** STOP: 0x000000FE (0x00000008, 0x000000006, 0x00000009, 0x847075cc\n\n\n\nCollecting data for crash dump ...\nInitializing disk for crash dump ...\n");

            Sleep(5000);
            system("color 7");

            jo();
            getchar();

            system("cls");
            system("color 7");

            cont--;
            goto mais;
        }

        // Aqui o programa testa se a palavra inserida eh igual as outras palavras ja inseridas.
        for(int i=1; i<cont; i++) {

            igual=strcasecmp(infojogo[cont].palavra, infojogo[i].palavra);

            if(igual==0)break;
        }

        // Caso a palavra tenha algum algarismo (que é analisando comparando todos os caracteres da palavra com o vetor numero), o programa recusa.
        if(strpbrk(infojogo[cont].palavra, numero) != NULL){

            system("color 6");
            Sleep(500);
            system("color 7");
            system("cls");

            printf(BRED "Nao insira numeros nas palavras"RED" >:(\n\n"RST"Insira uma palavra valida: ");

        }

        // Caso a palavra tenha apenas um caractere, o programa recusa.
        else if(strlen(infojogo[cont].palavra) <= 1){
            system("color 6");
            Sleep(500);
            system("color 7");
            system("cls");

            printf(BRED "Palavra muito pequena.\n\n" RST "Insira uma palavra com mais de uma letra: ");
        }

        // Caso a palavra seja igual a alguma palavra inserida anteriorente, o programa recusa.
        if(igual == 0){
            system("color 6");
            Sleep(500);
            system("color 7");
            system("cls");

            printf(BYEL"Essa palavra ja esta no jogo!\n\n" RST "Digite outra palavra: ");
        }
    } while (strlen(infojogo[cont].palavra)<=1||igual==0||strpbrk(infojogo[cont].palavra, numero)!=NULL);

    // Aqui o programa pede recebe a dica da palavra inserida.
    printf("Dica: ");
    fgets(infojogo[cont].dica, sizeof(infojogo[cont].dica), stdin);
    strtok(infojogo[cont].dica, "\n");

    // Ao final, o programa finaliza a insercao dos dados da palavra.
    printf(GRN "Voce inseriu a palavra %d"RST"\n\n",cont);
    infojogo[cont].respondido=0;

    // Este marcador de retorno sera utilizado mais tarde.
    repete1:

    // O programa pede se o jogador deseja inserir mais palavras.
    printf(YEL"Deseja inserir mais?"RST"\n");
    printf("1. [Sim]\n2. [Nao]\n");

    // O jogador insere sua resposta.
    scanf("%d",&c);
    getchar();

    // Caso a opcao escolhida seja 1, o programa volta para aquele primeiro marcador de retorno para que uma nova palavra seja inserida.
    if(c == 1){
        system("cls");
        goto mais;
    }

    // Caso a resposta nao seja valida, o programa informa e pede que o jogador responda novamente.
    if(c != 1 && c != 2){
        system("cls");
        system("color 6");
        Sleep(500);
        system("color 7");
        printf(RED "Digite uma opcao valida >:(\n\n"RST);
        goto repete1;
    }

    // Por fim, apos a insercao de todas as palavras, a variavel fim se torna o total de palavras no jogo.
    fim = cont;
    carregando();

    // Por fim, o programa chama a funcao "editadados".
    editadados(infojogo);
}

// Nesta funcao o jogador verifica se as palavras estao corretas. Caso queira consertar ou mudar alguma palavra eh aqui que sera feito.
void editadados(){
    system("cls");
    char c = 's';
    do {
        system("cls");
        printf(HBLU "Agora vamos revisar os dados!\n\n" RST);

        // O programa imprime os dados de todas as palavras inseridas.
        for (int l = 1; l <= cont; l++){
            mostradados(l);
            printf("\n");
        }

        // Este marcador de retorno sera utilizado mais tarde.
        repete2:

        // O programa pede se o jogador deseja alterar alguma palavra ou dica e recebe a resposta.
        printf(YEL"Deseja editar alguma palavra?"RST"\n1. [Sim]\n2. [Nao]\n");
        scanf("%d",&c);

        // Se a resposta for invalida o programa informa e volta para o marcador repete2 para que o jogador responda novamente.
        if(c != 1 && c !=2 ){
            system("cls");
            system("color 6");
            Sleep(500);
            system("color 7");
            printf(RED "Digite uma opcao valida >:("RST"\n");
            goto repete2;
        }

        // Se a resposta for 1, o programa inicia o procedimento para editar alguma palavra ou dica.
        if(c==1){
            char o;
            int edita;

            // Primeiramente ele pede qual palavra o jogador deseja editar e recebe a resposta.
            printf("\n"YEL"Diga o numero da palavra que voce quer editar: " RST);
            scanf("%d", &edita);
            getchar();

            // Caso a resposta seja invalida, o programa informa e entra no loop, onde pedira para que o jogador responda novamente ate obter uma resposta valida.
            while(edita <=0 || edita > cont) {
                printf(RED "Digite uma palavra valida! >:("RST"\n");
                scanf("%d", &edita);
                getchar();
            }

            // Apos a escolha da palavra, o jogador insere os novos dados.
            printf(BYEL "Entre os novos dados da palavra %d"RST"\n", edita);
            printf("Palavra: ");

            int igual;
            char numero[]="0123456789";

            // Da mesma forma que na funcao entradados, a palavra nao pode ser repetida, nem conter algarismos, nem ter apenas um digito.
            // Este do while, portanto, funciona basicamente da mesma forma que o do while do entradados.
            do {
                fgets(infojogo[edita].palavra, sizeof(infojogo[edita].palavra), stdin);
                strtok(infojogo[edita].palavra, "\n");

                for(int i = 1; i <= cont; i++){
                    if(i != edita) {
                        igual=strcasecmp(infojogo[edita].palavra, infojogo[i].palavra);
                        if(igual == 0) break;
                    }
                }
                if(strpbrk(infojogo[edita].palavra, numero) != NULL) {
                    system("color 6");
                    Sleep(500);
                    system("color 7");
                    system("cls");
                    printf(BRED "Nao insira numeros nas palavras"RED" >:(\n\n"RST"Insira uma palavra valida: ");
                }
                else if(strlen(infojogo[edita].palavra) <= 1){
                    system("color 6");
                    Sleep(500);
                    system("color 7");
                    system("cls");
                    printf(RED"Por favor, insira uma palavra com mais de uma letra: "RST);
                }
                if(igual == 0){
                    system("color 6");
                    Sleep(500);
                    system("color 7");
                    system("cls");
                    printf(YEL"Essa palavra ja esta no jogo!\n\n"RST"Digite outra palavra: ");
                }
            } while(strlen(infojogo[edita].palavra) <=1 || igual == 0||strpbrk(infojogo[edita].palavra, numero) != NULL);

            // Em seguida, o programa recebe a dica.
            printf("Dica: ");
            fgets(infojogo[edita].dica, sizeof(infojogo[edita].dica), stdin);
            strtok(infojogo[edita].dica, "\n");

            // Ao fim da edicao, o programa informa que a palavra foi devidamente atualizada e o codigo volta ao inicio do do while, ate que o jogador nao deseje mais editar palavras.
            printf(GRN"Voce editou a palavra %d"RST"\n\n",edita);
            getchar();
        }
    } while(c == 1);
    system("cls");

    // Depois de editar as palavras desejadas, o programa chama a funcao para montar a matriz do jogo.
    montamatriz();
}

// Esta fucao basicamente imprime na tela cada palavra com sua respectiva dica.
void mostradados(int a) {
    printf(CYN"Dados da palavra %d\n"RST, a);
    printf("Palavra: %s\nDica: %s\n", infojogo[a].palavra, infojogo[a].dica);
}

// Esta funcao basicamente imprime na tela as dicas de cada palavra. Apos uma palavra ser corretamente respondida, a funcao nao imprime mais sua dica na tela.
void imprimirdica() {
    printf(HBLU "DICAS\n\n" RST);
    for (int i = 1; i <= cont; i++) {

        // Por conta deste if, o programa so vai imprimir as dicas de palavras que nao foram respondidas.
        if(infojogo[i].respondido == 0){
            printf(BWHT "Palavra %d: " WHT, i);
            puts(infojogo[i].dica);
            printf("\n" RST);
        }
    }
}

// Esta funcao testa se a resposta do jogador para determinada palavra esta correta ou nao.
void jogada() {
    char resp[50];
    int t;

    // Aqui o programa imprime o tabuleiro do jogo, ocm as casas de palavras nao respondidas vazias.
    imprimirtabuleiro();

    // Em seguida, imprime as dicas das palavras que faltam.
    imprimirdica(infojogo);

    // Aqui, o programa pede qual palavra o jogador deseja tentar responder e escaneia a resposta.
    printf("\n");
    printf(GRN"Escolha a palavra que deseja tentar: "RST);
    scanf("%d", &t);
    getchar();

    // Caso a opcao escolhida seja invalida, o programa informa e pede que o jogador insira uma nova resposta ate que obtenha uma valida.
    while(t > cont||t <= 0||infojogo[t].respondido == 1){
        system("cls");

        // Caso o numero da resposta nao represente o numero de uma palavra inserida, o programa recusa.
        if(t > cont || t <= 0) {
            printf(YEL "Nao existe palavra com esse numero.\n\n" RST);
        }

        // Caso a palavra ja tenha sido respondida, o programa recusa.
        if(infojogo[t].respondido==1) {
            printf(YEL"Essa palavra ja foi respondida.\n\n" RST);
        }

        // O programa entao, imprime novamente o tabuleiro e as dicas...
        imprimirtabuleiro();
        imprimirdica(infojogo);
        printf("\n");
        printf(GRN"Escolha outra palavra: "RST);

        // ...e pede que o jogador escolha novamente.
        scanf("%d", &t);
        getchar();
    }

    // Obtendo uma resposta valida, o programa pede que o jogador insira a resposta que acredita ser a correta, e a recebe.
    printf("\n");
    printf(CYN"Insira sua resposta: "RST);
    fgets(resp, sizeof(resp), stdin);
    strtok(resp, "\n");

    // O programa, entao, compara a palavra escolhida com a resposta dada pelo jogador.

    // Se a resposta estiver correta:
    if(strcasecmp(infojogo[t].palavra, resp) == 0){

        // O programa informa que o jogador acertou;
        printf(GRN "Resposta correta! XD\n\n" RST);
        Sleep(600);
        system("cls");

        // A palavra escolhida eh definida como respondida;
        infojogo[t].respondido = 1;

        // A variavel fim diminui em 1;
        fim--;

        // E a palavra aparece no tabuleiro.
        addpalavra(tab, t, t, 1);
        system("cls");
    }

    // Se a resposta estiver incorreta:
    else {

        // O programa informa que o jogador errou.
        printf(RED "Resposta incorreta ;-;\n\n" RST);
        getchar();
        system("cls");
    }
}

// Esta funcao roda o jogo em si. Roda enquanto houver alguma palavra que ainda nao foi respondida corretamente.
void jogo() {
    system("cls");

    // Inicializa o tabuleiro de jogo.
    tabuleiro();
    char resp[50];
    int t;

    // Caso nenhuma palavra tenha sido inserida quando o jogador esolhe essa opcao no menu, o programa informa que nao ha palavras e volta para o meun.
    if(cont == 0) {
        system("color 4");
        printf("Nenhuma palavra foi inserida ainda!\nPressione qualquer tecla para voltar ao menu! :)");
        getchar();
        system("color 7");
        menu();
    }

    // Caso haja palavras, o programa procede com as tentativas
    else {

        // Enquanto houverem palavras nao respondidas, o programa chama a funcao jogada.
        while(1) {
            printf(BMAG "--- Bom jogo! ---\n\n" RST);
            jogada(infojogo);

            // Quando as palavras acabam...
            if(fim == 0) {
                Sleep(500);

                // ... o programa sai do loop, terminando o jogo.
                break;
            }
            system("cls");
        }
        return;
    }
}


void montamatriz() {

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
        printf(RED"Opcao incorreta!\n"RST);
        imprimirmatriz();
        goto orientacao1;
    }
    system("cls");

	mat = resetmatriz(m, n, mat);
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
        if (infojogo[p].orientacao == 1) {
            if (infojogo[p].y > n-strlen(infojogo[p].palavra)) {
                system("cls");
                printf(RED "Coordenada invalida: palavra extrapola os limites da matriz." RST);
                goto coordenadas;
            }

            for (int i = 0; i < strlen(infojogo[p].palavra); i++) {
                if (mat[infojogo[p].x][infojogo[p].y + i] != '.' && infojogo[p].palavra[i] != mat[infojogo[p].x][infojogo[p].y + i]) {
                    system("cls");
                   printf(RED "Coordenada invalida: conflito com outra palavra." RST);
                    goto coordenadas;
                }
            }
        }

        if (infojogo[p].orientacao == 2) {
            if (infojogo[p].x > m-strlen(infojogo[p].palavra)) {
                system("cls");
                printf(RED "Coordenada invalida: palavra extrapola os limites da matriz." RST);
                goto coordenadas;
            }

            for (int i = 0; i < strlen(infojogo[p].palavra); i++) {
                if (mat[infojogo[p].x + i][infojogo[p].y] != '.' && infojogo[p].palavra[i] != mat[infojogo[p].x + i][infojogo[p].y]) {
                    system("cls");
                    printf(RED "Coordenada invalida: conflito com outra palavra." RST);
                    goto coordenadas;
                }
            }
        }

        system("cls");
        addpalavra(mat, p, p, 0);

        int m_ = redlin(p);
        int n_ = redcol(p);

        freematriz(mat);
        m = m_;
        n = n_;
        mat = resetmatriz();

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
    printf("\n\n");
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
