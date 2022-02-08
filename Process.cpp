#include "Process.h"
#include <fstream>
#include <iostream>


int Process::getBinReviews(ifstream* files){
    files[0].seekg(0, ios::beg);
    //setando posicoes no binario e descobrindo o numero total de reviews
    files[1].seekg(0, ios::end);
    int size = files[1].tellg();
    files[1].seekg(0, ios::beg);
    return size/sizeof(int);
}

ReviewPtr* Process::importarBinario(ifstream* files, int reviews, double* enderecos){

    ReviewPtr* big_review_list = new ReviewPtr[reviews];
    double total = 0;
    for(int i = 0; i < reviews; i++){
        int tamanho_review;
        big_review_list[i] = Review::desserializar_review(files[0], &tamanho_review);
        total += Review::getSizeOf(tamanho_review);
        enderecos[i] = total;
    }
    return big_review_list;
}

ReviewPtr* Process::importarReviewsRandomicas(ReviewPtr* big_review_list, int reviews, int n){

    if(n <= reviews) {
        ReviewPtr *small_review_list = new ReviewPtr[n];
        for (int i = 0; i < n; i++) {
            small_review_list[i] = big_review_list[int(rand() % reviews)];
        }
        return small_review_list;
    } else{
        cout << "Erro: valor maior do que o numero de reviews!" << endl;
        exit(1);
    }

}

ReviewPtr* Process::importarReviewsRandomicasBalanceadas(ReviewPtr* big_review_list, double* enderecos_list, double* enderecos, int reviews, int n){

    if(n <= reviews) {
        ReviewPtr *small_review_list = new ReviewPtr[n];
        for (int i = 0; i < n; i++) {
            int option = int(rand() % reviews);
            small_review_list[i] = big_review_list[option];
            enderecos_list[i] =  enderecos[option];

        }
        return small_review_list;
    } else{
        cout << "Erro: valor maior do que o numero de reviews!" << endl;
        exit(1);
    }

}

//funcao responsavel por ler a linha e transforma-la nos dados formatados para os dados normais objeto "Review"
void Process::strToData(int* current, char delimiter, char* object, char* buffer, int objectSize){
    int i = 0;
    for(i = 0; i < objectSize && buffer[*current] != '\0' && buffer[*current] != '\n' && buffer[*current] != delimiter; i++){
        object[i] = buffer[*current];
        (*current)++;
    }

    object[i] = '\0';

    (*current)++;
}


//funcao similar a strToData, entretanto como a review pode pussir
// virgulas e tem variantes a mais que os outros dados, uma função específica para sua leitura foi feita
int Process::strToReview(int* current, char* object, char* buffer, int objectSize, int* char_counter){
    int i = 0;
    int lastQuotations = *current;
    int lastQuotationsObject = 0;
    bool check = false;
    char delimiter = ',';
    bool entreaspas = false;

    //verifica a presenca de aspas no inicio da review
    // e seta variaveis de base para verificacoes
    //a variavel "entreaspas" eh especialmente importante para perceber quais virgulas de fato sao separadoras do csv
    //ou apenas virgulas contidas na string da reivew
    if(buffer[*current] == '"'){
        check = true;
        entreaspas = true;
        delimiter = '\n';
        (*current)++;
    }

    //for loop para aplicar logica e ler string e transforma-la na review
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

//funcao que recebe a string de linha nao formata e a transforma no objeto da review
//esse processo eh feito utilizando as funcoes de strToData e strToreview
Review* Process::buildReview(char* buffer, int linesize, int* char_counter)
{
    //alocando vetores
    char* id = new char[90];
    char* review_text = new char[linesize];
    char* upvotes = new char[11];
    char* app_version = new char[21];
    char* posted_date = new char[21];

    char delimiter = ',';
    int current = 0;

    //formatacao dos dados
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
        //exit(1);
    }

    return review;
}

//funcao que criamos para concatenar dois vetores de char
void Process::mergeStr(char* s1, char* s2, int t2)
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

