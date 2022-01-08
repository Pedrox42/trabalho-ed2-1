#ifndef TRABALHO_ED2_1_REDBLACKTREE_H
#define TRABALHO_ED2_1_REDBLACKTREE_H

#include "RedBlackNode.h"

class RedBlackTree {
    private:
        RedBlackNode* raiz;
        void rotacionarEsq(RedBlackNode* child);
        void rotacionarDir(RedBlackNode* child);
        void consertar(RedBlackNode* child);
        RedBlackNode* libera(RedBlackNode* p);
        void emOrdemAux(RedBlackNode* p);
        RedBlackNode *inserirAux(RedBlackNode* node1, RedBlackNode *node2);
        bool compararId(char *id1, char *id2);
    public:
        // Constructor
        RedBlackTree();
        ~RedBlackTree();
        void inserir(double enderecoMemoria, char* id);
        void emOrdem();

};


#endif //TRABALHO_ED2_1_REDBLACKTREE_H
