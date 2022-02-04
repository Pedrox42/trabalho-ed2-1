#include "HuffmanHeap.h"
#include <iostream>

using namespace  std;

HuffmanHeap::HuffmanHeap(long capacidade) {
    this->size = 0;
    this->capacidade = capacidade;
    this->array = new HuffmanNode*[capacidade];
    raiz = nullptr;
}

HuffmanHeap::~HuffmanHeap() {
    for(int i = 0; i < size; i++){
        if(array[i] != nullptr){
            delete array[i];
        }
    }

    delete [] array;
}

long HuffmanHeap::getSize() {
    return size;
}

void HuffmanHeap::setSize(long size) {
    HuffmanHeap::size = size;
}

long HuffmanHeap::getCapacity() {
    return capacidade;
}

void HuffmanHeap::setCapacity(long capacidade) {
    HuffmanHeap::capacidade = capacidade;
}

// Swap function
void HuffmanHeap::swapHuffmanNode(HuffmanNode **a, HuffmanNode **b) {
    HuffmanNode* t = *a;
    *a = *b;
    *b = t;
}

void HuffmanHeap::heapify(int index) {
    int smallest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < this->size && this->array[left]->getFreq() < this->array[smallest]->getFreq()){
        smallest = left;
    }

    if (right < this->size && this->array[right]->getFreq() < this->array[smallest]->getFreq()){
        smallest = right;
    }

    if (smallest != index) {
        swapHuffmanNode(&this->array[smallest], &this->array[index]);
        heapify(smallest);
    }
}

bool HuffmanHeap::conferirTamanhoUm() {
    return this->size == 1;
}

HuffmanNode* HuffmanHeap::extrairMenor() {
    HuffmanNode *temp = this->array[0];
    this->array[0] = this->array[this->size - 1];

    this->size--;
    heapify(0);

    return temp;
}

// Insertion
void HuffmanHeap::inserir(HuffmanNode *node) {
    this->size++;
    int i = this->size - 1;

    while (i && node->getFreq() < this->array[(i - 1) / 2]->getFreq()) {
        this->array[i] = this->array[(i - 1) / 2];
        i = (i - 1) / 2;
    }

    this->array[i] = node;
}

// BUild min heap
void HuffmanHeap::organizar() {
    int n = this->size - 1;
    int i;

    for (i = (n - 1) / 2; i >= 0; --i){
        heapify(i);
    }
}


 void HuffmanHeap::ciarArrayEORganizar(char* data, int* freq) {
    for (int i = 0; i < this->size; ++i){
        this->array[i] = new HuffmanNode(data[i], freq[i]);
    }

    this->organizar();
}


void HuffmanHeap::comprimir(char* data, int* freq) {
    HuffmanNode *left, *right, *top;
    ciarArrayEORganizar(data, freq);

    while (!conferirTamanhoUm()) {
        left = extrairMenor();
        right = extrairMenor();

        top = new HuffmanNode('\0', left->getFreq() + right->getFreq());

        top->setLeft(left);
        top->setRight(right);

        inserir(top);
    }

    raiz = extrairMenor();
}

void HuffmanHeap::imprimirArray(int arr[], int n)
{
    int i;
    for (i = 0; i < n; ++i){
        cout << arr[i];
    }

    cout << "\n";
}

void HuffmanHeap::imprimirCodigos(HuffmanNode *node, int* array, int top) {
    if (node->getLeft()) {
        array[top] = 0;
        imprimirCodigos(node->getLeft(), array, top + 1);
    }

    if (node->getRight()) {
        array[top] = 1;
        imprimirCodigos(node->getRight(), array, top + 1);
    }
    if (node->ehFolha()) {
        cout << node->getData() << "  | ";
        this->imprimirArray(array, top);
    }
}

void HuffmanHeap::CodigosHuffman(char* data, int* freq) {
    comprimir(data, freq);
    int array[capacidade], top = 0;
    imprimirCodigos(raiz, array, top);
}

