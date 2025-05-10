#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <cmath>
#include <limits>

std::mutex mtx;
int melhor_soma = std::numeric_limits<int>::min();
std::vector<int> melhor_combinacao;
int alvo;

// Função para processar um conjunto de subconjuntos com base no bitmap
void processa_subconjuntos(const std::vector<int>& vetor, int inicio, int fim) {
    int n = vetor.size();
    int melhor_local = std::numeric_limits<int>::min();
    std::vector<int> melhor_local_combinacao;

    // Cada thread processa uma faixa de subconjuntos (representados por bits)
    for (int mask = inicio; mask < fim; ++mask) {
        int soma_atual = 0;
        std::vector<int> combinacao_atual;

        // Gera o subconjunto baseado nos bits da máscara
        for (int i = 0; i < n; ++i) {
            if (mask & (1 << i)) { // Se o bit estiver ativado, adiciona o número
                soma_atual += vetor[i];
                combinacao_atual.push_back(vetor[i]);
            }
        }

        // Atualiza a melhor soma localmente
        if (std::abs(alvo - soma_atual) < std::abs(alvo - melhor_local)) {
            melhor_local = soma_atual;
            melhor_local_combinacao = combinacao_atual;
        }
    }

    // Atualiza a melhor soma global com mutex
    std::lock_guard<std::mutex> lock(mtx);
    if (std::abs(alvo - melhor_local) < std::abs(alvo - melhor_soma)) {
        melhor_soma = melhor_local;
        melhor_combinacao = melhor_local_combinacao;
    }
}

int main() {
    // Vetor de números e alvo desejado
    std::vector<int> vetor = {3,
1,
4,
1,
5,
3,
2,
5,
5,
3,
2,
6,
7,
5,
8,
9,
6,
4,
7,
2,
5,
8,
3,
4,
5,
3,
1,
4,
1,
5,
3};
    alvo = 400;

    int total_subconjuntos = 1 << vetor.size(); // 2^n subconjuntos possíveis
    int num_threads = 8;
    int chunk = total_subconjuntos / num_threads;

    system("pause");

    // Criando threads
    std::vector<std::thread> threads;
    for (int i = 0; i < num_threads; i++) {
        int inicio = i * chunk;
        int fim = (i == num_threads - 1) ? total_subconjuntos : (i + 1) * chunk;
        threads.emplace_back(processa_subconjuntos, std::ref(vetor), inicio, fim);
    }

    // Aguarda todas as threads finalizarem
    for (auto& t : threads) {
        t.join();
    }

    // Exibe os resultados
    std::cout << "Soma mais próxima de " << alvo << " encontrada: " << melhor_soma << std::endl;
    std::cout << "Números usados: ";
    for (int num : melhor_combinacao) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}
