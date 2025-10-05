# Simulador de Substituição de Páginas – FIFO e LRU

**Disciplina:** Organização e Arquitetura de Computadores  
**Capítulo:** 17 – Paginação em Disco  
**Tema:** Substituição de Páginas (FIFO e LRU)  
**Autor:** Gabriel Rozendo

---

## Objetivo

Simular os algoritmos de substituição de páginas **FIFO (First-In, First-Out)** e **LRU (Least Recently Used)**, demonstrando como cada política impacta o número de *page faults* e o desempenho do sistema de paginação em disco.

O programa apresenta logs detalhados e exibe, passo a passo, o estado dos quadros de memória a cada referência de página.

---

## Conceitos Fundamentais

| Conceito           | Descrição                                                                     |
|--------------------|-------------------------------------------------------------------------------|
| **Página**         | Unidade lógica de alocação de memória virtual.                                |
| **Quadro (Frame)** | Unidade física correspondente na memória principal.                           |
| **Page Fault**     | Ocorre quando uma página referenciada não está presente em memória.           |
| **FIFO**           | Substitui a página mais antiga carregada.                                     |
| **LRU**            | Substitui a página menos recentemente usada (baseado no tempo lógico de uso). |

---

## Especificações Técnicas

- **Linguagem:** C (C11 ou superior)
- **Modo:** Console
- **Entrada fixa:** sequência de referências a páginas
- **Número de quadros:** configurável
- **Flags de controle:**
    - `ENABLE_LOGS` → ativa logs detalhados durante a simulação
- **Estruturas utilizadas:**
    - `struct Frame` → Representa cada quadro na memória (com página, timestamp e validade).

---


## Lógica do Programa

1. Define uma **sequência de referências a páginas** (ex.: `7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3`).
2. Define o **número de quadros disponíveis** (ex.: `3`).
3. Executa duas simulações:
    - **FIFO:** substitui a página mais antiga.
    - **LRU:** substitui a menos recentemente usada.
4. A cada referência:
    - Verifica se a página está presente.
    - Em caso negativo, ocorre um **Page Fault** e uma substituição.
5. Conta o número total de falhas e exibe comparativo final.

---

## **Exemplo de Código (Resumo)**

```c
int refs[] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3};
int num_frames = 3;

int fifo_faults = simulate_FIFO(refs, num_refs, num_frames);
int lru_faults  = simulate_LRU(refs, num_refs, num_frames);

printf("FIFO → %d page faults\n", fifo_faults);
printf("LRU  → %d page faults\n", lru_faults);
```

---

## Compilação e Execução

### Compilar
```bash
gcc src/simulador_paginas.c -o simulador_paginas
```

### Executar
```bash
./simulador_paginas
```

---

## Exemplo de Saída

```
============================================================
   SIMULADOR DE SUBSTITUIÇÃO DE PÁGINAS (FIFO / LRU)
============================================================

[LOG] Iniciando simulação FIFO...
Página referenciada: 7 -> [7 - -]
Página referenciada: 0 -> [7 0 -]
Página referenciada: 1 -> [7 0 1]
Página referenciada: 2 -> [2 0 1]   <-- Page Fault
Página referenciada: 0 -> [2 0 1]
Página referenciada: 3 -> [2 3 1]   <-- Page Fault
Página referenciada: 0 -> [2 3 0]   <-- Page Fault
Página referenciada: 4 -> [4 3 0]   <-- Page Fault
...
Resultado FIFO: 9 page faults

[LOG] Iniciando simulação LRU...
Página referenciada: 7 -> [7 - -]
Página referenciada: 0 -> [7 0 -]
Página referenciada: 1 -> [7 0 1]
Página referenciada: 2 -> [2 0 1]   <-- substitui a menos usada
Página referenciada: 0 -> [2 0 1]
Página referenciada: 3 -> [2 3 1]
Página referenciada: 0 -> [2 3 0]
Página referenciada: 4 -> [4 3 0]
...
Resultado LRU: 8 page faults

------------------------------------------------------------
Resumo Final:
  FIFO → 9 page faults
  LRU  → 8 page faults
-----------------------------------------------------------
LRU teve melhor desempenho.
```

---

## Comparativo Teórico

| Estratégia | Vantagem                                               | Desvantagem                                                              |
|------------|--------------------------------------------------------|--------------------------------------------------------------------------|
| **FIFO**   | Simples de implementar, custo constante.               | Pode substituir páginas ainda frequentemente usadas.                     |
| **LRU**    | Mais eficiente em cenários reais, reduz *page faults*. | Requer rastrear o uso histórico das páginas (maior custo computacional). |

---

## Conceitos Reforçados

- **Políticas de substituição** definem qual página será removida quando a memória estiver cheia.
- **Desempenho** é medido pelo número de *page faults*.
- **LRU** tenta se aproximar do comportamento ótimo teórico.
- **FIFO** é mais simples, mas pode gerar o fenômeno de **anomalia de Belady**, onde mais quadros não necessariamente reduzem falhas.

---

## Extensões Sugeridas

- Implementar **Optimal Page Replacement** (ótimo teórico).
- Adicionar **visualização gráfica** da linha do tempo de substituições.
- Simular **anomalia de Belady** com diferentes quantidades de quadros.
- Registrar resultados em arquivo `.csv` para análise estatística.

---
