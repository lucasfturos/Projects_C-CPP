# Projetos feito em C e C++

Repositório focado para salvar meus estudos nas linguagens C e C++

## Categoria

As pastas do repositório estão divididas em categorias (ASCII_Codes, RayTracing_Codes, OpenGL_Codes e SFML_Codes), logo a baixo está presente a organização das pastas:
<details><summary>Show</summary>


    ├── ASCII_Codes
    │   ├── Cubo3DASCII
    │   ├── Natal code
    │   ├── PenduloDuploASCII
    │   ├── SnakeGame
    │   ├── termtetris
    │   └── Tic-Tac-Toe
    ├── RayTracing_Codes
    │   └── EsferaRayTracing
    ├── OpenGL_Codes
    │   ├── Esfera3DOpenGL
    │   ├── Torus3DOpenGL
    │   └── TrianguloOpenGL
    └── SFML_Codes
        ├── BlackHole_Newtonian
        └── PenduloDuplo_SFML


</details>


## Sobre eles:

<details><summary>Show</summary>

- Tic-Tac-Toe é o jogo da velha feito em C++ usando classes (uma tentativa de classe abstrata). Foi feito no Linux.

- SnakeGame é o jogo da cobrinha feito em C. Foi feito no Linux.

- Natal code é uma árvore de Natal feita em C. Foi feito no Windows e testada no Linux.

- TrianguloOpenGL é um triângulo colorido feito em C++ usando a biblioteca OpenGL e o Glut. Foi feito no Linux.

- Torus3DOpenGL é uma toróide feita em C++ usando a biblioteca OpenGL e o Glut. Foi feito no Linux.

- Esfera3DOpenGL é uma esfera feita em C++ usando a biblioteca OpenGL e o Glut. Foi feito no Linux.

- EsferaRayTracing é uma esfera feita em C++ utilizando técnicas da própria linguagem para fazer o plot do objeto, a técnica utilizada é o RayTracing. Também será implementado métodos de paralelismo para tornar a renderização mais eficiente e logo irei organizar melhor as pastas de conteúdo do projeto. Foi feito no Linux.
  - OBS: Este projeto é fruto do meu aprendizado nas aulas do livro [_Ray Tracing in One Weekend_](https://raytracing.github.io/books/RayTracingInOneWeekend.html), recomendo a leitura do livro e acesse o repositório [RayTracing](https://github.com/RayTracing/raytracing.github.io) para ter acesso a todo o conteúdo (livro, código fonte e etc.) sobre essa prática da computação gráfica.

- Cubo3DASCII é um cubo feito em C++ sendo feito o plot em modo texto. Foi feito no Linux.
  - OBS: Este projeto foi feito com base no vídeo do canal [Servet Guinarogiu](https://youtu.be/p09i_hoFdd0) para praticar C++.
- PenduloDuploASCII é uma simulação do movimento caótico de um pêndulo duplo, seu plot é em modo texto (ASCII). Foi feito no Linux.

  - OBS: Esta simulação foi feita com base no código do [DinoZ1729](https://github.com/DinoZ1729/Double-Pendulum) para estudar sobre simulações de movimentos caóticos e praticar C++.

- PenduloDuplo_SFML é uma simulação de um pêndulo duplo, seu plot foi feito utilizando a biblioteca do SFML. Foi feito no sistema operacional Debian em C++.

</details>

## Instalação

Para usar os códigos presentes neste repositório é necessário ter as seguintes ferramentas.

<details><summary>Show</summary>


- O OpenGL e o Glut estão disponíveis no site:

```
https://www.khronos.org/opengl/wiki/Getting_Started
https://www.opengl.org/resources/libraries/glut/glut_downloads.php
```

- O SFML está disponível no link:

```
https://www.sfml-dev.org/
```

- Instalação no Linux para as ferramentas do C e C++ (Debian):

```
sudo apt install cmake make gcc g++
```

- Instalação no Windows para as ferramentas do C e C++:

No Windows use o MinGW e instale o gcc, g++, cmake e make, o link do site:

```
https://www.mingw-w64.org/
```

</details>

## Como usar

Após fazer a instalação das dependências acima você precisa seguir esses orientações para usar os projetos:


<details><summary>Show</summary>


Para os projetos com CMakeLists.txt é só rodar o comando:
```
cmake -B build
cd build/
make
./Nome_do_Executável
```

Para os projetos com Makefile é só rodar o comando:
```
make run
```
Ou abra o arquivo Makefile e veja quais os comandos existem e teste cada um.


Para o projeto EsferaRayTracing você precisa fazer os seguintes passos:
```
cmake -B build
cd build/
make
./EsferaRayTracing >> output.ppm
eog output.ppm
```
O comando eog é um programa de visualização de imagens do Gnome, caso não tenha use um visualizador de imagens compatível com o formato .ppm.

</details>
