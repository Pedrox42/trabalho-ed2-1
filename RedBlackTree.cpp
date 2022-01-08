#include "RedBlackTree.h"
#include "RedBlackNode.h"
#include <iostream>

enum Color {RED, BLACK};

using namespace std;

RedBlackTree::RedBlackTree(){
    raiz = nullptr;
}

RedBlackTree::~RedBlackTree(){
    raiz = libera(raiz);
}

RedBlackNode* RedBlackTree::libera(RedBlackNode* p)
{
    if (p != nullptr)
    {
        p->setEsq(libera(p->getEsq()));
        p->setDir(libera(p->getDir()));
        delete p;
        p = nullptr;
    }
    return nullptr;
}

//compara utilizando a tabela ascii os ids
//retorna verdadeiro para caso id1 maior que id2
//retorna falsa para id2 igual ou menor que id1
bool RedBlackTree::compararId(char* id1, char* id2){
    int i = 0;
//    cout << "teste" << endl;
    for(i = 0; id1[i] != '\0' && id1[i] == id2[i]; i++);
//    cout << (id1[i] > id2[i]) << endl;
    return id1[i] > id2[i];
}


void RedBlackTree::emOrdem() {
    if(raiz == nullptr){
        cout << "Arvore vazia!" << endl;
        return;
    }
    emOrdemAux(raiz);
}

void RedBlackTree::emOrdemAux(RedBlackNode *p)
{
    if (p == nullptr){
        return;
    }

    emOrdemAux(p->getEsq());
    cout << "---------- No --------" << endl;
    cout << "ID: " << p->getId() << endl;
    cout << "Cor: " << p->getCor() << endl;
    if(p->getPai() != nullptr){
        cout << "pai: " << p->getPai()->getId() << endl;
        if(p->getPai()->getEsq() != nullptr){
            cout << (p->getPai()->getEsq() == p ? "No esquerdo" : "No direito") << endl;
        }
    }
    cout << "----------------------" << endl << endl;
    emOrdemAux(p->getDir());
}

void RedBlackTree::inserir(double enderecoMemoria, char* id)
{
    RedBlackNode *p = new RedBlackNode(enderecoMemoria, id);

    // insercao normal utilizando busca binaria
    raiz = inserirAux(raiz, p);

    // consertar error de arvore vermelho-preto
//    consertar(p);
}

//inserindo novo no como se fosse uma uma arvore binaria de busca
RedBlackNode* RedBlackTree::inserirAux(RedBlackNode* node1, RedBlackNode *node2)
{
    //node1 = raiz local
    //node2 = no filho
    // se a arvore estiver vazia, retorna o novo no
    if (node1 == nullptr) {
        return node2;
    }

    // Caso contrario, faz uma busca binaria recursiva pela arvore para inserir o No no lugar certo
    if (compararId(node1->getId(), node2->getId()))
    {
        node1->setEsq(inserirAux(node1->getEsq(), node2));
        node1->getEsq()->setPai(node1);
    }
    else if (!compararId(node1->getId(), node2->getId()))
    {
        node1->setDir(inserirAux(node1->getDir(), node2));
        node1->getDir()->setPai(node1);
    }

    // retornando o no raiz local
    return node1;
}

//void RBTree::fixViolation(Node *&root, Node *&pt)
//{
//    Node *parent_pt = NULL;
//    Node *grand_parent_pt = NULL;
//
//    while ((pt != root) && (pt->color != BLACK) &&
//           (pt->parent->color == RED))
//    {
//
//        parent_pt = pt->parent;
//        grand_parent_pt = pt->parent->parent;
//
//        /*  Case : A
//            Parent of pt is left child
//            of Grand-parent of pt */
//        if (parent_pt == grand_parent_pt->left)
//        {
//
//            Node *uncle_pt = grand_parent_pt->right;
//
//            /* Case : 1
//               The uncle of pt is also red
//               Only Recoloring required */
//            if (uncle_pt != NULL && uncle_pt->color ==
//                                    RED)
//            {
//                grand_parent_pt->color = RED;
//                parent_pt->color = BLACK;
//                uncle_pt->color = BLACK;
//                pt = grand_parent_pt;
//            }
//
//            else
//            {
//                /* Case : 2
//                   pt is right child of its parent
//                   Left-rotation required */
//                if (pt == parent_pt->right)
//                {
//                    rotateLeft(root, parent_pt);
//                    pt = parent_pt;
//                    parent_pt = pt->parent;
//                }
//
//                /* Case : 3
//                   pt is left child of its parent
//                   Right-rotation required */
//                rotateRight(root, grand_parent_pt);
//                swap(parent_pt->color,
//                     grand_parent_pt->color);
//                pt = parent_pt;
//            }
//        }
//
//            /* Case : B
//               Parent of pt is right child
//               of Grand-parent of pt */
//        else
//        {
//            Node *uncle_pt = grand_parent_pt->left;
//
//            /*  Case : 1
//                The uncle of pt is also red
//                Only Recoloring required */
//            if ((uncle_pt != NULL) && (uncle_pt->color ==
//                                       RED))
//            {
//                grand_parent_pt->color = RED;
//                parent_pt->color = BLACK;
//                uncle_pt->color = BLACK;
//                pt = grand_parent_pt;
//            }
//            else
//            {
//                /* Case : 2
//                   pt is left child of its parent
//                   Right-rotation required */
//                if (pt == parent_pt->left)
//                {
//                    rotateRight(root, parent_pt);
//                    pt = parent_pt;
//                    parent_pt = pt->parent;
//                }
//
//                /* Case : 3
//                   pt is right child of its parent
//                   Left-rotation required */
//                rotateLeft(root, grand_parent_pt);
//                swap(parent_pt->color,
//                     grand_parent_pt->color);
//                pt = parent_pt;
//            }
//        }
//    }
//
//    root->color = BLACK;
//}
