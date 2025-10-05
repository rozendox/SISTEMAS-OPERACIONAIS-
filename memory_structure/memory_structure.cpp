/**
 * ============================================================
 *  Demonstrador de Estrutura de Memória de um Processo
 *  Autor: Gabriel Rozendo
 *  Capítulo: 15 – Uso de Memória (TEXT, DATA, BSS, HEAP, STACK)
 * ============================================================
 *  Objetivo:
 *  - Demonstrar a localização das variáveis nos segmentos:
 *      TEXT  → código executável
 *      DATA  → variáveis globais inicializadas
 *      BSS   → variáveis globais não inicializadas
 *      HEAP  → memória alocada dinamicamente
 *      STACK → variáveis locais e frames de função
 * ============================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// =====================
// SEGMENTOS GLOBAIS
// =====================

// Variável global inicializada → segmento DATA
int global_inicializada = 42;

// Variável global não inicializada → segmento BSS
int global_nao_inicializada;

// Função simples → segmento TEXT
void exemplo_funcao() {
    printf("Executando função no segmento TEXT.\n");
}

/**
 * @brief Imprime o endereço e o segmento estimado de uma variável.
 * @param nome Nome simbólico da variável
 * @param endereco Ponteiro ou endereço da variável
 * @param segmento Nome do segmento (DATA, BSS, HEAP, STACK)
 */
void print_endereco(const char *nome, void *endereco, const char *segmento) {
    printf("%-30s -> Endereço: %p   | Segmento: %s\n", nome, endereco, segmento);
}

int main(void) {
    printf("===========================================================\n");
    printf("   MAPA DE MEMÓRIA DE UM PROCESSO (Visualização Didática)\n");
    printf("===========================================================\n\n");

    // Variável local → segmento STACK
    int variavel_local = 99;

    // Alocação dinâmica → segmento HEAP
    int *ponteiro_heap = (int *) malloc(sizeof(int));
    if (!ponteiro_heap) {
        fprintf(stderr, "Erro: falha ao alocar memória dinâmica.\n");
        return EXIT_FAILURE;
    }
    *ponteiro_heap = 1234;

    // Impressão dos endereços e segmentos
    printf("🔹 Endereços de variáveis e segmentos:\n\n");
    print_endereco("Função exemplo_funcao()", (void *) exemplo_funcao, "TEXT");
    print_endereco("Variável global_inicializada", &global_inicializada, "DATA");
    print_endereco("Variável global_nao_inicializada", &global_nao_inicializada, "BSS");
    print_endereco("Ponteiro alocado (malloc)", ponteiro_heap, "HEAP");
    print_endereco("Variável local (main)", &variavel_local, "STACK");

    printf("\n===========================================================\n");
    printf("   OBSERVAÇÕES:\n");
    printf("===========================================================\n");
    printf("• TEXT: contém código executável (funções e instruções).\n");
    printf("• DATA: armazena variáveis globais e estáticas inicializadas.\n");
    printf("• BSS: contém variáveis globais e estáticas não inicializadas.\n");
    printf("• HEAP: região de crescimento ascendente (malloc/free).\n");
    printf("• STACK: região de crescimento descendente (frames de função).\n");
    printf("===========================================================\n");

    // Demonstra visualmente a separação entre as regiões
    printf("\nMapa conceitual (endereços podem variar):\n");
    printf("-----------------------------------------------------------\n");
    printf("|         STACK  ↑ (variáveis locais, frames)              |\n");
    printf("|----------------------------------------------------------|\n");
    printf("|         HEAP   ↑ (malloc, calloc, realloc)               |\n");
    printf("|----------------------------------------------------------|\n");
    printf("|         BSS / DATA (variáveis globais)                   |\n");
    printf("|----------------------------------------------------------|\n");
    printf("|         TEXT (código executável)                         |\n");
    printf("-----------------------------------------------------------\n");

    // Libera memória alocada dinamicamente
    free(ponteiro_heap);

    return EXIT_SUCCESS;
}
