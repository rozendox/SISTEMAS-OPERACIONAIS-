# Laboratório de Fundamentos de Sistemas Operacionais

Este repositório reúne miniaplicações utilizadas para demonstrar conceitos
clássicos de Sistemas Operacionais em aulas práticas. Os exemplos foram
escritos em Python e C/C++ e cobrem desde interrupções até hierarquia e
gerenciamento de memória.

## 📁 Organização do repositório

| Diretório / arquivo                          | Linguagem | Conceito principal                                                                 |
| -------------------------------------------- | --------- | ---------------------------------------------------------------------------------- |
| `Interruption/software-interruption.py`      | Python    | Simulação de interrupções de hardware (thread temporizada) e software (sinal SIGINT). |
| `sync-async/io-sync-async.py`                | Python    | Comparação entre E/S síncrona sequencial e E/S assíncrona com `asyncio`.          |
| `hard-hierarchy/memory-hierarchy.py`         | Python    | Medição comparativa de tempos de acesso a registradores, cache e RAM com NumPy.   |
| `hard-hierarchy/memoryHierarchy.cpp`         | C++       | Benchmark de hierarquia de memória usando contagem de ciclos da CPU.              |
| `memory_alloc/alloc_sml.cpp`                 | C         | Estratégias de alocação First Fit e Best Fit com controle de fragmentação.        |
| `memory_structure/memory_structure.cpp`      | C         | Visualização dos segmentos TEXT, DATA, BSS, HEAP e STACK em um processo.          |
| `mmu/mmu_simulator.cpp`                      | C         | Tradução de endereços lógicos via tabela de páginas e detecção de page faults.    |
| `page_replacement/page_replacement.cpp`      | C         | Simulação comparativa dos algoritmos FIFO e LRU de substituição de páginas.       |
| `TravelLog/TravelLog.cpp`                    | C (Win32) | Registro de viagens usando chamadas de sistema da API Windows (CreateFile, etc.). |

> Há binários `.exe` gerados previamente para algumas atividades. Recomenda-se
> recompilar os programas no seu ambiente-alvo para garantir compatibilidade.

## ✅ Pré-requisitos

- **Python 3.9+** com `pip` e, para a hierarquia de memória em Python, a
  biblioteca **NumPy** instalada (`pip install numpy`).
- **Compilador C/C++ moderno** (`gcc`/`g++` ou equivalente) com suporte a C11 e
  C++17.
- Para `TravelLog/TravelLog.cpp`, um ambiente Windows com o **Visual Studio
  Build Tools** ou `cl.exe`, pois o código depende da API Win32.

## ▶️ Executando os exemplos em Python

1. (Opcional) Crie e ative um ambiente virtual.
2. Instale as dependências necessárias:

   ```bash
   pip install numpy
   ```

3. Execute cada módulo diretamente com o Python:

   ```bash
   # Interrupções de hardware e software
   python3 Interruption/software-interruption.py

   # E/S síncrona versus assíncrona
   python3 sync-async/io-sync-async.py

   # Hierarquia de memória (requer NumPy)
   python3 hard-hierarchy/memory-hierarchy.py
   ```

   - O simulador de interrupções inicia uma thread que dispara mensagens a cada
     poucos segundos e encerra o programa ao receber `Ctrl+C` (SIGINT).
   - O exemplo de E/S mede o tempo total de tarefas executadas sequencialmente e
     com `asyncio`, exibindo a diferença de duração.
   - A simulação de hierarquia de memória imprime uma tabela com os tempos médios
     para acessar registradores, estruturas que cabem em cache e vetores grandes
     na RAM.

## 🛠️ Compilando os exemplos em C/C++

Os códigos em C/C++ podem ser compilados com `g++` (ou `gcc` quando o arquivo não
usa recursos específicos de C++). Cada diretório pode manter seu executável de
preferência; os comandos abaixo geram binários na própria pasta do módulo:

```bash
# Estratégias de alocação de memória (First Fit / Best Fit)
g++ -std=c11 memory_alloc/alloc_sml.cpp -o memory_alloc/alloc_sml

# Estrutura de memória de um processo
g++ -std=c11 memory_structure/memory_structure.cpp -o memory_structure/memory_structure

# Simulador simplificado de MMU
g++ -std=c11 mmu/mmu_simulator.cpp -o mmu/mmu_simulator

# Substituição de páginas (FIFO x LRU)
g++ -std=c11 page_replacement/page_replacement.cpp -o page_replacement/page_replacement

# Benchmark de hierarquia de memória em C++ (requer CPU x86 com rdtsc)
g++ -std=c++17 hard-hierarchy/memoryHierarchy.cpp -o hard-hierarchy/memory_hierarchy_benchmark
```

Após a compilação, execute o binário correspondente. Cada simulador apresenta
menus ou relatórios em modo texto descrevendo o fluxo do algoritmo:

- `memory_alloc/alloc_sml` lista os buracos restantes e os blocos alocados após
  aplicar First Fit e Best Fit.
- `memory_structure/memory_structure` exibe os endereços das variáveis em cada
  segmento (TEXT, DATA, BSS, HEAP, STACK) e um mapa conceitual do layout.
- `mmu/mmu_simulator` permite digitar endereços lógicos, mostra a tradução e
  sinaliza page faults para páginas não mapeadas.
- `page_replacement/page_replacement` compara o número de falhas de página entre
  FIFO e LRU e mostra o conteúdo dos quadros a cada referência.
- `hard-hierarchy/memory_hierarchy_benchmark` imprime os ciclos médios de CPU
  gastos ao acessar dados que simulam registradores, cache e RAM.

### Observações específicas

- Os programas fornecidos usam `stdio.h`/`iostream` e não dependem de bibliotecas
  externas além da padrão. Ajuste as flags do compilador caso esteja usando um
  toolchain diferente.
- `hard-hierarchy/memoryHierarchy.cpp` utiliza `__rdtsc`; o executável deve ser
  rodado em um processador x86 com suporte a TSC e permissões adequadas.
- `TravelLog/TravelLog.cpp` demonstra chamadas de sistema do Windows (`CreateFile`,
  `WriteFile`, `ReadFile`, `CloseHandle`). Para compilar no Windows com MSVC:

  ```powershell
  cl /EHsc TravelLog\TravelLog.cpp
  .\TravelLog.exe
  ```

  Ele cria o arquivo `log_viagens_win.txt`, grava dados de uma viagem e exibe o
  conteúdo lido em seguida.

## 📚 Referências sugeridas

As atividades foram inspiradas no livro **"Fundamentos de Sistemas Operacionais"**
(Silberschatz, Galvin e Gagne). Consulte os capítulos correspondentes para
aprofundar cada tópico:

- Interrupções e estrutura geral de um sistema operacional.
- Entrada/Saída síncrona e assíncrona.
- Hierarquia de memória e otimizações de cache.
- Gerência de memória: alocação, paginação e substituição de páginas.

## 🤝 Contribuições

Sugestões de melhorias, correções de bugs ou novos experimentos são bem-vindos.
Abra uma issue ou envie um pull request descrevendo o que foi alterado.
