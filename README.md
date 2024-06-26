# Projetos feito em C e C++

Repositório focado para salvar meus estudos nas linguagens C e C++

## Categoria

As pastas do repositório estão divididas em categorias (ASCII_Codes, OpenCV_Codes, OpenGL_Codes, Qt_Codes e SFML_Codes), logo a baixo está presente a organização das pastas:

<details><summary>Show</summary>

```bash

    ├── ASCII_Codes
    │   ├── ASCII_Art_3D
    │   ├── BongoCat
    │   ├── Cubo3DASCII
    │   ├── dotenv
    │   ├── ExpressoesNumericas
    │   ├── Natal code
    │   ├── PenduloDuploASCII
    │   ├── RGB_Terminal
    │   ├── SnakeGame
    │   ├── termtetris
    │   ├── Tic-Tac-Toe
    │   └── ToneGenerator
    ├── OpenCV_Codes
    │   └── FilterImage
    ├── OpenGL_Codes
    │   ├── Esfera3DOpenGL
    │   ├── Torus3DOpenGL
    │   └── TrianguloOpenGL
    ├── Qt_Codes
    │   ├── CuboOpenGL
    │   └── MiniNavegador
    └── SFML_Codes
        ├── BlackHole_Newtonian
        ├── FractalTree
        ├── Modelos3DSFML
        ├── Orb
        └── PenduloDuplo_SFML
```

</details>

## Sobre eles:

<details><summary>Show</summary>

### ASCII Codes

-   ASCII_Art_3D é um projeto onde é feito o plot de arquivos objetos ou modelos 3D calculados em tempo real seus vértices e faces/índices. Projeto feito em C++ no Linux.

-   BongoCat é uma animação simples usando bitmap e o plot em ASCII. Código feito em C no Linux.

-   Cubo3DASCII é um cubo feito em C++ sendo feito o plot em modo texto. Foi feito no Linux.

    -   OBS: Este projeto foi feito com base no vídeo do canal [Servet Guinarogiu](https://youtu.be/p09i_hoFdd0) para praticar C++.

-   dotenv é um projeto com duas funções, gera uma chave de API aleatória (key.cpp), lê o arquivo .env e mostra na tela as variáveis de ambiente (env_read.cpp), no caso API_KEY no .env de exemplo. Foi feito em C++.

-   ExpressoesNumericas é uma calculadora de expressões algébricas, resolve expressões com adição, subtração, multiplicação, divisão e potência e pode usar parênteses para separar melhor a ordem da resolução. Foi feito em C++.

    -   OBS: Este projeto foi feito com base no desafio 14 do site [OsProgramadores](https://osprogramadores.com/), caso queira conhecer os [Desafios](https://osprogramadores.com/desafios/) fique a vontade.

-   Tic-Tac-Toe é o jogo da velha feito em C++ usando classes (uma tentativa de classe abstrata). Foi feito no Linux.

-   Natal code é uma árvore de Natal feita em C. Foi feito no Windows e testada no Linux.

-   PenduloDuploASCII é uma simulação do movimento caótico de um pêndulo duplo, seu plot é em modo texto (ASCII). Foi feito no Linux.

    -   OBS: Esta simulação foi feita com base no código do [DinoZ1729](https://github.com/DinoZ1729/Double-Pendulum) para estudar sobre simulações de movimentos caóticos e praticar C++.

-   RGB_Terminal é um suporte para imagens para o terminal. Foi feito em C++ no Linux.

    -   OBS: Este suporte foi feito com base no vídeo [_3D ASCII with Colors_](https://youtu.be/M-sIyi9VMSU) do canal [Tsoding Daily](https://www.youtube.com/@TsodingDaily).

-   SnakeGame é o jogo da cobrinha feito em C. Foi feito no Linux.

-   ToneGenerator é para criar arquivos de áudio (no formato wav) para testes de som. Foi feito em C++ no Linux.

### OpenCV Codes

-   FilterImage é uma aplicação simples do OpenCV onde é demonstrado alguns filtros usados para atenuar bordas na imagem, o projeto é em C++. Foi feito no Linux.

### OpenGL Codes

-   Esfera3DOpenGL é uma esfera feita em C++ usando a biblioteca OpenGL e o Glut. Foi feito no Linux.

-   Torus3DOpenGL é uma toróide feita em C++ usando a biblioteca OpenGL e o Glut. Foi feito no Linux.

-   TrianguloOpenGL é um triângulo colorido feito em C++ usando a biblioteca OpenGL e o Glut. Foi feito no Linux.

### Qt Codes

-   CuboOpenGL é um cubo feito com as funções do Qt6 e C++. Foi feito no Linux com a IDE Qt Creator.

-   MiniNavegador é um navegador que pode mostrar páginas Web por link, foi feito com o Qt6 e C++. Foi usado o Linux e a IDE Qt Creator.

### SFML Codes

-   FractalTree é um modelo matemático da área dos fractais e é uma boa demonstração de recursão usando o C++ e a biblioteca do SFML. Foi feito no Linux.

-   Modelos3DSFML fiz dois modelos 3D de uma esfera e uma rosquinha usando o SFML e matemática. Foi feito no Linux.

    -   OBS: Na pasta a uma pasta com nome de img, o site de onde veio as imagens é [Solar System Scope](https://www.solarsystemscope.com/textures/). O uso das imagens foi para aplicar uma textura para testar.

-   Orb é desenhado 3 órbitas e ao longo que elas vão passando fica seu rastro em 3 cores diferentes (vermelho, ciano e preto), seu desenho foi feito com auxílio da biblioteca SFML. Foi feito no Linux.

-   PenduloDuplo_SFML é uma simulação de um pêndulo duplo, seu plot foi feito utilizando a biblioteca do SFML. Foi feito no sistema operacional Debian em C++.

</details>

## Instalação

Para usar os códigos presentes neste repositório é necessário ter as seguintes ferramentas.

<details><summary>Show</summary>

### Instalação do OpenGL e GLUT

O OpenGL e o Glut estão disponíveis no site:

1. [OpenGL Wiki: Getting Started - Khronos Group](https://www.khronos.org/opengl/wiki/Getting_Started)

2. [GLUT - The OpenGL Utility Toolkit](https://www.opengl.org/resources/libraries/glut/glut_downloads.php)

### Instalação do SFML

Siga a documentação do [SFML](https://www.sfml-dev.org/) para instala-lo.

### Instalação no Linux para as ferramentas do C e C++ (Debian)

```
sudo apt install cmake make gcc g++
```

### Instalação no Windows para as ferramentas do C e C++

No Windows use o [MinGW](https://www.mingw-w64.org/) e instale o gcc, g++, cmake e make.

### Instalação do Qt:

Siga a documentação no site do [Qt](https://www.qt.io/) para instala-lo.

### Instalação do OpenCV:

Siga a documentação no site do [OpenCV](https://opencv.org/) para instala-lo.

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

</details>

## Bibliografia

Documentações para consulta:

1.  [Boost C++ Libraries](https://www.boost.org/)
2.  [cplusplus.com](https://cplusplus.com/)
3.  [cppreference.com](https://pt.cppreference.com/w/P%C3%A1gina_principal)
4.  [Documentation OpenCV](https://docs.opencv.org/4.x/d1/dfb/intro.html)
5.  [Documentation Qt](https://doc.qt.io/)
