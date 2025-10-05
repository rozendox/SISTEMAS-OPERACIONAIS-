O programa visa reforçar a compreensão sobre:

O processo de mapeamento lógico–físico;

A organização de memória paginada;

O tratamento de endereços inválidos e páginas ausentes na memória principal.

🧩 Conceitos Reforçados
Conceito	Descrição
Endereço Lógico (VA)	Endereço gerado pela CPU, usado pelos processos.
Endereço Físico (PA)	Endereço real na memória RAM, obtido após tradução pela MMU.
Página (Page)	Unidade de divisão lógica do espaço de endereçamento.
Quadro (Frame)	Unidade de divisão física da memória.
Tabela de Páginas	Estrutura que relaciona páginas lógicas com quadros físicos.
Page Fault	Falha de página — ocorre quando uma página lógica não está carregada na memória física.
⚙️ Especificações Técnicas

Linguagem: C (C99+)

Tamanho da página: 1 KB (1024 bytes)

Número de páginas: 8

Tabela de páginas:

int page_table[8] = {2, -1, 5, 0, -1, 3, -1, 1};


Onde -1 indica uma página não mapeada (ocorrência de page fault).

🧮 Cálculo do Endereço Físico

A tradução é realizada pela seguinte fórmula:

Endere
c
¸
o F
ı
ˊ
sico (PA)
=
(
Quadro F
ı
ˊ
sico
)
×
PAGE_SIZE
+
Deslocamento
Endere
c
¸
​

o F
ı
ˊ
sico (PA)=(Quadro F
ı
ˊ
sico)×PAGE_SIZE+Deslocamento

Sendo:

Quadro Físico = page_table[número_página]

Deslocamento = VA % PAGE_SIZE

Número da Página = VA / PAGE_SIZE
```
📁 Estrutura do Projeto
mmu_simulator/
├── src/
│   └── mmu_simulator.c
├── Makefile
└── README.md
```

Execute o programa no terminal:

./mmu_simulator


Saída esperada (exemplo interativo):
```
=============================================
Simulador Simplificado de MMU (Memory Unit)
=============================================

Tabela de Páginas (Page Table)
-------------------------------
Página Lógica | Quadro Físico
-------------------------------
            0 |       2
            1 |   (não mapeada)
            2 |       5
            3 |       0
            4 |   (não mapeada)
            5 |       3
            6 |   (não mapeada)
            7 |       1
-------------------------------

Digite um endereço lógico em decimal (ou -1 para sair): 2050

--- Tradução de Endereço ---
Endereço lógico (VA): 2050
Número da página:     2
Deslocamento:         2
Quadro físico (frame): 5
Endereço físico (PA): 5122
-----------------------------
Tradução bem-sucedida: Endereço físico = 5122
```

-Tratamento de Page Fault

Caso a página não esteja mapeada na tabela, o sistema informará a falha:
```
Digite um endereço lógico em decimal (ou -1 para sair): 1500
-Page Fault: página lógica 1 não está mapeada.
-Não foi possível traduzir o endereço.
```

- explicação do Processo Interno
```
O usuário fornece um endereço lógico (em decimal).

O programa divide o endereço em:

Número da página (page_num)

Deslocamento (offset)

Consulta a tabela page_table[]:

Se o valor for -1 → Page Fault

Caso contrário, calcula o endereço físico.

Exibe logs detalhados de cada etapa da tradução.

```
Funções Implementadas
```
Função	Descrição
is_valid_page()	        -Valida se o número da página está dentro do intervalo permitido.
translate_address()	-Realiza a tradução VA → PA e exibe logs detalhados.
print_page_table()	-Mostra o estado completo da tabela de páginas.
main()	                -Gerencia o fluxo de entrada, saída e controle do simulador.
```
Possíveis Extensões (para trabalhos mais avançados)
```
Implementar alocação dinâmica de páginas.
Adicionar tratamento de substituição de páginas (FIFO, LRU).
Simular acessos de leitura/escrita com proteção de páginas.
Integrar logs em arquivo externo (.log).
Usar threads para simular acessos concorrentes à MMU.
```
Referências

```
TANENBAUM, Andrew S.; AUSTIN, Todd. Organização Estruturada de Computadores. 6ª ed. Pearson, 2013.
STALLINGS, William. Arquitetura e Organização de Computadores. 10ª ed. Pearson, 2021.
MACHADO, Ricardo. Sistemas Operacionais: Conceitos e Mecanismos Fundamentais. Elsevier, 2017.
```