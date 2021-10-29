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

    Review(const string &reviewId, const string &reviewText, const string &appVersion, const string &postedDate, int upvotes);

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
};


#endif //TRABALHO_ED2_1_REVIEW_H
