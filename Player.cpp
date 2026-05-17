#include "Player.hpp"
using namespace std;

Player::Player(int id, string name, int score, int timestamp) {
    this->id = id;
    this->name = name;
    this->score = score;
    this->timestamp = timestamp;
}

// Destrutor não possui nenhuma alocação para ser retirada da memória
Player::~Player() {
}

// Apenas os getters

int Player::getId() {
    return this->id;
}

std::string Player::getName() {
    return this->name;
}

int Player::getScore() {
    return this->score;
}

int Player::getTimestamp() {
    return this->timestamp;
}