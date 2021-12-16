#include "HashEncadeado.h"
#include "HashNode.h"
#include "Hash.h"
#include <fstream>
#include <iostream>

using namespace std;

Hash::Hash(int tamanho)
{
   this->tamanho = tamanho;
   hashList = new HashPtr[tamanho];
   for(int i = 0; i < tamanho; i++) {
       hashList[i] = new HashEncadeado();
   }
}

Hash::~Hash()
{
    for(int i = 0; i < tamanho; i++) {
        delete hashList[i];
    }
    delete[] hashList;
}

int Hash::getTamanho() {
    return tamanho;
}

HashPtr* Hash::getHashList() {
    return hashList;
}

int Hash::formula(char* array) {
    long hash = 5381;
    int c;

    int i = 0;
    while (array[i] != '\0') {
        c = array[i];
        hash = (hash*33) + c; /* hash * 33 + c */
        i++;
    }    

    return hash % tamanho;
}

void Hash::inserir(Review* review) {
    int chave = formula(review->getAppVersion());

    HashNode *node = hashList[chave]->getNode(review->getAppVersion());

    if(node == nullptr) {
        hashList[chave]->insere(review->getAppVersion());
    }
    else {
        node->setFrequencia(node->getFrequencia() + 1);
    }
}

void Hash::imprime()
{
    int numero = 0;
    int colisoes = 0;
    for(int i = 0; i < tamanho; i++) {
        if(!hashList[i]->vazia()) {
            cout << "Indice: " << i << endl;
            hashList[i]->imprime();
            numero += hashList[i]->getTamanho();
            if(hashList[i]->getTamanho() > 1) {
                colisoes += hashList[i]->getTamanho() - 1;
            }
        }
   }
   cout << "Numero total: " << numero << endl;
   cout << "Colisoes: " << colisoes << endl;
}





