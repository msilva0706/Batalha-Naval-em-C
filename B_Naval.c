/* batalha_naval_habilidades.c
 *
 * Jogo simplificado: Tabuleiro 10x10 com matrizes de habilidade:
 *  - Cone (apex no topo do patch)
 *  - Cruz (origem no centro)
 *  - Octaedro (vista frontal -> losango/diamante, origem no centro)
 *
 * Requisitos atendidos:
 *  - Matrizes de habilidade constru�das dinamicamente (0/1) usando loops aninhados e condicionais.
 *  - Sobreposi��o centrada no ponto de origem definido (com cuidado de limites).
 *  - Exibi��o do tabuleiro com 0 (�gua), 3 (navio) e 5 (�rea afetada).
 *
 * Compilar:
 *  gcc -std=c11 -O2 -o batalha_naval_habilidades batalha_naval_habilidades.c
 *
 * Autor: Exemplo para exerc�cio acad�mico
 */

#include <stdio.h>
#include <string.h>

#define ROWS 10
#define COLS 10

/* Valores do tabuleiro */
#define WATER 0
#define SHIP 3
#define AFFECT 5

/* Tamanho fixo para matrizes de habilidade (escolhi 5x5) */
#define SKILL_SIZE 5

/* Prototypes */
void init_board(int board[ROWS][COLS]);
void place_example_ships(int board[ROWS][COLS]);
void print_board(int board[ROWS][COLS]);
void build_cone(int mat[SKILL_SIZE][SKILL_SIZE]);
void build_cross(int mat[SKILL_SIZE][SKILL_SIZE]);
void build_octahedron(int mat[SKILL_SIZE][SKILL_SIZE]);
void overlay_skill_top_origin(int board[ROWS][COLS], int mat[SKILL_SIZE][SKILL_SIZE], int origin_r, int origin_c);
void overlay_skill_center_origin(int board[ROWS][COLS], int mat[SKILL_SIZE][SKILL_SIZE], int origin_r, int origin_c);

int main(void) {
    int board[ROWS][COLS];
    int cone[SKILL_SIZE][SKILL_SIZE];
    int cross[SKILL_SIZE][SKILL_SIZE];
    int octa[SKILL_SIZE][SKILL_SIZE];

    /* Inicializa o tabuleiro com �gua */
    init_board(board);

    /* Exemplo: coloca alguns navios (valor 3) - esses s�o s� exemplo */
    place_example_ships(board);

    /* Construir as matrizes de habilidade dinamicamente */
    build_cone(cone);        /* apex no topo-center da matriz */
    build_cross(cross);      /* cruz com origem no centro */
    build_octahedron(octa);  /* losango (diamante) com origem no centro */

    /* Definir pontos de origem para cada habilidade no tabuleiro (row, col)
       Observa��o: as posi��es s�o fixas no c�digo conforme simplifica��o pedida. */
    int cone_origin_r = 1, cone_origin_c = 4;   /* Para o cone, a origem � o topo (linha) */
    int cross_origin_r = 5, cross_origin_c = 5; /* Para cruz, origem � centro */
    int octa_origin_r  = 8, octa_origin_c  = 2; /* Para octaedro, origem � centro */

    /* Sobrep�e habilidades no tabuleiro
       - Cone: origem no topo da matriz (linha 0 da matriz corresponde ao origin_r no tabuleiro)
       - Cross e Octa: origem no centro da matriz (matriz centrada no origin) */
    overlay_skill_top_origin(board, cone, cone_origin_r, cone_origin_c);
    overlay_skill_center_origin(board, cross, cross_origin_r, cross_origin_c);
    overlay_skill_center_origin(board, octa, octa_origin_r, octa_origin_c);

    /* Imprime o tabuleiro resultante */
    printf("Legenda: 0 = agua, 3 = navio, 5 = area afetada\n\n");
    print_board(board);

    return 0;
}

/* Inicializa o tabuleiro com �gua (0) */
void init_board(int board[ROWS][COLS]) {
    for (int r = 0; r < ROWS; ++r)
        for (int c = 0; c < COLS; ++c)
            board[r][c] = WATER;
}

/* Coloca navios de exemplo (valor 3) - prop�sito visual */
void place_example_ships(int board[ROWS][COLS]) {
    /* Exemplo 1: navio horizontal tamanho 4 na linha 2, colunas 2..5 */
    for (int c = 2; c <= 5; ++c) board[2][c] = SHIP;

    /* Exemplo 2: navio vertical tamanho 3 na coluna 7, linhas 4..6 */
    for (int r = 4; r <= 6; ++r) board[r][7] = SHIP;

    /* Exemplo 3: um "bote" em 0,9 */
    board[0][9] = SHIP;
}

/* Imprime o tabuleiro linha por linha com espa�os */
void print_board(int board[ROWS][COLS]) {
    for (int r = 0; r < ROWS; ++r) {
        for (int c = 0; c < COLS; ++c) {
            printf("%d ", board[r][c]);
        }
        printf("\n");
    }
}

