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

    return 0;
}