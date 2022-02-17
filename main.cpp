#include <iostream>
#include <fstream>
#include "Review.h"
#include "HashEncadeado.h"
#include "Hash.h"
#include <string.h>
#include "Sorts.h"
#include "Process.h"
#include "RedBlackTree.h"
#include "BTreeNode.h"
#include "BTree.h"
#include <ctime>
#include <cmath>
#include <chrono>
#include "HuffmanHeap.h"
#include "Cronometrar.h"

//definindo como constantes os nomes dos arquivos que serão usados (tanto o csv quanto os binários)
const string csv_name = "tiktok_app_reviews.csv";
const string bin_name = "tiktok_app_reviews.bin";
const string index_name = "index.bin";
const string input_dat_name = "input.txt";
const string reviewsComp_name = "reviewsComp.bin";
const string reviewsOrig_name = "reviewsOrig.bin";
const string heap_name = "heap.bin";

typedef Review* ReviewPtr;


using namespace std::chrono;

int menu(){
    int selecao;

    //menu para que o usuário possa escolher a função na qual ele queira executar no momento
    cout << "-------------------" << endl;
    cout << "       MENU" << endl;
    cout << "-------------------" << endl;
    cout << "[1] Arvore Vermelho-Preto" << endl;
    cout << "[2] Arvore B" << endl;
    cout << "[0] Sair" << endl;

    cin >> selecao;

    int compensar=0;

    switch (selecao) {
        case 0: {
            return selecao;
        }
        case 1: {
            cout << "-------------------" << endl;
            cout << "       MENU" << endl;
            cout << "-------------------" << endl;
            cout << "[1] Arvore Vermelho-Preto" << endl;
            cout << "[2] Arvore Vermelho-Preto analises" << endl;
            cout << "[3] Arvore Vermelho-Preto busca por id" << endl;
            cout << "[0] Sair" << endl;
            break;
        }
        case 2: {
            cout << "-------------------" << endl;
            cout << "       MENU" << endl;
            cout << "-------------------" << endl;
            cout << "[1] Arvore B [20]" << endl;
            cout << "[2] Arvore B [200]" << endl;
            cout << "[3] Arvore B analises" << endl;
            cout << "[4] Arvore B busca por id" << endl;
            cout << "[0] Sair" << endl;
            compensar=3;
            break;
        }

    }
    cin >> selecao;

    return selecao == 0 ? 0 : selecao+compensar;
}

HuffmanHeap* configurarHuffman(ReviewPtr* review_list, int n, string path){
    long* todas_frequencias = new long[256];
    long* frequencias_relevantes;
    char* data;
    char* original;
    int size;
    long total_chars = 0;

    for(int i = 0; i < n; i++){
        total_chars += review_list[i]->getReviewSize();
    }

    for(int i = 0; i < 256; i++){
        todas_frequencias[i] = 0;
    }

    original = new char[total_chars];
    long original_counter = 0;
    for(int i = 0; i < n && original_counter < total_chars; i++){
        char* review_text = review_list[i]->getReviewText();
        for(int j = 0; review_text[j] != '\0' && original_counter < total_chars; j++){
            original[original_counter] = review_text[j];
            original_counter++;
            int char_value = review_text[j] + 128;
            todas_frequencias[char_value] += 1;
        }
    }

    size = 0;
    for(int i = 0; i < 256; i++){
        if(todas_frequencias[i] != 0){
            (size)++;
        }
    }

    data = new char[size];
    frequencias_relevantes = new long[size];

    int counter = 0;
    for(int i = 0; i < 256; i++){
        if(todas_frequencias[i] != 0){
            data[counter] = (i-128);
            frequencias_relevantes[counter] = todas_frequencias[i];
            counter++;
        }
    }

    HuffmanHeap* heap = new HuffmanHeap(size*10, size);
    heap->CodigosHuffman(data, frequencias_relevantes);
    bool* compressao = heap->compressaoHuffman(data, frequencias_relevantes, original, total_chars);
    char* traducao = heap->descompressaoHuffman(compressao);

    //0 -> binario para huffman Heap
    //1 -> binario para texto comprimido
    ofstream reviewComp_file;


    //salvando o arquivo comprimido em binario
    reviewComp_file.open(path + reviewsComp_name,  ios::binary | ios::trunc);
    reviewComp_file.write((char*)&compressao, sizeof(compressao));
    reviewComp_file.close();


    delete [] traducao;
//    delete [] compressao;
    delete [] data;
    delete [] todas_frequencias;
    delete [] frequencias_relevantes;
    delete [] original;

    return heap;
}


