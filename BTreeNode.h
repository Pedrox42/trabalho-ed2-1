#ifndef TRABALHO_ED2_1_BTREENODE_H
#define TRABALHO_ED2_1_BTREENODE_H


class BTreeNode
{
    private:
        char valores[90][1000];  // Array contendo os valores
        int grau;      // grau minimino de chaves preenchidas
        BTreeNode *chaves[1001]; // array dos ponteiros/enderecos de memoria
        int n;     // numero atual de chaves
        bool folha; // é verdadeiro quando um no é folha
        int tamanho;
    public:

        // Construtor
        BTreeNode(int grau, bool folha, int tamanho);

        //função para adicionar um novo id, desde que nao  o no esteja preenchido por completo
        void inserirNaoCompleto(char* id);

        //funcao para dar split no filho do no y e i é o index de y apontando para o
        // no filho que sera splitado, o no filho deve estar cheio
        // child array C[].  The Child y must be full when this function is called
        void splitFilho(int i, BTreeNode *y);

        // funcao para navegar a arvore
        void navegar();

        // funcao para buscar um valor dentro no
        BTreeNode *buscar(char* id);// retorna null se k nao existir

        int getGrau();

        void setGrau(int grau);

        BTreeNode** getChaves();

        void setChaves(BTreeNode **chaves);

        int getN();

        void setN(int n);

        bool isFolha();

        void setFolha(bool folha);

    int getTamanho();

    void setTamanho(int tamanho);


    friend class BTree;

    bool compararId(char *id1, char *id2);

    bool idIgual(char *id1, char *id2);
};


#endif //TRABALHO_ED2_1_BTREENODE_H
