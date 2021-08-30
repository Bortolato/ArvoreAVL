#ifndef MINHALISTAENCADEADA_H
#define MINHALISTAENCADEADA_H

#include "ListaEncadeadaAbstrata.hpp"

template <typename T>
class MinhaListaEncadeada : public ListaEncadeadaAbstrata<T>
{

public:
    MinhaListaEncadeada()
    {
        this->_primeiro = nullptr;
        this->_tamanho = 0;
    }

    ~MinhaListaEncadeada()
    {
        Elemento<T> *aux, *proximo;

        aux = this->_primeiro;
        for (int i = 0; i < this->_tamanho; i++)
        {
            proximo = aux->_proximo;
            delete aux;
            aux = proximo;
        }
    }

    virtual bool estaVazia()
    {
        if (this->_tamanho == 0)
        {
            return true;
        }
        return false;
    }

    virtual int getTamanho()
    {
        return this->_tamanho;
    }

    virtual int posicao(T umDado)
    {
        Elemento<T> *aux;
        aux = this->_primeiro;
        int i = 0;

        for (i = 1; i <= this->_tamanho; i++)
        {
            if (aux->_dado == umDado)
                return i;
            else
            {
                aux = aux->_proximo;
            }
        }

        //delete aux;

        return i;
    }

    virtual bool contem(T umDado)
    {
        Elemento<T> *aux;
        aux = this->_primeiro;

        for (int i = 1; i <= this->_tamanho; i++)
        {
            if (aux->_dado == umDado)
                return true;
            else
            {
                aux = aux->_proximo;
            }
        }

        //delete aux;

        return false;
    }

    virtual void adicionaNoInicio(T umDado)
    {
        Elemento<T> *novo = new Elemento<T>;
        novo->_proximo = this->_primeiro;
        novo->_dado = umDado;
        this->_primeiro = novo;
        this->_tamanho++;
    }

    virtual void adicionaNaPosicao(T umDado, int umaPosicao)
    {
        if (umaPosicao > (this->_tamanho + 1) || umaPosicao < 0)
        {
            throw posicao_invalida_exception();
        }

        if (umaPosicao == 0)
        {
            adicionaNoInicio(umDado);
            return;
        }

        Elemento<T> *novo = new Elemento<T>;
        Elemento<T> *aux;
        novo->_dado = umDado;
        aux = this->_primeiro;

        for (int i = 1; i < umaPosicao; i++)
        {
            aux = aux->_proximo;
        }

        novo->_proximo = aux->_proximo;
        aux->_proximo = novo;
        this->_tamanho++;

        //delete aux;
    }

    virtual void adicionaNoFim(T umDado)
    {
        adicionaNaPosicao(umDado, this->_tamanho);
    }

    virtual T retiraDoInicio()
    {
        if (estaVazia())
        {
            throw lista_encadeada_vazia_exception();
        }
        else
        {
            Elemento<T> *retirado;
            T
                umDado;
            retirado = this->_primeiro;
            umDado = retirado->_dado;
            this->_primeiro = retirado->_proximo;
            this->_tamanho--;
            delete retirado;
            return umDado;
        }
    }

    virtual T retiraDaPosicao(int umaPosicao)
    {
        if (estaVazia())
        {
            throw lista_encadeada_vazia_exception();
        }
        if (umaPosicao <= 0 || umaPosicao > this->_tamanho)
        {
            throw posicao_invalida_exception();
        }
        if (umaPosicao == 1)
        {
            return retiraDoInicio();
        }
        else
        {
            Elemento<T> *retirado;
            Elemento<T> *aux;
            T
                umDado;
            aux = this->_primeiro;

            for (int i = 1; i < umaPosicao - 1; i++)
            {
                aux = aux->_proximo;
            }
            retirado = aux->_proximo;
            aux->_proximo = retirado->_proximo;
            umDado = retirado->_dado;
            this->_tamanho--;

            delete retirado;
            return umDado;
        }
    }

    virtual T
    retiraDoFim()
    {
        return retiraDaPosicao(this->_tamanho);
    }

    virtual T
    retiraEspecifico(T
                         umDado)
    {
        int umaPosicao = posicao(umDado);
        return retiraDaPosicao(umaPosicao);
    }
};

#endif