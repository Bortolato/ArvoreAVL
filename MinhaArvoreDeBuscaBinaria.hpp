#ifndef MINHAARVOREDEBUSCABINARIA_HPP
#define MINHAARVOREDEBUSCABINARIA_HPP

#include "ArvoreDeBuscaBinaria.hpp"
#include <cassert>
#include <utility>
/**
 * @brief Representa uma árvore binária de busca.
 * 
 * @tparam T O tipo de dado guardado na árvore.
 */
template <typename T>
class MinhaArvoreDeBuscaBinaria : public ArvoreDeBuscaBinaria<T>
{
protected:
    int quantidadeChaves{0};

private:
    /**
     * @brief Auxiliar da destrutora para ser chamada recursivamente
     * @param aux nodo a ser destruido
     */
    void deletaEmOrdem(Nodo<T> *aux)
    {
        if (aux != nullptr)
        {
            if (aux->filhoEsquerda != nullptr)
            {
                deletaEmOrdem(aux->filhoEsquerda);
            }
            if (aux->filhoDireita != nullptr)
            {
                deletaEmOrdem(aux->filhoDireita);
            }
            delete aux;
        }
    }

    // como fazer com a altura??
    int inserirAux(Nodo<T> *aux, Nodo<T> *auxPai, T chave)
    {
        if (aux != nullptr)
        {
            if (chave < aux->chave)
            {
                aux->altura = inserirAux(aux->filhoEsquerda, aux, chave) + 1;
                return aux->altura;
            }
            else
            {
                aux->altura = inserirAux(aux->filhoDireita, aux, chave) + 1;
                return aux->altura;
            }
        }
        else
        {
            Nodo<T> *novo = new Nodo<T>;
            novo->chave = chave;
            this->quantidadeChaves++;

            if (chave < auxPai->chave)
            {
                auxPai->filhoEsquerda = novo;
            }
            else
            {
                auxPai->filhoDireita = novo;
            }
            return 0;
        }
        return 0;
    }

    void atualizaAltura(Nodo<T> *aux, T chave)
    {

        int contador = 0;
        Nodo<T> *aux2 = aux;

        while (chave != aux->chave)
        {
            contador++;
            if (chave < aux->chave)
            {
                aux = aux->filhoEsquerda;
            }
            else
            {
                aux = aux->filhoDireita;
            }
        }

        while (aux2 != aux)
        {
            if (aux2->altura < contador)
            {
                aux2->altura = contador;
            }

            contador--;

            if (chave < aux2->chave)
            {
                aux2 = aux2->filhoEsquerda;
            }
            else
            {
                aux2 = aux2->filhoDireita;
            }
        }
        return;
    }

    /** 
     *  @brief funcao auxiliar para retornar a chave do filho desejado
     *  @return caso filho = 0 retorna chave do filho da esquerda
     *  @return caso filho = 1 retorna chave do filho da direita
     */
    std::optional<T> chaveFilho(Nodo<T> *aux, int filho) const
    { // verificar se o filho nao é nulo caso sim retorn nullopt
        // filho da esquerda
        if (filho == 0)
        {
            if (aux->filhoEsquerda != nullptr)
            {
                return aux->filhoEsquerda->chave;
            }
        }

        // filho da direita
        if (filho == 1)
        {
            if (aux->filhoDireita != nullptr)
            {
                return aux->filhoDireita->chave;
            }
        }

        return std::nullopt;
    }

    void preOrdem_aux(Nodo<T> *aux, ListaEncadeadaAbstrata<T> *l) const
    {
        if (aux)
        {
            l->adicionaNoFim(aux->chave);
            preOrdem_aux(aux->filhoEsquerda, l);
            preOrdem_aux(aux->filhoDireita, l);
        }
        return;
    }

    void emOrdem_aux(Nodo<T> *aux, ListaEncadeadaAbstrata<T> *l) const
    {
        if (aux != nullptr)
        {
            emOrdem_aux(aux->filhoEsquerda, l);
            l->adicionaNoFim(aux->chave);
            emOrdem_aux(aux->filhoDireita, l);
        }
        return;
    }

