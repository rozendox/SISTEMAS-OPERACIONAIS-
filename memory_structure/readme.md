# Estrutura de Memória de um Processo

**Disciplina:** Organização e Arquitetura de Computadores  
**Capítulo:** 15 – Uso de Memória  
**Tema:** Estrutura de Memória de um Processo (TEXT, DATA, BSS, HEAP, STACK)  
**Autor:** Gabriel Rozendo  

---

## Objetivo

Compreender, de forma prática, como as variáveis e funções de um programa em C são **alocadas em diferentes regiões da memória** de um processo.  

O exercício demonstra, através de endereços reais de memória, a **separação entre os segmentos**:
- **TEXT** → código executável  
- **DATA** → variáveis globais inicializadas  
- **BSS** → variáveis globais não inicializadas  
- **HEAP** → alocação dinâmica (`malloc`)  
- **STACK** → variáveis locais e frames de função  

---

## Conceitos Reforçados

| Segmento | Descrição | Características |
|-----------|------------|----------------|
| **TEXT** | Contém o código executável do programa (funções, instruções). | Normalmente é **somente leitura** e pode ser **compartilhado** entre processos. |
| **DATA** | Armazena **variáveis globais e estáticas inicializadas**. | Conteúdo fixado em tempo de compilação. |
| **BSS** | Armazena **variáveis globais e estáticas não inicializadas**. | Inicializadas com zero em tempo de execução. |
| **HEAP** | Região de **alocação dinâmica** (via `malloc`, `calloc`, `realloc`). | Cresce **para cima** (endereços maiores). |
| **STACK** | Contém **variáveis locais** e **contextos de função**. | Cresce **para baixo** (endereços menores). |

---

## specificações Técnicas

- **Linguagem:** C (C99 ou superior)  
- **Ambiente:** Linux / Windows (com `gcc` ou MinGW)  
- **Bibliotecas utilizadas:**  
  - `<stdio.h>` – Entrada/saída padrão  
  - `<stdlib.h>` – Alocação dinâmica  
  - `<stdint.h>` – Tipos inteiros portáveis  


## Lógica do Programa

O programa:
1. Declara uma **variável global inicializada** (`DATA`).
2. Declara uma **variável global não inicializada** (`BSS`).
3. Aloca memória no **HEAP** com `malloc`.
4. Declara uma **variável local** no `main()` (alocada na **STACK**).
5. Chama uma **função simples** (`exemplo_funcao()`), localizada no **TEXT**.
6. Exibe o endereço de cada elemento com `printf("%p")`.
7. Explica o segmento correspondente e mostra um **mapa conceitual de memória**.

---

## Exemplo de Código (Resumo)

```c
int global_inicializada = 42;  // DATA
int global_nao_inicializada;   // BSS

void exemplo_funcao() {        // TEXT
    printf("Executando função no segmento TEXT.\n");
}

int main(void) {
    int variavel_local = 99;   // STACK
    int *heap_ptr = malloc(sizeof(int)); // HEAP
    *heap_ptr = 1234;

    printf("Função exemplo_funcao(): %p\n", exemplo_funcao);
    printf("Global inicializada:     %p\n", &global_inicializada);
    printf("Global não inicializada: %p\n", &global_nao_inicializada);
    printf("Variável local:          %p\n", &variavel_local);
    printf("Ponteiro (malloc):       %p\n", heap_ptr);

    free(heap_ptr);
}
```

---

## compilação e Execução

### Compilação manual
```bash
gcc src/estrutura_memoria.c -o estrutura_memoria
```

### Com Makefile
```bash
make run
```

---

## Exemplo de Saída

```
===========================================================
   MAPA DE MEMÓRIA DE UM PROCESSO (Visualização Didática)
===========================================================

 Endereços de variáveis e segmentos:

Função exemplo_funcao()        -> Endereço: 0x5555555547a9   | Segmento: TEXT
Variável global_inicializada   -> Endereço: 0x555555756018   | Segmento: DATA
Variável global_nao_inicializada -> Endereço: 0x55555575601c | Segmento: BSS
Ponteiro alocado (malloc)      -> Endereço: 0x55555576e2a0   | Segmento: HEAP
Variável local (main)          -> Endereço: 0x7fffffffdc3c   | Segmento: STACK

===========================================================
   OBSERVAÇÕES:
===========================================================
• TEXT: contém código executável (funções e instruções).
• DATA: armazena variáveis globais e estáticas inicializadas.
• BSS: contém variáveis globais e estáticas não inicializadas.
• HEAP: região de crescimento ascendente (malloc/free).
• STACK: região de crescimento descendente (frames de função).
===========================================================

Mapa conceitual (endereços podem variar):
-----------------------------------------------------------
|         STACK  ↑ (variáveis locais, frames)              |
|----------------------------------------------------------|
|         HEAP   ↑ (malloc, calloc, realloc)               |
|----------------------------------------------------------|
|         BSS / DATA (variáveis globais)                   |
|----------------------------------------------------------|
|         TEXT (código executável)                         |
-----------------------------------------------------------
```

---

## Explicação dos Endereços

- **Função (`TEXT`)**: aponta para o código executável carregado na memória.  
- **Globais (`DATA`, `BSS`)**: endereços próximos entre si.  
- **HEAP**: geralmente logo após os segmentos de dados.  
- **STACK**: localiza-se em endereços mais altos, decrescendo conforme o programa executa funções.  

---

## Observação sobre ASLR (Linux)

O sistema operacional aplica **Address Space Layout Randomization (ASLR)**, o que faz os endereços variarem a cada execução.  
Para desativar temporariamente (somente em laboratório):

```bash
sudo sysctl -w kernel.randomize_va_space=0
```

Para verificar o mapa real de memória de um processo em execução:

```bash
cat /proc/<PID>/maps
```

---

## Extensões Possíveis

- Incluir variáveis **estáticas locais** para demonstrar comportamento híbrido (entre DATA e BSS).  
- Comparar alocação em **C++ (`new`)** vs **C (`malloc`)**.  
- Plotar um **gráfico de layout de memória** via script externo (Python + Matplotlib).  
- Adicionar **funções recursivas** para observar o crescimento da pilha (STACK).  

---



