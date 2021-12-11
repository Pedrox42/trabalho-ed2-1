#include <iostream>
#include "Review.h"
#include <fstream>
#include <cstring>

//Construtor
Review::Review(char* reviewId, char* reviewText, char* appVersion, char* postedDate, int upvotes, int reviewSize){
    this->review_id = new char[id_size]; //aloca vetor de char para o id da review
    this->review_id = reviewId; //recebe vetor de char pelo parametro

    this->review_text = new char[reviewSize]; //aloca vetor de char para o texto da review
    this->review_text = reviewText; //recebe vetor de char pelo parametro

    this->app_version = new char[version_size]; //aloca vetor de char para a versao do app
    this->app_version = appVersion; //recebe vetor de char pelo parametro

    this->posted_date =  new char[date_size]; //aloca vetor de char para a data da review
    this->posted_date = postedDate; //recebe vetor de char pelo parametro

    this->upvotes = upvotes; //recebe int como parametro para a quantidade de votos favoraveis a review
    this->review_size = reviewSize; //tamanho do texto da review
}

Review::Review(){}

//Destrutor
Review::~Review(){
    delete [] review_id;
    delete [] review_text;
    delete [] app_version;
    delete [] posted_date;
}

//método para receber todos os atributos da review
void Review::receiveReview(Review* review){
    this->review_id = review->review_id;
    this->review_text = review->review_text;
    this->app_version = review->app_version;
    this->posted_date = review->posted_date;
    this->upvotes = review->upvotes;
    this->review_size = review->review_size;

}

//getters e setters
char* Review::getReviewId(){
    return review_id;
}

void Review::setReviewId(char* reviewId) {
    review_id = reviewId;
}

char* Review::getReviewText(){
    return review_text;
}

void Review::setReviewText(char* reviewText) {
    review_text = reviewText;
}

char* Review::getAppVersion(){
    return app_version;
}

void Review::setAppVersion(char* appVersion) {
    app_version = appVersion;
}

char* Review::getPostedDate(){
    return posted_date;
}

void Review::setPostedDate(char* postedDate) {
    posted_date = postedDate;
}

int Review::getUpvotes(){
    return upvotes;
}

void Review::setUpvotes(int upvotes) {
    Review::upvotes = upvotes;
}

int Review::getReviewSize() const {
    return review_size;
}

void Review::setReviewSize(int reviewSize) {
    review_size = reviewSize;
}

int Review::getSizeOf(int review_characters) {
    return (sizeof(char) * (id_size + review_characters + version_size + date_size)) + (5*sizeof(int));
    //return (sizeof(char) * (id_size+review_size)) + (2*sizeof(int));
}

//método para imprimir todos os atributos da review
void Review::print(){
    cout << "Id: " << this->getReviewId() << endl;
    cout << "App Version: " << this->getAppVersion() << endl;
    cout << "Data de postagem: " << this->getPostedDate() << endl;
    cout << "Texto: " << this->getReviewText() << endl;
    cout << "Upvotes: " << this->getUpvotes() << endl;
    cout << endl;
}

//Método para escrever no arquivo binário um vetor de char passado por parametro
void Review::serializar_char(ofstream& bin_file, char* str, int size){
    bin_file.write((char*)&size, sizeof(int)); //Método usado para escrever no binário
    bin_file.write((char*)str, size*sizeof(char)); //Método usado para escrever no binário
}

//Método para escrever no arquivo binário o texto da review
void Review::serializar_review_text(ofstream& bin_file, char* str){
    int size = 0;

    for(int i = 0; str[i] != '\0'; i++){ //For para achar tamanho do vetor de char
        cout << str[i] << endl;
        cout << i << endl;
        size++;
    }

    bin_file.write((char*)&size, sizeof(int)); //Método usado para escrever no binário
    bin_file.write((char*)str, size*sizeof(char)); //Método usado para escrever no binário
}

//Método para escrever no arquivo binário um int passado por parametro
void Review::serializar_int(ofstream& bin_file, int value){
    bin_file.write((char*)&value, sizeof(int)); //Método usado para escrever no binário
}

//Ler e interpretar do arquivo binário para receber char e processar pelo código c++
char* Review::desserializar_char(ifstream& bin_file){
    char* str;
    int size;
    bin_file.read((char*)&size, sizeof(int)); //Método usado para ler do arquivo binário
    str = new char[size];
    bin_file.read((char*)str, size*sizeof(char)); //Método usado para ler do arquivo binário
    return str;
}

//Interpretar o arquivo binário para receber int e processar pelo código c++
int Review::desserializar_int(ifstream& bin_file){
    int size;
    bin_file.read((char*)&size, sizeof(int)); //Método usado para ler do arquivo binário
    return size;
}

// int Review::stringLength(string str) {
//     int size = 0;
//     cout << str << endl;
//     for(int i = 0; str[i] != '\0'; i++) {
//         cout << str[i];
//         size++;
//     }
//     return size + 1;
// }

//Escrever a review no arquivo binário, usando os métodos
//serializar com todos os atributos do objeto de acordo com seu tipo
void Review::serializar_review(ofstream& bin_file){
    serializar_char(bin_file, this->getReviewId(), id_size);
    serializar_char(bin_file, this->getReviewText(), this->getReviewSize());
    Review::serializar_int(bin_file, this->getUpvotes());
    serializar_char(bin_file, this->getAppVersion(), version_size);
    serializar_char(bin_file, this->getPostedDate(), date_size);
}

//Ler e interpretar a review do arquivo binário, usando os métodos
//desserializar com todos os atributos do objeto de acordo com seu tipo
Review* Review::desserializar_review(ifstream& bin_file){
    Review* review = new Review();
    review->setReviewId(desserializar_char(bin_file));
    review->setReviewText(desserializar_char(bin_file));
    review->setUpvotes(desserializar_int(bin_file));
    review->setAppVersion(desserializar_char(bin_file));
    review->setPostedDate(desserializar_char(bin_file));

    return review;
}
