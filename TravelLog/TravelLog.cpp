/*
 * log_viagens_win.c
 * Demonstração completa de manipulacao de arquivos via system calls no Windows (Win32 API).
 *
 * Operacoes principais:
 *  - CreateFileA()  -> criar/abrir arquivo
 *  - WriteFile()    -> escrever dados
 *  - ReadFile()     -> ler dados
 *  - CloseHandle()  -> fechar arquivo
 *
 */

#include <windows.h>
#include <stdio.h>
#include <string.h>

// Constantes
#define FILE_NAME "log_viagens_win.txt"
#define BUFFER_SIZE 256

// Estrutura para registrar dados de viagem
typedef struct {
    int quilometragem;
    float combustivel;
    const char *destino;
} Viagem;

// Função para exibir erro padrao do Windows
void mostrarErro(const char *mensagem) {
    DWORD codigo = GetLastError();
    printf("%s (Erro %lu)\n", mensagem, codigo);
}

// Função para salvar os dados no arquivo
int salvarViagem(const Viagem *v) {
    HANDLE hFile;
    DWORD bytesWritten;
    char buffer[BUFFER_SIZE];

    // Criar ou sobrescrever o arquivo
    hFile = CreateFileA(
        FILE_NAME,
        GENERIC_WRITE,
        0,
        NULL,
        CREATE_ALWAYS,
        FILE_ATTRIBUTE_NORMAL,
        NULL
    );

    if (hFile == INVALID_HANDLE_VALUE) {
        mostrarErro("Falha ao criar arquivo");
        return 0;
    }
    printf("Arquivo criado com sucesso.\n");

    // Preparar conteudo
    sprintf(buffer, "Quilometragem: %d\nCombustivel: %.2f\nDestino: %s\n",
            v->quilometragem, v->combustivel, v->destino);

    // Escrever no arquivo
    if (!WriteFile(hFile, buffer, (DWORD)strlen(buffer), &bytesWritten, NULL)) {
        mostrarErro("Falha ao escrever no arquivo");
        CloseHandle(hFile);
        return 0;
    }
    printf("Dados gravados no arquivo.\n");

    // Fechar
    CloseHandle(hFile);
    printf("Arquivo fechado com sucesso.\n");

    return 1;
}

// Função para ler e exibir conteudo do arquivo
int lerViagem() {
    HANDLE hFile;
    DWORD bytesRead;
    char buffer[BUFFER_SIZE];

    // Abrir arquivo para leitura
    hFile = CreateFileA(
        FILE_NAME,
        GENERIC_READ,
        0,
        NULL,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        NULL
    );

    if (hFile == INVALID_HANDLE_VALUE) {
        mostrarErro("Falha ao abrir arquivo para leitura");
        return 0;
    }
    printf("Lendo arquivo...\n");

    // Ler em blocos
    while (ReadFile(hFile, buffer, sizeof(buffer) - 1, &bytesRead, NULL) && bytesRead > 0) {
        buffer[bytesRead] = '\0';
        printf("%s", buffer);
    }

    // Fechar
    CloseHandle(hFile);
    printf("\nArquivo fechado com sucesso.\n");

    return 1;
}

int main() {
    // Registro de exemplo
    Viagem v = {250, 20.5f, "Sao Paulo"};

    // Salvar viagem
    if (!salvarViagem(&v)) {
        return 1;
    }

    // Ler viagem
    if (!lerViagem()) {
        return 1;
    }

    return 0;
}
