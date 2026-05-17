#include "Matchmaking.hpp"
#include <iostream>
using namespace std;

Matchmaking::Matchmaking() {
    this->size = 0;
}

Matchmaking::~Matchmaking() {
    // Como o array interno "players" é estático, não precisamos remover nada da memória
}

// Questão 2
bool Matchmaking::insert(Player player) {

    if (this-> size >= MAX_PLAYERS) {
        cout << "Não foi possível inserir o Jogador" << endl;
        cout << "Size: " << this->size;
        cout << "Max players: " << MAX_PLAYERS;
        return false;
    }

    this->players[this->size] = player; //Inserindo no final do array
    this->size++;
    
    cout << "Jogador Inserido no array de matchmakin corretamente!! " << endl; 
    return true;
}

//Questão 3
bool Matchmaking::removePlayer(int id) {

    for (int i = 0; i < this->size; i++) { // Itera por player

        if (this->players[i].getId() == id) {

            for (int j = i; j < this->size - 1; j++) { // Empurra os outros jogadores para trás

                this->players[j] = this->players[j + 1];

            }
            this->size--;

            return true;
        }
    }

    return false;
}


void Matchmaking::sortByScoreInsertion() {

    // Inicializando os parâmetros do insertion sort
    Player* arr = this->players;
    int n = this->size;
    
    int i, j;
    Player current; //Inicializa o player que vamos iterar em cada i

    for (i = 1; i < n; i++) { // Para cada player no nosso array supostamente desordenado
        current = arr[i];
        j = i - 1;

        while (j >= 0) {
            bool currentIsGreater = false;
            
            // Caso de score maior que o atual
            if (arr[j].getScore() > current.getScore()) {
                currentIsGreater = true;
            } 

            // Caso de empate, então consideraremos o timestamp
            else if (arr[j].getScore() == current.getScore() && arr[j].getTimestamp() > current.getTimestamp()) {
                currentIsGreater = true;
            }

            if (!currentIsGreater) {
                break;
            }

            arr[j + 1] = arr[j];
            j = j - 1;
        }
        
        arr[j + 1] = current;
    }
}

// Função merge que junta os arrays da esquerda (left) e da direita (right)
Player* merge(Player* left, int n, Player* right, int m){
    Player* merged = new Player[n + m];
    int i = 0;
    int j = 0;
    int k = 0;

    while (i < n && j < m){
        bool arr_left_primeiro = false; // Booliano só pra sabe onde "costurar" os dois arrays, esquerda direita ou direita esquerda.

        if (left[i].getScore() < right[j].getScore()){
            arr_left_primeiro = true;
        }
        // Caso de empate no score
        else if (left[i].getScore() == right[j].getScore() && left[i].getTimestamp() < right[j].getTimestamp()){
            arr_left_primeiro = true;
        }

        if (arr_left_primeiro){
            merged[k] = left[i];
            i++;
            k++;
        } else{
            merged[k] = right[j];
            j++;
            k++;
        }
    }

    while (i < n) {
        merged[k] = left[i];
        i++;
        k++;
    }

    while (j < m) {
        merged[k] = right[j];
        j++;
        k++;
    }

    return merged;
}

Player* mergesort(Player* arr, int n) {

    if (n == 1) {
        Player* base = new Player[1];
        base[0] = arr[0];
        return base;
    }

    int mid = n / 2;
    
    Player* left = mergesort(arr, mid);
    Player* right = mergesort(arr + mid, n - mid);
    
    Player* merged = merge(left, mid, right, n - mid);
    
    delete[] left;
    delete[] right;

    return merged;
}

void Matchmaking::sortByScoreMerge() {

    if (this->size <= 1) { // Já está ordenado
        return; 
    }

    Player* sortedArray = mergesort(this->players, this->size);

    for (int i = 0; i < this->size; i++) {
        this->players[i] = sortedArray[i];
    }

    delete[] sortedArray;
}