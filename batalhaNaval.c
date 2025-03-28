#include <stdio.h>

// Desafio Batalha Naval - MateCheck
// Este código inicial serve como base para o desenvolvimento do sistema de Batalha Naval.
// Siga os comentários para implementar cada parte do desafio.

// Defini as constantes
#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3
// Função para inicializar o tabuleiro com água (0)
void inicializarTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[i][j] = 0;  // 0 representa água
        }
    }
}

// Função para exibir o tabuleiro no console
void exibirTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    //printf("Tabuleiro:\n");
    // Exibindo o cabeçalho de colunas
    printf("   ");
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        printf("%2d ", i + 1);
    }
    printf("\n");

    // Exibindo as linhas do tabuleiro
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        printf("%2c ", 'A' + i);  // Exibe a letra da linha
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            if (tabuleiro[i][j] == 0) {
                printf(" 0 ");  // Água
            } else if (tabuleiro[i][j] == 3) {
                printf(" 3 ");  // Navio
            } else if (tabuleiro[i][j] == 1) {
                printf(" 5 ");  // Área afetada pela habilidade(Cone, Cruz e Octaedro)
            }
        }
        printf("\n");
    }
}

// Função para posicionar um navio horizontalmente
int posicionarNavioHorizontal(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna) {
    if (coluna + TAMANHO_NAVIO > TAMANHO_TABULEIRO) {
        return 0;  // Verifica se o navio ultrapassa o limite da coluna
    }

    // Verifica se as posições estão livres
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        if (tabuleiro[linha][coluna + i] != 0) {
            return 0;  // Se houver sobreposição, retorna 0
        }
    }

    // Posiciona o navio
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        tabuleiro[linha][coluna + i] = 3;  // Marca as posições do navio
    }

    return 1;
}

// Função para posicionar um navio verticalmente
int posicionarNavioVertical(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna) {
    if (linha + TAMANHO_NAVIO > TAMANHO_TABULEIRO) {
        return 0;  // Verifica se o navio ultrapassa o limite da linha
    }

    // Verifica se as posições estão livres
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        if (tabuleiro[linha + i][coluna] != 0) {
            return 0;  // Se houver sobreposição, retorna 0
        }
    }

    // Posiciona o navio
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        tabuleiro[linha + i][coluna] = 3;  // Marca as posições do navio
    }

    return 1;
}

// Função para posicionar um navio diagonalmente
int posicionarNavioDiagonal(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna, int crescente) {
    // Verifica se o navio pode ser posicionado diagonalmente
    // Para diagonal crescente (da esquerda para baixo)
    // Para diagonal decrescente (da esquerda para cima)
    if (crescente) {  // Diagonal crescente (linha e coluna aumentam)
        if (linha + TAMANHO_NAVIO > TAMANHO_TABULEIRO || coluna + TAMANHO_NAVIO > TAMANHO_TABULEIRO) {
            return 0;  // Verifica se o navio ultrapassa os limites do tabuleiro
        }

        // Verifica se as posições estão livres
        for (int i = 0; i < TAMANHO_NAVIO; i++) {
            if (tabuleiro[linha + i][coluna + i] != 0) {
                return 0;  // Se houver sobreposição, retorna 0
            }
        }

        // Posiciona o navio
        for (int i = 0; i < TAMANHO_NAVIO; i++) {
            tabuleiro[linha + i][coluna + i] = 3;  // Marca as posições do navio
        }
    } else {  // Diagonal decrescente (linha diminui e coluna aumenta)
        if (linha - TAMANHO_NAVIO + 1 < 0 || coluna + TAMANHO_NAVIO > TAMANHO_TABULEIRO) {
            return 0;  // Verifica se o navio ultrapassa os limites do tabuleiro
        }

        // Verifica se as posições estão livres
        for (int i = 0; i < TAMANHO_NAVIO; i++) {
            if (tabuleiro[linha - i][coluna + i] != 0) {
                return 0;  // Se houver sobreposição, retorna 0
            }
        }

        // Posiciona o navio
        for (int i = 0; i < TAMANHO_NAVIO; i++) {
            tabuleiro[linha - i][coluna + i] = 3;  // Marca as posições do navio
        }
    }

    return 1;
}

// Função para aplicar a habilidade em cone
void habilidadeCone(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna) {
    int alcance = 3; // O alcance do cone (exemplo com 3, pode ser ajustado)

    for (int i = 0; i <= alcance; i++) {
        for (int j = -i; j <= i; j++) {
            int x = linha + i;
            int y = coluna + j;
            if (x >= 0 && x < TAMANHO_TABULEIRO && y >= 0 && y < TAMANHO_TABULEIRO) {
                tabuleiro[x][y] = 1; // Marca como área afetada pela habilidade
            }
        }
    }
}

// Função para aplicar a habilidade em cruz
void habilidadeCruz(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna) {
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        tabuleiro[linha][i] = 1; // Afeta a linha
        tabuleiro[i][coluna] = 1; // Afeta a coluna
    }
}

