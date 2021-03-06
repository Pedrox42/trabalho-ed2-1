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
        HashNode *hashRaiz;
        bool vazia();
        HashNode* getNode(char* appVersion);


private:
        HashNode *hashUltimo;
        int tamanho;
};

#endif