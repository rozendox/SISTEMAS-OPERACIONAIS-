"""
Módulo: hierarquia_memoria.py
-----------------------------
Demonstra o conceito de hierarquia de memória conforme discutido
no livro "Fundamentos de Sistemas Operacionais" (Silberschatz).

Níveis simulados:
- Registradores: acessos ultrarrápidos (variáveis locais).
- Cache: arrays pequenos que cabem em cache L1/L2.
- RAM: arrays grandes, dependem da memória principal.

Objetivo:
Comparar os tempos médios de acesso em cada nível e evidenciar
as diferenças de desempenho entre registradores, cache e RAM.
"""

import time
import numpy as np


class MemoryHierarchySimulator:
    """
    Simula o acesso em diferentes níveis de memória:
    - Registradores (variáveis locais rápidas)
    - Cache (arrays pequenos, cabem na cache L1/L2)
    - RAM (arrays grandes, dependem de memória principal)
    """
    def __init__(self):
        self.register = 42
        self.cache = np.arange(10**4)   # tamanho pequeno (simula cache)
        self.ram = np.arange(10**7)     # tamanho grande (simula RAM)

    def _measure_access(self, operation):
        """
        Mede o tempo médio de execução de uma operação (5 repetições).
        :param operation: função que simula o acesso.
        :return: tempo médio em segundos.
        """
        times = []
        for _ in range(5):
            start = time.perf_counter()
            operation()
            end = time.perf_counter()
            times.append(end - start)
        return sum(times) / len(times)

    def access_register(self):
        """Simula acesso a registradores (variáveis locais)."""
        return self._measure_access(lambda: self.register * 2)

    def access_cache(self):
        """Simula acesso a cache (array pequeno)."""
        return self._measure_access(lambda: np.sum(self.cache))

    def access_ram(self):
        """Simula acesso à RAM (array grande)."""
        return self._measure_access(lambda: np.sum(self.ram))


if __name__ == "__main__":
    sim = MemoryHierarchySimulator()

    print("\n=== Simulação: Hierarquia de Memória ===")
    print("Medindo tempos médios de acesso (5 execuções cada)\n")

    reg_time = sim.access_register()
    cache_time = sim.access_cache()
    ram_time = sim.access_ram()

    # saída organizada em forma de tabela
    print(f"{'Nível de Memória':<20} | {'Descrição':<35} | {'Tempo Médio'}")
    print("-"*75)
    print(f"{'Registrador':<20} | {'Variável local (ultrarrápido)':<35} | {reg_time:.8f}s")
    print(f"{'Cache':<20}       | {'Array pequeno (cache L1/L2)':<35} | {cache_time:.6f}s")
    print(f"{'RAM':<20}         | {'Array grande (memória principal)':<35} | {ram_time:.4f}s")

    print("\nObservação:")
    print("- Registradores são centenas de vezes mais rápidos que RAM.")
    print("- Cache atua como intermediária, reduzindo latência.")
    print("- Isso demonstra por que a hierarquia de memória é essencial.\n")