// Função para aplicar a habilidade em octaedro
void habilidadeOctaedro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna) {
    int alcance = 3; // O alcance do octaedro

    for (int i = -alcance; i <= alcance; i++) {
        for (int j = -alcance; j <= alcance; j++) {
            if (abs(i) + abs(j) <= alcance) {
                int x = linha + i;
                int y = coluna + j;
                if (x >= 0 && x < TAMANHO_TABULEIRO && y >= 0 && y < TAMANHO_TABULEIRO) {
                    tabuleiro[x][y] = 1; // Marca como área afetada pela habilidade
                }
            }
        }
    }
}

int main() {
    // Nível Novato - Posicionamento dos Navios
    // Sugestão: Declare uma matriz bidimensional para representar o tabuleiro (Ex: int tabuleiro[5][5];).
    // Sugestão: Posicione dois navios no tabuleiro, um verticalmente e outro horizontalmente.
    // Sugestão: Utilize `printf` para exibir as coordenadas de cada parte dos navios.

    // Nível Aventureiro - Expansão do Tabuleiro e Posicionamento Diagonal
    // Sugestão: Expanda o tabuleiro para uma matriz 10x10.
    // Sugestão: Posicione quatro navios no tabuleiro, incluindo dois na diagonal.
    // Sugestão: Exiba o tabuleiro completo no console, mostrando 0 para posições vazias e 3 para posições ocupadas.

    // Nível Mestre - Habilidades Especiais com Matrizes
    // Sugestão: Crie matrizes para representar habilidades especiais como cone, cruz, e octaedro.
    // Sugestão: Utilize estruturas de repetição aninhadas para preencher as áreas afetadas por essas habilidades no tabuleiro.
    // Sugestão: Exiba o tabuleiro com as áreas afetadas, utilizando 0 para áreas não afetadas e 1 para áreas atingidas.

    // Exemplos de exibição das habilidades:
    // Exemplo para habilidade em cone:
    // 0 0 1 0 0
    // 0 1 1 1 0
    // 1 1 1 1 1
    
    // Exemplo para habilidade em octaedro:
    // 0 0 1 0 0
    // 0 1 1 1 0
    // 0 0 1 0 0

    // Exemplo para habilidade em cruz:
    // 0 0 1 0 0
    // 1 1 1 1 1
    // 0 0 1 0 0
    
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
    // Desafio Nível Novato e Aventureiro:
    printf("Desafio Nível Novato e Aventureiro:\n");
    // Inicializa o tabuleiro
    inicializarTabuleiro(tabuleiro);

    // Exibe o tabuleiro antes de marcar os navios
    printf("Tabuleiro Não Preenchido:\n");
    exibirTabuleiro(tabuleiro);
    printf("\n");
    
    // Posicionando os navios
    // Navio horizontal (linha 2, coluna 4)
    if (!posicionarNavioHorizontal(tabuleiro, 2, 4)) {
        printf("Não foi possível posicionar o navio horizontal.\n");
    }

    // Navio vertical (linha 5, coluna 7)
    if (!posicionarNavioVertical(tabuleiro, 5, 7)) {
        printf("Não foi possível posicionar o navio vertical.\n");
    }

    // Posicionando navio diagonal crescente (linha 1, coluna 1)
    if (!posicionarNavioDiagonal(tabuleiro, 1, 1, 1)) {
        printf("Não foi possível posicionar o navio diagonal crescente.\n");
    }

    // Posicionando navio diagonal decrescente (linha 8, coluna 1)
    if (!posicionarNavioDiagonal(tabuleiro, 8, 1, 0)) {
        printf("Não foi possível posicionar o navio diagonal decrescente.\n");
    }

    // Exibindo o tabuleiro com os navios posicionados
    printf("Tabuleiro Preenchido:\n");
    exibirTabuleiro(tabuleiro);

    printf("\n");
    // Desafio Nível Mestre:
    printf("Desafio Nível Mestre:\n");
    // Inicializa o tabuleiro
    inicializarTabuleiro(tabuleiro);

    // Exibe o tabuleiro antes de marcar os navios
    printf("Tabuleiro Não Preenchido:\n");
    exibirTabuleiro(tabuleiro);
    printf("\n");

    // Exemplo de aplicação de habilidades
    habilidadeCone(tabuleiro, 4, 4); // Aplica habilidade em cone na posição (4, 4)
    
    // Exibindo o tabuleiro com as habilidades aplicadas
    printf("Tabuleiro com Habilidade Cone:\n");
    exibirTabuleiro(tabuleiro);

    // Inicializa o tabuleiro
    inicializarTabuleiro(tabuleiro);
    habilidadeCruz(tabuleiro, 4, 4); // Aplica habilidade em cruz na posição (4, 4)
    
    // Exibindo o tabuleiro com as habilidades aplicadas
    printf("\n");
    printf("Tabuleiro com Habilidade Cruz:\n");
    exibirTabuleiro(tabuleiro);

    // Inicializa o tabuleiro
    inicializarTabuleiro(tabuleiro);
    habilidadeOctaedro(tabuleiro, 4, 4); // Aplica habilidade em octaedro na posição (4, 4)

    // Exibindo o tabuleiro com as habilidades aplicadas
    printf("\n");
    printf("Tabuleiro com Habilidade Octaedro:\n");
    exibirTabuleiro(tabuleiro);

    return 0;
}
