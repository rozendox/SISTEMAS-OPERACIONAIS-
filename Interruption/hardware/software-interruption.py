"""
Módulo: interrupcao_hardware_software.py
----------------------------------------
Este programa demonstra o conceito de interrupções de hardware e software
conforme discutido no Capítulo 1 do livro "Fundamentos de Sistemas Operacionais"
(Silberschatz, Galvin, Gagne).

- Interrupção de Hardware:
  Simulada por uma thread que dispara periodicamente mensagens, representando
  um temporizador ou dispositivo de entrada/saída.

- Interrupção de Software:
  Simulada pela captura de sinais do sistema operacional (SIGINT - Ctrl+C),
  que alteram o fluxo do programa.

Objetivo: ilustrar como o fluxo normal de execução é interrompido
para lidar com eventos externos (hardware) ou internos (software).
"""

import logging

logging.basicConfig(level=logging.INFO, format="%(asctime)s [%(levelname)s] %(message)s")


class HardwareInterruptionSimulator:
    """
    docstring for HardwareInterruptionSimulator
    """

    def __init__(self):
        """
        Inicializa o simulador de interrupções.
        """
        pass

    def start_thread(self):
        logging.info("Inicializando")
        pass

    def simulate_interruption(self):
        pass

    def stop_thread(self):
        pass


class SoftwareInterruptSimulator:
    """
    docstring for SoftwareInterruptSimulator
    """

    def __init__(self):
        """Configura o manipulador para o sinal SIGINT (Ctrl+C)."""

    def _handle_signal(self, signum, frame):
        """Função chamada automaticamente quando um sinal é capturado."""
        logging.error(f"[SOFTWARE INTERRUPT] Capturado sinal {signum}. Fluxo alterado.")


if __name__ == "__main__":
    sim = HardwareInterruptionSimulator()
    sim.start_thread()
