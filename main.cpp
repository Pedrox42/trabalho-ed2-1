#include <iostream>
#include <fstream>
#include "Review.h"
#include <string.h>

int menu(){
    int selecao;

    cout << "MENU" << endl;
    cout << "----" << endl;
    cout << "[1] acessaRegistro(i)" << endl;
    cout << "[2] importaRegistro(n)" << endl;
    cout << "[3] testeImportacao()" << endl;
    cout << "[0] Sair" << endl;

    cin >> selecao;

    return selecao;
}

void selecionar(int selecao, ifstream& input_file){

    switch (selecao)
    {
        //Sair
        case 0:
        {
            cout << "Saindo!" << endl;
            exit(0);
            break;
        }
        //acessa diretamente o i-ésimo registro do arquivo binário e o imprime na tela. O valor de i deve ser fornecido pelo usuário.
        case 1:
        {

        }
        //Note que a função testeImportacao() é apenas uma função de teste.
        // O programa deve ser capaz de importar registros do arquivo para quaisquer valores de N, sem erros e sem gerar exceções.
        case 2:
        {

        }
        //importa N registros aleatórios do arquivo binário. Para essa importação, a função deve perguntar ao usuário
        // se ele deseja exibir a saída no console ou salvá-la em um arquivo. Se a opção for a saída em console, deve-se utilizar N = 10.
        // Para a saída em arquivo, utilize N = 100
        case 3:
        {

        }
    }
}

int mainMenu(ifstream& input_file){
    int selecao = 1;

    while(selecao != 0)
    {
        //system("cls");
        selecao = menu();

        selecionar(selecao, input_file);


    }
    return 0;
}


void strToData(int* current, char delimiter, char* object, char* buffer, int objectSize){
    int i = 0;
    for(i = 0; i < objectSize && buffer[*current] != '\0' && buffer[*current] != '\n' && buffer[*current] != delimiter; i++){
        object[i] = buffer[*current];
        (*current)++;
    }
    object[i] = '\0';

    (*current)++;
}

void strToReview(int* current, char* object, char* buffer, int objectSize){
    int i = 0;
    int lastQuotations = *current;
    int lastQuotationsObject = 0;
    bool check = false;
    char delimiter = ',';

    if(buffer[*current] == '"'){
        check = true;
        delimiter = '\n';
    }

    for(i = 0; i < objectSize && buffer[*current] != '\0' && buffer[*current] != '\n' && buffer[*current] != delimiter; i++){
        object[i] = buffer[*current];

        if(check && buffer[*current] == '"'){
            lastQuotations = (*current);
            lastQuotationsObject = i;
        }

        (*current)++;

    }

    if(check){
        object[lastQuotationsObject] = '\0';
        (*current) = lastQuotations+1;
    }
    (*current)++;
}

Review* buildReview(char* buffer)
{
    char* id = new char[89];
    char* review_text = new char[3500];
    char* upvotes = new char[10];
    char* app_version = new char[20];
    char* posted_date = new char[20];

    char delimiter = ',';
    int current = 0;


    strToData(&current, delimiter, id, buffer, 89);
    strToReview(&current, review_text, buffer, 3500);
    strToData(&current, delimiter, upvotes, buffer, 10);
    strToData(&current, delimiter, app_version, buffer, 20);
    strToData(&current, delimiter, posted_date, buffer, 20);

//    cout << "ERRO DE review_text: " << review_text << endl;
//    cout << "ERRO DE upvotes: " << upvotes << endl;
//    cout << "ERRO DE app_version: " << app_version << endl;
//    cout << "ERRO DE posted_date: " << posted_date << endl;

    Review *review;

    try{
        review = new Review(id, review_text, app_version, posted_date, stoi(upvotes));

    } catch (...){
        review = nullptr;
        cout << "Erro de stoi: id da linha: " << id << endl;
    }

    delete [] id;
    delete [] review_text;
    delete [] app_version;
    delete [] posted_date;
    delete [] upvotes;

    return review;
}



bool processar(ifstream& input_file){

    constexpr size_t bufferSize = 1024*1024*6; //equivalente a 5mb de memoria
    int const linesize = 3500;
    constexpr size_t readBufferSize = bufferSize - linesize;
    char* table_head = new char[100];


    input_file.getline(table_head, linesize, '\n');
    int counter = 0;
    Review* review_list[100000];


    while (input_file)
    {


        //criando buffer auxiliar
        char* buffer = new char[bufferSize];
        char* bufferAux = new char[linesize];

        //criando buffer de leitura, buscando por tamanho setado
        // e utilizando o getline para ir para a proxima linha
        input_file.read(buffer, readBufferSize);

        input_file.getline(bufferAux, linesize, '\n');

        strcat(buffer, bufferAux);

        int current = 0;
        while(buffer[current] != '\n' && current < linesize){

            char* line = new char[linesize];

            int i = 0;
            int virgulas = 0;
            bool entreAspas = false;
            int newlines = 0;
            for(i = 0; i < linesize; i++){
                if(buffer[current] == ',' && !entreAspas ){
                    virgulas++;
                }

                if(buffer[current] == '"'){
                    entreAspas = !entreAspas;
                }

                if(buffer[current] == '\n' && virgulas == 4){
                    break;
                } else if(buffer[current] == '\n'){
                    buffer[current] = ' ';
                }

                line[i] = buffer[current];
                current++;
            }

            line[i] = '\0';
            current++;
            Review *review = buildReview(line);
            counter++;

            delete [] line;
        }

        delete [] bufferAux;

    }

    return true;
}

int main(int argc, char const *argv[]) {

    //Verifica se todos os parametros do programa foram entrados
    if (argc != 2)
    {
        cout << "Erro! Esperado: ./<program_name> <input_file>" << endl;
        return 1;
    }

    string program_name(argv[0]);
    string input_file_name(argv[1]);

    string instance;
    if(!(input_file_name.find(".csv") <= input_file_name.size()))
    {
        cout << "Erro! Esperado arquivo CSV." << endl;
        return 1;
    }

    //Abrindo arquivo de entrada
    ifstream input_file;
    input_file.open(argv[1], ios::in);

    if(input_file.is_open())
    {
        processar(input_file);
        mainMenu(input_file);
    }else
        cout << "Impossibilitado de abrir o arquivo" << endl;

    //Fechando arquivo de entrada
    input_file.close();

    return 0;

    //Review* review = new Review("1234abcd", "Muito legal tiktok", "3.2", "22/10/2021", 30);


    //return 0;
}