//funcao responsavel por ler o csv utilizando um buffer e chamar as respectivas funcoes de
//serializacao nos arquivos binarios de index e tiktok_app_reviews
bool Process::processar(ifstream& input_file, ofstream* files){

    //declaracao de variaveis e alocacao de vetores necessarios
    constexpr size_t bufferSize = 1024*1024*5; //equivalente a 5mb de memoria
    int const linesize = Review::line_size;
    constexpr size_t readBufferSize = bufferSize - 3*linesize;
    char* table_head = new char[100];
    int review_array_size = 500000;

    //retirando primeira linha desnecessaria do csv
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
        //por fim concatena as 2 strings utilizando a funcao "mergeStr"
        input_file.read(buffer, readBufferSize);
        input_file.getline(bufferAux, linesize, '\n');
        mergeStr(buffer, bufferAux, linesize);

        int current = 0;
        //loop para criar as linhas e envia-las para as funcoes de formatacao
        //criar as reviews e serializa-las
        while (buffer[current] != '\0' && current < bufferSize) {

            char *line = new char[linesize];

            int i = 0;
            int virgulas = 0;
            bool entreAspas = false;
            int newlines = 0;
            for (i = 0; i < linesize && current < bufferSize; i++) {

                //verifica pra possiveis erros de newlines no final do buffer
                if(buffer[current] == '\0' && virgulas != 4){
                    char *bufferFix = new char[linesize];
                    input_file.getline(bufferFix, linesize, '\n');
                    mergeStr(buffer, bufferFix, linesize);
                    delete [] bufferFix;
                } else if(buffer[current] == '\0'){
                    break;
                }

                //verificacao se a virgula, e verificando se esta entre aspas
                //pois nesse caso seria uma virgula da string da review e nao um separador do csv
                if (buffer[current] == ',' && !entreAspas) {
                    virgulas++;
                }

                //verificacao para saber se esta ou nao "entre aspas"
                //sabendo que toda aspas na review sao duplas, com excecao da inicial e final
                if (buffer[current] == '"') {
                    entreAspas = !entreAspas;
                }

                //verifica para newlines errados no meio da linha, ao verificar se pelo menos os 4 objetos foram lidos
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

            //o processo de serializacao no index, utilizando a quantidade de caracteres atuais para poder posteriomente descobrir
            //sua posicao no binario principal
            Review::serializar_int(files[1], char_counter);

            //construindo a review utilizando a linha
            Review *r = buildReview(line, linesize, &char_counter);

            //serializacao da review no arquivo binario principal
            r->serializar_review(files[0]); //cria a review com os dados provenientes do binário

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

    return true;
}

void Process::acessaRegistro(ifstream* files){
    //binario no incio
    files[0].seekg(0, ios::beg);

    //index no fim
    files[1].seekg(0, ios::end);
    int size = files[1].tellg(); //usando metodo tellg para pegar a posição do caractere atual e isso retorna o tamanho do binario que possui apenas os indices dos reviews pois foi procurado o ultimo caracter usando seekg() passando ios::end como parametro
    files[1].seekg(0, ios::beg);

    int reviews = size / sizeof(int);

    cout << "qual review voce quer acessar de: " << reviews << " reviews" << endl;


    double chosen = 0;
    cin >> chosen;
    if (chosen > 0 && chosen <= reviews) {
        files[1].seekg((chosen - 1) * sizeof(int), ios::beg);
        int char_total = Review::desserializar_int(files[1]);
        double peso = (char_total * sizeof(char)) + ((chosen - 1) * Review::getSizeOf(0));
        cout << "peso de leitura: " << endl;
        files[0].seekg(peso, ios::beg);
        int review_size = 0;
        Review *review = Review::desserializar_review(files[0], &review_size);
        review->print();
        files[1].clear();
        files[0].clear(); //limpa variaveis de arquivos
    } else { //caso a review nao seja valida e nao esteja presente no range de reviews que estao no binario
        cout << "Erro: Essa review nao existe!" << endl;
    }
}

void Process::testeImportacao(ifstream* files, string path){
    //binario no incio
    files[0].seekg(0, ios::beg);

    //index no fim
    files[1].seekg(0, ios::end);
    int size = files[1].tellg(); //usando metodo tellg para pegar a posição do caractere atual e isso retorna o tamanho do binario que possui apenas os indices dos reviews pois foi procurado o ultimo caracter usando seekg() passando ios::end como parametro
    files[1].seekg(0, ios::beg);

    int reviews = size / sizeof(int);

    cout << "qual review voce quer acessar de: " << reviews << " reviews" << endl;
    cout << "escolha uma das opcoes: " << endl;
    cout << "[1] 10 reviews aleatorias sejam apresentadas no console" << endl;
    cout << "[2] 100 reviews sejam salvas para o arquvio output.txt" << endl;
    int resposta;
    int n = 0;
    cin >> resposta;
    if (resposta == 1) {
        n = 10;
        for (int i = 0; i < n; i++) {
            int random = rand();
            double option = int(random % reviews);
            files[1].seekg((option) * sizeof(int), ios::beg);
            int char_total = Review::desserializar_int(files[1]);
            double peso = (char_total * sizeof(char)) + ((option) * Review::getSizeOf(0));
            files[0].seekg(peso, ios::beg);
            int review_size;
            Review *review = Review::desserializar_review(files[0], &review_size);
            review->print();
            files[1].clear();
            files[0].clear(); //limpa arquivos
        }

    } else if (resposta == 2) {
        n = 100;
        //cria arquivo de texto para ser processado
        ofstream txt_file;
        txt_file.open((path + "output.txt"), ios::out | ios::trunc);

        for (int i = 0; i < n; i++) {
            int random = rand();
            double option = int(random % reviews);
            files[1].seekg((option) * sizeof(int), ios::beg);
            int char_total = Review::desserializar_int(files[1]);
            double peso = (char_total * sizeof(char)) + ((option) * Review::getSizeOf(0));
            files[0].seekg(peso, ios::beg);


            int review_size;
            Review *review = Review::desserializar_review(files[0], &review_size);
            txt_file << "Review: " << option << endl;
            txt_file << "Id: " << review->getReviewId() << endl;
            txt_file << "App Version: " << review->getAppVersion() << endl;
            txt_file << "Data de postagem: " << review->getPostedDate() << endl;
            txt_file << "Texto: " << review->getReviewText() << endl;
            txt_file << "Upvotes: " << to_string(review->getUpvotes()) << endl << endl;
            files[1].clear();
            files[0].clear();
        }
        txt_file.close();
    } else {
        cout << "resposta invalida!" << endl;
    }
}