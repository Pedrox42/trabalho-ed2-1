
#ifndef TRABALHO_ED2_1_HUFFMANNODE_H
#define TRABALHO_ED2_1_HUFFMANNODE_H

class HuffmanNode {
    private:
        char data;
        long freq;
        HuffmanNode *left, *right;

    public:
        HuffmanNode(char data, long freq);

        virtual ~HuffmanNode();

        char getData();

        void setData(char data);

        long getFreq();

        void setFreq(long freq);

        HuffmanNode *getLeft();

        void setLeft(HuffmanNode *left);

        HuffmanNode *getRight();

        void setRight(HuffmanNode *right);

        int ehFolha();
};



#endif //TRABALHO_ED2_1_HUFFMANNODE_H
