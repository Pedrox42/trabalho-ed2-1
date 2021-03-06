#ifndef TRABALHO_ED2_1_HUFFMANHEAP_H
#define TRABALHO_ED2_1_HUFFMANHEAP_H

#include "HuffmanNode.h"

class HuffmanHeap {
    private:
        long size;
        long charTypes;
        long capacidade;
        HuffmanNode** array;
        HuffmanNode* raiz;
        bool** tabela_codigos;
        int tabela_tamanhos[256];
        double tamanho_compressao;
        double tamanho_original;

    public:
        HuffmanHeap(long capacidade, long size);

        virtual ~HuffmanHeap();

        long getSize();

        void setSize(long size);

        long getCapacity();

        void setCapacity(long capacity);

        HuffmanNode **getArray();

        void setArray(HuffmanNode **array);

        void heapify(int index, int* comparacoes);

        bool conferirTamanhoUm();

        HuffmanNode *extrairMenor(int* comparacoes);

        void inserir(HuffmanNode *node, int* comparacoes);

        void organizar(int* comparacoes);

        void ciarArrayEORganizar(char *data, long *freq, int* comparacoes);

        void comprimir(char *data, long *freq, int* comparacoes);

        void imprimirArray(int *arr, int n);

        void armazenarCodigos(HuffmanNode *node, int* array, int top);

        void CodigosHuffman(char *data, long *freq, int* comparacoes);

        void swapHuffmanNode(HuffmanNode **a, HuffmanNode **b);

        void armazenarArray(int *arr, int n, bool *codigo);

        void calcularTamanhos(char *data, long *freq, long total);

        bool* compressaoHuffman(char *data, long *freq, char *uncompressed, long total);

        double getTamannhoCompressao();

        void setTamanhoCompressao(double tamanho_compressao);

        double getTamannhoOrignal();

        void setTamanhoOriginal(double tamanho_original);

        char* descompressaoHuffman(bool *compressao);
};


#endif //TRABALHO_ED2_1_HUFFMANHEAP_H
