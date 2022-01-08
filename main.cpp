#include <iostream>
#include <fstream>
#include "Review.h"
#include "HashEncadeado.h"
#include "Hash.h"
#include <string.h>
#include "Sorts.h"
#include "Process.h"
#include "RedBlackTree.h"
#include <ctime>
#include <cmath>
#include <chrono>

//definindo como constantes os nomes dos arquivos que serão usados (tanto o csv quanto os binários)
const string csv_name = "tiktok_app_reviews.csv";
const string bin_name = "tiktok_app_reviews.bin";
const string index_name = "index.bin";
const string input_dat_name = "input.txt";
typedef Review* ReviewPtr;


using namespace std::chrono;



int menu(){
    int selecao;

    //menu para que o usuário possa escolher a função na qual ele queira executar no momento
    cout << "MENU" << endl;
    cout << "----" << endl;
    cout << "[1] Ordenacao" << endl;
    cout << "[2] Hash" << endl;
    cout << "[3] Modulo de testes" << endl;
    cout << "[4] Arvore Vermelho-Preto" << endl;
    cout << "[0] Sair" << endl;

    cin >> selecao;

    return selecao;
}

ReviewPtr* cronometrarReviewList(ifstream* files, int n, ReviewPtr *big_review_list, int reviews){

    //variavel para cronometrar o tempo de execucao
    auto start = high_resolution_clock::now();

    ReviewPtr *review_list = Process::importarReviewsRandomicas(big_review_list, reviews, n);

    //cronometrando o tempo de execucao
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    //cout << "Tempo da importacao: " << duration.count() / pow(10, 6) << " seconds" << endl;
    return review_list;
}

float cronometrarQuickSort(ifstream* files, ReviewPtr* big_review_list, int reviews, int n, int* movimentacoes, int* comparacoes){

    ReviewPtr *review_list =  cronometrarReviewList(files, n, big_review_list, reviews);

    auto start = high_resolution_clock::now();

    //chmando função de quicksort

    Sorts::quicksort(review_list, 0, n - 1, movimentacoes, comparacoes);

    //cronometrando o tempo de execucao
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    delete[] review_list;

    return duration.count() / pow(10, 6);
}

float cronometrarHeapSort(ifstream* files, ReviewPtr* big_review_list, int reviews, int n, int* movimentacoes, int* comparacoes){
    ReviewPtr *review_list =  cronometrarReviewList(files, n, big_review_list, reviews);

    auto start = high_resolution_clock::now();

    //chmando função de heapSort
    Sorts::heapSort(review_list, n - 1, movimentacoes, comparacoes);

    //cronometrando o tempo de execucao
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);

    delete[] review_list;

    return duration.count() / pow(10, 6);
}

