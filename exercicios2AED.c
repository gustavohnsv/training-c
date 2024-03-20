// ex1: espelhar uma árvore

// ex2: exibir N maiores chaves de uma ABB

// ex3: exibir n chaves mais pŕomixas da raiz

// ex4: criar lista ligada c/todos elementos cuja chave é maior do que a do pai em árvore não ordenada

// ex5: verificar se uma árvore é ABB, retornando TRUE/FALSE

// ex6: verificar se árvore é assimétrica,retornando true/false

// ex7: verificar se árvore é cheia, retornando TRUE/FALSE

//(avançado) ex8: dada uma ABB e uma chave ch, encontre o antecessor de ch na sequência crescente de chaves

// ex 9: verifica se é ABB

/*ex 10: encontrar o pai de um elemento ch
 (i) em árvore comum
 (ii) em ABB/AVL*/

// ex 11: exibir chaves do nível n

// ex 12: em árvore não ordenada, mover a subárvore de raiz p1 para a esquerda do p2, que é vazio

// ex 13: excluir todo filho à esquerda que tenham no máximo 1 filho usando pós ordem

// ex 14: encontrar o 1° ancestral comum a ch1 e ch2 em ABB
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct aux
{
    int chave;
    struct aux *esq; // LADO ESQUERDO
    struct aux *dir; // LADO DIREITO
} NO;

NO *buscaABB(NO *p, int ch, NO **pai)
{
    *pai = NULL;
    while (p)
    {
        if (p->chave == ch)
            return p;
        *pai = p;
        if (p->chave > ch)
            p = p->esq;
        else
            p = p->dir;
    }
    return p;
}

bool inserirABB(NO **raiz, int ch)
{
    NO *pai;
    NO *p = buscaABB(*raiz, ch, &pai);
    if (p)
        return false;

    NO *novo = (NO *)malloc(sizeof(NO));
    novo->chave = ch;
    novo->dir = NULL;
    novo->esq = NULL;

    if (!pai)
    {
        *raiz = novo;
        return true;
    }

    if (novo->chave < pai->chave)
        pai->esq = novo;
    else
        pai->dir = novo;
    return true;
}

void exibirABB(NO *p)
{
    if (p)
    {
        exibirABB(p->esq);
        printf("%d ", p->chave);
        exibirABB(p->dir);
    }
}

void exibirESQ(NO *p)
{
    if (p)
    {
        exibirESQ(p->esq);
        if (p->esq)
            printf("%d ", p->esq->chave);
        exibirESQ(p->dir);
    }
}

void exibirDIR(NO *p)
{
    if (p)
    {
        exibirDIR(p->esq);
        if (p->dir)
            printf("%d ", p->dir->chave);
        exibirDIR(p->dir);
    }
}

void espelharABB(NO *p)
{
    if (p)
    {
        espelharABB(p->esq);
        espelharABB(p->dir);
        NO *aux = p->esq;
        p->esq = p->dir;
        p->dir = aux;
    }
}

void exibirMaiores(NO *p, int N, int *counter)
{
    if (p)
    {
        exibirMaiores(p->dir, N, counter);
        if (*counter < N)
        {
            printf("%d ", p->chave);
            (*counter)++;
        }
        exibirMaiores(p->esq, N, counter);
    }
}

int ehABB(NO *p)
{
    if (p)
    {
        if ((p->esq && p->esq->chave > p->chave) || (p->dir && p->dir->chave < p->chave))
            return -1;

        if (ehABB(p->esq) == -1 || ehABB(p->dir) == -1)
            return -1;
    }
    return 0;
}

bool verificarSimetrica(NO *p, bool ok)
{
    if (p)
    {
        if (p->dir && p->esq)
            ok = true;
        verificarSimetrica(p->esq, ok);
        verificarSimetrica(p->dir, ok);
    }
    return ok;
}

bool verificarCheia(NO *p)
{
    if (p == NULL)
    {
        return true; // Árvore vazia é considerada cheia
    }

    if ((p->esq == NULL && p->dir != NULL) || (p->esq != NULL && p->dir == NULL))
    {
        return false; // Se um dos filhos está vazio e o outro não, a árvore não é cheia
    }

    return verificarCheia(p->esq) && verificarCheia(p->dir);
}