/* Constr�i a matriz do Cone (apex no topo-center)
   L�gica:
   - Matriz de tamanho SKILL_SIZE (�mpar) com o ponto de origem no topo-centro (linha 0, coluna mid).
   - Para as primeiras linhas (0..mid) alargamos a "base" do cone: largura = 1 + 2*row.
   - Para linhas al�m do meio (se houver), deixamos 0 (n�o parte do cone).
   Exemplo SKILL_SIZE=5:
   row0: 0 0 1 0 0
   row1: 0 1 1 1 0
   row2: 1 1 1 1 1
   row3: 0 0 0 0 0
   row4: 0 0 0 0 0
*/
void build_cone(int mat[SKILL_SIZE][SKILL_SIZE]) {
    int n = SKILL_SIZE;
    int mid = n / 2;

    /* Inicializa com zeros */
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            mat[i][j] = 0;

    /* Preenche cone usando condicionais em loops aninhados */
    for (int i = 0; i <= mid; ++i) {
        int width = 1 + 2 * i;               /* largura do cone na linha i */
        int start_col = mid - (width / 2);
        int end_col = mid + (width / 2);
        for (int j = start_col; j <= end_col; ++j) {
            if (j >= 0 && j < n) {
                mat[i][j] = 1;
            }
        }
    }
}

/* Constr�i a matriz da Cruz (origem no centro)
   L�gica:
   - Na linha central -> todos 1s
   - Na coluna central -> todos 1s
   - Resto 0
   Exemplo 5x5:
   0 0 1 0 0
   0 0 1 0 0
   1 1 1 1 1
   0 0 1 0 0
   0 0 1 0 0
*/
void build_cross(int mat[SKILL_SIZE][SKILL_SIZE]) {
    int n = SKILL_SIZE;
    int mid = n / 2;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            mat[i][j] = 0;

    for (int i = 0; i < n; ++i) {
        mat[i][mid] = 1;  /* coluna central */
        mat[mid][i] = 1;  /* linha central */
    }
}

/* Constr�i a matriz do 'Octaedro' vista frontal -> losango/diamante (origem no centro)
   L�gica (diamante):
   - Para cada linha i, calcula distance = abs(i - mid)
   - largura = n - 2*distance
   - marca 1s centralizados nessa linha
   Exemplo 5x5:
   0 0 1 0 0
   0 1 1 1 0
   1 1 1 1 1
   0 1 1 1 0
   0 0 1 0 0
*/
void build_octahedron(int mat[SKILL_SIZE][SKILL_SIZE]) {
    int n = SKILL_SIZE;
    int mid = n / 2;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            mat[i][j] = 0;

    for (int i = 0; i < n; ++i) {
        int dist = (i > mid) ? (i - mid) : (mid - i); /* abs(i-mid) */
        int width = n - 2 * dist;                     /* largura na linha i */
        int start_col = mid - (width / 2);
        int end_col = mid + (width / 2);
        for (int j = start_col; j <= end_col; ++j) {
            if (j >= 0 && j < n) mat[i][j] = 1;
        }
    }
}

/* Sobrep�e a matriz de habilidade ao tabuleiro assumindo que
   a origem da habilidade � o topo-central da matriz:
   - Matriz row 0 mapeia para origin_r no tabuleiro
   - Matriz col mid mapeia para origin_c no tabuleiro (top center)
   Verifica limites do tabuleiro (condicionais) antes de atribuir.
*/
void overlay_skill_top_origin(int board[ROWS][COLS], int mat[SKILL_SIZE][SKILL_SIZE], int origin_r, int origin_c) {
    int n = SKILL_SIZE;
    int mid = n / 2;

    for (int mr = 0; mr < n; ++mr) {
        for (int mc = 0; mc < n; ++mc) {
            if (mat[mr][mc] == 1) {
                /* calcula a posi��o correspondente no tabuleiro:
                   - row = origin_r + mr (porque topo da matriz � origin)
                   - col = origin_c + (mc - mid) (centralizar colunas em torno do origin_c) */
                int br = origin_r + mr;
                int bc = origin_c + (mc - mid);

                /* Verifica limites do tabuleiro */
                if (br >= 0 && br < ROWS && bc >= 0 && bc < COLS) {
                    /* Marca como �rea afetada (5). Observa��o:
                       - atualmente sobrescrevemos qualquer valor anterior (incluindo navio 3).
                       - se desejar preservar navios, checar board[br][bc] != SHIP antes de escrever. */
                    board[br][bc] = AFFECT;
                }
            }
        }
    }
}

/* Sobrep�e a matriz de habilidade ao tabuleiro assumindo que
   a origem da habilidade � o centro da matriz:
   - Matriz center (mid,mid) mapeia para origin_r, origin_c do tabuleiro
*/
void overlay_skill_center_origin(int board[ROWS][COLS], int mat[SKILL_SIZE][SKILL_SIZE], int origin_r, int origin_c) {
    int n = SKILL_SIZE;
    int mid = n / 2;

    for (int mr = 0; mr < n; ++mr) {
        for (int mc = 0; mc < n; ++mc) {
            if (mat[mr][mc] == 1) {
                int br = origin_r + (mr - mid); /* desloca pela diferen�a ao centro */
                int bc = origin_c + (mc - mid);

                /* Verifica limites do tabuleiro */
                if (br >= 0 && br < ROWS && bc >= 0 && bc < COLS) {
                    board[br][bc] = AFFECT;
                }
            }
        }
    }
}
