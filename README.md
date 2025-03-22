# Projeto de Limpeza de Área em Cenários

Este projeto é uma implementação em C++ que simula a limpeza de áreas em cenários representados por matrizes binárias. O programa lê um arquivo XML contendo informações sobre os cenários, valida a estrutura do XML e, em seguida, realiza a limpeza das áreas especificadas.

## Estrutura do Projeto

O projeto é composto pelos seguintes arquivos:

- **main.cpp**: Contém a função principal do programa, que lê o arquivo XML, valida sua estrutura e processa os cenários para calcular a área limpa.
- **array_stack.h**: Implementação de uma pilha (stack) usando arrays.
- **array_queue.h**: Implementação de uma fila (queue) usando arrays.

## Como Funciona

1. **Leitura do XML**: O programa lê um arquivo XML que contém informações sobre os cenários, como nome, dimensões (altura e largura), posição inicial (x, y) e a matriz que representa o cenário.
2. **Validação do XML**: O programa verifica se o arquivo XML está bem formado, garantindo que todas as tags estejam corretamente abertas e fechadas.
3. **Processamento dos Cenários**: Para cada cenário, o programa calcula a área que pode ser limpa a partir da posição inicial (x, y) usando um algoritmo de busca em largura (BFS).
4. **Saída**: O programa imprime o nome do cenário e a área limpa correspondente.
