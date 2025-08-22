"""
Módulo: hierarquia_memoria.py
-----------------------------
Este programa demonstra o conceito de hierarquia de memória,
conforme discutido no Capítulo 8 do livro "Fundamentos de Sistemas Operacionais".

Níveis simulados:
- Registradores: acessos ultrarrápidos (variáveis locais).
- Cache: arrays pequenos que cabem em cache L1/L2.
- RAM: arrays grandes, dependem da memória principal.

Objetivo: medir o tempo médio de acesso em cada nível e mostrar
por que a hierarquia de memória é necessária para equilibrar
custo e desempenho.
"""

import time
import numpy as np


class MemoryHierarchySimulator:
    """
    docstring for MemoryHierarchySimulator
    """

    def __init__(self):
        """
        Inicializa os dados simulando diferentes níveis de memória.
        """

    def _measure_access(self):
        pass

    def access_register(self):
        pass

    def access_cache(self):
        """Simula acesso a cache (array pequeno)."""
        pass

    def access_ram(self):
        """Simula acesso à RAM (array grande)."""
        pass


if __name__ == "__main__":
    sim = MemoryHierarchySimulator()