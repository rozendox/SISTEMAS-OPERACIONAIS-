#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define PAGE_SIZE 1024        // 1 KB por página
#define NUM_PAGES 8           // Total de páginas lógicas
#define INVALID_PAGE -1       // Valor que representa page fault

// Tabela de páginas simulando a MMU
int page_table[NUM_PAGES] = {2, -1, 5, 0, -1, 3, -1, 1};

/**
 * @brief Verifica se a página lógica é válida.
 * @param page_num número da página lógica
 * @return true se for válida, false caso contrário
 */
bool is_valid_page(int page_num) {
    return (page_num >= 0 && page_num < NUM_PAGES);
}

/**
 * @brief Traduz um endereço lógico em físico.
 * 
 * @param logical_address endereço lógico em decimal
 * @return endereço físico em decimal, ou -1 em caso de page fault
 */
int translate_address(int logical_address) {
    int page_number = logical_address / PAGE_SIZE;
    int offset = logical_address % PAGE_SIZE;

    if (!is_valid_page(page_number)) {
        fprintf(stderr, "[ERRO] Número de página fora do intervalo válido (0-%d)\n", NUM_PAGES - 1);
        return INVALID_PAGE;
    }

    int frame_number = page_table[page_number];
    if (frame_number == INVALID_PAGE) {
        // Simula um page fault — a página não está carregada na memória física
        printf("⚠️  Page Fault: página lógica %d não está mapeada.\n", page_number);
        return INVALID_PAGE;
    }

    int physical_address = frame_number * PAGE_SIZE + offset;

    // Log detalhado do processo de tradução
    printf("\n--- Tradução de Endereço ---\n");
    printf("Endereço lógico (VA): %d\n", logical_address);
    printf("Número da página:     %d\n", page_number);
    printf("Deslocamento:         %d\n", offset);
    printf("Quadro físico (frame): %d\n", frame_number);
    printf("Endereço físico (PA): %d\n", physical_address);
    printf("-----------------------------\n");

    return physical_address;
}

/**
 * @brief Exibe o estado atual da tabela de páginas.
 */
void print_page_table() {
    printf("\nTabela de Páginas (Page Table)\n");
    printf("-------------------------------\n");
    printf("Página Lógica | Quadro Físico\n");
    printf("-------------------------------\n");
    for (int i = 0; i < NUM_PAGES; i++) {
        if (page_table[i] == INVALID_PAGE)
            printf("%13d |   (não mapeada)\n", i);
        else
            printf("%13d | %7d\n", i, page_table[i]);
    }
    printf("-------------------------------\n");
}

int main(void) {
    int logical_address;

    printf("=============================================\n");
    printf("  Simulador Simplificado de MMU (Memory Unit)\n");
    printf("=============================================\n");

    print_page_table();

    while (1) {
        printf("\nDigite um endereço lógico em decimal (ou -1 para sair): ");
        if (scanf("%d", &logical_address) != 1) {
            fprintf(stderr, "Entrada inválida. Encerrando.\n");
            break;
        }

        if (logical_address < 0) {
            printf("Encerrando execução.\n");
            break;
        }

        int physical_address = translate_address(logical_address);
        if (physical_address != INVALID_PAGE) {
            printf("✅ Tradução bem-sucedida: Endereço físico = %d\n", physical_address);
        } else {
            printf("❌ Não foi possível traduzir o endereço.\n");
        }
    }

    return 0;
}
