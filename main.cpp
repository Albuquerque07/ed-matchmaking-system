#include <iostream>
#include <string>
#include <chrono>
#include "Player.hpp"
#include "Matchmaking.hpp"

using namespace std;

int main() {
    Matchmaking match;
    int n = 0;
    Player* grupo = nullptr;

    match.insert(Player(1, "Magnus Carlsen", 2880, 5));
    match.insert(Player(2, "Hikaru Nakamura", 2740, 2));
    match.insert(Player(3, "Praggnanandhaa", 2700, 1));
    match.insert(Player(4, "Krikor Mekhitarian", 2500, 4));
    match.insert(Player(5, "Supi", 2580, 3));
    match.insert(Player(6, "Alexandr Fier", 2590, 8));
    match.insert(Player(7, "Ding Liren", 2790, 6));
    match.insert(Player(8, "Fabiano Caruana", 2800, 10));
    match.insert(Player(9, "Rafael Leitao", 2600, 7));
    match.insert(Player(10, "Ian Nepomniachtchi", 2750, 9));

    auto start = chrono::high_resolution_clock::now(); // Começando o cronômetro

    // Ordenando por merge sort (Por ser mais rápido, na teoria)
    match.sortByScoreMerge();
    
    // Para testar o insertion:
    // match.sortByScoreInsertion();

    auto end = chrono::high_resolution_clock::now(); // Fim do cronômetro
    chrono::duration<double, std::milli> duration = end - start;

    cout << "Tempo de ordenacao: " << duration.count() << " ms\n";

    match.printWaitingPlayers(); // Jogadores ordenados

    // Primeira tentativa de matchmaking (Mal sucedida)
    int size1 = 3;
    int delta1 = 10;
    
    cout << "Tentativa 1 - Tamanho: " << size1 << "; Delta: " << delta1 << "\n";
    
    grupo = match.formGroup(size1, delta1, &n); // Vai falhar pois o trio tem delta de 20 (acho)
    


    // Segunda tentativa de matchmaking (Bem sucedida)
    int sizeTentativa2 = 3;
    int deltaTentativa2 = 30;
    
    cout << "Tentativa 2 - Tamanho: " << sizeTentativa2 << "; Delta: " << deltaTentativa2 << "\n";

    grupo = match.formGroup(sizeTentativa2, deltaTentativa2, &n); // Agora o trio vai ser aceito

    match.printWaitingPlayers(); // Fila após a remoção dos 3 primeiros

    delete [] grupo; // Criei o ponteiro no início do main de teste, tem que riscar o cpf dele agora

    // Remoção de jogador
    cout << "\n=== Teste: Remocao ===" << endl;
    Matchmaking matchRemocao;
    matchRemocao.insert(Player(1, "Ana",   1000, 1));
    matchRemocao.insert(Player(2, "Bruno", 1100, 2));
    matchRemocao.insert(Player(3, "Carla", 1250, 3));
    bool removido = matchRemocao.removePlayer(2);      // ID existente
    cout << "Remover ID 2: " << (removido ? "true" : "false") << endl;
    bool naoEncontrado = matchRemocao.removePlayer(99); // ID inexistente
    cout << "Remover ID 99: " << (naoEncontrado ? "true" : "false") << endl;
    matchRemocao.printWaitingPlayers();

    // Insertion sort
    cout << "\n=== Teste: Insertion Sort ===" << endl;
    Matchmaking matchInsertion;
    matchInsertion.insert(Player(1, "Magnus Carlsen", 2880, 5));
    matchInsertion.insert(Player(2, "Hikaru Nakamura", 2740, 2));
    matchInsertion.insert(Player(3, "Praggnanandhaa", 2700, 1));
    matchInsertion.insert(Player(4, "Krikor Mekhitarian", 2500, 4));
    matchInsertion.insert(Player(5, "Supi", 2580, 3));

    auto startIns = chrono::high_resolution_clock::now();
    matchInsertion.sortByScoreInsertion();
    auto endIns = chrono::high_resolution_clock::now();
    chrono::duration<double, std::milli> durIns = endIns - startIns;
    cout << "Tempo insertion sort: " << durIns.count() << " ms\n";
    matchInsertion.printWaitingPlayers();

    // Empate de score (desempate por timestamp)
    cout << "\n=== Teste: Empate de Score ===" << endl;
    Matchmaking matchEmpate;
    matchEmpate.insert(Player(1, "Ana",   1000, 5));
    matchEmpate.insert(Player(2, "Bruno", 900,  2));
    matchEmpate.insert(Player(3, "Carla", 1000, 1));
    matchEmpate.insert(Player(4, "Diego", 900,  4));
    matchEmpate.sortByScoreMerge();
    matchEmpate.printWaitingPlayers();
    // Esperado: Bruno(900,t2), Diego(900,t4), Carla(1000,t1), Ana(1000,t5)

    // getWaitingPlayers
    cout << "\n=== Teste: getWaitingPlayers ===" << endl;
    Player* jogadores = nullptr;
    Matchmaking matchGet;
    matchGet.insert(Player(1, "Ana",   1000, 1));
    matchGet.insert(Player(2, "Bruno", 1100, 2));
    jogadores = matchGet.getWaitingPlayers(&n);
    cout << "Total retornado: " << n << endl;
    for (int i = 0; i < n; i++) {
        cout << "[" << jogadores[i].getId() << " | " << jogadores[i].getName()
             << " | " << jogadores[i].getScore() << " | " << jogadores[i].getTimestamp() << "]" << endl;
    }
    delete[] jogadores;

    // getWaitingPlayers com fila vazia
    Matchmaking matchVazio;
    jogadores = matchVazio.getWaitingPlayers(&n);
    cout << "Fila vazia - retorno: " << (jogadores == nullptr ? "nullptr" : "array") << ", n = " << n << endl;
    matchVazio.printWaitingPlayers();

    return 0;
}