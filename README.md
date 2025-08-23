# Fundamentos de Sistemas Operacionais - Atividades Práticas

Este repositório contém três atividades práticas baseadas no livro 
**Fundamentos de Sistemas Operacionais (Silberschatz, Galvin, Gagne, 9ª Ed.)**.

As atividades demonstram:

1. **Interrupções de Hardware/Software**  
2. **E/S Síncrona vs. Assíncrona**  
3. **Hierarquia de Memória**

---

## 🚀 Pré-requisitos

- Python **3.9+** instalado  
- `pip` atualizado  
- Ambiente virtual configurado (recomendado)

---

## ⚙️ Configuração do Ambiente

### 1. Criar ambiente virtual

#### Windows (PowerShell):
```powershell



























python -m venv venv
.\venv\Scripts\activate
```
Linux/macOS (bash/zsh):
bash
```
python3 -m venv venv
source venv/bin/activate
```

2. Instalar dependências
bash
```
pip install -r requirements.txt
```
📂 Estrutura de Arquivos
bash

```
├── interrupcao_hardware_software.py   # Subatividade 1
├── io_sincrona_assincrona.py          # Subatividade 2
├── hierarquia_memoria.py              # Subatividade 3
├── requirements.txt
└── README.md
```
▶️ Execução dos Exemplos
1. Interrupções de Hardware/Software
bash
```
python interrupcao_hardware_software.py
```
O programa executa uma tarefa principal.

A cada 5s, ocorre uma "interrupção de hardware" simulada (temporizador).

Pressione Ctrl+C para gerar uma interrupção de software (SIGINT).

2. E/S Síncrona vs. Assíncrona
bash
```
python io_sincrona_assincrona.py
```
Executa três tarefas de I/O:

Modo síncrono → tarefas em sequência (tempo total ≈ 6s).

Modo assíncrono → tarefas em paralelo (tempo total ≈ 2s).

3. Hierarquia de Memória
bash
```
python hierarquia_memoria.py
```
Mede tempos de acesso simulando diferentes níveis:

Registrador (variável local, ultrarrápido).

Cache (array pequeno).

RAM (array grande, acesso mais lento).

Saída típica:

yaml
```
Tempo médio acesso registrador: 0.00000050s
Tempo médio acesso cache:       0.000800s
Tempo médio acesso RAM:         0.040000s
```
🧹 Encerrando o Ambiente Virtual
Windows:
powershell
```
deactivate
```
Linux/macOS:
```
deactivate
```
