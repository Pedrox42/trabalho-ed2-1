#include <iostream>
#include "Sorts.h"
using namespace std;

int Sorts::heapLeft(int i){
    return i*2;
}

int Sorts::heapRight(int i){
    return (i*2)+1;
}

int Sorts::heapParent(int i){
    return i/2;
}


//algoritmos de sort
void Sorts::maxHeapify(ReviewPtr* review_list, int i, int n, int* movimentacao, int* comparacoes){
    int l = heapLeft(i);
    int r = heapRight(i);
    int m = i;

    (*comparacoes) += 2;

    if(l <= n && review_list[l]->getUpvotes() > review_list[i]->getUpvotes()){
        m = l;
    }

    if(r <= n && review_list[r]->getUpvotes() > review_list[m]->getUpvotes()){
        m = r;
    }

    if(m != i){
        (*movimentacao)++;
        swap(review_list[i], review_list[m]);
        maxHeapify(review_list, m, n, movimentacao, comparacoes);
    }
}

void Sorts::buildMaxHeap(ReviewPtr* review_list, int n, int* movimentacao, int* comparacoes){
    for(int i = n/2; i >= 0; i--){
        maxHeapify(review_list, i, n, movimentacao, comparacoes);
    }
}

void Sorts::heapSort(ReviewPtr* review_list, int n, int* movimentacao, int* comparacoes){
    buildMaxHeap(review_list, n, movimentacao, comparacoes);
    for(int i = n; i > 0; i--){
        swap(review_list[0], review_list[i]);
        maxHeapify(review_list, 0, i-1, movimentacao, comparacoes);
    }
}

int Sorts::medianaDeTres(ReviewPtr* review_list, int a, int b, int c) {
    if ( (review_list[a]->getUpvotes() > review_list[b]->getUpvotes()) ^ (review_list[a]->getUpvotes() > review_list[c]->getUpvotes()) )
        return a;
    else if ( (review_list[b]->getUpvotes() < review_list[a]->getUpvotes()) ^ (review_list[b]->getUpvotes() < review_list[c]->getUpvotes()) )
        return b;
    else
        return c;
}

int Sorts::particionamento(ReviewPtr* review_list, int p, int q, int* movimentacao, int* comparacoes){
    //declaraçoes das variaveis com pivo sendo o ponto mais a direita

    int pivo = medianaDeTres(review_list, p, int((p+q)/2), q );
    int i = p;
    int j = q;

    (*movimentacao)++;
    swap(review_list[pivo], review_list[q]);
    pivo = q;

    //loop principal de comparacoes
    do {
        //levando em conta as comparacoes que serão falsas
        (*comparacoes) += 2;
        while(review_list[i]->getUpvotes() < review_list[pivo]->getUpvotes()) { i++; (*comparacoes)++; }
        while(review_list[j]->getUpvotes() > review_list[pivo]->getUpvotes()) { j--; (*comparacoes)++; }
        if(i <= j){
            //fazendo a troca das posicoes
            swap(review_list[i], review_list[j]);
            (*movimentacao)++;
            i++;
            j--;
        }
    } while(i <= j);

    return j;
}

void Sorts::quicksort(ReviewPtr* review_list, int p, int r, int* movimentacao, int* comparacoes){
    //caso os valores recebidos sejam invalidos ou iguais
    if(p < r){
        //recebendo o pivo
        int q = particionamento(review_list, p, r, movimentacao, comparacoes);

        //aplicando quicksort nos vetores resultantes
        quicksort(review_list, p, q, movimentacao, comparacoes);
        quicksort(review_list, q+1, r, movimentacao, comparacoes);
    }
}

void Sorts::countingSort(ReviewPtr review_list[], int n, int max, int *movimentacao, float *memoria_alocada)
{
    //Array para guardar a lista reordenada
    ReviewPtr* output = new ReviewPtr[n];

    //Cria para fazer a contagem usada no algoritimo
    int lastIndex = max + 1;
    int *count = new int[lastIndex];
    //Instancia todos os valors como 0
    for(int i = 0; i < lastIndex; i++){
        count[i] = 0;
    }
    //Laço para guardar a contagem total de cada um dos upvotes no indice correspondente
    for (int i = 0; i < n; i++) {
        count[review_list[i]->getUpvotes()]++;
    }
    //Corrige o valor do vetor de count para o indice no vetor output
    for (int i = 1; i < lastIndex; i++) {
        count[i] += count[i - 1];
    }
    //Coloca os valores nas posicoes corretas do vetor output
    for (int i = 0; i < n; i++) {
        output[count[review_list[i]->getUpvotes()] - 1] = review_list[i];
        (*movimentacao)++;
        count[review_list[i]->getUpvotes()]--;
    }
    //Copia o vetor output ja ordenado para o vetor review_list
    for (int i = 0; i < n; i++) {
        review_list[i] = output[i];
        (*movimentacao)++;
    }

    delete [] output;

    (*memoria_alocada) = (lastIndex) * (sizeof(int)) + (n * sizeof(ReviewPtr));
}