void selecionar(int selecao, ifstream* files, string path){
    int reviews = Process::getBinReviews(files);
    double* enderecos = new double[reviews];
    ReviewPtr* big_review_list = Process::importarBinario(files, reviews, enderecos);

    switch (selecao) {
        //Sair
        case 0: {
            cout << "Saindo!" << endl;
            exit(0);
            break;
        }

        case 1:{
            int n = 100000;
            ReviewPtr *review_list =  Cronometrar::reviewList(files, n, big_review_list, reviews);

            auto start = high_resolution_clock::now();

            HuffmanHeap* heap = configurarHuffman(review_list, n, path);

            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<microseconds>(stop - start);

            cout << "tempo para criacao da Huffman Tree: " << duration.count() / pow(10, 6) <<  " segundos" << endl;

            cout << "-------------------" << endl;
            cout << "       Reviews comprimidas com sucesso!" << endl;
            cout << "-------------------" << endl;
            cout << "[1] Descomprimir" << endl;
            cout << "[0] Sair" << endl;

            //chmando função de heapSort

            //cronometrando o tempo de execucao

            int input;
            cin >> input;
            if(input){

                ifstream reviewComp_file;
                ofstream reviewOrig_file;

                bool* comprimido = new bool[(int) heap->getTamannhoCompressao()];

                reviewComp_file.open(path + reviewsComp_name, ios::binary);
                reviewComp_file.read((char*)&comprimido, sizeof(comprimido));
                reviewComp_file.close();

                start = high_resolution_clock::now();

                char* traducao = heap->descompressaoHuffman(comprimido);

                stop = high_resolution_clock::now();
                duration = duration_cast<microseconds>(stop - start);

                cout << "tempo para descompressao: " << duration.count() / pow(10, 6) << " segundos" << endl;

                reviewOrig_file.open(path + reviewsOrig_name, ios::binary | ios::trunc);
                reviewOrig_file.write((char*)&traducao, sizeof(char) * ((int)heap->getTamannhoOrignal()+1) );
                reviewOrig_file.close();

                char* teste = new char[(int)heap->getTamannhoOrignal() + 1];

                reviewComp_file.open(path + reviewsOrig_name, ios::binary);
                reviewComp_file.read((char*)&teste, sizeof(teste));
                reviewComp_file.close();

                delete [] teste;
                delete [] comprimido;
            } else{
                exit(1);
            }

            delete [] review_list;
            delete heap;

            break;
        }
        case 2:{

            //setando streams
            ofstream reviewOrig_file;

            //0 -> binario da heap
            //1 -> binario do texto comprimido
            ifstream read_files[2];

            HuffmanHeap* heap;

            //lendo heap do binario
            read_files[0].open(path + heap_name, ios::binary);
            read_files[0].read((char*)&heap, sizeof(heap));
            read_files[0].close();

            cout << "teste" << endl;

            bool* comprimido = new bool[(int) heap->getTamannhoCompressao()];

            cout << "teste2" << endl;

            read_files[0].open(path + reviewsComp_name, ios::binary);
            read_files[0].read((char*)&comprimido, sizeof(comprimido));
            read_files[0].close();

            cout << "teste3" << endl;

            char* original = heap->descompressaoHuffman(comprimido);

            cout << "teste4" << endl;

            cout << original << endl;

            //salvando a heap no arquivo binario
//            write_files[0].open(path + heap_name,  ios::binary | ios::trunc);
//            write_files[0].write((char*)&heap, sizeof(heap));
//            write_files[0].close();

            delete heap;
            delete [] comprimido;
            break;
        }
        case 3:{
            //cronometrarRbtBuscaId(files, big_review_list, enderecos, reviews);
            break;
        }
        case 4:{
            //cronometrarBTree(files, 1000000, big_review_list, enderecos, reviews, 20);
            break;
        }
        case 5:{
            //cronometrarBTree(files, 1000000, big_review_list, enderecos, reviews, 200);
            break;
        }
        case 6:{
            //cronometrarBTree_teste(files, big_review_list, enderecos, reviews, path);
            break;
        }
        case 7:{
            //cronometrarBTreeBuscaId(files, big_review_list, enderecos, reviews);
            break;
        }
    }

    for(int i = 0; i < reviews; i++){
        delete big_review_list[i];
    }
    delete [] big_review_list;
    delete [] enderecos;

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

    ifstream read_files[2];
    read_files[0].open(argv[1] + bin_name, ios::in); //abre o arquivo binario com o conteudo das reviews
    read_files[1].open(argv[1] + index_name, ios::in); //abre o arquivo binario com os indices das reviews
    if(read_files[0].is_open() && read_files[1].is_open()) //caso tenha sido encontrado algum binario no diretorio informado
    {
        cout << "Arquivos binarios encontrados com sucesso!" << endl;
        mainMenu(read_files, argv[1]); //chama o menu

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
