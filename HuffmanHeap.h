#ifndef TRABALHO_ED2_1_HUFFMANHEAP_H
#define TRABALHO_ED2_1_HUFFMANHEAP_H

#include "HuffmanNode.h"

class HuffmanHeap {
    private:
        long size;
        long capacidade;
        HuffmanNode** array;
        HuffmanNode* raiz;

    public:
        HuffmanHeap(long capacidade, long size);

        virtual ~HuffmanHeap();

        long getSize();

        void setSize(long size);

        long getCapacity();

        void setCapacity(long capacity);

        HuffmanNode **getArray();

        void setArray(HuffmanNode **array);

        void heapify(int index);

        bool conferirTamanhoUm();

        HuffmanNode *extrairMenor();

        void inserir(HuffmanNode *node);

        void organizar();

        void ciarArrayEORganizar(char *data, int *freq);

        void comprimir(char *data, int *freq);

        void imprimirArray(int *arr, int n);

        void imprimirCodigos(HuffmanNode *node, int* array, int top);

        void CodigosHuffman(char *data, int *freq);

    void swapHuffmanNode(HuffmanNode **a, HuffmanNode **b);
};


#endif //TRABALHO_ED2_1_HUFFMANHEAP_H
