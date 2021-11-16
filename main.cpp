#include <iostream>
#include <fstream>
#include "Review.h"
#include <string.h>


const string csv_name = "tiktok_app_reviews.csv";
const string bin_name = "tiktok_app_reviews.bin";





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
//            input_file.seekg(0, ios::end);
//            float total = input_file.tellg();
//            float reviews = total/Review::getSizeOf();
//            cout << "qual review voce quer acessar de: " << reviews << " reviews" << endl;
//
//            input_file.seekg(0, ios::beg);
//            float chosen = 0;
//            cin >> chosen;
//            if(chosen > 0 && chosen <= reviews){
//                cout << "VALOR: " << (chosen-1) * Review::getSizeOf() << endl;
//                input_file.seekg((chosen-1) * Review::getSizeOf(), ios::beg);
//                Review* review = Review::desserializar_review(input_file);
//                review->print();
//            } else {
//                cout << "Erro: Essa review nao existe!" << endl;
//            }

            input_file.seekg(0, ios::end);
            float total = input_file.tellg();
            float reviews = total/Review::getSizeOf();
            input_file.seekg(0, ios::beg);
            for(int i = 0; i < 100000; i++){
                Review::desserializar_review(input_file)->print();
                cout << endl << "parou no byte: " << input_file.tellg() << endl << endl;
            }

            exit(1);

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
        (*current)++;
    }

    for(i = 0; i < objectSize && buffer[*current] != '\0' && buffer[*current] != '\n' && buffer[*current] != delimiter; i++){
        object[i] = buffer[*current];

        if(check && buffer[*current] == '"'){
            lastQuotations = (*current);
            lastQuotationsObject = i;
        }

        (*current)++;

    }
    object[i] = '\0';
    if(check){
        object[lastQuotationsObject] = '\0';
        (*current) = lastQuotations+1;
    }
    (*current)++;
}

Review* buildReview(char* buffer, int linesize)
{
    char* id = new char[90];
    char* review_text = new char[linesize];
    char* upvotes = new char[11];
    char* app_version = new char[21];
    char* posted_date = new char[21];

    char delimiter = ',';
    int current = 0;


    strToData(&current, delimiter, id, buffer, 90);
    strToReview(&current, review_text, buffer, linesize);
    strToData(&current, delimiter, upvotes, buffer, 11);
    strToData(&current, delimiter, app_version, buffer, 21);
    strToData(&current, delimiter, posted_date, buffer, 21);

    Review *review;

    try{
        review = new Review(id, review_text, app_version, posted_date, stoi(upvotes));

    } catch (...){
        review = nullptr;
        cout << "Erro na linha de id: " << id << endl;
        cout << "review: " << review_text << endl;
        cout << "upvotes " << upvotes << endl;
    }

    delete [] id;
    delete [] review_text;
    delete [] app_version;
    delete [] posted_date;
    delete [] upvotes;

    return review;
}

bool processar(ifstream& input_file, ofstream& bin_file){

    constexpr size_t bufferSize = 1024*1024*50; //equivalente a 5mb de memoria
    int const linesize = Review::review_size;
    constexpr size_t readBufferSize = bufferSize - linesize;
    char* table_head = new char[100];
    int review_array_size = 50000;
    Review* review_list = new Review[review_array_size];


    input_file.getline(table_head, linesize, '\n');
    int counter = 0;
    int total_lines = 0;

    cout << "Iniciando processamento: " << endl;

    while (input_file)
    {
        char *buffer = new char[bufferSize];
        char *bufferAux = new char[linesize];

        //criando buffer de leitura, buscando por tamanho setado
        // e utilizando o getline para ir para a proxima linha
        input_file.read(buffer, readBufferSize);

        input_file.getline(bufferAux, linesize, '\n');

        strcat(buffer, bufferAux);



        int current = 0;
        while (buffer[current] != '\0') {

            char *line = new char[linesize];

            int i = 0;
            int virgulas = 0;
            bool entreAspas = false;
            int newlines = 0;
            for (i = 0; i < linesize; i++) {

                if(buffer[current] == '\0' && virgulas != 4){
                    char *bufferFix = new char[linesize];
                    input_file.getline(bufferFix, linesize, '\n');
                    strcat(buffer, bufferFix);
                    delete [] bufferFix;
                }

                if (buffer[current] == ',' && !entreAspas) {
                    virgulas++;
                }

                if (buffer[current] == '"') {
                    entreAspas = !entreAspas;
                }

                if (buffer[current] == '\n' && virgulas == 4) {
                    break;
                } else if (buffer[current] == '\n') {
                    buffer[current] = ' ';
                }

                line[i] = buffer[current];
                current++;
            }

            line[i] = '\0';

            current++;
            if(counter > 100000){
                buildReview(line, linesize)->serializar_review(bin_file);

            }
            counter++;
            if(counter == 220000){
                exit(1);
            }


            delete[] line;
//
//            if(counter == review_array_size){
//
//                total_lines += counter;
//
//                int counter2 = 0;
//                for(int j = 0; j < counter; j++){
//                    review_list[j].serializar_review(bin_file);
//                    counter2++;
//                }
//
//
//                delete [] review_list;
//                review_list = new Review[review_array_size];
//                counter = 0;
//
//                cout << total_lines << " de Reviews processadas" << endl << "continuando processamento..." << endl;
//            }
        }

        delete[] bufferAux;
    }

    total_lines += counter;
    cout << "Processamento finalizado! Total de Reviews analisadas: " << total_lines << endl;

    for(int j = 0; j < counter; j++){
        review_list[j].serializar_review(bin_file);
    }

    delete [] review_list;

    return true;
}

int main(int argc, char const *argv[]) {

    //Verifica se todos os parametros do programa foram entrados
    if (argc != 2)
    {
        cout << "Erro! Esperado: ./<program_name> <input_file_path>" << endl;
        return 1;
    }

    ifstream input_file;
    input_file.open(argv[1] + bin_name, ios::in);
    if(input_file.is_open())
    {
        cout << "Arquivo binario econtrado com sucesso!" << endl;
        // Pré-processamento do arquivo csv para binário
        mainMenu(input_file);
    }else{
        input_file.close();
        cout << "Arquivo binario nao encontrado, procurando csv..." << endl;
        input_file.open(argv[1] + csv_name, ios::in);
        if(input_file.is_open())
        {
            cout << "Csv econtrado com sucesso!" << endl;
            // Pré-processamento do arquivo csv para binário


            ofstream write_bin_file;
            write_bin_file.open(argv[1] + bin_name,  ios::binary);

            Review* review = new Review();
            processar(input_file, write_bin_file);
            write_bin_file.close();


            ifstream read_bin_file;
            read_bin_file.open(argv[1] + bin_name, ios::binary);

            if(read_bin_file.is_open()) {
                mainMenu(read_bin_file);
            } else{
                cout << "Impossibilitado de abrir o arquivo binario" << endl;
                exit(1);
            }

        }else{
            input_file.close();
            cout << "Impossibilitado de abrir o arquivo csv" << endl;
            exit(1);
        }

    }

    return 0;

}
