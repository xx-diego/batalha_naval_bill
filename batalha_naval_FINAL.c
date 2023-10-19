#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#define Tabuleiro_SIZE 10

//estrutura
typedef struct {
    int row;
    int col;
    bool isSunk;
} navio;

// codigo pra iniciar o tabuleiro --- zero sera agua
void initializeTabuleiro(int Tabuleiro[Tabuleiro_SIZE][Tabuleiro_SIZE]) {
    for (int i = 0; i < Tabuleiro_SIZE; i++) {
        for (int j = 0; j < Tabuleiro_SIZE; j++) {
            Tabuleiro[i][j] = 0;
        }
    }
}

// trazer tabuleiro na tela
void printTabuleiro(int Tabuleiro[Tabuleiro_SIZE][Tabuleiro_SIZE], int Historico[Tabuleiro_SIZE][Tabuleiro_SIZE], navio navios[], int numnavios) {
    printf("  0 1 2 3 4 5 6 7 8 9\n");
    for (int i = 0; i < Tabuleiro_SIZE; i++) {
        printf("%d ", i);
        for (int j = 0; j < Tabuleiro_SIZE; j++) {
            if (Historico[i][j] == -1) {
                printf("~ "); // Água revelada
            } else if (Tabuleiro[i][j] == 0) {
                printf(". "); // Local não revelado
            } else if (Tabuleiro[i][j] == 1) {
                printf("O "); // Navio do jogador
            } else if (Tabuleiro[i][j] == 2) {
                printf("X "); // Navio do oponente afundado
            }
        }
        printf("\n");
    }
}

// qtd de navio ativo ou afundado
bool allnavioSunk(navio navios[], int numnavios) {
    for (int i = 0; i < numnavios; i++) {
        if (!navios[i].isSunk) {
            return false;
        }
    }
    return true;
}

// Função para colocar os navios no tabuleiro ----- =1 será local com navio e 0 local vazio
        void placenavios(int Tabuleiro[Tabuleiro_SIZE][Tabuleiro_SIZE], navio navios[], int numnavios) {
            printf("Selecione a coluna e linha para colocar seus navios de guerra (inserir o numero da linha e em seguida o numero coluna, ambos de 0 a 9):\n");

            for (int i = 0; i < numnavios; i++) {
                printf("Navio %d: ", i + 1);
        
         int row, col;
        
        // garantir que os valores estejam dentro do intervalo de 0 a 9
            do {
                printf("Digite a linha (0 a 9): ");
                scanf("%d", &row);
            } while (row < 0 || row > 9);
        
            do {
                printf("Digite a coluna (0 a 9): ");
                scanf("%d", &col);
            } while (col < 0 || col > 9);

            if (Tabuleiro[row][col] == 0) {
                Tabuleiro[row][col] = 1;
                navios[i].row = row;
                navios[i].col = col;
            } else {
                printf("Local indisponivel, pode existir uma montanha neste local ou uma ilha, talvez um barco...tente outro local!\n");
                
            i--;
        }
    }
}

// Função para realizar um disparo e contar os tiros --- sera mantido agua revelada e navio afundado
void takeShot(int Tabuleiro[Tabuleiro_SIZE][Tabuleiro_SIZE], int Historico[Tabuleiro_SIZE][Tabuleiro_SIZE], navio navios[], int numnavios, int *shots) {
    int row, col;
    printf("Onde iremos atirar, capitao? (inserir o numero da linha e em seguida o numero coluna, ambos de 0 a 9):\n");
    scanf("%d %d", &row, &col);

    if (Historico[row][col] != -1) {
        if (Tabuleiro[row][col] == 1) {
            printf("EM CHEIO, capitao!\n");
            Tabuleiro[row][col] = 2;
            Historico[row][col] = 2;
            for (int i = 0; i < numnavios; i++) {
                if (navios[i].row == row && navios[i].col == col) {
                    navios[i].isSunk = true;
                    printf("1 tiro e o navio fez companhia pro titanic!\n");
                }
            }
        } else if (Tabuleiro[row][col] == 2) { // utilizar 2 pra quando acertar
            printf("Capitao, ja atiramos neste local!\n");
        } else {
            printf("Acertamos só agua e talvez alguns peixes( \n");
            Tabuleiro[row][col] = -1; //-1 será usado pra quando errar o tiro (acertar agua)
            Historico[row][col] = -1;
            (*shots)++;
        }
    } else {
        printf("Capitao, ja sabemos que aqui e agua!\n");
    }
}

//menuzinho para iniciar o jogo
    void printMenu() {
        printf("Batalha Naval - Menu:\n");
        printf("1. Iniciar Jogo\n");
        printf("2. Manual\n");
        printf("3. Sair\n");
    }

    void printSymbolMeaning() {
        printf("Simbolos no tabuleiro:\n");
        printf(". - Local ainda não revelado\n");
        printf("O - Navio do jogador\n");
        printf("X - Navio do oponente afundado\n");
        printf("~ - Tiro na agua\n");
    }

    int main() {
        int player1Tabuleiro[Tabuleiro_SIZE][Tabuleiro_SIZE];
        int player2Tabuleiro[Tabuleiro_SIZE][Tabuleiro_SIZE];
        int Historico[Tabuleiro_SIZE][Tabuleiro_SIZE];
        navio player1navios[5];
        navio player2navios[5];
        int numnavios = 5; //usado padrão de 5navios pra cada jogador


        initializeTabuleiro(player1Tabuleiro);
        initializeTabuleiro(player2Tabuleiro);
        initializeTabuleiro(Historico);

    int choice;

        do {
            printMenu();
            printf("Escolha uma opcao: ");
            scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Jogador 1, coloque seus navios na agua:\n");
                placenavios(player1Tabuleiro, player1navios, numnavios);
                printf("Jogador 2, coloque seus navios na agua:\n");
                placenavios(player2Tabuleiro, player2navios, numnavios);

                int currentPlayer = 1;
                int player1Shots = 0;
                int player2Shots = 0;

                while (1) {
                    printf("\n");
                    printf("\n");
                    printf("\n");
                    printf("\n");
                    printf("\n");
                    printf("\n");
                    printf("\n");
                    
                    printf("\nTabuleiro do Jogador %d:\n", currentPlayer);
                    printTabuleiro((currentPlayer == 1) ? player1Tabuleiro : player2Tabuleiro, Historico, (currentPlayer == 1) ? player2navios : player1navios, numnavios);

                    printf("Jogador %d, agora eh com voce! (total de tiros: %d):\n", currentPlayer, (currentPlayer == 1) ? player1Shots : player2Shots);
                    takeShot((currentPlayer == 1) ? player2Tabuleiro : player1Tabuleiro, Historico, (currentPlayer == 1) ? player2navios : player1navios, numnavios, (currentPlayer == 1) ? &player1Shots : &player2Shots);

                    if (allnavioSunk((currentPlayer == 1) ? player2navios : player1navios, numnavios)) {
                        printf("Jogador %d afundou todos os navios do oponente e agora eh o novo rei dos mares!!!\n", currentPlayer);
                        break;
                    }

                    currentPlayer = (currentPlayer == 1) ? 2 : 1;
                }

                break;

            case 2:
                printSymbolMeaning();
                break;

            case 3:
                printf("Saindo do jogo. Ate a proxima!\n");
                break;

            default:
                printf("Opcao inválida. Tente novamente.\n");
                break;
        }
    } while (choice != 3);

    return 0;
}
