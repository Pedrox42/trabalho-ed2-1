#include "HashNode.h"
#include <fstream>
#include <iostream>

HashNode::HashNode(char* appVersion, int frequencia)
{
    //this->appVersion = new char[version_size];
    this->appVersion = appVersion;
    this->frequencia = frequencia;
}

HashNode::~HashNode()
{
    delete [] this->appVersion;
}

int HashNode::getFrequencia()
{
    return this->frequencia;
}

bool HashNode::compareAppVersion(char* string1) {
    int i;
    for(i = 0; string1[i] != '\0'; i++) {
        if(this->getAppVersion()[i] != string1[i]) {
            return false;
        }
    }
    return this->getAppVersion()[i] == '\0' && string1[i] == '\0';
}


void HashNode::setFrequencia(int frequencia)
{
    this->frequencia = frequencia;
}

char* HashNode::getAppVersion()
{
    return this->appVersion;
}

void HashNode::setAppVersion(char* appVersion)
{
    this->appVersion = appVersion;
}

HashNode* HashNode::getProx(){
    return this->proximo;
}

void HashNode::setProx(HashNode *h) {
    this->proximo = h;
}

