
# Trabalho Prático - Parte 1
## Aplicação da disciplina de Estrutura de Dados II da UFJF.

<!--ts-->
   * [Desenvolvedores](#desenvolvedores)
   * [Professores](#professores)
   * [Tecnologias](#tecnologias)
   * [Instalação](#instalação)
   * [Pré-requisitos para utilização](#pré-requisitos-para-utilização)
   * Utilização
      * [Preparação de ambiente](#preparação-de-ambiente)
      * [Compilação](#compilação)
      * [Extra](#extra)
<!--te-->

### Desenvolvedores:
- Anna Letícia Franco Monteiro - 202065106A 
- Davi Esteves dos Santos - 202065504B
- Gabriel do Carmo Silva - 202065030A
- Pedro Campos Lima - 202065521B

### Professores:
- Marcelo Caniato Renhe

### Tecnologias

As seguintes ferramentas foram usadas na construção do projeto:
- [C++](https://isocpp.org/)

### Instalação:

- Basta clonar ou fazer download do arquivos do repositório.

Para clonar abra o terminal na pasta desejada e digite o comando:
```
git clone https://github.com/Pedrox42/trabalho-ed2-1.git
```
### Pré-requisitos para utilização:

Antes de começar, você vai precisar ter instalado em sua máquina as seguintes ferramentas: [Git](https://git-scm.com) e [C++](https://isocpp.org/).
Além disto é interessante uma IDE que suporte a linguagem, como [VSCode](https://code.visualstudio.com/) ou [CLion](https://www.jetbrains.com/pt-br/clion/).

### Utilização:
#### Preparação de ambiente:
- Após clonar o repositório ou descompactar o .zip enviado, o arquivo CSV contendo as *reviews* a serem lidas e o input.dat (input.txt) deverão estar no diretório a ser passado como argumento. Para compilar, executar o programa e receber a saída esperada, siga as instruções abaixo.

#### Compilação
Ainda no terminal, utilize o comando:
```
g++ *.cpp *.h -o trabalhoED2
```
E em seguida:
```
./trabalhoED2 diretorio/
```
Sendo "diretorio" a pasta onde se encontra o CSV e o input.dat (input.txt).

Quando necessários, os arquivos de saída serão criados na mesma pasta onde o CSV está, sendo esses saida.txt e teste.txt, e no caso da necessidade de pré-tratamento do arquivo CSV, os arquivos binários criados também estarão nessa pasta.

Depois de compilado será mostrado um menu com algumas opções, onde cada uma delas é correspondente a uma das funções, e existe também uma opção para parar de executar o programa.
