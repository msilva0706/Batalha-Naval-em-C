# Batalha Naval com Habilidades Especiais (C)

Este projeto implementa um tabuleiro de **Batalha Naval 10x10** em linguagem **C**, com o uso de habilidades especiais que afetam áreas do tabuleiro.

## 🚀 Funcionalidades
- Tabuleiro 10x10 inicializado com água (`0`).
- Colocação de navios de exemplo (`3`) em posições fixas.
- Implementação de três habilidades especiais:
  - **Cone** → origem no topo e expansão para baixo.
  - **Cruz** → origem no centro, formando um `+`.
  - **Octaedro (losango)** → origem no centro, formando um diamante.
- Matrizes de habilidade (`5x5`) construídas dinamicamente com **loops aninhados** e **condicionais**.
- Sobreposição das áreas de efeito no tabuleiro:
  - Água = `0`
  - Navio = `3`
  - Área afetada pela habilidade = `5`
- Impressão final do tabuleiro no console.

## 🛠️ Como compilar e executar
### Usando GCC no terminal:
```bash
gcc -std=c11 -O2 -o batalha_naval batalha_naval_habilidades.c
./batalha_naval
```

### Usando Code::Blocks
1. Crie um novo projeto `Console application (C)`.
2. Substitua o conteúdo do `main.c` pelo código do arquivo `batalha_naval_habilidades.c`.
3. Compile (`F9`) e execute (`Ctrl+F10`).

## 📌 Exemplo de saída
Legenda:
```
0 = água
3 = navio
5 = área afetada
```

Saída (exemplo ilustrativo):
```
0 0 0 0 5 0 0 0 0 3
0 0 0 5 5 5 0 0 0 0
0 0 3 3 5 3 3 5 0 0
0 0 0 0 5 0 0 0 0 0
0 0 0 0 5 0 0 0 3 0
0 0 0 0 5 0 0 0 3 0
0 0 0 0 5 0 0 0 3 0
0 0 0 0 5 0 0 0 0 0
0 5 5 5 5 5 0 0 0 0
0 0 5 0 0 0 0 0 0 0
```

## 📖 Estrutura
- `batalha_naval_habilidades.c` → código fonte principal.
- `README.md` → documentação do projeto.
- `LOGICA.md` → explicação detalhada da lógica.

## 📌 Simplificações
- As posições das habilidades estão definidas diretamente no código (sem input do usuário).
- Não há cálculo de dano, apenas visualização.
- Matrizes fixas em 5x5.
- Verificação de limites simplificada.
