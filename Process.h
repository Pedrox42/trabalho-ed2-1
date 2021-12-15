#ifndef TRABALHO_ED2_1_PROCESS_H
#define TRABALHO_ED2_1_PROCESS_H

#include "Review.h"
#include <fstream>
#include <iostream>

typedef Review* ReviewPtr;

class Process {
    public:

        static ReviewPtr *importarBinario(ifstream *files, int *reviews);

        static void strToData(int *current, char delimiter, char *object, char *buffer, int objectSize);

        static int strToReview(int *current, char *object, char *buffer, int objectSize, int *char_counter);

        static Review *buildReview(char *buffer, int linesize, int *char_counter);

        static void mergeStr(char *s1, char *s2, int t2);

        static bool processar(ifstream &input_file, ofstream *files);

        static void acessaRegistro(ifstream *files);

        static void testeImportacao(ifstream *files, string path);

        static ReviewPtr *importarReviewsRandomicas(ReviewPtr *big_review_list, int reviews, int n);
};


#endif //TRABALHO_ED2_1_PROCESS_H
