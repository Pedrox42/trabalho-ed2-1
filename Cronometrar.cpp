#include "Cronometrar.h"

using namespace std::chrono;

typedef Review* ReviewPtr;

ReviewPtr* Cronometrar::reviewList(ifstream* files, int n, ReviewPtr *big_review_list, int reviews){

    //variavel para cronometrar o tempo de execucao
    auto start = high_resolution_clock::now();

    ReviewPtr *review_list = Process::importarReviewsRandomicas(big_review_list, reviews, n);

    //cronometrando o tempo de execucao
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    return review_list;
}

float Cronometrar::quickSort(ifstream* files, ReviewPtr* big_review_list, int reviews, int n, int* movimentacoes, int* comparacoes){

    ReviewPtr *review_list =  reviewList(files, n, big_review_list, reviews);

    auto start = high_resolution_clock::now();

    //chmando função de quicksort

    Sorts::quicksort(review_list, 0, n - 1, movimentacoes, comparacoes);

    //cronometrando o tempo de execucao
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    delete[] review_list;

    return duration.count() / pow(10, 6);
}

float Cronometrar::heapSort(ifstream* files, ReviewPtr* big_review_list, int reviews, int n, int* movimentacoes, int* comparacoes){
    ReviewPtr *review_list =  reviewList(files, n, big_review_list, reviews);

    auto start = high_resolution_clock::now();

    //chmando função de heapSort
    Sorts::heapSort(review_list, n - 1, movimentacoes, comparacoes);

    //cronometrando o tempo de execucao
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);

    delete[] review_list;

    return duration.count() / pow(10, 6);
}

float Cronometrar::countingSort(ifstream* files, ReviewPtr* big_review_list, int reviews, int n, int* movimentacoes, float* memoria_alocada){

    int max = -1;
    ReviewPtr *review_list =  reviewList(files, n, big_review_list, reviews);

    for(int i = 0; i < n; i++){
        if(review_list[i]->getUpvotes() > max){
            max = review_list[i]->getUpvotes();
        }
    }

    auto start = high_resolution_clock::now();

//    chamando função de quicksort
    *memoria_alocada = 0;

    Sorts::countingSort(review_list, n, max, movimentacoes, memoria_alocada);

    //cronometrando o tempo de execucao
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);

    delete[] review_list;

    return duration.count() / pow(10, 6);
}

float Cronometrar::quickSortTeste(ifstream* files, ReviewPtr* big_review_list, int reviews, int n, int* movimentacoes, int* comparacoes, ofstream& output_file){

    ReviewPtr *review_list =  reviewList(files, n, big_review_list, reviews);

    auto start = high_resolution_clock::now();

    //chmando função de quicksort

    Sorts::quicksort(review_list, 0, n - 1, movimentacoes, comparacoes);

    //cronometrando o tempo de execucao
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);

    output_file << "Quciksort: Array de Reviews ordenada de forma crescente pelos upvotes: " << endl;
    for(int i = 0; i < n; i++){
        output_file << "Review = Upvotes: " << review_list[i]->getUpvotes() << " " << "Id: " << review_list[i]->getReviewId() << endl;
    }
    output_file << endl << endl;

    delete[] review_list;

    return duration.count() / pow(10, 6);
}

float Cronometrar::heapSortTeste(ifstream* files, ReviewPtr* big_review_list, int reviews, int n, int* movimentacoes, int* comparacoes, ofstream& output_file){
    ReviewPtr *review_list =  reviewList(files, n, big_review_list, reviews);

    auto start = high_resolution_clock::now();

    //chmando função de heapSort
    Sorts::heapSort(review_list, n - 1, movimentacoes, comparacoes);

    //cronometrando o tempo de execucao
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);

    output_file << "HeapSort: Array de Reviews ordenada de forma crescente pelos upvotes: " << endl;
    for(int i = 0; i < n; i++){
        output_file << "Review = Upvotes: " << review_list[i]->getUpvotes() << " " << "Id: " << review_list[i]->getReviewId() << endl;
    }
    output_file << endl << endl;

    delete[] review_list;

    return duration.count() / pow(10, 6);
}

