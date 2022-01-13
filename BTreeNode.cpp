#include "BTreeNode.h"
#include <iostream>

using namespace std;

BTreeNode::BTreeNode(int grau, bool folha, int tamanho){
    this->grau = grau;
    this->folha = folha;
    this->n = 0;
    this->tamanho = tamanho;
}

int BTreeNode::getGrau() {
    return this->grau;
}

void BTreeNode::setGrau(int grau) {
    this->grau = grau;
}

BTreeNode** BTreeNode::getChaves() {
    return this->chaves;
}

void BTreeNode::setChaves(BTreeNode **chaves) {
    *this->chaves = *chaves;
}

int BTreeNode::getN() {
    return this->n;
}

void BTreeNode::setN(int n) {
    this->n = n;
}

bool BTreeNode::isFolha() {
    return this->folha;
}

void BTreeNode::setFolha(bool folha) {
    this->folha = folha;
}

int BTreeNode::getTamanho(){
    return this->tamanho;
}

void BTreeNode::setTamanho(int tamanho) {
    this->tamanho = tamanho;
}

bool BTreeNode::compararId(char* id1, char* id2){
    int i = 0;
//    cout << "teste" << endl;
    for(i = 0; id1[i] != '\0' && id1[i] == id2[i]; i++);
//    cout << (id1[i] > id2[i]) << endl;
    return id1[i] > id2[i];
}

bool BTreeNode::idIgual(char* id1, char* id2){
    int i = 0;
//    cout << "teste" << endl;
    for(i = 0; id1[i] != '\0' && id1[i] == id2[i]; i++);
//    cout << (id1[i] > id2[i]) << endl;
    return id1[i] == id2[i];
}


// Function to search key k in subtree rooted with this node
BTreeNode *BTreeNode::buscar(char* id)
{
    // Find the first key greater than or equal to k
    int i = 0;
    while (i < n && compararId(id, valores[i]))
        i++;

    // If the found key is equal to k, return this node
    if (idIgual(id, valores[i]))
        return this;

    // If key is not found here and this is a leaf node
    if (folha)
        return nullptr;

    // Go to the appropriate child
    return chaves[i]->buscar(id);
}

void BTreeNode::inserirNaoCompleto(char* id)
{
    // Initialize index as index of rightmost element
    int i = n-1;

    // If this is a leaf node
    if (folha && n < tamanho)
    {
        // The following loop does two things
        // a) Finds the location of new key to be inserted
        // b) Moves all greater keys to one place ahead
        while (i >= 0 && compararId(valores[i], id))
        {
            *valores[i+1] = *valores[i];
            i--;
        }

        // Insert the new key at found location
        *valores[i+1] = *id;
        n++;
    }
    else // If this node is not leaf
    {
        // Find the child which is going to have the new key
        while (i >= 0 && compararId(valores[i], id))
            i--;

        // See if the found child is full
        if (chaves[i+1]->getN() == tamanho)
        {
            // If the child is full, then split it
            splitFilho(i+1, chaves[i+1]);

            // After split, the middle key of C[i] goes up and
            // C[i] is splitted into two.  See which of the two
            // is going to have the new key
            if (compararId(id, valores[i+1]))
                i++;
        }
        chaves[i+1]->inserirNaoCompleto(id);
    }
}

// A utility function to split the child y of this node
// Note that y must be full when this function is called
void BTreeNode::splitFilho(int i, BTreeNode *y)
{
    // Create a new node which is going to store (t-1) keys
    // of y
    BTreeNode *z = new BTreeNode(y->grau, y->folha, y->tamanho);
    z->n = grau - 1;

    // Copy the last (t-1) keys of y to z
    for (int j = 0; j < grau-1 && j+grau < tamanho; j++)
        *z->valores[j] = *y->valores[j+grau];

    // Copy the last t children of y to z
    if (!y->folha)
    {
        for (int j = 0; j < grau; j++)
            *z->chaves[j] = *y->chaves[j+grau];
    }

    // Reduce the number of keys in y
    y->n = grau - 1;

    // Since this node is going to have a new child,
    // create space of new child
    for (int j = n; j >= i+1; j--)
        chaves[j+1] = chaves[j];

    // Link the new child to this node
    *chaves[i+1] = *z;

    // A key of y will move to this node. Find the location of
    // new key and move all greater keys one space ahead
    for (int j = n-1; j >= i; j--)
        *valores[j+1] = *valores[j];

    // Copy the middle key of y to this node
    *valores[i] = *y->valores[grau-1];

    // Increment count of keys in this node
    n = n + 1;
}

// Function to traverse all nodes in a subtree rooted with this node
void BTreeNode::navegar()
{
    // There are n keys and n+1 children, traverse through n keys
    // and first n children
    int i;
    for (i = 0; i < n; i++)
    {
        // If this is not leaf, then before printing key[i],
        // traverse the subtree rooted with child C[i].
        if (!folha)
            chaves[i]->navegar();
        cout << " " << valores[i];
    }

    // Print the subtree rooted with last child
    if (!folha)
        chaves[i]->navegar();
}