/**
 * ============================================================
 *  SIMULADOR DE ESTRATÉGIAS DE ALOCAÇÃO DE MEMÓRIA
 *  ------------------------------------------------------------
 *  Capítulo: 16 – Alocação de Memória
 *  Autor: Gabriel Rozendo
 *  Modo: Avançado / Produção Simulada
 * ============================================================
 *
 *  Conceitos abordados:
 *   - Estratégias First Fit e Best Fit
 *   - Fragmentação interna e externa
 *   - Estrutura de lista encadeada para buracos de memória
 *   - Gerenciamento de blocos de alocação com métricas
 *   - Uso de logs e diagnósticos avançados
 * ============================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_LABEL 32
#define DEBUG_MODE 1   // 1 = habilita logs detalhados, 0 = modo silencioso

// =============================================================
// Estruturas de dados — modelagem da memória simulada
// =============================================================

typedef struct Hole {
    int id;
    int size;
    struct Hole *next;
} Hole;

typedef struct Allocation {
    int id;
    int size;
    int allocated_in;  // ID do buraco em que foi alocado
    struct Allocation *next;
} Allocation;

// =============================================================
// Cabeçalhos de funções — separação por módulos conceituais
// =============================================================

Hole *create_hole_list(const int holes[], size_t n);
Allocation *allocate_first_fit(Hole *head, const int requests[], size_t n);
Allocation *allocate_best_fit(Hole *head, const int requests[], size_t n);
void print_memory_state(Hole *holes, Allocation *allocs);
void free_memory(Hole *holes, Allocation *allocs);
void reset_holes(Hole **holes, const int initial_holes[], size_t n);
void log_event(const char *msg);

// =============================================================
// Implementação — Funções utilitárias e gerenciadores
// =============================================================

/**
 * @brief Cria a lista encadeada inicial de buracos de memória.
 */
Hole *create_hole_list(const int holes[], size_t n) {
    Hole *head = NULL, *curr = NULL;
    for (size_t i = 0; i < n; i++) {
        Hole *new_hole = (Hole *)malloc(sizeof(Hole));
        if (!new_hole) {
            perror("Falha na alocação de memória para buraco");
            exit(EXIT_FAILURE);
        }
        new_hole->id = (int)i + 1;
        new_hole->size = holes[i];
        new_hole->next = NULL;

        if (!head) head = new_hole;
        else curr->next = new_hole;

        curr = new_hole;
    }
    return head;
}

/**
 * @brief Função genérica de log — ativa apenas em DEBUG_MODE.
 */
void log_event(const char *msg) {
    if (DEBUG_MODE)
        printf("[LOG] %s\n", msg);
}

/**
 * @brief Reseta os buracos ao estado inicial (útil para comparar First Fit x Best Fit)
 */
void reset_holes(Hole **holes, const int initial_holes[], size_t n) {
    free_memory(*holes, NULL);
    *holes = create_hole_list(initial_holes, n);
}

/**
 * @brief Libera toda a memória alocada dinamicamente (buracos e alocações).
 */
void free_memory(Hole *holes, Allocation *allocs) {
    while (holes) {
        Hole *temp = holes;
        holes = holes->next;
        free(temp);
    }
    while (allocs) {
        Allocation *temp = allocs;
        allocs = allocs->next;
        free(temp);
    }
}

/**
 * @brief Exibe o estado atual dos buracos e alocações.
 */
void print_memory_state(Hole *holes, Allocation *allocs) {
    printf("\n📊 Estado atual da memória:\n");
    printf("----------------------------------------------------\n");
    printf("Buracos disponíveis:\n");
    while (holes) {
        printf("  -> Buraco #%d: %d unidades livres\n", holes->id, holes->size);
        holes = holes->next;
    }

    printf("\nBlocos alocados:\n");
    while (allocs) {
        printf("  -> Alocação #%d: %d unidades em Buraco #%d\n",
               allocs->id, allocs->size, allocs->allocated_in);
        allocs = allocs->next;
    }
    printf("----------------------------------------------------\n");
}