float Cronometrar::countingSortTeste(ifstream* files, ReviewPtr* big_review_list, int reviews, int n, int* movimentacoes, float* memoria_alocada, ofstream& output_file){

    int max = -1;
    ReviewPtr *review_list =  reviewList(files, n, big_review_list, reviews);

    for(int i = 0; i < n; i++){
        if(review_list[i]->getUpvotes() > max){
            max = review_list[i]->getUpvotes();
        }
    }

    auto start = high_resolution_clock::now();

    //chamando função de quicksort
    *memoria_alocada = 0;

    Sorts::countingSort(review_list, n, max, movimentacoes, memoria_alocada);

    //cronometrando o tempo de execucao
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);

    output_file << "CountingSort: Array de Reviews ordenada de forma crescente pelos upvotes: " << endl;
    for(int i = 0; i < n; i++){
        output_file << "Review = Upvotes: " << review_list[i]->getUpvotes() << " " << "Id: " << review_list[i]->getReviewId() << endl;
    }
    output_file << endl << endl;

    delete[] review_list;

    return duration.count() / pow(10, 6);
}

float Cronometrar::hash(ifstream* files, ReviewPtr* big_review_list, int n, int reviews, int m){

    Hash *hashList = new Hash(6000);

    ReviewPtr *review_list =  reviewList(files, n, big_review_list, reviews);



    auto start = high_resolution_clock::now();
    //Executando o hash
    for(int i = 0; i < n; i++) {
        hashList->inserir(review_list[i]);
    }

    //cronometrando o tempo de execucao
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    hashList->imprimeMaisFrequentes(m);

    delete[] review_list;
    delete hashList;
    return duration.count() / pow(10, 6);
}

float Cronometrar::hashTeste(ifstream* files, ReviewPtr* big_review_list, int n, int reviews, ofstream& output_file){

    Hash *hashList = new Hash(6000);

    ReviewPtr *review_list =  reviewList(files, n, big_review_list, reviews);



    auto start = high_resolution_clock::now();
    //Executando o hash
    for(int i = 0; i < n; i++) {
        hashList->inserir(review_list[i]);
    }

    //cronometrando o tempo de execucao
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
//    cout << "Versoes mais frequentes do app:"<< endl;
    hashList->imprimeMaisFrequentesTeste(output_file);

    delete[] review_list;
    delete hashList;
    return duration.count() / pow(10, 6);
}

float Cronometrar::insercaoRBT(ifstream* files, RedBlackTree* arv, ReviewPtr* review_list, double* enderecos, int n, int reviews, double* comparacoes_insercao){
    double* enderecos_list = new double[n];

    auto start = high_resolution_clock::now();
    for(int i = 0; i < n; i++){
        arv->inserir(enderecos_list[i], review_list[i]->getReviewId(), comparacoes_insercao);
    }

    //cronometrando o tempo de execucao
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    //cout << "imprimindo:" << endl;
    //arv->emOrdem();

    delete [] enderecos_list;
    return duration.count() / pow(10, 6);
}

float Cronometrar::insercao_btree(ifstream* files, BTree* arv, ReviewPtr* review_list, double* enderecos, int n, int reviews, double* comparacoes_insercao){
    double* enderecos_list = new double[n];

    auto start = high_resolution_clock::now();
    for(int i = 0; i < n; i++){
        arv->inserir(review_list[i]->getReviewId(), enderecos_list[i], comparacoes_insercao);
    }

    //cronometrando o tempo de execucao
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    //cout << "imprimindo:" << endl;
    //arv->emOrdem();

    delete [] enderecos_list;
    return duration.count() / pow(10, 6);
}

