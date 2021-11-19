#include <iostream>
#include "Review.h"
#include <fstream>
#include <cstring>

Review::Review(const string &reviewId, const string &reviewText, const string &appVersion, const string &postedDate, int upvotes){
    this->review_id = reviewId;
    this->review_text = reviewText;
    this->app_version = appVersion;
    this->posted_date = postedDate;
    this->upvotes = upvotes;
}

Review::Review(){}

Review::~Review(){
}

void Review::recieveReview(Review* review){
    this->review_id = review->review_id;
    this->review_text = review->review_text;
    this->app_version = review->app_version;
    this->posted_date = review->posted_date;
    this->upvotes = review->upvotes;

}

const string &Review::getReviewId() const {
    return review_id;
}

void Review::setReviewId(const string &reviewId) {
    review_id = reviewId;
}

const string &Review::getReviewText() const {
    return review_text;
}

void Review::setReviewText(const string &reviewText) {
    review_text = reviewText;
}

const string &Review::getAppVersion() const {
    return app_version;
}

void Review::setAppVersion(const string &appVersion) {
    app_version = appVersion;
}

const string &Review::getPostedDate() const {
    return posted_date;
}

void Review::setPostedDate(const string &postedDate) {
    posted_date = postedDate;
}

int Review::getUpvotes() const {
    return upvotes;
}

void Review::setUpvotes(int upvotes) {
    Review::upvotes = upvotes;
}

int Review::getSizeOf(int review_characters) {
    return (sizeof(char) * (id_size + review_characters + version_size + date_size)) + (5*sizeof(int));
    //return (sizeof(char) * (id_size+review_size)) + (2*sizeof(int));
}

void Review::print(){
    cout << "Id: " << this->getReviewId() << endl;
    cout << "App Version: " << this->getAppVersion() << endl;
    cout << "Data de postagem: " << this->getPostedDate() << endl;
    cout << "Texto: " << this->getReviewText() << endl;
    cout << "Upvotes: " << this->getUpvotes() << endl;
    cout << endl;
}

void Review::serializar_char(ofstream& bin_file, char* str, int size){
    int counter = 0;
    char* serialized_char = new char[size];

    for(int i = 0; str[i] != '\0'; i++){
        serialized_char[i] = str[i];
        counter++;
    }

    serialized_char[counter] = '\0';

    bin_file.write((char*)&size, sizeof(int));
    bin_file.write((char*)serialized_char, size*sizeof(char));
}

void Review::serializar_review_text(ofstream& bin_file, char* str){
    cout << "Entrou na função" << endl;
    int size = 0;

    for(int i = 0; str[i] != '\0'; i++){
        cout << str[i] << endl;
        cout << i << endl;
        size++;
    }

    cout << "Antes do write bin file" << endl;

    bin_file.write((char*)&size, sizeof(int));
    bin_file.write((char*)str, size*sizeof(char));

    cout << "Final serializar review" << endl;
}


void Review::serializar_int(ofstream& bin_file, int value){
    bin_file.write((char*)&value, sizeof(int));
}

char* Review::desserializar_char(ifstream& bin_file){
    char* str;
    int size;
    bin_file.read((char*)&size, sizeof(int));
    str = new char[size];
    bin_file.read((char*)str, size*sizeof(char));

    return str;
}

int Review::desserializar_int(ifstream& bin_file){
    int size;
    bin_file.read((char*)&size, sizeof(int));
    return size;
}

int Review::stringLength(string str) {
    int size = 0;
    cout << str << endl;
    for(int i = 0; str[i] != '\0'; i++) {
        cout << str[i];
        size++;
    }
    return size + 1;
}

void Review::serializar_review(ofstream& bin_file){

    stringLength(this->getReviewId());
    // char * id = new char [this->getReviewId().length()+1];
    // // strcpy(id, this->getReviewId().c_str());
    // // serializar_char(bin_file, id, id_size);

    // char * review_text = new char [this->getReviewText().length()+1];
    // // strcpy(review_text, this->getReviewText().c_str());
    // // serializar_review_text(bin_file, review_text);

    // //Review::serializar_int(bin_file, this->getUpvotes());

    // char * app_version = new char [this->getAppVersion().length()+1];
    // // strcpy(app_version, this->getAppVersion().c_str());
    // // serializar_char(bin_file, app_version, version_size);

    // char * posted_date = new char [this->getPostedDate().length()+1];
    // // strcpy(posted_date, this->getPostedDate().c_str());
    // // serializar_char(bin_file, posted_date, date_size);

    // // delete [] id;
    // // delete [] review_text;
    // // delete [] app_version;
    // // delete [] posted_date;

}

Review* Review::desserializar_review(ifstream& bin_file){
    Review* review = new Review();
    review->setReviewId(desserializar_char(bin_file));
    review->setReviewText(desserializar_char(bin_file));
    review->setUpvotes(desserializar_int(bin_file));
    review->setAppVersion(desserializar_char(bin_file));
    review->setPostedDate(desserializar_char(bin_file));

    return review;
}

