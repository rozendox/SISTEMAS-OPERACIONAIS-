"""
Módulo: io_sync_async.py
------------------------
Demonstra a diferença entre Entrada/Saída (E/S) síncrona e assíncrona.

- E/S Síncrona:
  Cada tarefa espera a anterior terminar (bloqueio).
  Tempo total = soma dos tempos de todas as tarefas.

- E/S Assíncrona:
  Todas as tarefas são iniciadas em paralelo.
  Tempo total ≈ tempo da tarefa mais longa (não soma os atrasos).

Objetivo:
Mostrar de forma clara e comparativa como operações assíncronas
são mais eficientes em cenários de múltiplas operações de I/O.
"""

import asyncio
import time
import logging

# Configuração do logger
logging.basicConfig(
    level=logging.INFO,
    format="%(asctime)s [%(levelname)s] %(message)s",
    datefmt="%H:%M:%S"
)


class IOSimulator:
    """Simulador de operações de Entrada/Saída (I/O)."""

    def __init__(self, delay: int = 2):
        """
        Inicializa o simulador.
        :param delay: tempo (em segundos) que cada operação de I/O leva.
        """
        self.delay = delay

    def sync_io(self, task_id: int):
        """Simula I/O síncrona (bloqueante)."""
        logging.info(f"[SYNC] → Tarefa {task_id} iniciada")
        time.sleep(self.delay)
        logging.info(f"[SYNC] ← Tarefa {task_id} concluída")

    async def async_io(self, task_id: int):
        """Simula I/O assíncrona (não bloqueante)."""
        logging.info(f"[ASYNC] → Tarefa {task_id} iniciada")
        for i in range(self.delay):  # progresso por segundo
            await asyncio.sleep(1)
            logging.info(f"[ASYNC] ... Tarefa {task_id} em progresso ({i+1}/{self.delay}s)")
        logging.info(f"[ASYNC] ← Tarefa {task_id} concluída")


async def run_async_tasks(io: IOSimulator, num_tasks: int = 3):
    """Executa várias tarefas assíncronas em paralelo."""
    await asyncio.gather(*(io.async_io(i) for i in range(num_tasks)))


if __name__ == "__main__":
    io = IOSimulator(delay=3)  # cada tarefa demora 3 segundos
    num_tasks = 3

    logging.info("=== Demonstração de E/S Síncrona ===")
    start = time.perf_counter()
    for i in range(num_tasks):
        io.sync_io(i)
    end = time.perf_counter()
    sync_time = end - start
    logging.info(f"Tempo total (síncrono): {sync_time:.2f}s\n")

    logging.info("=== Demonstração de E/S Assíncrona ===")
    start = time.perf_counter()
    asyncio.run(run_async_tasks(io, num_tasks=num_tasks))
    end = time.perf_counter()
    async_time = end - start
    logging.info(f"Tempo total (assíncrono): {async_time:.2f}s\n")

    # --- Comparação final ---
    logging.info("=== Comparação Final ===")
    logging.info(f"Número de tarefas      : {num_tasks}")
    logging.info(f"Tempo de cada tarefa   : {io.delay}s")
    logging.info("-" * 55)
    logging.info(f"Execução SÍNCRONA      : {sync_time:.2f}s (tarefas em SEQUÊNCIA)")
    logging.info(f"Execução ASSÍNCRONA    : {async_time:.2f}s (tarefas em PARALELO)")
    logging.info("-" * 55)
    ganho = sync_time / async_time if async_time > 0 else float("inf")
    logging.info(f"💡 Ganho de desempenho : ~{ganho:.1f}x mais rápido com assíncrono\n")
