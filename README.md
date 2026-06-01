# Tetris em C++

Este repositório contém uma recriação do clássico jogo Tetris, desenvolvida em C++ como um pequeno projeto de alguns dias, para a consola do Windows.

## Funcionalidades e Mecânicas

* Multithreading: O jogo utiliza as bibliotecas `<thread>` e `<mutex>` para processar a gravidade das peças e os controlos do jogador em simultâneo, sem bloqueios de interface.
* Sistema de High Score: Guarda automaticamente as pontuações mais altas de forma persistente. O jogo utiliza a biblioteca `<filesystem>` e a API do Windows para criar e ler um ficheiro de texto oculto na pasta AppData do jogador.
* Mecânicas Clássicas:
  * Rotação de peças nos dois sentidos.
  * Função Hold (guardar a peça atual para usar mais tarde).
  * Previsão (sombra) que mostra onde a peça vai cair.
  * Sistema de pontuação baseado na limpeza de múltiplas linhas e níveis de dificuldade crescentes.

## Como Compilar

O Tetris requer suporte para o padrão C++17 e para as bibliotecas de threads e da Windows Shell. Para compilar, execute o seguinte comando no terminal:

    g++ tetris.cpp -o tetris.exe -std=c++17 -static-libgcc -static-libstdc++ -static -pthread -lshell32


## Controlos

* Setas Esquerda / Direita: Mover a peça horizontalmente.
* Seta Cima ou X: Rodar a peça no sentido dos ponteiros do relógio.
* Z: Rodar a peça no sentido contrário aos ponteiros do relógio.
* Seta Baixo: Acelerar a queda da peça.
* Espaço ou Enter: Hard Drop (queda instantânea da peça).
* C: Guardar/Trocar peça (Hold).