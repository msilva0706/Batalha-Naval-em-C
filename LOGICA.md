# Lógica do Programa

Este documento descreve a lógica usada para implementar o projeto **Batalha Naval com Habilidades**.

## 1. Estrutura do Tabuleiro
- O tabuleiro é uma matriz `10x10` (`int board[10][10]`).
- Valores possíveis:
  - `0` → água
  - `3` → navio
  - `5` → área afetada por habilidade

## 2. Matrizes de Habilidade
Cada habilidade é representada por uma matriz `5x5` com valores:
- `1` → posição afetada
- `0` → posição não afetada

### 2.1 Cone
- Origem no **topo-centro** da matriz.
- Cada linha expande a largura do cone:
  - Linha 0: um ponto.
  - Linha 1: três pontos.
  - Linha 2: cinco pontos.
- Linhas abaixo do meio ficam zeradas.

Exemplo (5x5):
```
0 0 1 0 0
0 1 1 1 0
1 1 1 1 1
0 0 0 0 0
0 0 0 0 0
```

### 2.2 Cruz
- Origem no **centro** da matriz.
- Preenche linha e coluna central.

Exemplo (5x5):
```
0 0 1 0 0
0 0 1 0 0
1 1 1 1 1
0 0 1 0 0
0 0 1 0 0
```

### 2.3 Octaedro (Losango)
- Origem no **centro** da matriz.
- Cada linha forma parte de um diamante:
  - Quanto mais perto do centro, mais larga a linha.

Exemplo (5x5):
```
0 0 1 0 0
0 1 1 1 0
1 1 1 1 1
0 1 1 1 0
0 0 1 0 0
```

## 3. Sobreposição no Tabuleiro
- **Cone** → origem é o topo da matriz (`linha 0` alinhada com posição no tabuleiro).
- **Cruz e Octaedro** → origem é o centro da matriz (`linha/coluna central` alinhada com posição no tabuleiro).
- Para cada célula da matriz:
  1. Se valor = `1`, calcula posição correspondente no tabuleiro.
  2. Verifica se a posição está dentro dos limites `0 <= r < 10` e `0 <= c < 10`.
  3. Marca a posição com `5`.

## 4. Impressão do Tabuleiro
- Usa `printf` dentro de dois loops (`for` aninhados).
- Cada linha é exibida com valores separados por espaço.

## 5. Regras de Implementação
- Matrizes criadas dinamicamente com **loops aninhados e condicionais**.
- Sobreposição respeita limites do tabuleiro.
- O código é comentado e organizado para facilitar a leitura.
