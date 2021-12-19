#ifndef TRABALHO_ED2_1_HASH_H
#define TRABALHO_ED2_1_HASH_H

#include "Review.h"
#include "HashEncadeado.h"
#include <fstream>
#include <iostream>

typedef HashEncadeado* HashPtr;

class Hash
{
    private:
        int tamanho;
        HashPtr *hashList;

    public:
        Hash(int tamanho);
        ~Hash();
        int getTamanho();
        HashPtr* getHashList();
        void inserir(Review *review);
        void colisao();
        int formula(char* array);
        void imprime();
        void imprimeMaisFrequentes(int m);
        int* getArrayInt(int* tamanhoArray);
        char** getArrayChar(int* tamanhoArray);
        static const int version_size = 21;
};

#endif