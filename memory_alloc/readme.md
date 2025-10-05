# Simulador de Estratégias de Alocação de Memória (First Fit e Best Fit)

**Disciplina:** Organização e Arquitetura de Computadores  
**Capítulo:** 16 – Alocação de Memória  
**Tema:** Estratégias de Alocação e Fragmentação  
**Autor:** Gabriel Rozendo

---

## Objetivo

Simular os algoritmos de alocação de memória **First Fit** e **Best Fit**, demonstrando como diferentes estratégias influenciam a **fragmentação interna e externa**.

O programa implementa uma **simulação realista** de gerenciamento de buracos de memória, com estrutura de dados dinâmica, logs detalhados e arquitetura modular.

---

## Conceitos Fundamentais

| Conceito                 | Descrição                                                                                                      |
|--------------------------|----------------------------------------------------------------------------------------------------------------|
| **First Fit**            | Aloca o primeiro buraco que tenha espaço suficiente para o bloco.                                              |
| **Best Fit**             | Escolhe o **menor buraco possível** que acomode o bloco, minimizando sobras.                                   |
| **Fragmentação Interna** | Espaço desperdiçado *dentro* de um bloco alocado (diferença entre o tamanho solicitado e o tamanho do buraco). |
| **Fragmentação Externa** | Espaço desperdiçado *fora* dos blocos, devido à dispersão dos buracos não utilizados.                          |

---

## Especificações Técnicas

- **Linguagem:** C (C11 ou superior)
- **Arquitetura:** Modular e orientada a funções puras
- **Estruturas utilizadas:**
    - `struct Hole` → Representa um buraco de memória disponível
    - `struct Allocation` → Representa um bloco de alocação ativo
- **Modo de Execução:** Console
- **Flag de Debug:** `DEBUG_MODE` (ativa logs detalhados)

---

## Estrutura do Projeto

```
alocacao_memoria/
├── src/
│   └── simulador_alocacao.c
├── Makefile
└── README.md
```

---

## Lógica do Programa

1. Cria uma lista encadeada representando os **buracos disponíveis na memória**.
2. Recebe pedidos de alocação (tamanho de blocos).
3. Executa **duas simulações independentes**:
    - **First Fit** → Aloca no primeiro buraco que couber.
    - **Best Fit** → Aloca no buraco mais justo possível.
4. Atualiza os tamanhos dos buracos após cada alocação.
5. Exibe o estado da memória e o impacto das alocações.

---

## Exemplo de Código (Resumo)

```c
const int initial_holes[] = {100, 500, 200, 300, 600};
const int requests[] = {212, 417, 112, 426};

printf("🔹 Estratégia: FIRST FIT\n");
Allocation *first_allocs = allocate_first_fit(holes, requests, num_requests);
print_memory_state(holes, first_allocs);

reset_holes(&holes, initial_holes, num_holes);

printf("🔹 Estratégia: BEST FIT\n");
Allocation *best_allocs = allocate_best_fit(holes, requests, num_requests);
print_memory_state(holes, best_allocs);
```

---

## Compilação e Execução

### Compilar manualmente
```bash
gcc src/simulador_alocacao.c -o simulador_alocacao
```

### Executar
```bash
./alloc_sml
```

---

## Exemplo de Saída

```
============================================================
   SIMULADOR DE ALOCAÇÃO DE MEMÓRIA (FIRST FIT / BEST FIT)
============================================================

Estratégia: FIRST FIT
[LOG] Iniciando alocação com algoritmo FIRST FIT.
[LOG] Bloco alocado (FIRST FIT). Atualizando buraco.
[LOG] Bloco alocado (FIRST FIT). Atualizando buraco.
Não foi possível alocar o bloco #4 (426 unidades).

Estado atual da memória:
----------------------------------------------------
Buracos disponíveis:
  -> Buraco #1: 100 unidades livres
  -> Buraco #2: 71 unidades livres
  -> Buraco #3: 88 unidades livres
  -> Buraco #4: 300 unidades livres
  -> Buraco #5: 600 unidades livres

Blocos alocados:
  -> Alocação #1: 212 unidades em Buraco #2
  -> Alocação #2: 417 unidades em Buraco #5
  -> Alocação #3: 112 unidades em Buraco #3
----------------------------------------------------

Estratégia: BEST FIT
[LOG] Iniciando alocação com algoritmo BEST FIT.
[LOG] Bloco alocado (BEST FIT). Buraco ajustado.
[LOG] Bloco alocado (BEST FIT). Buraco ajustado.
 Falha na alocação: bloco #4 (426 unidades) não coube em nenhum buraco.

 Estado atual da memória:
----------------------------------------------------
Buracos disponíveis:
  -> Buraco #1: 100 unidades livres
  -> Buraco #2: 83 unidades livres
  -> Buraco #3: 88 unidades livres
  -> Buraco #4: 300 unidades livres
  -> Buraco #5: 183 unidades livres

Blocos alocados:
  -> Alocação #1: 212 unidades em Buraco #2
  -> Alocação #2: 417 unidades em Buraco #5
  -> Alocação #3: 112 unidades em Buraco #3
----------------------------------------------------
Simulação encerrada com sucesso.
```

---

## análise Comparativa

| Estratégia    | Vantagem                                  | Desvantagem                                                                                           |
|---------------|-------------------------------------------|-------------------------------------------------------------------------------------------------------|
| **First Fit** | Simples e rápido; percorre menos buracos. | Gera mais **fragmentação externa** a longo prazo.                                                     |
| **Best Fit**  | Reduz o desperdício imediato.             | Mais **custoso** (precisa percorrer toda a lista); tende a aumentar fragmentação externa com o tempo. |

---

## Conceitos Reforçados

- **Fragmentação interna:** espaço desperdiçado dentro de blocos alocados.
- **Fragmentação externa:** buracos pequenos demais que permanecem inativos.
- **Importância da estratégia:** a escolha do algoritmo afeta desempenho e utilização de memória.

---

## Extensões Sugeridas

- Implementar **Worst Fit** (usa o maior buraco possível).
- Adicionar **coalescência** (junção automática de buracos contíguos).
- Criar **visualização gráfica** do mapa de memória.
- Incluir **métricas de eficiência** (% de fragmentação total).

---
