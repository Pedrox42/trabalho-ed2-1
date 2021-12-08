#include <iostream>
#include <fstream>
#include "Review.h"
#include <string.h>
#include <ctime>
#include <cmath>
#include <chrono>


const string csv_name = "tiktok_app_reviews.csv";
const string bin_name = "tiktok_app_reviews.bin";
const string index_name = "index.bin";
typedef Review* ReviewPtr;


using namespace std::chrono;

//algoritmos de sort
int particionamento(ReviewPtr* review_list, int p, int q, int* movimentacao, int* comparacoes){
    //declaraçoes das variaveis com pivo sendo o ponto mais a direita
    int pivo = q;
    int i = p;
    int j = q;

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

void quicksort(ReviewPtr* review_list, int p, int r, int* movimentacao, int* comparacoes){
    //caso os valores recebidos sejam invalidos ou iguais
    if(p < r){
        //recebendo o pivo
        int q = particionamento(review_list, p, r, movimentacao, comparacoes);

        //aplicando quicksort nos vetores resultantes
        quicksort(review_list, p, q, movimentacao, comparacoes);
        quicksort(review_list, q+1, r, movimentacao, comparacoes);
    }
}





int menu(){
    int selecao;

    cout << "MENU" << endl;
    cout << "----" << endl;
    cout << "[1] acessaRegistro(i)" << endl;
    cout << "[2] testeImportacao()" << endl;
    cout << "[3] importar binario()" << endl;
    cout << "[0] Sair" << endl;

    cin >> selecao;

    return selecao;
}

ReviewPtr* importarBinario(int n, ifstream* files){
    files[0].seekg(0, ios::beg);

    //setando posicoes no binario e descobrindo o numero total de reviews
    files[1].seekg(0, ios::end);
    int size = files[1].tellg();
    files[1].seekg(0, ios::beg);
    int reviews = size/sizeof(int);

    //for loop principal
    if(n <= reviews){

        //alocando array de reviews
        ReviewPtr* review_list = new ReviewPtr[n];
        for (int i = 0; i < n; ++i) {
            review_list[i] = new Review();
        }

        for(int i = 0; i < n; i++){

            //gerando numero da review e desserializando a review respectiva utilizando o sistema de index
            int random = rand();
            double option = int(random % reviews);
            files[1].seekg((option) * sizeof(int), ios::beg);
            int char_total = Review::desserializar_int(files[1]);
            double peso = ( char_total*sizeof(char) ) + ( (option) * Review::getSizeOf(0) );
            files[0].seekg(peso, ios::beg);

            //lista recebe a review desserializada
            review_list[i]->receiveReview(Review::desserializar_review(files[0]));

            //clear nos files
            files[1].clear();
            files[0].clear();

        }

        return review_list;

    } else{
        cout << "Erro: valor maior do que o numero de reviews!" << endl;
        return nullptr;
    }

}


void selecionar(int selecao, ifstream* files, string path){

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
            //binario no incio
            files[0].seekg(0, ios::beg);

            //index no fim
            files[1].seekg(0, ios::end);
            int size = files[1].tellg();
            files[1].seekg(0, ios::beg);

            int reviews = size/sizeof(int);

            cout << "qual review voce quer acessar de: " << reviews << " reviews" << endl;


            double chosen = 0;
            cin >> chosen;
            if(chosen > 0 && chosen <= reviews){
                files[1].seekg((chosen-1) * sizeof(int), ios::beg);
                int char_total = Review::desserializar_int(files[1]);
                double peso = ( char_total*sizeof(char) ) + ( (chosen-1) * Review::getSizeOf(0) );
                cout << "peso de leitura: " << endl;
                files[0].seekg(peso, ios::beg);
                Review* review = Review::desserializar_review(files[0]);
                review->print();
                files[1].clear();
                files[0].clear();
            } else {
                cout << "Erro: Essa review nao existe!" << endl;
            }
            break;
        }
//        Note que a função testeImportacao() é apenas uma função de teste.
//         O programa deve ser capaz de importar registros do arquivo para quaisquer valores de N, sem erros e sem gerar exceções.
        case 2:
        {
            //binario no incio
            files[0].seekg(0, ios::beg);

            //index no fim
            files[1].seekg(0, ios::end);
            int size = files[1].tellg();
            files[1].seekg(0, ios::beg);

            int reviews = size/sizeof(int);

            cout << "qual review voce quer acessar de: " << reviews << " reviews" << endl;

            cout << "escolha uma das opcoes: " << endl;
            cout << "[1] 10 reviews aleatorias sejam apresentadas no console" << endl;
            cout << "[2] 100 reviews sejam salvas para o arquvio output.txt" << endl;
            int resposta;
            int n = 0;
            cin >> resposta;
            if(resposta == 1){
                n = 10;
                for(int i = 0; i < n; i++) {
                    int random = rand();
                    double option = int(random % reviews);
                    files[1].seekg((option) * sizeof(int), ios::beg);
                    int char_total = Review::desserializar_int(files[1]);
                    double peso = ( char_total*sizeof(char) ) + ( (option) * Review::getSizeOf(0) );
                    files[0].seekg(peso, ios::beg);
                    Review* review = Review::desserializar_review(files[0]);
                    review->print();
                    files[1].clear();
                    files[0].clear();
                }

            } else if(resposta == 2) {
                n = 100;
                ofstream txt_file;
                txt_file.open((path + "output.txt"), ios::out | ios::trunc);

                for(int i = 0; i < n; i++){
                    int random = rand();
                    double option = int(random % reviews);
                    files[1].seekg((option) * sizeof(int), ios::beg);
                    int char_total = Review::desserializar_int(files[1]);
                    double peso = ( char_total*sizeof(char) ) + ( (option) * Review::getSizeOf(0) );
                    files[0].seekg(peso, ios::beg);

                    Review* review = Review::desserializar_review(files[0]);
                    txt_file << "Review: " << option << endl;
                    txt_file << "Id: " << review->getReviewId() << endl;
                    txt_file <<  "App Version: " << review->getAppVersion() << endl;
                    txt_file <<  "Data de postagem: " << review->getPostedDate() << endl;
                    txt_file <<  "Texto: " << review->getReviewText() << endl;
                    txt_file <<  "Upvotes: " << to_string(review->getUpvotes()) << endl << endl;
                    files[1].clear();
                    files[0].clear();
                }
                txt_file.close();
            } else{
                cout << "resposta invalida!" << endl;
            }
            break;
        }

        case 3:
            cout << "Numero de reviews desejada para importacao: " << endl;
            int n;
            cin >> n;

            //variavel para cronometrar o tempo de execucao
            auto start = high_resolution_clock::now();

            ReviewPtr* review_list = importarBinario(n, files);

            //cronometrando o tempo de execucao
            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<microseconds>(stop - start);
            cout << "Tempo da importação: " << duration.count() / pow(10, 6) << " seconds" << endl;

            start = high_resolution_clock::now();

            //chmando função de quicksort
            int movimentacoes = 0;
            int comparacoes = 0;
            quicksort(review_list, 0, n-1, &movimentacoes, &comparacoes);

            //cronometrando o tempo de execucao
            stop = high_resolution_clock::now();
            duration = duration_cast<microseconds>(stop - start);
            cout << "Tempo da execução do quicksort: " << duration.count() / pow(10, 6) << " seconds" << endl;
            cout << "movimentacoes " << movimentacoes << endl;
            cout << "comparacoes " << comparacoes << endl;

            delete [] review_list;

            break;
    }
}

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


