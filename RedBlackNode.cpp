#include "RedBlackNode.h"

enum Cor {VERMELHO, PRETO};

RedBlackNode::RedBlackNode(double enderecoMemoria, char* id) {
    this->enderecoMemoria = enderecoMemoria;
    this->id = new char[id_size];
    this->id = id;
    esq = dir = pai = nullptr;
    this->cor = VERMELHO;
}

RedBlackNode::~RedBlackNode() {
    delete[] id;
}

bool RedBlackNode::getCor() const {
    return cor;
}

void RedBlackNode::setCor(bool cor) {
    this->cor = cor;
}

RedBlackNode *RedBlackNode::getEsq() const {
    return esq;
}

void RedBlackNode::setEsq(RedBlackNode *esq) {
    this->esq = esq;
}

RedBlackNode *RedBlackNode::getDir() const {
    return dir;
}

void RedBlackNode::setDir(RedBlackNode *dir) {
    this->dir = dir;
}

RedBlackNode *RedBlackNode::getPai() const {
    return pai;
}

void RedBlackNode::setPai(RedBlackNode *pai) {
    this->pai = pai;
}

double RedBlackNode::getEnderecoMemoria() const {
    return enderecoMemoria;
}

void RedBlackNode::setEnderecoMemoria(double enderecoMemoria) {
    this->enderecoMemoria = enderecoMemoria;
}

char *RedBlackNode::getId() const {
    return id;
}

void RedBlackNode::setId(char *id) {
    this->id = id;
}

