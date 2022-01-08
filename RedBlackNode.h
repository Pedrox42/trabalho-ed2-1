#ifndef TRABALHO_ED2_1_REDBLACKNODE_H
#define TRABALHO_ED2_1_REDBLACKNODE_H


class RedBlackNode {
    private:
        double enderecoMemoria;
        char* id;

        bool cor;
        RedBlackNode *esq, *dir, *pai;

    public:
        static const int id_size = 90;
        // Constructor
        RedBlackNode(double enderecoMemoria, char* id);
        ~RedBlackNode();

        bool getCor() const;
        void setCor(bool cor);
        RedBlackNode *getEsq() const;
        void setEsq(RedBlackNode *esq);
        RedBlackNode *getDir() const;
        void setDir(RedBlackNode *dir);
        RedBlackNode *getPai() const;
        void setPai(RedBlackNode *parent);

    double getEnderecoMemoria() const;

    void setEnderecoMemoria(double enderecoMemoria);

    char *getId() const;

    void setId(char *id);

};


#endif //TRABALHO_ED2_1_REDBLACKNODE_H
