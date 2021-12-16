#ifndef TRABALHO_ED2_1_HASHNODE_H
#define TRABALHO_ED2_1_HASHNODE_H

#include <fstream>
#include <iostream>

class HashNode
{
    public:
        HashNode(char* appVersion, int frequencia);
        ~HashNode();
        int getFrequencia();
        char* getAppVersion();
        HashNode* getProx();
        void setFrequencia(int frequencia);
        void setAppVersion(char* appVersion);
        void setProx(HashNode *h);
        static const int version_size = 21;
        bool compareAppVersion(char* string1);

    private:
        int frequencia;
        char* appVersion;
        HashNode* proximo;
};

#endif