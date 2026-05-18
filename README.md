# Sistema de Matchmaking

Trabalho 3 de Estruturas de Dados. Implementa um sistema de matchmaking para jogos online em C++: jogadores entram numa fila de espera, são ordenados por score e agrupados com base na proximidade de nível.

## Como compilar

```bash
g++ main.cpp Matchmaking.cpp Player.cpp -o matchmaking
```

## Como executar

```bash
./matchmaking
```

## Arquivos

- `Player.hpp / Player.cpp` — classe que representa um jogador (id, nome, score, timestamp)
- `Matchmaking.hpp / Matchmaking.cpp` — classe principal com insert, remoção, ordenação e formação de grupos
- `Constants.hpp` — define o tamanho máximo do array (`MAX_PLAYERS = 100000`)
- `main.cpp` — testes de todas as funcionalidades

## Testes no main.cpp

Os testes rodam em sequência e cobrem:

- inserção de jogadores na fila
- ordenação por merge sort e insertion sort, com medição de tempo
- caso de empate no score (desempate por timestamp)
- formação de grupo bem-sucedida e sem sucesso
- remoção de jogador por ID
- uso do `getWaitingPlayers`, incluindo fila vazia
