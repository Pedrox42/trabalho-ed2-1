#ifndef TRABALHO_ED2_1_SORTS_H
#define TRABALHO_ED2_1_SORTS_H

#include "Review.h"

typedef Review* ReviewPtr;

class Sorts {

public:
    static int heapLeft(int i);

    static int heapRight(int i);

    static int heapParent(int i);

    static void maxHeapify(ReviewPtr *review_list, int i, int n, int *movimentacao, int *comparacoes);

    static void buildMaxHeap(ReviewPtr *review_list, int n, int *movimentacao, int *comparacoes);

    static void heapSort(ReviewPtr *review_list, int n, int *movimentacao, int *comparacoes);

    static int medianaDeTres(ReviewPtr *review_list, int a, int b, int c);

    static int particionamento(ReviewPtr *review_list, int p, int q, int *movimentacao, int *comparacoes);

    static void quicksort(ReviewPtr *review_list, int p, int r, int *movimentacao, int *comparacoes);

private:
};


#endif //TRABALHO_ED2_1_SORTS_H
