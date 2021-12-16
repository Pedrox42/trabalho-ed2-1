#ifndef TRABALHO_ED2_1_HASHENCADEADO_H
#define TRABALHO_ED2_1_HASHENCADEADO_H

#include "HashNode.h"
#include <fstream>
#include <iostream>

class HashEncadeado
{
    public:
        HashEncadeado();
        ~HashEncadeado();
        
        void insere(char* appVersion);
        bool busca(char* appVersion);
        void imprime();
        int getTamanho();

    private:
        HashNode *hashRaiz;
        HashNode *hashUltimo;
        int tamanho;
};

#endif