#ifndef TRABALHO_ED2_1_REVIEW_H
#define TRABALHO_ED2_1_REVIEW_H

#include <string>

using namespace std;

class Review {

private:
    string review_id;
    string review_text;
    string app_version;
    string posted_date;
    int upvotes;



public:

    static const int id_size = 90;
    static const int review_size = 1000;
    static const int date_size = 21;
    static const int version_size = 21;

    Review(const string &reviewId, const string &reviewText, const string &appVersion, const string &postedDate, int upvotes);

    //construtor vazio para possiblitar criação de array
    Review();

    ~Review();

    const string &getReviewId() const;

    void setReviewId(const string &reviewId);

    const string &getReviewText() const;

    void setReviewText(const string &reviewText);

    const string &getAppVersion() const;

    void setAppVersion(const string &appVersion);

    const string &getPostedDate() const;

    void setPostedDate(const string &postedDate);

    int getUpvotes() const;

    void setUpvotes(int upvotes);

    void print();

    void recieveReview(Review* review);

    static void serializar_char(ofstream &bin_file, char* str, int size);

    static char *desserializar_char(ifstream &bin_file);

    static Review* desserializar_review(ifstream &bin_file);

    static int desserializar_int(ifstream &bin_file);

    static int getSizeOf(int review_characters);

    static void serializar_int(ofstream &bin_file, int value);

    static void serializar_review_text(ofstream &bin_file, char *str);

    void serializar_review(ofstream &bin_file);

    static int stringLength(string str);
};


#endif //TRABALHO_ED2_1_REVIEW_H