float Cronometrar::busca_RBT(ifstream* files, RedBlackTree* arv, ReviewPtr* review_list, int n, double* comparacoes_busca, int buscas){
    ReviewPtr *search_list =  reviewList(files, buscas, review_list, n);
    auto start = high_resolution_clock::now();

    for(int i = 0; i < buscas; i++){
        arv->buscar(search_list[i]->getReviewId(), comparacoes_busca);
    }

    //cronometrando o tempo de execucao
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);

    delete [] search_list;

    return duration.count() / pow(10, 6);
}

float Cronometrar::buscaId_RBT(ifstream* files, RedBlackTree* arv, ReviewPtr* review_list, int n, double* comparacoes_busca, char* id){
    auto start = high_resolution_clock::now();

    arv->buscar(id, comparacoes_busca);

    //cronometrando o tempo de execucao
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);

    return duration.count() / pow(10, 6);
}

float Cronometrar::buscaId_BTree(ifstream* files, BTree* arv, ReviewPtr* review_list, int n, double* comparacoes_busca, char* id){
    auto start = high_resolution_clock::now();

    arv->buscar(id, comparacoes_busca);

    //cronometrando o tempo de execucao
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);

    return duration.count() / pow(10, 6);
}

float Cronometrar::busca_btree(ifstream* files, BTree* arv, ReviewPtr* review_list, int n, double* comparacoes_busca, int buscas){
    ReviewPtr *search_list =  reviewList(files, buscas, review_list, n);
    auto start = high_resolution_clock::now();

    for(int i = 0; i < buscas; i++){
        arv->buscar(search_list[i]->getReviewId(), comparacoes_busca);
    }

    //cronometrando o tempo de execucao
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);

    delete search_list;
    return duration.count() / pow(10, 6);
}

void Cronometrar::rbt(ifstream* files, int n, ReviewPtr *big_review_list, double* enderecos, int reviews){

    double* enderecos_list = new double[n];
    //variavel para cronometrar o tempo de execucao
    auto start = high_resolution_clock::now();

    ReviewPtr *review_list = Process::importarReviewsRandomicasBalanceadas(big_review_list, enderecos_list, enderecos, reviews, n);


    double insercao_total = 0;
    double busca_total = 0;
    double comparacoes_insercao_total = 0;
    double comparacoes_busca_total = 0;
    for(int i = 0; i < 3; i++){
        RedBlackTree* arv = new RedBlackTree();
        double comparacoes_insercao = 0;
        double comparacoes_busca = 0;
        double tempo_insercao = insercaoRBT(files, arv, review_list, enderecos, n, reviews, &comparacoes_insercao);
        double tempo_busca = busca_RBT(files, arv, review_list, n, &comparacoes_busca, 100);
        cout << "#--------------- Arvore Vermelho-Preto ----------------------#" << endl;
        cout << "tempo de execuacao para insercao de 1000000 registros: " << endl;
        cout << tempo_insercao << " segundos" << endl;
        cout << "comparacoes: " << comparacoes_insercao << endl;
        cout << "tempo de execuacao para busca de 100 registros: " << endl;
        cout << tempo_busca << " segundos" << endl;
        cout << "comparacoes: " << comparacoes_busca << endl;
        cout << "#----------------------------------------------------------#" << endl << endl;
        insercao_total += tempo_insercao;
        busca_total += tempo_busca;
        comparacoes_insercao_total += comparacoes_insercao;
        comparacoes_busca_total += comparacoes_busca;
        delete arv;
    }

    cout << "#--------------- Arvore Vermelho-Preto Medias---------------------#" << endl;
    cout << "tempo de execuacao medio para insercao de 1000000 registros: " << endl;
    cout << insercao_total/3 << " segundos" << endl;
    cout << "media de comparacoes: " << comparacoes_insercao_total/3 << endl;
    cout << "tempo de execuacao medio para busca de 100 registros: " << endl;
    cout << busca_total/3 << " segundos" << endl;
    cout << "media comparacoes: " << comparacoes_busca_total/3 << endl;
    cout << "#----------------------------------------------------------#" << endl << endl;

    delete [] review_list;
    delete [] enderecos_list;

}

