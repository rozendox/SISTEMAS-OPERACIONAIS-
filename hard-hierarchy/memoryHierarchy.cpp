#include <iostream>
#include <locale>
#include <codecvt>
#include <vector>
#include <cstdlib>
#include <cstdint>
#include <x86intrin.h>   // para __rdtsc (funciona em CPUs Intel/AMD com suporte a TSC)

// Função auxiliar para medir tempo em ciclos de CPU
inline uint64_t rdtsc() {
    return __rdtsc();
}

template<typename Func>
uint64_t measure(Func func, int iterations = 5) {
    uint64_t total = 0;
    for (int i = 0; i < iterations; i++) {
        uint64_t start = rdtsc();
        func();
        uint64_t end = rdtsc();
        total += (end - start);
    }
    return total / iterations;
}

int main() {
    // --- Simulação de diferentes níveis ---
    int reg = 42;                          // registrador
    std::vector<int> cache(10'000, 1);     // ~40 KB (cabe em cache L1/L2)
    std::vector<int> ram(50'000'000, 1);   // ~200 MB (força uso da RAM)

    // Medição
    auto reg_time = measure([&]() {
        int x = reg * 2;
    });

    auto cache_time = measure([&]() {
        long long sum = 0;
        for (int i = 0; i < cache.size(); i++)
            sum += cache[i];
    });

    auto ram_time = measure([&]() {
        long long sum = 0;
        for (int i = 0; i < ram.size(); i += 64)  // salto de 64 bytes (tamanho típico de linha de cache)
            sum += ram[i];
    });

    // Saída
    std::cout << "\n=== Medicao real de hierarquia de memoria (ciclos de CPU) ===\n\n";
    std::cout << "Nivel         | Descricao                         | Tempo MeSdio (ciclos)\n";
    std::cout << "-----------------------------------------------------------------\n";
    std::cout << "Registrador   | Variavel local (ultrarrapido)     | " << reg_time << "\n";
    std::cout << "Cache (L1/L2) | Array pequeno (~40KB)             | " << cache_time << "\n";
    std::cout << "RAM           | Array grande (~200MB)             | " << ram_time << "\n";

    std::cout << "\nObservacao:\n";
    std::cout << "- Registradores sao praticamente instantaneos.\n";
    std::cout << "- Cache L1/L2 atende rapidamente arrays pequenos.\n";
    std::cout << "- RAM tem latencia centenas de vezes maior.\n";
}