void strToData(int* current, char delimiter, char* object, char* buffer, int objectSize){
    int i = 0;
    for(i = 0; i < objectSize && buffer[*current] != '\0' && buffer[*current] != '\n' && buffer[*current] != delimiter; i++){
        object[i] = buffer[*current];
        (*current)++;
    }

    object[i] = '\0';

    (*current)++;
}

int strToReview(int* current, char* object, char* buffer, int objectSize, int* char_counter){
    int i = 0;
    int lastQuotations = *current;
    int lastQuotationsObject = 0;
    bool check = false;
    char delimiter = ',';
    bool entreaspas = false;

    if(buffer[*current] == '"'){
        check = true;
        entreaspas = true;
        delimiter = '\n';
        (*current)++;
    }

    for(i = 0; i < objectSize && buffer[*current] != '\0' && buffer[*current] != '\n' && buffer[*current] != delimiter; i++){

        object[i] = buffer[*current];

        if(check && buffer[*current] == '"'){
            lastQuotations = (*current);
            lastQuotationsObject = i;
            entreaspas = !entreaspas;

        }

        if(buffer[*current+1] == '\0' && entreaspas){
            (*current)++;
        }

        (*current)++;

    }

    int size = 0;
    object[i] = '\0';

    size = i;
    if(check){
        object[lastQuotationsObject] = '\0';
        (*current) = lastQuotations+1;
        size = lastQuotationsObject;
    }

    (*current)++;
    (*char_counter) += (size);
    return size;
}

Review* buildReview(char* buffer, int linesize, int* char_counter)
{
    char* id = new char[90];
    char* review_text = new char[linesize];
    char* upvotes = new char[11];
    char* app_version = new char[21];
    char* posted_date = new char[21];

    char delimiter = ',';
    int current = 0;

    strToData(&current, delimiter, id, buffer, 90);
    int reviewSize = strToReview(&current, review_text, buffer, linesize, char_counter);
    strToData(&current, delimiter, upvotes, buffer, 11);
    strToData(&current, delimiter, app_version, buffer, 21);
    strToData(&current, delimiter, posted_date, buffer, 21);

    Review *review;



    try{
        review = new Review(id, review_text, app_version, posted_date, stoi(upvotes), reviewSize);
    } catch (...){
        review = nullptr;
        cout << "Erro na linha de id: " << id << endl;
        cout << "review: " << review_text << endl;
        cout << "upvotes " << upvotes << endl;
        exit(1);
    }

    // delete [] id;
    // delete [] review_text;
    // delete [] app_version;
    // delete [] posted_date;
    // delete [] upvotes;

    return review;
}

