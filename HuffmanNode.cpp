#include "HuffmanNode.h"

HuffmanNode::HuffmanNode(char data, long freq){
    this->data = data;
    this->freq = freq;
    this->left = this->right = nullptr;
}

HuffmanNode::~HuffmanNode() { }

char HuffmanNode::getData() {
    return data;
}

void HuffmanNode::setData(char data) {
    HuffmanNode::data = data;
}

long HuffmanNode::getFreq() {
    return freq;
}

void HuffmanNode::setFreq(long freq) {
    HuffmanNode::freq = freq;
}

HuffmanNode *HuffmanNode::getLeft() {
    return left;
}

void HuffmanNode::setLeft(HuffmanNode *left) {
    HuffmanNode::left = left;
}

HuffmanNode *HuffmanNode::getRight() {
    return right;
}

void HuffmanNode::setRight(HuffmanNode *right) {
    HuffmanNode::right = right;
}

int HuffmanNode::ehFolha() {
    return this->left == nullptr && this->right == nullptr;
}





