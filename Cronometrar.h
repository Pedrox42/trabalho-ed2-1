//
// Created by pedro on 11/02/2022.
//

#ifndef TRABALHO_ED2_1_CRONOMETRAR_H
#define TRABALHO_ED2_1_CRONOMETRAR_H

#include <iostream>
#include "Review.h"
#include "Hash.h"
#include "Sorts.h"
#include "Process.h"
#include "RedBlackTree.h"
#include "BTree.h"
#include <cmath>
#include <chrono>
#include "Cronometrar.h"

class Cronometrar {

    public:

        static ReviewPtr *reviewList(ifstream *files, int n, ReviewPtr *big_review_list, int reviews);

        static float quickSort(ifstream *files, ReviewPtr *big_review_list, int reviews, int n, int *movimentacoes, int *comparacoes);

        static float heapSort(ifstream *files, ReviewPtr *big_review_list, int reviews, int n, int *movimentacoes, int *comparacoes);

        static float countingSort(ifstream *files, ReviewPtr *big_review_list, int reviews, int n, int *movimentacoes, float *memoria_alocada);

        static float quickSortTeste(ifstream *files, ReviewPtr *big_review_list, int reviews, int n, int *movimentacoes, int *comparacoes, ofstream &output_file);

        static float heapSortTeste(ifstream *files, ReviewPtr *big_review_list, int reviews, int n, int *movimentacoes, int *comparacoes, ofstream &output_file);

        static float countingSortTeste(ifstream *files, ReviewPtr *big_review_list, int reviews, int n, int *movimentacoes, float *memoria_alocada, ofstream &output_file);

        static float hash(ifstream *files, ReviewPtr *big_review_list, int n, int reviews, int m);

        static float hashTeste(ifstream *files, ReviewPtr *big_review_list, int n, int reviews, ofstream &output_file);

        static float insercaoRBT(ifstream *files, RedBlackTree *arv, ReviewPtr *review_list, double *enderecos, int n, int reviews, double *comparacoes_insercao);

        static float insercao_btree(ifstream *files, BTree *arv, ReviewPtr *review_list, double *enderecos, int n, int reviews, double *comparacoes_insercao);

        static float busca_RBT(ifstream *files, RedBlackTree *arv, ReviewPtr *review_list, int n, double *comparacoes_busca, int buscas);

        static float buscaId_RBT(ifstream *files, RedBlackTree *arv, ReviewPtr *review_list, int n, double *comparacoes_busca, char *id);

        static float buscaId_BTree(ifstream *files, BTree *arv, ReviewPtr *review_list, int n, double *comparacoes_busca, char *id);

        static float busca_btree(ifstream *files, BTree *arv, ReviewPtr *review_list, int n, double *comparacoes_busca, int buscas);

        static void rbt(ifstream *files, int n, ReviewPtr *big_review_list, double *enderecos, int reviews);

        static void rbt_teste(ifstream *files, ReviewPtr *big_review_list, double *enderecos, int reviews, string path);

        static void btree_teste(ifstream *files, ReviewPtr *big_review_list, double *enderecos, int reviews, string path);

        static void btree(ifstream *files, int n, ReviewPtr *big_review_list, double *enderecos, int reviews, int b);

        static void rbtBuscaId(ifstream *files, ReviewPtr *big_review_list, double *enderecos, int reviews);

        static void btreeBuscaId(ifstream *files, ReviewPtr *big_review_list, double *enderecos, int reviews);
};


#endif //TRABALHO_ED2_1_CRONOMETRAR_H
