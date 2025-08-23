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
  Simulada pela captura de sinais do sistema operacional (SIGINT - Ctrl+C).
  Ao ser capturado, o sinal encerra o programa de forma controlada,
  após registrar a interrupção e parar o simulador de hardware.

Objetivo:
Mostrar como o fluxo normal de execução pode ser interrompido
para lidar com eventos externos (hardware) ou internos (software).
"""

import signal
import time
import threading
import logging

# Configuração do logger para simular mensagens de sistema operacional
logging.basicConfig(level=logging.INFO, format="%(asctime)s [%(levelname)s] %(message)s")


class HardwareInterruptSimulator:
    """
    Classe que simula uma interrupção de hardware usando threads.
    Exemplo: um temporizador que dispara periodicamente.
    """

    def __init__(self, interval: int = 3):
        """
        Inicializa o simulador de interrupções.
        :param interval: intervalo em segundos entre cada interrupção.
        """
        self.interval = interval
        self.running = True
        self.thread = threading.Thread(target=self._simulate_interrupt, daemon=True)

    def start(self):
        """Inicia a thread que dispara interrupções de hardware."""
        logging.info("Iniciando simulador de interrupção de hardware...")
        self.thread.start()

    def _simulate_interrupt(self):
        """Método interno: gera interrupções a cada intervalo definido."""
        while self.running:
            time.sleep(self.interval)
            logging.warning("[HARDWARE INTERRUPT] Temporizador disparado!")

    def stop(self):
        """Interrompe a simulação de hardware interrupt."""
        self.running = False


class SoftwareInterruptSimulator:
    """
    Classe que simula uma interrupção de software via sinais do SO.
    Ao capturar Ctrl+C (SIGINT), interrompe o hardware e encerra o sistema.
    """

    def __init__(self, hardware: HardwareInterruptSimulator):
        """
        Configura o manipulador para o sinal SIGINT (Ctrl+C).
        :param hardware: instância do simulador de hardware para ser encerrada.
        """
        self.hardware = hardware
        signal.signal(signal.SIGINT, self._handle_signal)

    def _handle_signal(self, signum, frame):
        """
        Manipulador do sinal SIGINT.
        Interrompe o hardware e encerra o programa.
        """
        logging.error(f"[SOFTWARE INTERRUPT] Capturado sinal {signum}. Encerrando sistema...")
        self.hardware.stop()
        raise SystemExit


if __name__ == "__main__":
    # Inicializa simuladores
    hw = HardwareInterruptSimulator(interval=5)
    sw = SoftwareInterruptSimulator(hw)

    # Inicia o simulador de hardware
    hw.start()

    # Loop principal (tarefa de usuário)
    while True:
        logging.info("Executando tarefa principal...")
        time.sleep(2)
