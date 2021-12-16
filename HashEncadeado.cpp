#include "HashEncadeado.h"
#include "HashNode.h"
#include <fstream>
#include <iostream>

HashEncadeado::HashEncadeado()
{
    hashRaiz = nullptr;
    hashUltimo = nullptr;
    tamanho = 0;
}

HashEncadeado::~HashEncadeado()
{
    HashNode *h = hashRaiz;
    while (h != NULL) {
        HashNode *t = h->getProx();
        delete h;
        h = t;
    }
}

void HashEncadeado::insere(char* appVersion)
{
    HashNode* h = new HashNode(appVersion, 1);
    h->setProx(nullptr);
    if(tamanho == 0) {
        hashRaiz = h;
        hashFinal = h;   
    }
    else {
        hashFinal->setProx(h);
        hashFinal = h;
    }
    tamanho++;
}

bool HashEncadeado::busca(char* appVersion)
{
    for(HashNode* node = hashRaiz; node != nullptr; node = node->getProx()) {
        if(node->compareAppVersion(appVersion)) {
            return true;
        }
    }
    return false;
}

int HashEncadeado::getTamanho()
{
    return this->tamanho;
}

void HashEncadeado::imprime()
{
    for(HashNode* node = hashRaiz; node != nullptr; node = node->getProx()) {
        cout << "App Version: " << node->appVersion << endl;
        cout << "Frequencia: " << node->frequencia << endl << endl;
    }   
}



