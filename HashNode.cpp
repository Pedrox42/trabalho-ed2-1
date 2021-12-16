#include "HashNode.h"
#include <fstream>
#include <iostream>

HashNode::HashNode(char* appVersion, int frequencia)
{
    this->appVersion = new char[version_size];
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
    if ((string1 == NULL) && (this->appVersion == NULL))
        return true;
    if ((string1 == NULL) || (this->appVersion == NULL))
        return false;
    while (((*string1) != '\0') && ((*this->appVersion) != '\0') && ((*string1) == (*this->appVersion)))
    {
        string1++;
        this->appVersion++;
    }
    return ((*string1) == *this->appVersion);
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

