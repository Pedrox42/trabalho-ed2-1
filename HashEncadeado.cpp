#include "HashEncadeado.h"
#include "HashNode.h"
#include <fstream>
#include <iostream>
using namespace std;
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
        hashUltimo = h;
    }
    else {
        hashUltimo->setProx(h);
        hashUltimo = h;
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

HashNode* HashEncadeado::getNode(char* appVersion)
{
    for(HashNode* node = hashRaiz; node != nullptr; node = node->getProx()) {
        if(node->compareAppVersion(appVersion)) {
            return node;
        }
    }
    return nullptr;
}

int HashEncadeado::getTamanho()
{
    return this->tamanho;
}

void HashEncadeado::imprime()
{
    for(HashNode* node = hashRaiz; node != nullptr; node = node->getProx()) {
        cout << "App Version: " << node->getAppVersion() << endl;
        cout << "Frequencia: " << node->getFrequencia() << endl << endl;
    }   
}

bool HashEncadeado::vazia()
{
    return hashRaiz == nullptr;
}