float cronometrarCountingSort(ifstream* files, ReviewPtr* big_review_list, int reviews, int n, int* movimentacoes, float* memoria_alocada){

    int max = -1;
    ReviewPtr *review_list =  cronometrarReviewList(files, n, big_review_list, reviews);

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

float cronometrarQuickSortTeste(ifstream* files, ReviewPtr* big_review_list, int reviews, int n, int* movimentacoes, int* comparacoes, ofstream& output_file){

    ReviewPtr *review_list =  cronometrarReviewList(files, n, big_review_list, reviews);

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

float cronometrarHeapSortTeste(ifstream* files, ReviewPtr* big_review_list, int reviews, int n, int* movimentacoes, int* comparacoes, ofstream& output_file){
    ReviewPtr *review_list =  cronometrarReviewList(files, n, big_review_list, reviews);

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

float cronometrarCountingSortTeste(ifstream* files, ReviewPtr* big_review_list, int reviews, int n, int* movimentacoes, float* memoria_alocada, ofstream& output_file){

    int max = -1;
    ReviewPtr *review_list =  cronometrarReviewList(files, n, big_review_list, reviews);

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

    output_file << "CountingSort: Array de Reviews ordenada de forma crescente pelos upvotes: " << endl;
    for(int i = 0; i < n; i++){
        output_file << "Review = Upvotes: " << review_list[i]->getUpvotes() << " " << "Id: " << review_list[i]->getReviewId() << endl;
    }
    output_file << endl << endl;

    delete[] review_list;

    return duration.count() / pow(10, 6);
}

float cronometrarHash(ifstream* files, ReviewPtr* big_review_list, int n, int reviews, int m){

    Hash *hashList = new Hash(6000);

    ReviewPtr *review_list =  cronometrarReviewList(files, n, big_review_list, reviews);



    auto start = high_resolution_clock::now();
    //Executando o hash
    for(int i = 0; i < n; i++) {
        hashList->inserir(review_list[i]);
    }

    //cronometrando o tempo de execucao
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
//    cout << "Versoes mais frequentes do app:"<< endl;
    hashList->imprimeMaisFrequentes(m);

    delete[] review_list;
    delete hashList;
    return duration.count() / pow(10, 6);
}

float cronometrarHashTeste(ifstream* files, ReviewPtr* big_review_list, int n, int reviews, ofstream& output_file){

    Hash *hashList = new Hash(6000);

    ReviewPtr *review_list =  cronometrarReviewList(files, n, big_review_list, reviews);



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

float cronometrarRedBlackTree(){

    RedBlackTree* arv = new RedBlackTree();


    auto start = high_resolution_clock::now();
    //inserindo na arv vermelho-preto
    char str1[2] = {'K', '\0'};
    char str2[2] = {'A', '\0'};
    char str3[2] = {'N', '\0'};
    char str4[2] = {'B', '\0'};
    char str5[2] = {'G', '\0'};
    char str6[2] = {'O', '\0'};

    arv->inserir(1, str1);
    arv->inserir(1, str2);
    arv->inserir(1, str3);
    arv->inserir(1, str4);
    arv->inserir(1, str5);
    arv->inserir(1, str6);

    //cronometrando o tempo de execucao
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "imprimindo:" << endl;
    arv->emOrdem();
    //delete[] arv;
    return duration.count() / pow(10, 6);
}

void selecionar(int selecao, ifstream* files, string path){
    int reviews = 0;
    ReviewPtr* big_review_list = Process::importarBinario(files, &reviews);
    switch (selecao) {
        //Sair
        case 0: {
            cout << "Saindo!" << endl;
            exit(0);
            break;
        }

        //ordenacao
        case 1: {
            int n = 0;
            ofstream txt_file;
            txt_file.open((path + "saida.txt"), ios::out | ios::trunc);

            while (files[2] >> n) {
                float mediaTempoQS = 0;
                float mediaTempoHS = 0;
                float mediaTempoCS = 0;

                float mediaComparacoesQS = 0;
                float mediaComparacoesHS = 0;
                float mediaMovimentacoesQS = 0;
                float mediaMovimentacoesHS = 0;
                float mediaMovimentacoesCS = 0;

                float mediaMemoriaAlocadaCS = 0;

                cout << "Iniciando processamentos e importacoes: " << endl;
                for (int i = 0; i < 3; i++) {
                    cout << "Processamento de " << n << " em " << (i+1)*33.33 << "%" << endl;
                    float memoriaAlocadaCS_loop = 0;

                    int comparacoesQS_loop = 0;
                    int comparacoesHS_loop = 0;

                    int movimentacoesQS_loop = 0;
                    int movimentacoesHS_loop = 0;
                    int movimentacoesCS_loop = 0;

                    float tempoQS_loop = cronometrarQuickSort(files, big_review_list, reviews, n, &movimentacoesQS_loop,&comparacoesQS_loop);
                    float tempoHS_loop = cronometrarHeapSort(files, big_review_list, reviews, n, &movimentacoesHS_loop,&comparacoesHS_loop);
                    float tempoCS_loop = cronometrarCountingSort(files, big_review_list, reviews, n, &movimentacoesCS_loop, &memoriaAlocadaCS_loop);

                    mediaTempoQS += tempoQS_loop / 3;
                    mediaTempoHS += tempoHS_loop / 3;
                    mediaTempoCS += tempoCS_loop / 3;

                    mediaComparacoesQS += comparacoesQS_loop / 3;
                    mediaComparacoesHS += comparacoesHS_loop / 3;

                    mediaMovimentacoesQS += movimentacoesQS_loop / 3;
                    mediaMovimentacoesHS += movimentacoesHS_loop / 3;
                    mediaMovimentacoesCS += movimentacoesCS_loop / 3;

                    mediaMemoriaAlocadaCS += memoriaAlocadaCS_loop / 3;

                    txt_file << "#---------------------------------#" << endl;
                    txt_file << "Resultados para N (espaco amostral " << (i+1) << " ): " << n << endl << endl;
                    txt_file << "tempo de execucao: " << endl;
                    txt_file << "QuickSort: " << tempoQS_loop << endl;
                    txt_file << "HeapSort: " << tempoHS_loop << endl;
                    txt_file << "CoutingSort: " << tempoCS_loop << endl << endl;

                    txt_file << "Comparacoes: " << endl;
                    txt_file << "QuickSort: " << comparacoesQS_loop << endl;
                    txt_file << "HeapSort: " << comparacoesHS_loop << endl << endl;

                    txt_file << "Movimentacoes: " << endl;
                    txt_file << "QuickSort: " << movimentacoesQS_loop << endl;
                    txt_file << "HeapSort: " << movimentacoesHS_loop << endl;
                    txt_file << "CoutingSort: " << movimentacoesCS_loop << endl << endl;

                    txt_file << "memoria alocada pelo CountingSort: " << memoriaAlocadaCS_loop / (1024 * 1024)
                             << " MB" << endl << endl;
                    txt_file << "#---------------------------------#" << endl << endl;
                }

                txt_file << "#---------------------------------#" << endl;
                txt_file << "Medias para N: " << n << endl << endl;
                txt_file << "Medias de tempo de execucao: " << endl;
                txt_file << "QuickSort: " << mediaTempoQS << endl;
                txt_file << "HeapSort: " << mediaTempoHS << endl;
                txt_file << "CoutingSort: " << mediaTempoCS << endl << endl;

                txt_file << "Medias de Comparacoes: " << endl;
                txt_file << "QuickSort: " << mediaComparacoesQS << endl;
                txt_file << "HeapSort: " << mediaComparacoesHS << endl << endl;

                txt_file << "Medias de Movimentacoes: " << endl;
                txt_file << "QuickSort: " << mediaMovimentacoesQS << endl;
                txt_file << "HeapSort: " << mediaMovimentacoesHS << endl;
                txt_file << "CoutingSort: " << mediaMovimentacoesCS << endl << endl;

                txt_file << "Media de memoria alocada pelo CountingSort: " << mediaMemoriaAlocadaCS / (1024 * 1024)
                         << " MB" << endl << endl;
                txt_file << "#---------------------------------#" << endl << endl;

            }
            cout << "Processamento concluido, dados savlos em " << path << "input.txt" << endl;
            break;
        }

            //Hash
        case 2: {
            int n = 0;
            cout << "quantas reviews voce deseja ler?" << endl;
            cin >> n;

            int m = 0;
            cout << "Digite quantas versoes do app devem ser impressas:" << endl;
            cin >> m;

            float tempo = cronometrarHash(files, big_review_list,  n, reviews, m);
            cout << "Tempo da execução do hash: " << tempo << " seconds" << endl;

            break;
        }

        //Módulo de teste
        case 3: {
            int n = 100;
            ofstream txt_file;
            txt_file.open((path + "teste.txt"), ios::out | ios::trunc);
            int mediaComparacoesQS = 0;
            int mediaComparacoesHS = 0;
            int mediaMovimentacoesQS = 0;
            int mediaMovimentacoesHS = 0;
            int mediaMovimentacoesCS = 0;

            float mediaMemoriaAlocadaCS = 0;

            cout << "Iniciando processamentos e importacoes: " << endl;

            int mediaTempoQS = cronometrarQuickSortTeste(files, big_review_list, reviews, n, &mediaMovimentacoesQS, &mediaComparacoesQS, txt_file);
            int mediaTempoHS = cronometrarHeapSortTeste(files, big_review_list, reviews, n, &mediaMovimentacoesHS, &mediaComparacoesHS, txt_file);
            int mediaTempoCS = cronometrarCountingSortTeste(files, big_review_list, reviews, n, &mediaMovimentacoesCS, &mediaMemoriaAlocadaCS, txt_file);

            txt_file << "#------------  Ordenacao  ------------#" << endl;
            txt_file << "Medias para N: " << n << endl << endl;
            txt_file << "tempo de execucao: " << endl;
            txt_file << "QuickSort: " << mediaTempoQS << endl;
            txt_file << "HeapSort: " << mediaTempoHS << endl;
            txt_file << "CoutingSort: " << mediaTempoCS << endl << endl;

            txt_file << "Comparacoes: " << endl;
            txt_file << "QuickSort: " << mediaComparacoesQS << endl;
            txt_file << "HeapSort: " << mediaComparacoesHS << endl << endl;

            txt_file << "Movimentacoes: " << endl;
            txt_file << "QuickSort: " << mediaMovimentacoesQS << endl;
            txt_file << "HeapSort: " << mediaMovimentacoesHS << endl;
            txt_file << "CoutingSort: " << mediaMovimentacoesCS << endl << endl;

            txt_file << "memoria alocada pelo CountingSort: " << mediaMemoriaAlocadaCS / (1024 * 1024) << " MB" << endl << endl;
            txt_file << "#-------------------------------------#\"" << endl << endl;

            txt_file << "#------------  Hash  ------------#" << endl;
            int mediaTempoHash = cronometrarHashTeste(files, big_review_list, n, reviews, txt_file);
            txt_file << "Tempo de execucao do hash: " << mediaTempoHash << endl;
            txt_file << "#-------------------------------------#\"" << endl << endl;

            cout << "Processamento concluido, dados savlos em " << path << "teste.txt" << endl;
        }

        case 4:{
            cronometrarRedBlackTree();
            break;
        }
    }

    for(int i = 0; i < reviews; i++){
        delete big_review_list[i];
    }
    delete [] big_review_list;

}

//funcao para continuar apresentando o menu até o usuário digitar 0, o botão de sair do menu
int mainMenu(ifstream* files, string path){
    int selecao = 1;

    while(selecao != 0)
    {
        //system("cls");
        selecao = menu();

        selecionar(selecao, files, path);

    }
    return 0;
}

int main(int argc, char const *argv[]) {
    srand ( time(NULL) );
    //Verifica se todos os parametros do programa foram entrados
    if (argc != 2)
    {
        cout << "Erro! Esperado: ./<program_name> <input_file_path>" << endl;
        return 1;
    }

    ifstream read_files[3];
    read_files[0].open(argv[1] + bin_name, ios::in); //abre o arquivo binario com o conteudo das reviews
    read_files[1].open(argv[1] + index_name, ios::in); //abre o arquivo binario com os indices das reviews
    read_files[2].open(argv[1] + input_dat_name, ios::in); //abre o txt com as encontrado na pasta dos binarios
    if(read_files[0].is_open() && read_files[1].is_open()) //caso tenha sido encontrado algum binario no diretorio informado
    {
        if(read_files[2].is_open()){
            cout << "Arquivos binarios e input.dat econtrados com sucesso!" << endl;
            mainMenu(read_files, argv[1]); //chama o menu
        } else{
            cout << "Erro: arquivo input.dat não encontrado! por favor o insira na pasta: " << argv[1] << endl;
        }
    }else{ //caso nao tenha sido encontrado nenhum arquivo binario na pasta
        read_files[0].close();
        read_files[1].close();
        cout << "Arquivos binarios nao encontrados, procurando csv..." << endl;

        read_files[0].open(argv[1] + csv_name, ios::in); //abre arquivo csv
        if(read_files[0].is_open())
        {
            cout << "Csv econtrado com sucesso!" << endl;
            // Pré-processamento do arquivo csv para binário


            //file 0 = binario
            //file 1 = index
            ofstream write_files[2]; //vetor que armazenará arquivo que possui indices das reviews e arquivo que possui todo o conteúdo das reviews
            write_files[0].open(argv[1] + bin_name,  ios::binary | ios::trunc); //cria arquivo binário que possuirá o conteudo das reviews
            write_files[1].open(argv[1] + index_name, ios::binary | ios::trunc); //cria arquivo binário que possuirá os indices das reviews

            Process::processar(read_files[0], write_files); //chama funcao processar para converter o conteudo do csv para binario

            write_files[0].close(); //fecha arquivos
            write_files[1].close();
            read_files[0].close();

            write_files[0].clear(); //limpa variaveis
            write_files[1].clear();
            read_files[0].clear();

            read_files[0].open(argv[1] + bin_name, ios::binary); //abre os arquivos processados
            read_files[1].open(argv[1] + index_name, ios::binary);

            if(read_files[0].is_open() && read_files[1].is_open()) { //verifica se foi processado corretamente
                mainMenu(read_files, argv[1]); //chama o menu
            } else{ //caso tenha dado algum erro para processar
                cout << "Impossibilitado de abrir o arquivo binario" << endl;
                exit(1);
            }

        }else{ //caso nao tenha como abrir o arquivo csv (em caso de ele nao estar na pasta correta, por exemplo)
            read_files[0].close();
            cout << "Impossibilitado de abrir o arquivo csv" << endl;
            exit(1);
        }

    }

    return 0;

}
