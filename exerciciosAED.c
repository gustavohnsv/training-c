#include <stdio.h>
#include <stdlib.h>

typedef struct est
{
    int chave;
    struct est *prox;
} NO;

typedef struct est3
{
    int chave;
    struct est3 *prox;
    struct est3 *ant;
} NO2;

typedef struct
{
    NO2 *inicio;
} LISTADUPLA;

typedef struct est2
{
    int chave;
    int cl;
    int ln;
    struct est2 *prox;
} NOMATRIZ;

typedef struct
{
    NO *inicio;
} listaSimples;

typedef struct
{
    NOMATRIZ *inicio;
    int maxCl;
    int maxLn;
} matrizEsparsa;

void criarMatrizEsparsa(matrizEsparsa *m, int n)
{
    m->maxCl = n;
    m->maxLn = n;
    m->inicio = NULL;
    return;
}

void adicionarElementoMatriz(matrizEsparsa *m, int i, int j, int key)
{
    NOMATRIZ *ultimo = NULL;
    NOMATRIZ *p = m->inicio;
    if (p)
    {
        while (p)
        {
            ultimo = p;
            p = p->prox;
        }
    }

    NOMATRIZ *novo = (NOMATRIZ *)malloc(sizeof(NOMATRIZ));
    novo->chave = key;
    novo->ln = i;
    novo->cl = j;
    novo->prox = NULL;
    if (!m->inicio)
        m->inicio = novo;
    else
        ultimo->prox = novo;
    return;
}

void exibirLinha(matrizEsparsa *m, int i)
{
    NOMATRIZ *p = m->inicio;
    NOMATRIZ *aux = p;
    int value = 0;
    while (aux->ln <= i)
    {
        if (aux->ln == i)
        {
            for (; value <= aux->cl; value++)
            {
                if (value == aux->ln)
                    printf("%d ", aux->chave);
                else
                    printf("0 ");
            }
        }
        aux = aux->prox;
    }
    return;
}

void zerarDiagonalPrincipal(matrizEsparsa *m)
{
    NOMATRIZ *p = m->inicio;
    NOMATRIZ *ant = NULL;
    while (p)
    {
        if (p->cl == p->ln)
        {
            if (p->prox == m->inicio->prox)
            {
                m->inicio = p->prox;
                free(p);
            }
            else
            {
                ant->prox = p->prox;
                free(p);
            }
        }
        ant = p;
        p = p->prox;
    }
    return;
}

void exibirMatriz(matrizEsparsa *m)
{
    NOMATRIZ *p = m->inicio;
    while (p)
    {
        printf("%d\n", p->chave);
        p = p->prox;
    }
    return;
}

void exibirDiagonal(matrizEsparsa *m)
{
    NOMATRIZ *p = m->inicio;
    int col = 0;
    while (p)
    {
        if (p->cl == p->ln)
        {
            for (int i = col; i <= p->cl; i++)
            {
                if (i == p->cl)
                    printf("%d ", p->chave);
                else
                    printf("0 ");
                col = i + 1;
            }
        }
        p = p->prox;
    }
    return;
}

NO2 *listaNumerada(int n)
{
    NO2 *resp = NULL;
    NO2 *aux = resp; // NULL por padrão
    for (int i = 1; i <= n+1; i++)
    {
        NO2 *novo = (NO2 *)malloc(sizeof(NO2));
        novo->chave = i;
        if (!resp)
        {
            novo->prox = novo;
            novo->ant = novo;
            resp = novo;
        }
        else
        {
            novo->prox = resp;
            novo->ant = aux;
            aux->prox = novo;
            resp->ant = novo;
        }
        aux = novo;
    }
    return (resp);
}

void exibirLista(NO2 *l)
{
    NO2 *p = l;
    while (p->prox != l)
    {
        printf("Anterior: %p\n", p->ant);
        printf("Chave: %d\n", p->chave);
        printf("Endereco: %p\n", p);
        printf("Proximo: %p\n", p->prox);
        p = p->prox;
    }
    return;
}

int main()
{
    NO2 *listadupla = listaNumerada(5);
    exibirLista(listadupla);
    return 0;
}

/*
    matrizEsparsa *matriz = (matrizEsparsa *)malloc(sizeof(matrizEsparsa));

    criarMatrizEsparsa(matriz, 10);
    adicionarElementoMatriz(matriz, 1, 1, 10);
    adicionarElementoMatriz(matriz, 2, 3, 20);
    adicionarElementoMatriz(matriz, 3, 4, 30);
    adicionarElementoMatriz(matriz, 3, 8, 40);
    adicionarElementoMatriz(matriz, 9, 9, 50);

    // zerarDiagonalPrincipal(matriz);
    // exibirMatriz(matriz);
    exibirDiagonal(matriz);

*/