#ifndef TRABALHO_ED2_1_BTREE_H
#define TRABALHO_ED2_1_BTREE_H
#include "BTreeNode.h"



class BTree
{
    private:
        BTreeNode *raiz; // ponteiro para a raiz
        int grau;  // grau minimo
        int tamanho;

    public:
        // Constructor (Initializes tree as empty)
        BTree(int grau, int tamanho);

        ~BTree();

        void libera(BTreeNode* node);

        // funccao para percorrer a aravore
        void navegar();

        // buscar por um id na arvore
        BTreeNode* buscar(char* id);

        // The main function that inserts a new key in this B-Tree
        void inserir(char* id);

        BTreeNode *getRaiz();

        void setRaiz(BTreeNode *raiz);

        int getGrau();

        void setGrau(int grau);

        int getTamanho();

        void setTamanho(int tamanho);
};


#endif //TRABALHO_ED2_1_BTREE_H
