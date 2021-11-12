#include <iostream>
#include "Review.h"

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

void Review::print(){
    cout << "Id: " << this->getReviewId() << endl;
    cout << "App Version: " << this->getAppVersion() << endl;
    cout << "Data de postagem: " << this->getPostedDate() << endl;
    cout << "Texto: " << this->getReviewText() << endl;
    cout << "Upvotes: " << this->getUpvotes() << endl;
    cout << endl;
}

