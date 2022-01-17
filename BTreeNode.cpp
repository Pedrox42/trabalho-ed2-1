#include "BTreeNode.h"
#include <iostream>

using namespace std;

BTreeNode::BTreeNode(int grau, bool folha, int tamanho){
    this->grau = grau;
    this->folha = folha;
    this->n = 0;
    this->tamanho = tamanho;
    this->valores = new data[tamanho];
    this->chaves = new BTreeNode*[tamanho+1];//para compensar o valor de chaves
}

BTreeNode::~BTreeNode() {

    delete [] chaves;
    delete [] valores;
}

int BTreeNode::getGrau() {
    return this->grau;
}

void BTreeNode::setGrau(int grau) {
    this->grau = grau;
}

BTreeNode** BTreeNode::getChaves() {
    return this->chaves;
}

void BTreeNode::setChaves(BTreeNode **chaves) {
    *this->chaves = *chaves;
}

int BTreeNode::getN() {
    return this->n;
}

void BTreeNode::setN(int n) {
    this->n = n;
}

bool BTreeNode::isFolha() {
    return this->folha;
}

void BTreeNode::setFolha(bool folha) {
    this->folha = folha;
}

int BTreeNode::getTamanho(){
    return this->tamanho;
}

void BTreeNode::setTamanho(int tamanho) {
    this->tamanho = tamanho;
}

bool BTreeNode::compararId(char* id1, char* id2, double* comparacoes){
    int i = 0;
    (*comparacoes)++;
    for(i = 0; id1[i] != '\0' && id1[i] == id2[i]; i++);
    return id1[i] > id2[i];
}

bool BTreeNode::idIgual(char* id1, char* id2, double* comparacoes){
    int i = 0;
    (*comparacoes)++;
    for(i = 0; id1[i] != '\0' && id1[i] == id2[i]; i++);
    return id1[i] == id2[i];
}


// funcao para pesquisar um id na arvore
BTreeNode *BTreeNode::buscar(char* id, double* comparacoes)
{
    //achar o primeiro valor maior que o id
    int i = 0;
    while (i < n && compararId(id, valores[i].idText, comparacoes)){
        i++;
    }

    // verificar se a chave eh igual
    if (i < n && idIgual(id, valores[i].idText, comparacoes)){
        return this;
    }

    // caso a chave nao tenha sido achada e seja uma folha
    if (folha){
        return nullptr;
    }

    // continuar busca no filho apropriado caso nao seja folha
    return chaves[i]->buscar(id, comparacoes);
}

void BTreeNode::inserirNaoCompleto(char* id, double endereco, double* comparacoes)
{

    // inicializa como no index mais a direita
    int i = n-1;

    // se eh folha ou esta dentro do tamanho possivel
    if (folha)
    {
        //encontra a posicao para o novo id e rarranja os ids "maiores"
        (*comparacoes)++;
        while (i >= 0 && compararId(valores[i].idText, id, comparacoes))
        {
            valores[i+1] = valores[i];
            i--;
        }

        //insere o valor na nova localizacao
        valores[i+1].idText = id;
        valores[i+1].endereco = endereco;
        n++;
    }
    else // se nao e folha
    {
        // encontrando a chave para o valor
        while (i >= 0 && compararId(valores[i].idText, id, comparacoes)){
            i--;
        }

        // verificando se o filho encontrado esta completo
        if (chaves[i+1]->getN() == tamanho)
        {
            // se estiver completo, utilizar o split
            splitFilho(i+1, chaves[i+1]);

            if (compararId(id, valores[i+1].idText, comparacoes)){
                i++;
            }
        }
        chaves[i+1]->inserirNaoCompleto(id, endereco, comparacoes);
    }
}

//funcao para splitar filho
void BTreeNode::splitFilho(int i, BTreeNode *y)
{
    // criando no novo
    BTreeNode *z = new BTreeNode(y->grau, y->folha, y->tamanho);
    z->n = grau - 1;

    // passando as chaves depois do grau
    for (int j = 0; j < grau-1; j++)
        z->valores[j] = y->valores[j+grau];

    // copiar o ultimo de grau filho de y para z
    if (!y->folha)
    {
        for (int j = 0; j < grau; j++)
            z->chaves[j] = y->chaves[j+grau];
    }

    // reduzir o numero de chaves
    y->n = grau - 1;

    // criando uma chave e espaco para uma nova chave
    for (int j = n; j >= i+1; j--)
        chaves[j+1] = chaves[j];

    //linkando o novo no
    chaves[i+1] = z;

    //buscando um novo no e movendo as chaves para abrir espaco
    for (int j = n-1; j >= i; j--)
        valores[j+1] = valores[j];

    //copiando a espaco de y para
    valores[i] = y->valores[grau-1];

    // incrementando n
    n++;
}

// navegar entre os nos
void BTreeNode::navegar()
{
    //navegando pelos nos de i
    int i;
    for (i = 0; i < n; i++)
    {
        // se nao e uma folha, percorrer as chaves antes de imprimir,
        if (!folha)
            chaves[i]->navegar();
        cout <<  "id: " << valores[i].idText << " endereco: " << valores[i].endereco << endl;
    }

    //  imprimindo os valores do ultimo no
    if (!folha)
        chaves[i]->navegar();
}