void mergeStr(char* s1, char* s2, int t2)
{
    int count = 0;
    int j = 0;
    for(int i = 0; s1[i] != '\0'; i++) {
        count++;
    }
    for(int i = count; i < count+t2; i++) {
        s1[i] = s2[j];
        j++;
    }
    s1[count+t2+1] = '\0';
}

bool processar(ifstream& input_file, ofstream* files){

    constexpr size_t bufferSize = 100000; //equivalente a 5mb de memoria
    int const linesize = Review::line_size;
    constexpr size_t readBufferSize = bufferSize - 3*linesize;
    char* table_head = new char[100];
    int review_array_size = 100000;

    input_file.getline(table_head, linesize, '\n');
    int counter = 0;
    int total_lines = 0;
    int char_counter = 0;

    cout << "Iniciando processamento: " << endl;

    while (input_file)
    {
        char *buffer = new char[bufferSize];
        char *bufferAux = new char[linesize];

        //criando buffer de leitura, buscando por tamanho setado
        // e utilizando o getline para ir para a proxima linha
        input_file.read(buffer, readBufferSize);

        input_file.getline(bufferAux, linesize, '\n');

        mergeStr(buffer, bufferAux, linesize);
        //strncat(buffer, bufferAux, linesize);

        int current = 0;
        while (buffer[current] != '\0' && current < bufferSize) {

            char *line = new char[linesize];

            int i = 0;
            int virgulas = 0;
            bool entreAspas = false;
            int newlines = 0;
            for (i = 0; i < linesize && current < bufferSize; i++) {
                if(buffer[current] == '\0' && virgulas != 4){
                    char *bufferFix = new char[linesize];
                    input_file.getline(bufferFix, linesize, '\n');
                    mergeStr(buffer, bufferFix, linesize);
                    delete [] bufferFix;
                } else if(buffer[current] == '\0'){
                    break;
                }

                if (buffer[current] == ',' && !entreAspas) {
                    virgulas++;
                }

                if (buffer[current] == '"') {
                    entreAspas = !entreAspas;
                }

                if (buffer[current] == '\n' && virgulas == 4) {
                    current++;
                    break;
                } else if (buffer[current] == '\n') {
                    current++;
                    continue;
                }
                line[i] = buffer[current];

                current++;
            }
            line[i] = '\0';
            Review::serializar_int(files[1], char_counter);

            Review *r = buildReview(line, linesize, &char_counter);
            r->serializar_review(files[0]);

            delete r;

            counter++;

           delete[] line;

            if(counter == review_array_size){

                total_lines += counter;
                counter = 0;

                cout << total_lines << " de Reviews processadas" << endl << "continuando processamento..." << endl;
            }

        }

        delete[] bufferAux;
    }

    total_lines += counter;
    cout << "Processamento finalizado! Total de Reviews analisadas: " << total_lines << endl;

    // delete [] review_list;


    return true;
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
    read_files[0].open(argv[1] + bin_name, ios::in);
    read_files[1].open(argv[1] + index_name, ios::in);
    if(read_files[0].is_open() && read_files[1].is_open())
    {
        cout << "Arquivos binarios econtrados com sucesso!" << endl;
        // Pré-processamento do arquivo csv para binário
        mainMenu(read_files, argv[1]);
    }else{
        read_files[0].close();
        read_files[1].close();
        cout << "Arquivos binarios nao encontrados, procurando csv..." << endl;

        read_files[0].open(argv[1] + csv_name, ios::in);
        if(read_files[0].is_open())
        {
            cout << "Csv econtrado com sucesso!" << endl;
            // Pré-processamento do arquivo csv para binário


            //file 0 = binario
            //file 1 = index
            ofstream write_files[2];
            write_files[0].open(argv[1] + bin_name,  ios::binary | ios::trunc);
            write_files[1].open(argv[1] + index_name, ios::binary | ios::trunc);

            processar(read_files[0], write_files);

            write_files[0].close();
            write_files[1].close();
            read_files[0].close();

            write_files[0].clear();
            write_files[1].clear();
            read_files[0].clear();

            read_files[0].open(argv[1] + bin_name, ios::binary);
            read_files[1].open(argv[1] + index_name, ios::binary);

            if(read_files[0].is_open() && read_files[1].is_open()) {
                mainMenu(read_files, argv[1]);
            } else{
                cout << "Impossibilitado de abrir o arquivo binario" << endl;
                exit(1);
            }

        }else{
            read_files[0].close();
            cout << "Impossibilitado de abrir o arquivo csv" << endl;
            exit(1);
        }

    }

    return 0;

}