int verificarPai(NO *p, int ch)
{
    if (p)
    {
        if (p->esq && p->esq->chave == ch)
            return p->chave;
        if (p->dir && p->dir->chave == ch)
            return p->chave;
        int paiEsquerda = verificarPai(p->esq, ch);
        if (paiEsquerda != 0)
            return paiEsquerda;
        return verificarPai(p->dir, ch);
    }
    return 0;
}

void buscarNO(NO *p, NO **resp, int ch)
{
    if (p)
    {
        if (p->chave == ch)
            *resp = p;
        if (*resp == NULL)
            buscarNO(p->esq, resp, ch);
        if (*resp == NULL)
            buscarNO(p->dir, resp, ch);
    }
}

// CÓDIGO DE PROVA (FEITO)
int contarMaiores(NO *raiz, int ch)
{
    NO *resp = NULL;
    buscarNO(raiz, &resp, ch);
    NO *aux = resp;
    while (aux)
    {
        if (aux->esq && aux->esq->chave > ch)
            printf("%d ", aux->esq->chave);
        if (aux->dir)
            printf("%d ", aux->dir->chave);
        aux = aux->dir;
    }
    return 0;
}

// CÓDIGO DE PROVA (FEITO)

int max(int a, int b)
{
    if (a > b)
        return a;
    else
        return b;
}

int contarNiveis(NO *p)
{
    if (!p)
        return 0;
    if (!p->esq && !p->dir)
        return 1;
    return (1 + max(contarNiveis(p->esq), contarNiveis(p->dir)));
}

// CÓDIGO DE PROVA (NAO FEITO)

NO* folhasParaLista(NO *p, NO **pai, NO **resp)
{
    if (p)
    {
        folhasParaLista(p->esq, pai, resp);
        folhasParaLista(p->dir, pai, resp);
        if (!p->esq && !p->dir)
        { // FOLHA
            printf("%d ", p->chave);
            if (!*resp)
            {
                *pai = p;
                *resp = *pai;
            }
            else
            {
                (*pai)->esq = p;
                *pai = p;
            }
        }
    }
    return *resp;
}

// Função para encontrar o primeiro ancestral comum
int acharAncestral(NO* p, int ch1, int ch2) {
    while (p) { // ENQUANTO EXISTIR NÓS
        if (p->chave > ch1 && p->chave > ch2) // VERIFICA SE O ATUAL É MAIOR QUE OS DOIS
            p = p->esq; // SE FOR, SEGUE PELA ESQUERDA
        else if (p->chave < ch1 && p->chave < ch2) //CASOCONTRARIO, SE FOR MENOR QUE OS DOIS
            p = p->dir; //SEGUE PELA DIREITA
        else
            return p->chave; // SE HOUVER UM DESEQUILIBRIO, RETORNA O ATUAL (ATUAL "DIVIDE" O CAMINHO DOS DOIS)
    }

    return 0; // Se não encontrar nenhum ancestral comum
}

int main()
{
    NO *arvore = NULL;
    inserirABB(&arvore, 10);
    inserirABB(&arvore, 50);
    inserirABB(&arvore, 20);
    inserirABB(&arvore, 30);
    inserirABB(&arvore, 40);
    inserirABB(&arvore, 5);
    inserirABB(&arvore, 7);
    inserirABB(&arvore, 3);
    // exibirABB(arvore);
    // printf("\n");
    // exibirESQ(arvore);
    // printf("\n");
    // exibirDIR(arvore);
    // int contador = 0;
    // exibirMaiores(arvore, 2, &contador);
    // printf("%d", ehABB(arvore));
    // bool ok = verificarSimetrica(arvore, &ok);
    // bool resultado = verificarCheia(arvore);
    // if (resultado)
    //    printf("Simétrica/Cheia");
    // else
    //    printf("Não simétrica/Não cheia");
    // printf("%d", verificarPai(arvore, 20));
    // NO* resp = NULL;
    // buscarNO(arvore, &resp, 20);
    // contarMaiores(arvore, 20);
    // printf("%d", contarNiveis(arvore));
    printf("%d", acharAncestral(arvore, 40, 30));
    return 0;
}