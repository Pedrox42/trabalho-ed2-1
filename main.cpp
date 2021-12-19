#include <iostream>
#include <fstream>
#include "Review.h"
#include "HashEncadeado.h"
#include "Hash.h"
#include <string.h>
#include "Sorts.h"
#include "Process.h"
#include <ctime>
#include <cmath>
#include <chrono>

//definindo como constantes os nomes dos arquivos que serão usados (tanto o csv quanto os binários)
const string csv_name = "tiktok_app_reviews.csv";
const string bin_name = "tiktok_app_reviews.bin";
const string index_name = "index.bin";
typedef Review* ReviewPtr;


using namespace std::chrono;



int menu(){
    int selecao;

    //menu para que o usuário possa escolher a função na qual ele queira executar no momento
    cout << "MENU" << endl;
    cout << "----" << endl;
    cout << "[1] acessaRegistro(i)" << endl;
    cout << "[2] testeImportacao()" << endl;
    cout << "[3] quicksort" << endl;
    cout << "[4] heapSort" << endl;
    cout << "[5] countingSort" << endl;
    cout << "[6] Hash" << endl;
    cout << "[0] Sair" << endl;

    cin >> selecao;

    return selecao;
}

ReviewPtr* cronometrarReviewList(ifstream* files, int* n, ReviewPtr *big_review_list, int reviews){
    cout << "Numero de reviews desejada para importacao: " << endl;
    cin >> *n;

    //variavel para cronometrar o tempo de execucao
    auto start = high_resolution_clock::now();

    ReviewPtr *review_list = Process::importarReviewsRandomicas(big_review_list, reviews, *n);

    //cronometrando o tempo de execucao
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Tempo da importação: " << duration.count() / pow(10, 6) << " seconds" << endl;
    return review_list;
}

void cronometrarQuickSort(ReviewPtr* review_list, int n){
    auto start = high_resolution_clock::now();

    //chmando função de quicksort
    int movimentacoes = 0;
    int comparacoes = 0;

    Sorts::quicksort(review_list, 0, n - 1, &movimentacoes, &comparacoes);

    //cronometrando o tempo de execucao
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Tempo da execução do quicksort: " << duration.count() / pow(10, 6) << " seconds" << endl;
    cout << "movimentacoes " << movimentacoes << endl;
    cout << "comparacoes " << comparacoes << endl;
}

void cronometrarHeapSort(ReviewPtr* review_list, int n){
    auto start = high_resolution_clock::now();

    //chmando função de heapSort
    int movimentacoes = 0;
    int comparacoes = 0;

    Sorts::heapSort(review_list, n - 1, &movimentacoes, &comparacoes);

    //cronometrando o tempo de execucao
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Tempo da execução do heapSort: " << duration.count() / pow(10, 6) << " seconds" << endl;
    cout << "movimentacoes " << movimentacoes << endl;
    cout << "comparacoes " << comparacoes << endl;
}

void cronometrarCountingSort(ReviewPtr* review_list, int n, int max){
    auto start = high_resolution_clock::now();

//    chmando função de quicksort
    int movimentacoes = 0;
    int comparacoes = 0;
    float memoria_alocada = 0;

    Sorts::countingSort(review_list, n, max, &movimentacoes, &memoria_alocada);

    //cronometrando o tempo de execucao
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Tempo da execução do countingSort: " << duration.count() / pow(10, 6) << " seconds" << endl;
    cout << "movimentacoes " << movimentacoes << endl;
    cout << "comparacoes " << comparacoes << endl;
    cout << "memoria adicional alocada " << memoria_alocada/(1024*1024) << " MB" << endl;
}

void cronometrarHash(Hash *hashList, ReviewPtr *review_list, int n){

    int m = 0;
    cout << "Digite quantas versoes do app devem ser impressas:" << endl;
    cin >> m;

    auto start = high_resolution_clock::now();
    //Executando o hash
    for(int i = 0; i < n; i++) {
        hashList->inserir(review_list[i]);
    }

    //cronometrando o tempo de execucao
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Tempo da execução do hash: " << duration.count() / pow(10, 6) << " seconds" << endl;
//    cout << "Versoes mais frequentes do app:"<< endl;
    hashList->imprimeMaisFrequentes(m);
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
            //acessa diretamente o i-ésimo registro do arquivo binário e o imprime na tela. O valor de i deve ser fornecido pelo usuário.
        case 1: {
            Process::acessaRegistro(files);
            break;
        }
//        Note que a função testeImportacao() é apenas uma função de teste.
//         O programa deve ser capaz de importar registros do arquivo para quaisquer valores de N, sem erros e sem gerar exceções.
        case 2: {
            Process::testeImportacao(files, path);
            break;
        }

        case 3: {

            int n = 0;

            ReviewPtr *review_list =  cronometrarReviewList(files, &n, big_review_list, reviews);

            cronometrarQuickSort(review_list, n);

            delete[] review_list;

            break;
        }

        case 4: {

            int n = 0;

            ReviewPtr *review_list =  cronometrarReviewList(files, &n, big_review_list, reviews);

            cronometrarHeapSort(review_list, n);

            delete[] review_list;

            break;

        }

        case 5: {

            int n = 0, max = -1;

            ReviewPtr *review_list =  cronometrarReviewList(files, &n, big_review_list, reviews);

            for(int i = 0; i < n; i++){
                if(review_list[i]->getUpvotes() > max){
                    max = review_list[i]->getUpvotes();
                }
            }

            cronometrarCountingSort(review_list, n, max);

            delete[] review_list;

            break;

        }
        case 6: {
            Hash *hashList = new Hash(6000);

            int n = 0;

            ReviewPtr *review_list =  cronometrarReviewList(files, &n, big_review_list, reviews);

            cronometrarHash(hashList, review_list, n);

            delete[] review_list;
            delete hashList;

            break;
        }
    }

    cout << "deletei!" << endl;
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

    ifstream read_files[2];
    read_files[0].open(argv[1] + bin_name, ios::in); //abre o arquivo binario com o conteudo das reviews
    read_files[1].open(argv[1] + index_name, ios::in); //abre o arquivo binario com os indices das reviews
    if(read_files[0].is_open() && read_files[1].is_open()) //caso tenha sido encontrado algum binario no diretorio informado
    {
        cout << "Arquivos binarios econtrados com sucesso!" << endl;
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
