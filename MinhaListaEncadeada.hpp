#ifndef LISTAENCADEADAABSTRATA_HPP
#define LISTAENCADEADAABSTRATA_HPP

#include <exception>
#include <stdexcept>

class posicao_invalida_exception : public std::exception
{
    virtual const char *what() const throw()
    {
        return "Posicao invalida na lista encadeada";
    }
};

class lista_encadeada_vazia_exception : public std::exception
{
    virtual const char *what() const throw()
    {
        return "Lista encadeada vazia";
    }
};

class nao_implementado_exception : public std::runtime_error
{
public:
    nao_implementado_exception() : std::runtime_error{"esta funcao ainda nao foi implementada"}
    {
    }
};

template <typename T>
struct Elemento
{
    Elemento *_proximo;
    T _dado;
};

template <typename T>
class ListaEncadeadaAbstrata
{
protected:
    Elemento<T> *_primeiro;
    int _tamanho;

public:
    virtual ~ListaEncadeadaAbstrata()
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

    virtual int posicao(T *umDado)
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

    virtual bool contem(T *umDado)
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

    virtual void adicionaNoInicio(T *umDado)
    {
        Elemento<T> *novo = new Elemento<T>;
        novo->_proximo = this->_primeiro;
        novo->_dado = umDado;
        this->_primeiro = novo;
        this->_tamanho++;
    }

    virtual void adicionaNaPosicao(T *umDado, int umaPosicao)
    {
        if (umaPosicao > (this->_tamanho + 1) || umaPosicao <= 0)
        {
            throw posicao_invalida_exception();
        }

        if (umaPosicao == 1)
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

    virtual void adicionaNoFim(T *umDado)
    {
        adicionaNaPosicao(umDado, this->_tamanho);
    }

    virtual T *retiraDoInicio()
    {
        if (estaVazia())
        {
            throw lista_encadeada_vazia_exception();
        }
        else
        {
            Elemento<T> *retirado;
            T *umDado;
            retirado = this->_primeiro;
            umDado = retirado->_dado;
            this->_primeiro = retirado->_proximo;
            this->_tamanho--;
            delete retirado;
            return umDado;
        }
    }

    virtual T *retiraDaPosicao(int umaPosicao)
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
            T *umDado;
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

    virtual T *retiraDoFim()
    {
        return retiraDaPosicao(this->_tamanho);
    }

    virtual T *retiraEspecifico(T *umDado)
    {
        int umaPosicao = posicao(umDado);
        return retiraDaPosicao(umaPosicao);
    }
};

#endif
