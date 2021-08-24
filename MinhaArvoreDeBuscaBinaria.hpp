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
private:
    int quantidadeChaves;

public:
    ArvoreDeBuscaBinaria()
    {
        this->_raiz = nullptr;
        this->quantidadeChaves = 0;
    }

    // percorrer toda a árvore para eliminar nodo por nodo (usar delete?)
    virtual ~ArvoreDeBuscaBinaria() {}

    /**
     * @brief Verifica se a arvore esta vazia
     * @return Verdade se a arvore esta vazia.
     */
    virtual bool vazia() const
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
    virtual int quantidade() const
    {
        if (vazia())
        {
            return 0;
        }
        else
        {
            return this->quantidadeChaves;
        }
    }

    /**
     * @brief Verifica se a arvore contem uma chave
     * @param chave chave a ser procurada na arvore
     * @return Verdade se a arvore contem a chave
     */
    virtual bool contem(T chave) const
    {

        Nodo<T> *aux = this->_raiz;

        while (aux != nullptr)
        {
            if (chave == aux->chave)
            {
                return true;
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
    virtual std::optional<int> altura(T chave) const
    {

        Nodo<T> *aux = this->_raiz;

        while (aux != nullptr)
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
        return std::nullopt;
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
            Nodo<T> *novo = new Nodo<T>; //Esta certo ??
            novo->chave = chave;
            novo->filhoEsquerda = nullptr;
            novo->filhoDireita = nullptr;
            novo->altura = 0;
            this->quantidadeChaves++;
            return novo;
        }
        // insere no restante da arvore
        else
        {
            Nodo<T> *auxPai = this->_raiz;
            Nodo<T> *aux;
            int altura = 0;

            // setando qual subárvore vai começar o aux
            // como tratar o caso de ter a mesma chave?
            // como calcular a altura?
            if (chave < auxPai->chave)
                aux = auxPai->filhoEsquerda;
            if (chave > auxPai->chave)
                aux = auxPai->filhoDireita;

            // localiza o lugar que será adicionado
            while (aux != nullptr)
            {
                auxPai = aux;
                if (chave < aux->chave)
                    aux = aux->filhoEsquerda;
                if (chave > aux->chave)
                    aux = aux->filhoDireita;
            }

            // criacao do novo nodo
            Nodo<T> *novo = new Nodo<T>;
            novo->chave = chave;
            novo->filhoEsquerda = nullptr;
            novo->filhoDireita = nullptr;

            // seta o novo no na subarvore adequada
            if (chave < auxPai->chave)
                auxPai->filhoEsquerda = novo;
            if (chave > auxPai->chave)
                auxPai->filhoDireita = novo;
            this->quantidadeChaves++;
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

    // esta correto a declaração da função T?
    T chaveFilho(Nodo<T> *aux, int filho)
    {
        // filho da esquerda
        if (filho == 0)
        {
            return aux->filhoEsquerda->chave;
        }

        // filho da direita
        if (filho == 1)
        {
            return aux->filhoDireita->chave;
        }
    }

    /**
     * @brief Busca a chave do filho a esquerda de uma (sub)arvore
     * @param chave chave da arvore que eh pai do filho a esquerda
     * @return Chave do filho a esquerda. Se chave nao esta na arvore, retorna std::nullopt
     */
    virtual std::optional<T> filhoEsquerdaDe(T chave) const
    {
        Nodo<T> *aux = this->_raiz;

        while (aux != nullptr)
        {
            if (chave == aux->chave)
            {
                return chaveFilho(aux, 0); // essa chamada de função esta certo? no return?
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
        return nullptr;
    }

    /**
     * @brief Busca a chave do filho a direita de uma (sub)arvore
     * @param chave chave da arvore que eh pai do filho a direita
     * @return Chave do filho a direita. Se chave nao esta na arvore, retorna nullptr
     */
    virtual std::optional<T> filhoDireitaDe(T chave) const
    {
        Nodo<T> *aux = this->_raiz;

        while (aux != nullptr)
        {
            if (chave == aux->chave)
            {
                return chaveFilho(aux, 1); // essa chamada de função esta certo? no return?
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
        return nullptr;
    }

    /**
     * @brief Lista chaves visitando a arvore em ordem
     * @return Lista encadeada contendo as chaves em ordem. 
     */
    virtual ListaEncadeadaAbstrata<T> *emOrdem() const
    {
        ListaEncadeadaAbstrata<T> *lista = new MinhaListaEncadeada<T>;
        Nodo *aux = this->_raiz;

        if (this->_raiz != nullptr)
        {
            emOrdem_aux(aux->filhoEsquerda, lista);
            lista->adicionaNoFim(this->_raiz->chave);
            emOrdem_aux(aux->filhoDireita, lista);
        }
    }

    void emOrdem_aux(Nodo<T> *aux, ListaEncadeadaAbstrata<T> *l)
    {
        if (aux != nullptr)
        {
            emOrdem_aux(aux->filhoEsquerda, l);
            l->adicionaNoFim(aux->chave);
            emOrdem_aux(aux->filhoDireita, l);
        }
    }

    /**
     * @brief Lista chaves visitando a arvore em pre-ordem
     * @return Lista encadeada contendo as chaves em pre-ordem. 
     */
    virtual ListaEncadeadaAbstrata<T> *preOrdem() const
    {
        ListaEncadeadaAbstrata<T> *lista = new MinhaListaEncadeada<T>;
        Nodo<T> *aux = this->_raiz;

        if (this->_raiz != nullptr)
        {
            lista->adicionaNoFim(aux->chave);
            preOrdem_aux(aux->filhoEsquerda, lista);
            preOrdem_aux(aux->filhoDireita, lista);
        }
    }

    void preOrdem_aux(Nodo<T> *aux, ListaEncadeadaAbstrata<T> *l)
    {
        if (aux != nullptr)
        {
            l->adicionaNoFim(aux->chave);
            preOrdem_aux(aux->filhoEsquerda, l);
            preOrdem_aux(aux->filhoDireita, l);
        }
    }

    /**
     * @brief Lista chaves visitando a arvore em pos-ordem
     * @return Lista encadeada contendo as chaves em pos ordem. 
     */
    virtual ListaEncadeadaAbstrata<T> *posOrdem() const
    {
        ListaEncadeadaAbstrata<T> *lista = new MinhaListaEncadeada<T>;
        Nodo *aux = this->_raiz;

        if (this->_raiz != nullptr)
        {
            posOrdem_aux(aux->filhoEsquerda, lista);
            posOrdem_aux(aux->filhoDireita, lista);
            adicionaNoFim(this->_raiz->chave);
        }
    }

    void posOrdem_aux(Nodo<T> *aux, ListaEncadeadaAbstrata<T> *l)
    {
        if (aux != nullptr)
        {
            preOrdem_aux(aux->filhoEsquerda, l);
            preOrdem_aux(aux->filhoDireita, l);
            l->adicionaNoFim(aux->chave);
        }
    }
};

#endif
