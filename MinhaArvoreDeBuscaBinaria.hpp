#ifndef MINHA_ARVORE_DE_BUSCA_BINARIA_HPP
#define MINHA_ARVORE_DE_BUSCA_BINARIA_HPP

#include "ArvoreDeBuscaBinaria.hpp"

/**
 * @brief Representa uma árvore binária de busca.
 * 
 * @tparam T O tipo de dado guardado na árvore.
 */
template <typename T>
class MinhaArvoreDeBuscaBinaria : public ArvoreDeBuscaBinaria<T>
{
    ArvoreDeBuscaBinaria();
    virtual ~ArvoreDeBuscaBinaria();

    /**
     * @brief Verifica se a arvore esta vazia
     * @return Verdade se a arvore esta vazia.
     */
    virtual bool vazia()
    {
        if (this->_raiz == nullptr)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    /**
     * @brief Retornar quantidade de chaves na arvore
     * @return Numero natural que representa a quantidade de chaves na arvore
     */
    virtual int quantidade()
    {
        if (vazia())
        {
            return 0;
        }
        else
        {
        }
    }

    /**
     * @brief Verifica se a arvore contem uma chave
     * @param chave chave a ser procurada na arvore
     * @return Verdade se a arvore contem a chave
     */
    virtual bool contem(T chave)
    {

        Nodo *aux = _raiz;

        while (aux != 0)
        {

            if (chave == aux->chave)
            {
                return true
            }

            // se a chave for menor
            if (chave < aux->chave)
            {
                aux = aux->filhoEsquerda;
            }

            // se a chave for maior
            if (chave > aux->chave)
            {
                aux = aux->filhoDireita;
            }
        }
        return false;
    }

    /**
     * @brief Retorna a altura da (sub)arvore
     * @param chave chave que é raiz da (sub)arvore cuja altura queremos. Se chave é nula, retorna a altura da arvore.
     * @return Numero inteiro representando a altura da (subarvore). Se chave nao esta na arvore, retorna std::nullopt
     */
    virtual std::optional<int> altura(T chave)
    {
        if (chave == nullptr)
        {
            return _raiz->altura;
        }
        Nodo *aux = _raiz;

        while (aux != 0)
        {

            if (chave == aux->chave)
            {
                return aux->altura;
            }

            // se a chave for menor
            if (chave < aux->chave)
            {
                aux = aux->filhoEsquerda;
            }

            // se a chave for maior
            if (chave > aux->chave)
            {
                aux = aux->filhoDireita;
            }
        }
        return std::nullopt
    }

    /**
     * @brief Insere uma chave na arvore
     * @param chave chave a ser inserida
     */
    virtual void inserir(T chave)
    {

        // insere na raiz
        if (_raiz == nullptr)
        {
            Nodo<T> *novo = (Nodo<T> *)calloc(1, sizeof(Nodo<T>));
            novo->chave = chave;
            novo->filhoEsquerda = nullptr;
            novo->filhoDireita = nullptr;
            novo->altura = 0;
            return novo;
        }
        else
        {
        }
    }

    /**
     * @brief Remove uma chave da arvore
     * @param chave chave a removida
     * @return Retorna a chave removida ou nullptr se a chave nao esta na arvore
     */
    virtual void remover(T chave)
    {
    }

    /**
     * @brief Busca a chave do filho a esquerda de uma (sub)arvore
     * @param chave chave da arvore que eh pai do filho a esquerda
     * @return Chave do filho a esquerda. Se chave nao esta na arvore, retorna std::nullopt
     */
    virtual std::optional<T> filhoEsquerdaDe(T chave) const = 0;

    /**
     * @brief Busca a chave do filho a direita de uma (sub)arvore
     * @param chave chave da arvore que eh pai do filho a direita
     * @return Chave do filho a direita. Se chave nao esta na arvore, retorna nullptr
     */
    virtual std::optional<T> filhoDireitaDe(T chave) const = 0;

    /**
     * @brief Lista chaves visitando a arvore em ordem
     * @return Lista encadeada contendo as chaves em ordem. 
     */
    virtual ListaEncadeadaAbstrata<T> *emOrdem() const = 0;

    /**
     * @brief Lista chaves visitando a arvore em pre-ordem
     * @return Lista encadeada contendo as chaves em pre-ordem. 
     */
    virtual ListaEncadeadaAbstrata<T> *preOrdem() const = 0;

    /**
     * @brief Lista chaves visitando a arvore em pos-ordem
     * @return Lista encadeada contendo as chaves em pos ordem. 
     */
    virtual ListaEncadeadaAbstrata<T> *posOrdem() const = 0;
};

template <typename T>
ArvoreDeBuscaBinaria<T>::ArvoreDeBuscaBinaria() : _raiz{}
{
}

template <typename T>
ArvoreDeBuscaBinaria<T>::~ArvoreDeBuscaBinaria() = default;
}
;

#endif
