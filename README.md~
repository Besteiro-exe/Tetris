#Tetris em C++

Este repositório contém uma recriacao do classico jogo Tetris, desenvolvida em C++ como um pequeno projeto em alguns dias, para a consola do Windows.

## Funcionalidades e Mecanicas

* Multithreading: O jogo utiliza a biblioteca <thread> e <mutex> para processar a gravidade das peças e os controlos do jogador em simultaneo, sem bloqueios de interface.
* Sistema de High Score: Guarda automaticamente as pontuações mais altas de forma persistente. O jogo utiliza a biblioteca <filesystem> e a API do Windows para criar e ler um ficheiro de texto oculto na pasta AppData do jogador.
* Mecanicas Classicas:
  * Rotacao de pecas nos dois sentidos.
  * Funcao Hold (guardar a peca atual para usar mais tarde).
  * Previsão (sombra) que mostra onde a peca vai cair.
  * Sistema de pontuacao baseado na limpeza de multiplas linhas e niveis de dificuldade crescentes.

## Como Compilar

O Tetris requer suporte para o padrao C++17 e para as bibliotecas de threads e da Windows Shell. Para compilar execute o seguinte comando no terminal:

    g++ tetris.cpp -o tetris.exe -std=c++17 -static-libgcc -static-libstdc++ -static -pthread -lshell32

## Controlos

* Setas Esquerda / Direita: Mover a peca horizontalmente.
* Seta Cima ou X: Rodar a peca no sentido dos ponteiro do relógio.
* Z: Rodar a peca no sentido contrário aos ponteiros do relógio.
* Seta Baixo: Acelerar a queda da peca.
* Espaco ou Enter: Hard Drop (queda instantânea da peça).
* C: Guardar/Trocar peça (Hold).
