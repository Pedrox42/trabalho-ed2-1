#include <iostream>
#include <fstream>
#include "Review.h"

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

void selecionar(int selecao, Review* review, ifstream& input_file){

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
int mainMenu(ifstream& input_file, Review* review){
    int selecao = 1;

    while(selecao != 0)
    {
        //system("cls");
        selecao = menu();

        selecionar(selecao, review, input_file);


    }
    return 0;
}
int main(int argc, char const *argv[]) {

    //Verifica se todos os parametros do programa foram entrados
    if (argc != 2)
    {
        cout << "Erro! Esperado: ./<program_name> <diretorio> <input_file>" << endl;
        return 1;
    }

    string program_name(argv[0]);
    string diretorio(argv[1])
    string input_file_name(argv[2]);

    //abrir diretorio
    DIR* dp = opendir(diretorio.c_str());

    struct dirent *diread;
    //vetor p guardar os arquivos do diretorio
    vector<char *> files;

    if (dp == NULL) 
    {
        cout << "Erro! Esperado caminho completo do diretorio";
        perror("opendir");
        return errno;

    } else {
        //loop para adicionar os arquivos no vetor
        while ((diread = readdir(diretorio)) != nullptr) {
            files.push_back(diread->d_name);
        }
    }

    for (auto file : files) cout << file << "| ";
    cout << endl;

    string instance;

    bool file_found = false;
    //Verifica a substring depois do carater acima
    for (auto file : files) {
            //Procura o ultimo caracter especificado
            string found = file.find_last_of(".")

            if((file.substr(found+1))!="bin")
            {
                if((file.substr(found+1))=="csv")
                {
                    //off:trata o arquivo csv p programa funcionar

                    //Arquivo csv encontrado
                    file_found=true;
                    break;
                }
            } else{
                //Arquivo binario encontrado
                file_found=true;
                break;
            }
        
    }

    //Abrindo arquivo de entrada
    ifstream input_file;
    //input_file.open(argv[1], ios::in);

    Review* review;
    if(input_file.is_open())
    {
        mainMenu(input_file, review);
    }else{
        cout << "Impossibilitado de abrir o arquivo" << endl;
    }

    //Fechando arquivo de entrada
    input_file.close();
    closedir(dp);
    return 0;

    //Review* review = new Review("1234abcd", "Muito legal tiktok", "3.2", "22/10/2021", 30);

    //cout << "Id: " << review->getReviewId() << endl;
    //cout << "App Version: " << review->getAppVersion() << endl;
    //cout << "Data de postagem: " << review->getPostedDate() << endl;
    //cout << "Texto: " << review->getReviewText() << endl;
    //cout << "Upvotes: " << review->getUpvotes() << endl;
    //return 0;
}