void Cronometrar::rbt_teste(ifstream* files, ReviewPtr *big_review_list, double* enderecos, int reviews, string path){
    ofstream txt_file;
    txt_file.open((path + "saida.txt"), ios::out | ios::trunc);

    int n = 0;
    int m = 0;
    cout << "Quantas reviews voce quer importar Para a Arvore Vermelho-Preto?" << endl;
    cin >> n;
    cout << "Quantas reviews voce quer buscar na Arvore Vermelho-Preto?" << endl;
    cin >> m;


    double* enderecos_list = new double[n];
    //variavel para cronometrar o tempo de execucao
    auto start = high_resolution_clock::now();

    ReviewPtr *review_list = Process::importarReviewsRandomicasBalanceadas(big_review_list, enderecos_list, enderecos, reviews, n);


    double insercao_total = 0;
    double busca_total = 0;
    double comparacoes_insercao_total = 0;
    double comparacoes_busca_total = 0;
    for(int i = 0; i < 3; i++){
        RedBlackTree* arv = new RedBlackTree();
        double comparacoes_insercao = 0;
        double comparacoes_busca = 0;
        double tempo_insercao = insercaoRBT(files, arv, review_list, enderecos, n, reviews, &comparacoes_insercao);
        double tempo_busca = busca_RBT(files, arv, review_list, n, &comparacoes_busca, m);
        txt_file << "#--------------- Arvore Vermelho-Preto ----------------------#" << endl;
        txt_file << "tempo de execuacao para insercao de " << n << " registros: " << endl;
        txt_file << tempo_insercao << " segundos" << endl;
        txt_file << "comparacoes: " << comparacoes_insercao << endl;
        txt_file << "tempo de execuacao para busca de " << m << " registros: " << endl;
        txt_file << tempo_busca << " segundos" << endl;
        txt_file << "comparacoes: " << comparacoes_busca << endl;
        txt_file << "#------------------------------------------------------------#" << endl << endl;
        insercao_total += tempo_insercao;
        busca_total += tempo_busca;
        comparacoes_insercao_total += comparacoes_insercao;
        comparacoes_busca_total += comparacoes_busca;
        cout << "Processando..." << endl;
        delete arv;
    }

    txt_file << "#--------------- Arvore Vermelho-Preto Medias---------------------#" << endl;
    txt_file << "tempo de execuacao medio para insercao de " << n << " registros: " << endl;
    txt_file << insercao_total/3 << " segundos" << endl;
    txt_file << "media de comparacoes: " << comparacoes_insercao_total/3 << endl;
    txt_file << "tempo de execuacao medio para busca de " << m << " registros: " << endl;
    txt_file << busca_total/3 << " segundos" << endl;
    txt_file << "media de comparacoes: " << comparacoes_busca_total/3 << endl;
    txt_file << "#-----------------------------------------------------------------#" << endl << endl;

    cout << "Processo concluido com sucesso! Dados salvos no arquivo saida.txt." << endl;

    delete [] review_list;
    delete [] enderecos_list;

}

