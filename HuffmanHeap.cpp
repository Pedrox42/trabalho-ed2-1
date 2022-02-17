#include "HuffmanHeap.h"
#include <iostream>

using namespace  std;

HuffmanHeap::HuffmanHeap(long capacidade, long size) {
    this->charTypes = size;
    this->size = size;
    this->capacidade = capacidade;
    this->array = new HuffmanNode*[capacidade];
    this->raiz = nullptr;
    this->tabela_codigos = new bool*[256];
    this->tamanho_compressao = 0;
    this->tamanho_original = 0;
}

HuffmanHeap::~HuffmanHeap() {
    for(int i = 0; i < size; i++){
        if(array[i] != nullptr){
            delete array[i];
        }
    }

    delete [] array;
}

double HuffmanHeap::getTamannhoCompressao(){
    return this->tamanho_compressao;
}

void HuffmanHeap::setTamanhoCompressao(double tamanho_compressao){
    this->tamanho_compressao = tamanho_compressao;
}

double HuffmanHeap::getTamannhoOrignal(){
    return this->tamanho_original;
}

void HuffmanHeap::setTamanhoOriginal(double tamanho_original){
    this->tamanho_original = tamanho_original;
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


 void HuffmanHeap::ciarArrayEORganizar(char* data, long* freq) {
    for (int i = 0; i < this->size; ++i){
        this->array[i] = new HuffmanNode(data[i], freq[i]);
    }

    this->organizar();
}


void HuffmanHeap::comprimir(char* data, long* freq) {
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

void HuffmanHeap::armazenarArray(int arr[], int n, bool* codigo)
{
    int i;
    for (i = 0; i < n; ++i){
        codigo[i] = arr[i];
    }
}

void HuffmanHeap::armazenarCodigos(HuffmanNode *node, int* array, int top) {
    if (node->getLeft()) {
        array[top] = 0;
        armazenarCodigos(node->getLeft(), array, top + 1);
    }

    if (node->getRight()) {
        array[top] = 1;
        armazenarCodigos(node->getRight(), array, top + 1);
    }
    if (node->ehFolha()) {

        //transformando para int (range 0-255)
        int char_value = node->getData() + 128;
        this->tabela_codigos[char_value] = new bool[top];
        this->tabela_tamanhos[char_value] = top;
        this->armazenarArray(array, top, this->tabela_codigos[char_value]);
    }
}

void HuffmanHeap::calcularTamanhos(char* data, long* freq, long total){
    this->tamanho_compressao = 0;
    this->tamanho_original = total;
    for(int i = 0; i < this->charTypes; i++){
        int char_value = data[i] + 128;
        this->tamanho_compressao += (this->tabela_tamanhos[char_value] * freq[i]);
    }
}

bool* HuffmanHeap::compressaoHuffman(char* data, long* freq, char* uncompressed, long total){
    this->calcularTamanhos(data, freq, total);
    bool* array_compressao = new bool[(int)this->tamanho_compressao];
    int counter = 0;

    for(int i = 0; i < this->tamanho_original; i++){
        int char_value = uncompressed[i] + 128;
        for(int j = 0; j < this->tabela_tamanhos[char_value]; j++){
            array_compressao[counter] = this->tabela_codigos[char_value][j];
            counter++;
        }
    }

    return array_compressao;
}

char* HuffmanHeap::descompressaoHuffman(bool *compressao) {
    char* traducao = new char[((int) tamanho_original) + 1];
    int contador = 0;
    HuffmanNode* node = this->raiz;

    for (int i=0; i < ((int)this->tamanho_compressao); i++)
    {
        // no folha
        if (node->ehFolha())
        {
           // cout << node->getData();
            traducao[contador] = node->getData();
            contador++;
            node = this->raiz;
        }

        if (compressao[i]){
            node = node->getRight();
        }
        else{
            node = node->getLeft();
        }
    }
    traducao[((int) tamanho_original)] = '\0';

    return traducao;
}

void HuffmanHeap::CodigosHuffman(char* data, long* freq) {
    comprimir(data, freq);
    int array[capacidade], top = 0;
    armazenarCodigos(this->raiz, array, top);
}