    void posOrdem_aux(Nodo<T> *aux, ListaEncadeadaAbstrata<T> *l) const
    {
        if (aux != nullptr)
        {
            preOrdem_aux(aux->filhoEsquerda, l);
            preOrdem_aux(aux->filhoDireita, l);
            l->adicionaNoFim(aux->chave);
        }
        return;
    }

public:
    // construtor da arvore, inicializa uma arvore vazia
    MinhaArvoreDeBuscaBinaria()
    {
        this->quantidadeChaves = 0;
    }

    // destrutor que percorre toda a árvore para eliminar nodo por nodo
    virtual ~MinhaArvoreDeBuscaBinaria()
    {
        Nodo<T> *aux = this->_raiz;

        if (this->_raiz != nullptr)
        {
            if (aux->filhoEsquerda != nullptr)
            {
                deletaEmOrdem(aux->filhoEsquerda);
            }
            if (aux->filhoDireita != nullptr)
            {
                deletaEmOrdem(aux->filhoDireita);
            }
            delete aux;
        }
    }

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
        return this->quantidadeChaves;
    }

    /**
     * @brief Verifica se a arvore contem uma chave
     * @param chave chave a ser procurada na arvore
     * @return Verdade se a arvore contem a chave
     */
    virtual bool contem(T chave) const
    {
        if (this->_raiz == nullptr)
        {
            return false;
        }

        Nodo<T> *aux = this->_raiz;

        while (aux != nullptr)
        {
            if (chave == aux->chave)
            {
                return true;
            }

            if (chave < aux->chave)
            {
                aux = aux->filhoEsquerda;
            }
            else
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

            if (chave < aux->chave)
            {
                aux = aux->filhoEsquerda;
            }
            else
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
        if (this->_raiz == nullptr)
        {
            Nodo<T> *novo = new Nodo<T>;
            novo->chave = chave;
            this->quantidadeChaves++;
            this->_raiz = novo;
            return;
        }

        // insere no restante da arvore
        else
        {
            this->_raiz->altura = inserirAux(this->_raiz, this->_raiz, chave);
            //atualizaAltura(this->_raiz, chave);
        }
        return;
    }

    /**
     * @brief Remove uma chave da arvore
     * @param chave chave a removida
     */
    virtual void remover(T chave)
    {
        if (!contem(chave))
        {
            return;
        }
        else
        {
            Nodo<T> *auxPai = nullptr;
            Nodo<T> *aux = this->_raiz;

            // caso do nodo ser a raiz
            if (aux->chave == chave)
            {
                if ((aux->filhoEsquerda == nullptr) && (aux->filhoDireita == nullptr))
                {
                    this->quantidadeChaves--;
                    this->_raiz = nullptr;
                    delete aux;
                    return;
                }
                else if (aux->filhoDireita != nullptr)
                {
                    aux = aux->filhoDireita;
                    auxPai = aux;
                    while (aux->filhoEsquerda != nullptr)
                    {
                        auxPai = aux;
                        aux = aux->filhoEsquerda;
                    }
                    if (aux == auxPai)
                    {
                        auxPai->filhoEsquerda = this->_raiz->filhoEsquerda;
                        aux = this->_raiz;
                        delete aux;
                        this->_raiz = auxPai;
                        this->quantidadeChaves--;
                        return;
                    }
                    else
                    {
                        this->_raiz->chave = aux->chave;
                        auxPai->filhoEsquerda = nullptr;
                        delete aux;
                        this->quantidadeChaves--;
                        return;
                    }
                }
                else if (aux->filhoEsquerda != nullptr)
                {
                    aux = aux->filhoEsquerda;
                    auxPai = aux;
                    while (aux->filhoDireita != nullptr)
                    {
                        auxPai = aux;
                        aux = aux->filhoDireita;
                    }
                    if (aux == auxPai)
                    {
                        auxPai->filhoDireita = this->_raiz->filhoDireita;
                        aux = this->_raiz;
                        delete aux;
                        this->_raiz = auxPai;
                        this->quantidadeChaves--;
                        return;
                    }
                    else
                    {
                        this->_raiz->chave = aux->chave;
                        auxPai->filhoDireita = nullptr;
                        delete aux;
                        this->quantidadeChaves--;
                        return;
                    }
                }
                return;
            }
            auxPai = nullptr;
            aux = this->_raiz;
            // encontra qual o nodo a ser removido e seu pai
            while (aux->chave != chave)
            {
                auxPai = aux;
                if (chave < aux->chave)
                {
                    aux = aux->filhoEsquerda;
                }
                else
                {
                    aux = aux->filhoDireita;
                }
            }

            // remocao no caso do nodo ser uma folha
            if ((aux->filhoEsquerda == nullptr) && (aux->filhoDireita == nullptr))
            {
                if (auxPai->filhoEsquerda == aux)
                {
                    auxPai->filhoEsquerda = nullptr;
                }
                else
                {
                    auxPai->filhoDireita = nullptr;
                }
                this->quantidadeChaves--;
                delete aux;
                return;
            }

            // remocao no caso tem somente filho a direita
            else if ((aux->filhoDireita != nullptr) && (aux->filhoEsquerda == nullptr))
            {
                if (auxPai->filhoEsquerda == aux)
                {
                    auxPai->filhoEsquerda = aux->filhoDireita;
                }
                else
                {
                    auxPai->filhoDireita = aux->filhoDireita;
                }
                this->quantidadeChaves--;
                delete aux;
                return;
            }

            // remocao no caso tem somente filho a esquerda
            else if ((aux->filhoEsquerda != nullptr) && (aux->filhoDireita == nullptr))
            {
                if (auxPai->filhoEsquerda == aux)
                {
                    auxPai->filhoEsquerda = aux->filhoEsquerda;
                }
                else
                {
                    auxPai->filhoDireita = aux->filhoEsquerda;
                }
                this->quantidadeChaves--;
                delete aux;
                return;
            }
            else if ((aux->filhoEsquerda != nullptr) && (aux->filhoDireita != nullptr))
            {
                if (auxPai->filhoEsquerda == aux)
                {
                    auxPai->filhoEsquerda = aux->filhoDireita;
                }
                else
                {
                    auxPai->filhoDireita = aux->filhoDireita;
                }
                aux->filhoDireita->filhoEsquerda = aux->filhoEsquerda;
                this->quantidadeChaves--;
                delete aux;
                return;
            }
        }
        return;
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
                return chaveFilho(aux, 0);
            }

            if (chave < aux->chave)
            {
                aux = aux->filhoEsquerda;
            }
            else
            {
                aux = aux->filhoDireita;
            }
        }
        return std::nullopt;
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
                return chaveFilho(aux, 1);
            }

            if (chave < aux->chave)
            {
                aux = aux->filhoEsquerda;
            }
            else
            {
                aux = aux->filhoDireita;
            }
        }
        return std::nullopt;
    }

    /**
     * @brief Lista chaves visitando a arvore em pre-ordem
     * @return Lista encadeada contendo as chaves em pre-ordem. 
     */
    virtual ListaEncadeadaAbstrata<T> *preOrdem() const
    {
        ListaEncadeadaAbstrata<T> *lista = new MinhaListaEncadeada<T>;
        Nodo<T> *aux = ArvoreDeBuscaBinaria<T>::_raiz;

        if (ArvoreDeBuscaBinaria<T>::_raiz != nullptr)
        {
            lista->adicionaNoFim(aux->chave);
            preOrdem_aux(aux->filhoEsquerda, lista);
            preOrdem_aux(aux->filhoDireita, lista);
        }
        return lista;
    }

    /**
     * @brief Lista chaves visitando a arvore em ordem
     * @return Lista encadeada contendo as chaves em ordem. 
     */
    virtual ListaEncadeadaAbstrata<T> *emOrdem() const
    {
        ListaEncadeadaAbstrata<T> *lista = new MinhaListaEncadeada<T>;
        Nodo<T> *aux = this->_raiz;

        if (this->_raiz != nullptr)
        {
            emOrdem_aux(aux->filhoEsquerda, lista);
            lista->adicionaNoFim(this->_raiz->chave);
            emOrdem_aux(aux->filhoDireita, lista);
        }
        return lista;
    }

    /**
     * @brief Lista chaves visitando a arvore em pos-ordem
     * @return Lista encadeada contendo as chaves em pos ordem. 
     */
    virtual ListaEncadeadaAbstrata<T> *posOrdem() const
    {
        ListaEncadeadaAbstrata<T> *lista = new MinhaListaEncadeada<T>;
        Nodo<T> *aux = this->_raiz;

        if (this->_raiz != nullptr)
        {
            posOrdem_aux(aux->filhoEsquerda, lista);
            posOrdem_aux(aux->filhoDireita, lista);
            lista->adicionaNoFim(this->_raiz->chave);
        }
        return lista;
    }
};

#endif