// =============================================================
// Estratégia 1 — FIRST FIT
// =============================================================

Allocation *allocate_first_fit(Hole *head, const int requests[], size_t n) {
    log_event("Iniciando alocação com algoritmo FIRST FIT.");
    Allocation *alloc_head = NULL, *curr_alloc = NULL;

    for (size_t i = 0; i < n; i++) {
        Hole *curr = head;
        bool allocated = false;

        while (curr) {
            if (curr->size >= requests[i]) {
                // Cria registro da alocação
                Allocation *new_alloc = (Allocation *)malloc(sizeof(Allocation));
                new_alloc->id = (int)i + 1;
                new_alloc->size = requests[i];
                new_alloc->allocated_in = curr->id;
                new_alloc->next = NULL;

                if (!alloc_head) alloc_head = new_alloc;
                else curr_alloc->next = new_alloc;

                curr_alloc = new_alloc;

                // Reduz o tamanho do buraco
                curr->size -= requests[i];
                log_event("Bloco alocado (FIRST FIT). Atualizando buraco.");
                allocated = true;
                break;
            }
            curr = curr->next;
        }

        if (!allocated)
            printf("🚫 Não foi possível alocar o bloco #%zu (%d unidades).\n", i + 1, requests[i]);
    }
    return alloc_head;
}

// =============================================================
// Estratégia 2 — BEST FIT
// =============================================================

Allocation *allocate_best_fit(Hole *head, const int requests[], size_t n) {
    log_event("Iniciando alocação com algoritmo BEST FIT.");
    Allocation *alloc_head = NULL, *curr_alloc = NULL;

    for (size_t i = 0; i < n; i++) {
        Hole *best_hole = NULL;
        int best_size = __INT_MAX__;

        // Busca o buraco mais justo
        for (Hole *curr = head; curr; curr = curr->next) {
            if (curr->size >= requests[i] && curr->size < best_size) {
                best_hole = curr;
                best_size = curr->size;
            }
        }

        if (best_hole) {
            Allocation *new_alloc = (Allocation *)malloc(sizeof(Allocation));
            new_alloc->id = (int)i + 1;
            new_alloc->size = requests[i];
            new_alloc->allocated_in = best_hole->id;
            new_alloc->next = NULL;

            if (!alloc_head) alloc_head = new_alloc;
            else curr_alloc->next = new_alloc;
            curr_alloc = new_alloc;

            best_hole->size -= requests[i];
            log_event("Bloco alocado (BEST FIT). Buraco ajustado.");
        } else {
            printf("🚫 Falha na alocação: bloco #%zu (%d unidades) não coube em nenhum buraco.\n", i + 1, requests[i]);
        }
    }
    return alloc_head;
}

// =============================================================
// Ponto de entrada — MAIN
// =============================================================

int main(void) {
    const int initial_holes[] = {100, 500, 200, 300, 600};
    const int requests[] = {212, 417, 112, 426};

    size_t num_holes = sizeof(initial_holes) / sizeof(initial_holes[0]);
    size_t num_requests = sizeof(requests) / sizeof(requests[0]);

    printf("============================================================\n");
    printf("   SIMULADOR DE ALOCAÇÃO DE MEMÓRIA (FIRST FIT / BEST FIT)\n");
    printf("============================================================\n");

    Hole *holes = create_hole_list(initial_holes, num_holes);

    printf("\n🔹 Estratégia: FIRST FIT\n");
    Allocation *first_allocs = allocate_first_fit(holes, requests, num_requests);
    print_memory_state(holes, first_allocs);

    reset_holes(&holes, initial_holes, num_holes);

    printf("\n🔹 Estratégia: BEST FIT\n");
    Allocation *best_allocs = allocate_best_fit(holes, requests, num_requests);
    print_memory_state(holes, best_allocs);

    free_memory(holes, first_allocs);
    free_memory(NULL, best_allocs);

    printf("\n✅ Simulação encerrada com sucesso.\n");
    return 0;
}
