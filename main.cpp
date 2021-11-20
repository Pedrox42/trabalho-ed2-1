#include <iostream>
#include <fstream>
#include "Review.h"
#include <string.h>
#include <ctime>
#include <cmath>

//definindo como constantes os nomes dos arquivos que serão usados (tanto o csv quanto os binários)
const string csv_name = "tiktok_app_reviews.csv";
const string bin_name = "tiktok_app_reviews.bin";
const string index_name = "index.bin";






int menu(){
    int selecao;

    //menu para que o usuário possa escolher a função na qual ele queira executar no momento
    cout << "MENU" << endl;
    cout << "----" << endl;
    cout << "[1] acessaRegistro(i)" << endl;
    cout << "[2] testeImportacao()" << endl;
    cout << "[0] Sair" << endl;

    cin >> selecao;

    return selecao;
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
            int size = files[1].tellg(); //usando metodo tellg para pegar a posição do caractere atual e isso retorna o tamanho do binario que possui apenas os indices dos reviews pois foi procurado o ultimo caracter usando seekg() passando ios::end como parametro
            files[1].seekg(0, ios::beg);

            int reviews = size/sizeof(int); //divide o tamanho do arquivo binario dos indices pelo tamanho de um inteiro para saber quantas reviews tem no binario

            cout << "qual review voce quer acessar de: " << reviews << " reviews" << endl;


            double chosen = 0;
            cin >> chosen; //review escolhida pelo usuario
            if(chosen > 0 && chosen <= reviews){ //verificando se o indice da review eh valido
                files[1].seekg((chosen-1) * sizeof(int), ios::beg); //pegando a posicao do review escolhido no binario
                int char_total = Review::desserializar_int(files[1]);
                double peso = ( char_total*sizeof(char) ) + ( (chosen-1) * Review::getSizeOf(0) );
                cout << "peso de leitura: " << endl;
                files[0].seekg(peso, ios::beg); //buscar no arquivo contendo as reviews pelo peso de leitura no arquivo com os indices do indice pedido pelo usuario 
                Review* review = Review::desserializar_review(files[0]); //usa metodo desserializar para pegar review no binario e poder processar pelo codigo c++
                review->print(); //imprime review
                files[1].clear();
                files[0].clear(); //limpa variaveis de arquivos
            } else { //caso a review nao seja valida e nao esteja presente no range de reviews que estao no binario
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
            int size = files[1].tellg(); //usando metodo tellg para pegar a posição do caractere atual e isso retorna o tamanho do binario que possui apenas os indices dos reviews pois foi procurado o ultimo caracter usando seekg() passando ios::end como parametro
            files[1].seekg(0, ios::beg);

            int reviews = size/sizeof(int); //divide o tamanho do arquivo binario dos indices pelo tamanho de um inteiro para saber quantas reviews tem no binario

            cout << "qual review voce quer acessar de: " << reviews << " reviews" << endl;
            cout << "escolha uma das opcoes: " << endl;
            cout << "[1] 10 reviews aleatorias sejam apresentadas no console" << endl;
            cout << "[2] 100 reviews sejam salvas para o arquvio output.txt" << endl;
            int resposta;
            int n = 0;
            cin >> resposta; //recebe resposta do usuario sobre apresentar 10 reviews no console ou salvar 100 em um arquivo
            if(resposta == 1){ //caso o usuario tenha escolhido 10 reviews no console
                n = 10;
                for(int i = 0; i < n; i++) { //for com 10 iterações
                    int random = rand(); //seleciona int randomico
                    double option = int(random % reviews); //garantir que o int seja menor do que o numero de reviews
                    files[1].seekg((option) * sizeof(int), ios::beg); //pegando a posicao do review sorteado no binario
                    int char_total = Review::desserializar_int(files[1]);
                    double peso = ( char_total*sizeof(char) ) + ( (option) * Review::getSizeOf(0) );
                    files[0].seekg(peso, ios::beg); //buscar no arquivo contendo as reviews pelo peso de leitura no arquivo com os indices do indice pedido pelo usuario 
                    Review* review = Review::desserializar_review(files[0]); //usa metodo desserializar para pegar review no binario e poder processar pelo codigo c++
                    review->print(); //imprime a review no console
                    files[1].clear();
                    files[0].clear(); //limpa arquivos
                }

            } else if(resposta == 2) { //caso o usuario tenha escolhido 100 reviews no console
                n = 100;
                //cria arquivo de texto para ser processado
                ofstream txt_file; 
                txt_file.open((path + "output.txt"), ios::out | ios::trunc);

                for(int i = 0; i < n; i++){ //for com 100 iterações
                    int random = rand(); //seleciona int randomico
                    double option = int(random % reviews); //garantir que o int seja menor do que o numero de reviews
                    files[1].seekg((option) * sizeof(int), ios::beg); //pegando a posicao do review sorteado no binario
                    int char_total = Review::desserializar_int(files[1]);
                    double peso = ( char_total*sizeof(char) ) + ( (option) * Review::getSizeOf(0) );
                    files[0].seekg(peso, ios::beg); //buscar no arquivo contendo as reviews pelo peso de leitura no arquivo com os indices do indice pedido pelo usuario 

                    Review* review = Review::desserializar_review(files[0]); //usa metodo desserializar para pegar review no binario e poder processar pelo codigo c++
                    //escreve no arquivo as informações de cada review
                    txt_file << "Review: " << option << endl;
                    txt_file << "Id: " << review->getReviewId() << endl;
                    txt_file <<  "App Version: " << review->getAppVersion() << endl;
                    txt_file <<  "Data de postagem: " << review->getPostedDate() << endl;
                    txt_file <<  "Texto: " << review->getReviewText() << endl;
                    txt_file <<  "Upvotes: " << to_string(review->getUpvotes()) << endl << endl;
                    //limpa variaveis
                    files[1].clear();
                    files[0].clear();
                }
                txt_file.close();
            } else{ //caso a resposta seja diferente de 1 ou 2
                cout << "resposta invalida!" << endl;
            }
            break;
        }
    }
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

//funcao que criamos para concatenar dois vetores de char
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
            Review::serializar_int(files[1], char_counter); //pega no arquivo binario com os indices a review correspondente pelo iterador

            Review *r = buildReview(line, linesize, &char_counter);
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

            processar(read_files[0], write_files); //chama funcao processar para converter o conteudo do csv para binario

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
