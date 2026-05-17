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

// Questão 5
Player* Matchmaking::formGroup(int groupSize, int delta, int* n) {

    // Sem jogadores suficientes nem tenta
    if (groupSize <= 0 || groupSize > this->size) {
        *n = 0;
        return nullptr;
    }

    // Testa cada janela de groupSize jogadores seguidos
    for (int i = 0; i + groupSize - 1 < this->size; i++) {
        int menorScore = this->players[i].getScore();
        int maiorScore = this->players[i + groupSize - 1].getScore();

        if (maiorScore - menorScore <= delta) {
            // Copia o grupo antes de mexer na fila
            Player* grupo = new Player[groupSize];
            for (int j = 0; j < groupSize; j++) {
                grupo[j] = this->players[i + j];
            }

            // Tira o grupo da fila empurrando o resto pra tras
            for (int j = i; j + groupSize < this->size; j++) {
                this->players[j] = this->players[j + groupSize];
            }
            this->size -= groupSize;

            *n = groupSize;
            return grupo;
        }
    }

    // Nenhuma janela funcionou
    *n = 0;
    return nullptr;
}

// Questão 6
Player* Matchmaking::getWaitingPlayers(int* n) {

    // Fila vazia, nao devolve nada
    if (this->size == 0) {
        *n = 0;
        return nullptr;
    }

    // Array novo so com as copias dos jogadores
    Player* copia = new Player[this->size];
    for (int i = 0; i < this->size; i++) {
        copia[i] = this->players[i];
    }

    *n = this->size;
    return copia;
}

// Questão 7
void Matchmaking::printWaitingPlayers(){
    cout << "Waiting Players:" << endl;
    if(size == 0){
        cout << "empty" << endl;
        return;
    }
    
    for(int i = 0; i < size; i++){
        cout << "[" 
        << players[i].getId() 
        << " | "
        << players[i].getName()
        << " | "
        << players[i].getScore()
        << " | "
        << players[i].getTimestamp()
        << "]" << endl;     
    }
}
