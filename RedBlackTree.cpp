#include "RedBlackTree.h"
#include "RedBlackNode.h"
#include <iostream>

enum Color {VERMELHO, PRETO};

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

bool RedBlackTree::idIgual(char* id1, char* id2){
    int i = 0;
//    cout << "teste" << endl;
    for(i = 0; id1[i] != '\0' && id1[i] == id2[i]; i++);
//    cout << (id1[i] > id2[i]) << endl;
    return id1[i] == id2[i];
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
    cout << "Cor: " << (p->getCor() ? "Preto" : "Vermelho") << endl;
    cout << "endereco: " << p->getEnderecoMemoria() << endl;
    if(p->getPai() != nullptr){
        cout << "pai: " << p->getPai()->getId() << endl;
        if(p->getPai()->getEsq() != nullptr || p->getPai()->getDir() != nullptr){
            cout << (p->getPai()->getEsq() == p ? "No esquerdo" : "No direito") << endl;
        }
    }
    cout << "----------------------" << endl << endl;
    emOrdemAux(p->getDir());
}

void RedBlackTree::inserir(double enderecoMemoria, char* id, double* comparacoes)
{
    RedBlackNode *p = new RedBlackNode(enderecoMemoria, id);

    // insercao normal utilizando busca binaria
    raiz = inserirAux(raiz, p, comparacoes);

    // consertar error de arvore vermelho-preto
    consertar(raiz, p);
}

//inserindo novo no como se fosse uma uma arvore binaria de busca
RedBlackNode* RedBlackTree::inserirAux(RedBlackNode* node1, RedBlackNode *node2, double* comparacoes)
{
    //node1 = raiz local
    //node2 = no filho
    // se a arvore estiver vazia, retorna o novo no
    (*comparacoes)++;
    if (node1 == nullptr) {
        return node2;
    }

    // Caso contrario, faz uma busca binaria recursiva pela arvore para inserir o No no lugar certo
    (*comparacoes)++;
    if (compararId(node1->getId(), node2->getId()))
    {
        node1->setEsq(inserirAux(node1->getEsq(), node2, comparacoes));
        node1->getEsq()->setPai(node1);
    }
    else
    {
        node1->setDir(inserirAux(node1->getDir(), node2, comparacoes));
        node1->getDir()->setPai(node1);
    }

    // retornando o no raiz local
    return node1;
}

void RedBlackTree::rotacionarEsq(RedBlackNode* node)
{
    RedBlackNode* pt_right = node->getDir();

    node->setDir(pt_right->getEsq());

    if (node->getDir() != nullptr)
        node->getDir()->setPai(node);

    pt_right->setPai(node->getPai());

    if (node->getPai() == nullptr)
        raiz = pt_right;

    else if (node == node->getPai()->getEsq())
        node->getPai()->setEsq(pt_right);

    else
        node->getPai()->setDir(pt_right);

    pt_right->setEsq(node);
    node->setPai(pt_right);
}

void RedBlackTree::rotacionarDir(RedBlackNode* node)
{
    RedBlackNode* pt_left = node->getEsq();

    node->setEsq(pt_left->getDir());

    if (node->getEsq() != nullptr)
        node->getEsq()->setPai(node);

    pt_left->setPai(node->getPai());

    if (node->getPai() == nullptr)
        raiz = pt_left;

    else if (node == node->getPai()->getEsq())
        node->getPai()->setEsq(pt_left);

    else
        node->getPai()->setDir(pt_left);

    pt_left->setDir(node);
    node->setPai(pt_left);
}

void RedBlackTree::consertar(RedBlackNode* node1, RedBlackNode* node2)
{
    //node1 -> raiz local
    //node2 -> no inserido/no local

    RedBlackNode* pai_pt = nullptr;
    RedBlackNode* avo_pt = nullptr;

    while ((node2 != node1) && (node2->getCor() != PRETO) && (node2->getPai()->getCor() == VERMELHO))
    {

        pai_pt = node2->getPai();
        avo_pt = node2->getPai()->getPai();

        //  Caso : A
        //   pai do no conflitante esta a esquerda do avo de pai
        if (pai_pt == avo_pt->getEsq())
        {
            RedBlackNode *tio_pt = avo_pt->getDir();

            // Caso : 1
            // o avo eh vermelho
            if (tio_pt != nullptr && tio_pt->getCor() == VERMELHO)
            {
                avo_pt->setCor(VERMELHO);
                pai_pt->setCor(PRETO);
                tio_pt->setCor(PRETO);
                node2 = avo_pt;
            }
            else
            {
                // Caso : 2
                // o no conflitante esta a direita de seu pai
                // rotaciona para a esquerda
                if (node2 == pai_pt->getDir())
                {
                    rotacionarEsq(pai_pt);
                    node2 = pai_pt;
                    pai_pt = node2->getPai();
                }

                // Caso : 3
                // o no conflitante está a esquerda de seu pai
                // rotaciona para a direita
                rotacionarDir(avo_pt);

                //swap de cores
                bool corAux = pai_pt->getCor();
                pai_pt->setCor(avo_pt->getCor());
                avo_pt->setCor(corAux);

                node1 = pai_pt;
            }
        }

            // Caso : B
            //   pai do no conflitante é o filho da direita de seu avo
        else
        {
            RedBlackNode *tio_pt = avo_pt->getEsq();

            // o tio do no conflitante tambem e vermelho
            if ((tio_pt != nullptr) && (tio_pt->getCor() == VERMELHO))
            {
                avo_pt->setCor(VERMELHO);
                pai_pt->setCor(PRETO);
                tio_pt->setCor(PRETO);
                node2 = avo_pt;
            }
            else
            {
                // Caso : 2
                //   o no conflitante esta a esquerda de seu pai
                //   rotacao a direita precisa
                if (node2 == pai_pt->getEsq())
                {
                    rotacionarDir(pai_pt);
                    node2 = pai_pt;
                    pai_pt = node2->getPai();
                }

                // Caso : 3
                // o no conflitante esta a direita de seu pai
                // rotacao para a esquerda precisa
                rotacionarEsq(avo_pt);

                //swap de cores
                bool corAux = pai_pt->getCor();
                pai_pt->setCor(avo_pt->getCor());
                avo_pt->setCor(corAux);

                node2 = pai_pt;
            }
        }
    }

    node1->setCor(PRETO);
}

RedBlackNode* RedBlackTree::buscar(char* id, double* comparacoes)
{
    if(raiz != nullptr){
        RedBlackNode* node = buscarAux(raiz, id, comparacoes);
        if(node != nullptr){
            return node;
        } else{
            cout << "Erro: Id nao encontrado!" << endl;
            return nullptr;
        }
    } else{
        cout << "Erro: Arvore vazia!" << endl;
        return nullptr;
    }
}


RedBlackNode* RedBlackTree::buscarAux(RedBlackNode* node, char* id, double* comparacoes)
{
    //caso o no atual seja o valor, ou seja nulo.
    (*comparacoes)++;
    if (node == nullptr || idIgual(node->getId(), id))
        return node;

    // caso o id seja "maior" que o atual
    (*comparacoes)++;
    if (!compararId(node->getId(), id))
        return buscarAux(node->getDir(), id, comparacoes);

    // caso o id seja menor que o atual
    return buscarAux(node->getEsq(), id, comparacoes);
}
