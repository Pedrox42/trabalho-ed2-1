#include <iostream>
#include "Review.h"

int main() {
    Review* review = new Review("1234abcd", "Muito legal tiktok", "3.2", "22/10/2021", 30);

    cout << "Id: " << review->getReviewId() << endl;
    cout << "App Version: " << review->getAppVersion() << endl;
    cout << "Data de postagem: " << review->getPostedDate() << endl;
    cout << "Texto: " << review->getReviewText() << endl;
    cout << "Upvotes: " << review->getUpvotes() << endl;
    return 0;
}
