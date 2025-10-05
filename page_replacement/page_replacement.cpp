/**
 * ============================================================
 *  SIMULADOR DE SUBSTITUIÇÃO DE PÁGINAS – FIFO e LRU
 *  ------------------------------------------------------------
 *  Capítulo: 17 – Paginação em Disco
 *  Autor: Gabriel Rozendo
 *  Nível: Profissional / Kernel Educacional
 * ============================================================
 *
 *  Este simulador implementa dois algoritmos clássicos:
 *   • FIFO (First-In, First-Out)
 *   • LRU (Least Recently Used)
 *
 *  Objetivo:
 *   - Demonstrar o impacto da política de substituição
 *     sobre o número de Page Faults.
 *   - Simular a movimentação das páginas na memória.
 * ============================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_REF 32
#define MAX_FRAMES 10
#define ENABLE_LOGS 1   // 1 = habilita logs detalhados, 0 = modo silencioso

// =============================================================
// Estrutura da memória (quadro de páginas)
// =============================================================

typedef struct {
    int page;
    int timestamp;  // usado pelo LRU
    bool valid;
} Frame;

// =============================================================
// Funções utilitárias
// =============================================================

void log_event(const char *msg) {
    if (ENABLE_LOGS)
        printf("[LOG] %s\n", msg);
}

/**
 * @brief Inicializa os quadros de memória.
 */
void initialize_frames(Frame *frames, int num_frames) {
    for (int i = 0; i < num_frames; i++) {
        frames[i].page = -1;
        frames[i].timestamp = 0;
        frames[i].valid = false;
    }
}

/**
 * @brief Verifica se a página já está em memória.
 */
int find_page(Frame *frames, int num_frames, int page) {
    for (int i = 0; i < num_frames; i++)
        if (frames[i].valid && frames[i].page == page)
            return i;
    return -1;
}

/**
 * @brief Exibe o estado atual da memória.
 */
void print_frames(Frame *frames, int num_frames, int current_page) {
    printf("Página referenciada: %d -> [", current_page);
    for (int i = 0; i < num_frames; i++) {
        if (frames[i].valid)
            printf("%d", frames[i].page);
        else
            printf("-");
        if (i < num_frames - 1) printf(" ");
    }
    printf("]\n");
}

// =============================================================
// FIFO — First-In, First-Out
// =============================================================

int simulate_FIFO(int *refs, int num_refs, int num_frames) {
    Frame frames[MAX_FRAMES];
    initialize_frames(frames, num_frames);

    int page_faults = 0;
    int pointer = 0;

    log_event("Iniciando simulação FIFO...");

    for (int i = 0; i < num_refs; i++) {
        int page = refs[i];
        if (find_page(frames, num_frames, page) == -1) {
            frames[pointer].page = page;
            frames[pointer].valid = true;
            pointer = (pointer + 1) % num_frames;
            page_faults++;
            log_event("Page Fault (FIFO) — página substituída.");
        }
        print_frames(frames, num_frames, page);
    }

    printf("\n📊 Resultado FIFO: %d page faults\n", page_faults);
    return page_faults;
}

// =============================================================
// LRU — Least Recently Used
// =============================================================

int simulate_LRU(int *refs, int num_refs, int num_frames) {
    Frame frames[MAX_FRAMES];
    initialize_frames(frames, num_frames);

    int page_faults = 0;
    int time = 0;

    log_event("Iniciando simulação LRU...");

    for (int i = 0; i < num_refs; i++) {
        time++;
        int page = refs[i];
        int index = find_page(frames, num_frames, page);

        if (index != -1) {
            // Página já em memória → atualiza tempo de uso
            frames[index].timestamp = time;
            log_event("Página já presente (hit). Atualizando timestamp.");
        } else {
            // Page Fault → encontra a menos recentemente usada
            int lru_index = -1, min_time = __INT_MAX__;
            for (int j = 0; j < num_frames; j++) {
                if (!frames[j].valid) { lru_index = j; break; }
                if (frames[j].timestamp < min_time) {
                    min_time = frames[j].timestamp;
                    lru_index = j;
                }
            }
            frames[lru_index].page = page;
            frames[lru_index].timestamp = time;
            frames[lru_index].valid = true;
            page_faults++;
            log_event("Page Fault (LRU) — substituindo página menos usada.");
        }

        print_frames(frames, num_frames, page);
    }

    printf("\n📊 Resultado LRU: %d page faults\n", page_faults);
    return page_faults;
}

// =============================================================
// MAIN
// =============================================================

int main(void) {
    int refs[] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3};
    int num_refs = sizeof(refs) / sizeof(refs[0]);
    int num_frames = 3;

    printf("============================================================\n");
    printf("   SIMULADOR DE SUBSTITUIÇÃO DE PÁGINAS (FIFO / LRU)\n");
    printf("============================================================\n");

    int fifo_faults = simulate_FIFO(refs, num_refs, num_frames);
    int lru_faults  = simulate_LRU(refs, num_refs, num_frames);

    printf("\n------------------------------------------------------------\n");
    printf("Resumo Final:\n");
    printf("  FIFO → %d page faults\n", fifo_faults);
    printf("  LRU  → %d page faults\n", lru_faults);
    printf("------------------------------------------------------------\n");

    if (lru_faults < fifo_faults)
        printf("✅ LRU teve melhor desempenho.\n");
    else if (fifo_faults < lru_faults)
        printf("✅ FIFO teve melhor desempenho.\n");
    else
        printf("⚖️  Ambos apresentaram o mesmo número de falhas.\n");

    printf("\nSimulação encerrada.\n");
    return 0;
}