void Cronometrar::btree_teste(ifstream* files, ReviewPtr *big_review_list, double* enderecos, int reviews, string path){
    ofstream txt_file;
    txt_file.open((path + "saida.txt"), ios::out | ios::trunc);

    int n = 0;
    int m = 0;
    int b = 0;
    cout << "Qual e o numero maximo de filhos da Arvore B?" << endl;
    cin >> b;
    cout << "Quantas reviews voce quer importar Para a Arvore B?" << endl;
    cin >> n;
    cout << "Quantas reviews voce quer buscar na Arvore B?" << endl;
    cin >> m;

    double* enderecos_list = new double[n];

    ReviewPtr *review_list = Process::importarReviewsRandomicasBalanceadas(big_review_list, enderecos_list, enderecos, reviews, n);


    double insercao_total = 0;
    double busca_total = 0;
    double comparacoes_insercao_total = 0;
    double comparacoes_busca_total = 0;
    for(int i = 0; i < 3; i++){
        BTree* arv = new BTree((int)(b+1)/2, b);
        double comparacoes_insercao = 0;
        double comparacoes_busca = 0;
        double tempo_insercao = insercao_btree(files, arv, review_list, enderecos, n, reviews, &comparacoes_insercao);
        double tempo_busca = busca_btree(files, arv, review_list, n, &comparacoes_busca, m);
        txt_file << "#--------------- Arvore B [" << b << "]  ----------------------#" << endl;
        txt_file << "tempo de execuacao para insercao de " << n << " registros: " << endl;
        txt_file << tempo_insercao << " segundos" << endl;
        txt_file << "comparacoes: " << comparacoes_insercao << endl;
        txt_file << "tempo de execuacao para busca de " << m << " registros: " << endl;
        txt_file << tempo_busca << " segundos" << endl;
        txt_file << "comparacoes: " << comparacoes_busca << endl;
        txt_file << "#-------------------------------------------------------------#" << endl << endl;
        insercao_total += tempo_insercao;
        busca_total += tempo_busca;
        comparacoes_insercao_total += comparacoes_insercao;
        comparacoes_busca_total += comparacoes_busca;
        cout << "Processando..." << endl;
        delete arv;
    }

    txt_file << "#--------------- Arvore b [" << b << "] Medias---------------------#" << endl;
    txt_file << "tempo de execuacao medio para insercao de " << n << " registros: " << endl;
    txt_file << insercao_total/3 << " segundos" << endl;
    txt_file << "media de comparacoes: " << comparacoes_insercao_total/3 << endl;
    txt_file << "tempo de execuacao medio para busca de " << m << " registros: " << endl;
    txt_file << busca_total/3 << " segundos" << endl;
    txt_file << "media de comparacoes: " << comparacoes_busca_total/3 << endl;
    txt_file << "#-----------------------------------------------------------------#" << endl << endl;

    cout << "Processo concluido com sucesso! Dados salvos no arquivo saida.txt." << endl;

    delete [] review_list;
    delete [] enderecos_list;

}

void Cronometrar::btree(ifstream* files, int n, ReviewPtr *big_review_list, double* enderecos, int reviews, int b){

    double* enderecos_list = new double[n];
    //variavel para cronometrar o tempo de execucao
    auto start = high_resolution_clock::now();

    ReviewPtr *review_list = Process::importarReviewsRandomicasBalanceadas(big_review_list, enderecos_list, enderecos, reviews, n);

    double insercao_total = 0;
    double busca_total = 0;
    double comparacoes_insercao_total = 0;
    double comparacoes_busca_total = 0;
    for(int i = 0; i < 3; i++){
        BTree* arv = new BTree((int)(b+1)/2, b);
        double comparacoes_insercao = 0;
        double comparacoes_busca = 0;
        double tempo_insercao = insercao_btree(files, arv, review_list, enderecos, n, reviews, &comparacoes_insercao);

        double tempo_busca = busca_btree(files, arv, review_list, n, &comparacoes_busca, 100);

        cout << "#--------------- Arvore B [" << b << "] ----------------------#" << endl;
        cout << "tempo de execuacao para insercao de 1000000 registros: " << endl;
        cout << tempo_insercao << " segundos" << endl;
        cout << "comparacoes: " << comparacoes_insercao << endl;
        cout << "tempo de execuacao para busca de 100 registros: " << endl;
        cout << tempo_busca << " segundos" << endl;
        cout << "comparacoes: " << comparacoes_busca << endl;
        cout << "#----------------------------------------------------------#" << endl << endl;
        insercao_total += tempo_insercao;
        busca_total += tempo_busca;
        comparacoes_insercao_total += comparacoes_insercao;
        comparacoes_busca_total += comparacoes_busca;
        delete arv;
    }

    cout << "#--------------- Arvore B [" << b << "] Medias---------------------#" << endl;
    cout << "tempo de execuacao medio para insercao de 1000000 registros: " << endl;
    cout << insercao_total/3 << " segundos" << endl;
    cout << "media de comparacoes: " << comparacoes_insercao_total/3 << endl;
    cout << "tempo de execuacao medio para busca de 100 registros: " << endl;
    cout << busca_total/3 << " segundos" << endl;
    cout << "media comparacoes: " << comparacoes_busca_total/3 << endl;
    cout << "#----------------------------------------------------------#" << endl << endl;

    delete [] review_list;
    delete [] enderecos_list;

}

