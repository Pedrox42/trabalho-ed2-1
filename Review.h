#ifndef TRABALHO_ED2_1_REVIEW_H
#define TRABALHO_ED2_1_REVIEW_H

#include <string>

using namespace std;


class Review {

private:
    char* review_id;
    char* review_text;
    char* app_version;
    char* posted_date;
    int upvotes;
    int review_size;

public:

    static const int id_size = 90;
    static const int date_size = 21;
    static const int version_size = 21;
    static const int line_size = 5000;

    Review(char* reviewId, char* reviewText, char* appVersion, char* postedDate, int upvotes, int reviewSize);

    //construtor vazio para possiblitar criação de array
    Review();

    ~Review();

    char* getReviewId();

    void setReviewId(char* reviewId);

    char* getReviewText();

    void setReviewText(char* reviewText);

    char* getAppVersion();

    void setAppVersion(char* appVersion);

    char* getPostedDate();

    void setPostedDate(char* postedDate);

    int getUpvotes();

    void setUpvotes(int upvotes);

    void print();

    void receiveReview(Review* review);

    static void serializar_char(ofstream &bin_file, char* str, int size);

    static char *desserializar_char(ifstream &bin_file);

    static Review* desserializar_review(ifstream &bin_file, int* size);

    static char* desserializar_reviewText(ifstream &bin_file, int* size);

    static int desserializar_int(ifstream &bin_file);

    static int getSizeOf(int review_characters);

    static void serializar_int(ofstream &bin_file, int value);

    static void serializar_review_text(ofstream &bin_file, char *str);

    void serializar_review(ofstream &bin_file);

    static int stringLength(string str);

    int getReviewSize() const;

    void setReviewSize(int reviewSize);

    static void swap(Review review1, Review review2);
};


#endif //TRABALHO_ED2_1_REVIEW_H
