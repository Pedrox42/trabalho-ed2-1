#ifndef TRABALHO_ED2_1_REDBLACKTREE_H
#define TRABALHO_ED2_1_REDBLACKTREE_H

#include "RedBlackNode.h"

class RedBlackTree {
    private:
        RedBlackNode* raiz;
        void rotacionarEsq(RedBlackNode* node);
        void rotacionarDir(RedBlackNode* node);
        void consertar(RedBlackNode* node1, RedBlackNode* node2);
        RedBlackNode* libera(RedBlackNode* p);
        void emOrdemAux(RedBlackNode* p);
        RedBlackNode *inserirAux(RedBlackNode* node1, RedBlackNode *node2, double* comparacoes);
        bool compararId(char *id1, char *id2);
        bool idIgual(char *id1, char *id2);
        RedBlackNode* buscarAux(RedBlackNode* node, char* id, double* comparacoes);
    public:
        // Constructor
        RedBlackTree();
        ~RedBlackTree();
        void inserir(double enderecoMemoria, char* id, double* comparacoes);
        void emOrdem();
        RedBlackNode* buscar(char* id, double* comparacoes);
};


#endif //TRABALHO_ED2_1_REDBLACKTREE_H