void Cronometrar::rbtBuscaId(ifstream* files, ReviewPtr *big_review_list, double* enderecos, int reviews){
    int n;
    char* id = new char[90];
    cout << "Quantas reviews voce deseja importar para a Arvore Vermelho-Preto?" << endl;
    cin >> n;
    cout << "Digite o id que deseja procurar: " << endl;
    cin >> id;
    double* enderecos_list = new double[n];

    ReviewPtr *review_list = Process::importarReviewsRandomicasBalanceadas(big_review_list, enderecos_list, enderecos, reviews, n);

    RedBlackTree* arv = new RedBlackTree();

    double comparacoes_insercao = 0;
    double comparacoes_busca = 0;
    double tempo_insercao = insercaoRBT(files, arv, review_list, enderecos, n, reviews, &comparacoes_insercao);
    double tempo_busca = buscaId_RBT(files, arv, review_list, n, &comparacoes_busca, id);
    cout << "#--------------- Arvore Vermelho-Preto ----------------------#" << endl;
    cout << "tempo de execuacao para insercao de " << n << " registros: " << endl;
    cout << tempo_insercao << " segundos" << endl;
    cout << "comparacoes: " << comparacoes_insercao << endl;
    cout << "tempo de execuacao para busca do id: " << id << " registros: " << endl;
    cout << tempo_busca << " segundos" << endl;
    cout << "comparacoes: " << comparacoes_busca << endl;
    cout << "#------------------------------------------------------------#" << endl << endl;

    delete [] review_list;
    delete [] enderecos_list;
    delete [] id;
}

void Cronometrar::btreeBuscaId(ifstream* files, ReviewPtr *big_review_list, double* enderecos, int reviews){
    int n;
    int b;
    char* id = new char[90];
    cout << "Digite numero de filhos maximo de B: " << endl;
    cin >> b;
    cout << "Quantas reviews voce deseja importar para a Arvore B?" << endl;
    cin >> n;
    cout << "Digite o id que deseja procurar: " << endl;
    cin >> id;

    double* enderecos_list = new double[n];

    ReviewPtr *review_list = Process::importarReviewsRandomicasBalanceadas(big_review_list, enderecos_list, enderecos, reviews, n);

    BTree* arv = new BTree((int)(b+1)/2, b);

    double comparacoes_insercao = 0;
    double comparacoes_busca = 0;
    double tempo_insercao = insercao_btree(files, arv, review_list, enderecos, n, reviews, &comparacoes_insercao);
    double tempo_busca = buscaId_BTree(files, arv, review_list, n, &comparacoes_busca, id);
    cout << "#--------------- Arvore Vermelho-Preto ----------------------#" << endl;
    cout << "tempo de execuacao para insercao de " << n << " registros: " << endl;
    cout << tempo_insercao << " segundos" << endl;
    cout << "comparacoes: " << comparacoes_insercao << endl;
    cout << "tempo de execuacao para busca do id: " << id << " registros: " << endl;
    cout << tempo_busca << " segundos" << endl;
    cout << "comparacoes: " << comparacoes_busca << endl;
    cout << "#------------------------------------------------------------#" << endl << endl;

    delete arv;
    delete [] review_list;
    delete [] enderecos_list;
    delete [] id;
}