#ifndef MINHA_ARVORE_AVL_HPP
#define MINHA_ARVORE_AVL_HPP

#include "MinhaArvoreDeBuscaBinaria.hpp"

/**
 * @brief Representa uma árvore AVL.
 * 
 * @tparam T O tipo de dado guardado na árvore.
 */
template <typename T>
class MinhaArvoreAVL final : public MinhaArvoreDeBuscaBinaria<T>
{
private:
    /**
     * @brief Busca a maior altura dos filhos de um Nodo
     * @param Nodo que se deseja saber a maior altura entre os filhos
     * @return retorna a maior altura
     */
    int maiorAltura(Nodo<T> *aux)
    {
        int alturaD = 0;
        int alturaE = 0;

        // pega a altura da esquerda
        alturaE = alturaEsquerda(aux);

        // pega a altura da direita
        alturaD = alturaDireita(aux);

        // retorna a maior altura
        if (alturaE >= alturaD)
        {
            return alturaE;
        }
        else
        {
            return alturaD;
        }
    }

    /**
     * @brief Busca a altura da subarvore da direita de um Nodo
     * @param Nodo que se deseja saber a altura da direita
     * @return retorna a altura da direita ou -1 se nao tiver filho
     */
    int alturaDireita(Nodo<T> *aux)
    {
        // pega a altura da direita
        if (aux->filhoDireita != nullptr)
        {
            return aux->filhoDireita->altura;
        }
        else
        {
            return -1;
        }
    }

    /**
     * @brief Busca a altura da subarvore da esquerda de um Nodo
     * @param Nodo que se deseja saber a altura da esquerda
     * @return retorna a altura da esquerda ou -1 se nao tiver filho
     */
    int alturaEsquerda(Nodo<T> *aux)
    {
        // pega a altura da direita
        if (aux->filhoEsquerda != nullptr)
        {
            return aux->filhoEsquerda->altura;
        }
        else
        {
            return -1;
        }
    }

    /**
     * @brief Busca o pai de um nodo específico
     * @param Nodo o qual se deseja saber o pai
     * @return retorna o pai de um nodo dado como parametro
     */
    Nodo<T> *encontrarPaiPeloNodo(Nodo<T> *aux)
    {
        Nodo<T> *auxPai = MinhaArvoreDeBuscaBinaria<T>::_raiz;
        Nodo<T> *auxFilho = MinhaArvoreDeBuscaBinaria<T>::_raiz;

        // contornar excessoes
        if (aux == MinhaArvoreDeBuscaBinaria<T>::_raiz)
        {
            return auxPai;
        }
        if (!aux)
        {
            return nullptr;
        }

        // percorre a arvore ate encontrar o nodo
        while (auxFilho != aux)
        {
            auxPai = auxFilho;
            if (aux->chave < auxFilho->chave)
            {
                auxFilho = auxFilho->filhoEsquerda;
            }
            else
            {
                auxFilho = auxFilho->filhoDireita;
            }
        }
        return auxPai;
    }

    /**
     * @brief Busca o pai de uma chave específica
     * @param Nodo o qual se deseja saber o pai
     * @return retorna o pai de um nodo dado como parametro
     */
    Nodo<T> *encontrarPaiPelaChave(T chave)
    {
        Nodo<T> *auxPai = nullptr;
        Nodo<T> *aux = MinhaArvoreDeBuscaBinaria<T>::_raiz;

        // contornar excessoes
        if (!chave)
        {
            return nullptr;
        }
        while (chave != aux->chave)
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
        return auxPai;
    }

    /**
     * @brief Verifica onde esta o desbalanceamento do Nodo
     * @param Nodo que tem o fator de desbalanceamento <= -2
     * @return retorna true caso seja rotacao esquerda-direita e false caso seja direita simples
     */
    bool verificaPesoED(Nodo<T> *aux)
    {
        aux = aux->filhoEsquerda;

        if (aux == nullptr)
        {
            return false;
        }
        if (aux->filhoEsquerda == nullptr)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    /**
     * @brief Verifica onde esta o desbalanceamento do Nodo
     * @param Nodo que tem o fator de desbalanceamento >= +2
     * @return retorna true caso seja rotacao direita-esquerda e false caso seja esquerda simples
     */
    bool verificaPesoDE(Nodo<T> *aux)
    {
        aux = aux->filhoDireita;
        if (aux == nullptr)
        {
            return false;
        }
        else if (aux->filhoDireita == nullptr)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    /**
     * @brief Verifica se precisa balancear, se necessario chama rotacao
     * @param auxPai raiz atual da subarvore
     */
    void verificarBalanceamento(Nodo<T> *auxPai)
    {
        int alturaD = 0;
        int alturaE = 0;
        int b = 0;

        // pega a altura da subarvore da direita
        alturaD = alturaDireita(auxPai);

        // pega a altura da subarvore da esquerda
        alturaE = alturaEsquerda(auxPai);

        b = (alturaE - alturaD);
        if (b <= -2)
        {
            Nodo<T> *auxVo = encontrarPaiPeloNodo(auxPai);
            if (verificaPesoDE(auxPai))
            {
                rotacaoDE(auxVo, auxPai, auxPai->filhoDireita);
                return;
            }
            else
            {
                rotacaoE(auxVo, auxPai);
            }
        }
        else if (b >= 2)
        {
            Nodo<T> *auxVo = encontrarPaiPeloNodo(auxPai);
            if (verificaPesoED(auxPai))
            {
                rotacaoED(auxVo, auxPai, auxPai->filhoEsquerda);
                return;
            }
            else
            {
                rotacaoD(auxVo, auxPai);
            }
            return;
        }
    }

    /**
     * @brief Insere um novo Nodo na arvore recursivamente
     * @param aux e auxPai para chegar na folha e a chave a adicionar
     * @return retorna a altura do Nodo atual
     */
    int inserirAuxAVL(Nodo<T> *aux, Nodo<T> *auxPai, T chave)
    {
        // vai chamar a funcao recursivamente até encontrar o lugar de insercao
        if (aux != nullptr)
        {
            // caso a chave seja menor, vai pra esquerda
            if (chave < aux->chave)
            {
                int alturaE = inserirAuxAVL(aux->filhoEsquerda, aux, chave);
                int alturaD = alturaDireita(aux);
                int b = 0;

                // atualiza a altura do Nodo
                if (alturaE >= alturaD)
                {
                    aux->altura = alturaE + 1;
                }
                else
                {
                    aux->altura = alturaD + 1;
                }

                // calculo do fator de balanceamento
                b = (alturaE - alturaD);
                if (b <= -2)
                {
                    Nodo<T> *auxPai = encontrarPaiPeloNodo(aux);
                    if (verificaPesoDE(aux))
                    {
                        rotacaoDE(auxPai, aux, aux->filhoDireita);
                        auxPai = encontrarPaiPeloNodo(aux);
                        return auxPai->altura;
                    }
                    else
                    {
                        rotacaoE(auxPai, aux);
                    }
                }
                else if (b >= 2)
                {
                    Nodo<T> *auxPai = encontrarPaiPeloNodo(aux);
                    if (verificaPesoED(aux))
                    {
                        rotacaoED(auxPai, aux, aux->filhoEsquerda);
                        auxPai = encontrarPaiPeloNodo(aux);
                        return auxPai->altura;
                    }
                    else
                    {
                        rotacaoD(auxPai, aux);
                    }
                    return aux->altura;
                }
                return aux->altura;
            }
            else
            {
                int alturaD = inserirAuxAVL(aux->filhoDireita, aux, chave);
                int alturaE = alturaEsquerda(aux);
                int b = 0;

                // atualiza a altura do nó
                if (alturaD >= alturaE)
                {
                    aux->altura = alturaD + 1;
                }
                else
                {
                    aux->altura = alturaE + 1;
                }

                // calculo do fator de balanceamento
                b = (alturaE - alturaD);
                if (b <= -2)
                {
                    Nodo<T> *auxPai = encontrarPaiPeloNodo(aux);
                    if (verificaPesoDE(aux))
                    {
                        rotacaoDE(auxPai, aux, aux->filhoDireita);
                        auxPai = encontrarPaiPeloNodo(aux);
                        return auxPai->altura;
                    }
                    else
                    {
                        rotacaoE(auxPai, aux);
                    }
                }
                else if (b >= 2)
                {
                    Nodo<T> *auxPai = encontrarPaiPeloNodo(aux);
                    if (verificaPesoED(aux))
                    {
                        rotacaoED(auxPai, aux, aux->filhoEsquerda);
                        auxPai = encontrarPaiPeloNodo(aux);
                        return auxPai->altura;
                    }
                    else
                    {
                        rotacaoD(auxPai, aux);
                    }
                    return aux->altura;
                }
                return aux->altura;
            }
        }
        else
        {
            Nodo<T> *novo = new Nodo<T>;
            novo->chave = chave;
            MinhaArvoreDeBuscaBinaria<T>::quantidadeChaves++;

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
    }

    /**
     * @brief Remove uma chave da arvore recursivamente
     * @param aux e auxPai para chegar na folha e a chave a remover
     * @return retorna a altura do Nodo atual
     */
    int removerAuxAVL(Nodo<T> *aux, Nodo<T> *auxPai, T chave)
    {
        // caso é a raiz a ser removida
        if (MinhaArvoreDeBuscaBinaria<T>::_raiz->chave == chave)
        {
            // caso a raiz é uma folha
            if ((aux->filhoEsquerda == nullptr) && (aux->filhoDireita == nullptr))
            {
                MinhaArvoreDeBuscaBinaria<T>::quantidadeChaves--;
                MinhaArvoreDeBuscaBinaria<T>::_raiz = nullptr;
                delete aux;
                return 0;
            }
            // caso a raiz tem filho pra direita
            else if (aux->filhoDireita != nullptr)
            {
                aux = aux->filhoDireita;
                auxPai = aux;

                // encontra o menor valor da subarvore da direita
                while (aux->filhoEsquerda != nullptr)
                {
                    auxPai = aux;
                    aux = aux->filhoEsquerda;
                }

                // se o menor valor e ele mesmo
                if (aux == auxPai)
                {
                    // verifica a altura das subarvores
                    int alturaE = 0;
                    int alturaD = auxPai->altura;
                    if (MinhaArvoreDeBuscaBinaria<T>::_raiz->filhoEsquerda != nullptr)
                    {
                        alturaE = MinhaArvoreDeBuscaBinaria<T>::_raiz->filhoEsquerda->altura;
                    }

                    // atualiza altura
                    if (alturaE >= alturaD)
                    {
                        auxPai->altura = alturaE + 1;
                    }
                    else
                    {
                        auxPai->altura = alturaD - 1;
                    }

                    auxPai->filhoEsquerda = MinhaArvoreDeBuscaBinaria<T>::_raiz->filhoEsquerda;
                    aux = MinhaArvoreDeBuscaBinaria<T>::_raiz;
                    delete aux;
                    MinhaArvoreDeBuscaBinaria<T>::_raiz = auxPai;
                    MinhaArvoreDeBuscaBinaria<T>::quantidadeChaves--;
                    return 0;
                }
                // caso tenha outro nodo menor
                else
                {
                    MinhaArvoreDeBuscaBinaria<T>::_raiz->chave = aux->chave;
                    auxPai->filhoEsquerda = nullptr;
                    delete aux;
                    MinhaArvoreDeBuscaBinaria<T>::quantidadeChaves--;
                    return 0;
                }
            }
            // caso a raiz tem filho pra esquerda
            else if (aux->filhoEsquerda != nullptr)
            {
                aux = aux->filhoEsquerda;
                auxPai = aux;

                // encontra o menor valor da subarvore da esquerda
                while (aux->filhoDireita != nullptr)
                {
                    auxPai = aux;
                    aux = aux->filhoDireita;
                }

                // se o menor valor e ele mesmo
                if (aux == auxPai)
                {
                    auxPai->filhoDireita = MinhaArvoreDeBuscaBinaria<T>::_raiz->filhoDireita;
                    auxPai->altura--;
                    aux = MinhaArvoreDeBuscaBinaria<T>::_raiz;
                    delete aux;
                    MinhaArvoreDeBuscaBinaria<T>::_raiz = auxPai;
                    MinhaArvoreDeBuscaBinaria<T>::quantidadeChaves--;
                    return 0;
                }
                // caso tenha outro menor valor
                else
                {
                    MinhaArvoreDeBuscaBinaria<T>::_raiz->chave = aux->chave;
                    auxPai->filhoDireita = nullptr;
                    delete aux;
                    MinhaArvoreDeBuscaBinaria<T>::quantidadeChaves--;
                    return 0;
                }
            }
        }
        // vai chamar recursivamente até encontrar a chave a remover
        if (aux->chave != chave)
        {
            // caso a chave for menor pega a subarvore da esquerda
            if (chave < aux->chave)
            {
                int alturaE = (removerAuxAVL(aux->filhoEsquerda, aux, chave));
                int alturaD = alturaDireita(aux);
                int b = 0;

                // atualiza a altura do nó
                if (alturaD >= alturaE)
                {
                    aux->altura = alturaD + 1;
                }
                else
                {
                    aux->altura = alturaE + 1;
                }
                return aux->altura;
            }
            // caso for maior pega a subarvore da direita
            else
            {
                int alturaD = (removerAuxAVL(aux->filhoDireita, aux, chave));
                int alturaE = alturaEsquerda(aux);
                int b = 0;

                // atualiza a altura do nó
                if (alturaD >= alturaE)
                {
                    aux->altura = alturaD + 1;
                }
                else
                {
                    aux->altura = alturaE + 1;
                }
                return aux->altura;
            }
        }
        // caso encontrou a chave a ser removida
        else
        {
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
                MinhaArvoreDeBuscaBinaria<T>::quantidadeChaves--;
                delete aux;
                return -1;
            }
            // remocao no caso tem somente filho a direita
            else if ((aux->filhoDireita != nullptr) && (aux->filhoEsquerda == nullptr))
            {
                MinhaArvoreDeBuscaBinaria<T>::quantidadeChaves--;
                if (auxPai->filhoEsquerda == aux)
                {
                    int alturaD = alturaDireita(auxPai);
                    int alturaE = aux->filhoDireita->altura;

                    auxPai->filhoEsquerda = aux->filhoDireita;
                    delete aux;
                    if (alturaD >= alturaE)
                    {
                        return alturaD;
                    }
                    else
                    {
                        return alturaE;
                    }
                }
                else
                {
                    int alturaE = alturaEsquerda(auxPai);
                    int alturaD = aux->filhoDireita->altura;

                    auxPai->filhoDireita = aux->filhoDireita;
                    delete aux;
                    if (alturaD >= alturaE)
                    {
                        return alturaD;
                    }
                    else
                    {
                        return alturaE;
                    }
                }
            }
            // remocao no caso tem somente filho a esquerda
            else if ((aux->filhoEsquerda != nullptr) && (aux->filhoDireita == nullptr))
            {
                MinhaArvoreDeBuscaBinaria<T>::quantidadeChaves--;
                if (auxPai->filhoEsquerda == aux)
                {
                    auxPai->filhoEsquerda = aux->filhoEsquerda;
                    delete aux;
                    return auxPai->filhoEsquerda->altura;
                }
                else
                {
                    auxPai->filhoDireita = aux->filhoEsquerda;
                    delete aux;
                    return auxPai->filhoDireita->altura;
                }
            }
            // remocao no caso tem filho pra esquerda e direita
            else if ((aux->filhoEsquerda != nullptr) && (aux->filhoDireita != nullptr))
            {
                Nodo<T> *auxRemover = aux;
                Nodo<T> *auxPaiRemover = auxPai;
                aux = aux->filhoDireita;
                auxPai = aux;
                int alturaE = 0;
                int alturaD = 0;

                // encontra o menor valor da subarvore da direita
                while (aux->filhoEsquerda != nullptr)
                {
                    auxPai = aux;
                    aux = aux->filhoEsquerda;
                }

                // caso ele e o menor
                if (aux = auxPai)
                {
                    alturaE = auxRemover->filhoEsquerda->altura;
                    alturaD = auxPai->altura;
                    aux->filhoEsquerda = auxRemover->filhoEsquerda;
                    MinhaArvoreDeBuscaBinaria<T>::quantidadeChaves--;
                    delete auxRemover;

                    if (alturaE >= alturaD)
                    {
                        aux->altura = alturaE + 1;
                    }

                    if (auxPaiRemover->filhoEsquerda == auxRemover)
                    {
                        auxPaiRemover->filhoEsquerda = aux;
                    }
                    else
                    {
                        auxPaiRemover->filhoDireita = aux;
                    }
                    return aux->altura;
                }
                // caso tenha um menor
                else
                {
                    auxRemover->chave = aux->chave;
                    auxPai->filhoEsquerda = aux->filhoDireita;

                    //atualiza a altura do auxPai
                    if (auxPai->filhoEsquerda != nullptr)
                    {
                        alturaE = auxPai->filhoEsquerda->altura;
                        if (alturaE >= alturaD)
                        {
                            auxPai->altura = alturaE + 1;
                        }
                    }
                    else if (auxPai->filhoDireita == nullptr)
                    {
                        auxPai->altura = 0;
                    }
                    alturaE = auxPai->altura;

                    // atualiza a altura até o caminho de auxPai
                    while (auxPai != auxRemover)
                    {
                        auxPai = encontrarPaiPeloNodo(auxPai);
                        if (auxPai->filhoDireita != nullptr)
                        {
                            alturaD = auxPai->filhoDireita->altura;
                        }
                        if (alturaE >= alturaD)
                        {
                            auxPai->altura = alturaE + 1;
                        }
                    }
                    alturaE = auxRemover->filhoEsquerda->altura;
                    alturaD = auxRemover->filhoEsquerda->altura;
                    if (alturaD >= alturaE)
                    {
                        auxRemover->altura = alturaD + 1;
                    }
                    delete aux;
                    return auxRemover->altura;
                }
            }
            return 0;
        }
    }

    /**
     * @brief Insere uma chave na arvore, chama um metodo recursivo
     * @param chave chave a ser inserida
     */
    virtual void inserir(T chave)
    {
        // insere na raiz
        if (MinhaArvoreDeBuscaBinaria<T>::_raiz == nullptr)
        {
            Nodo<T> *novo = new Nodo<T>;
            novo->chave = chave;
            MinhaArvoreDeBuscaBinaria<T>::quantidadeChaves++;
            MinhaArvoreDeBuscaBinaria<T>::_raiz = novo;
            return;
        }
        // insere no restante da arvore
        else
        {
            MinhaArvoreDeBuscaBinaria<T>::_raiz->altura = inserirAuxAVL(MinhaArvoreDeBuscaBinaria<T>::_raiz, MinhaArvoreDeBuscaBinaria<T>::_raiz, chave);
        }
        return;
    }

    /**
     * @brief Remove uma chave da arvore
     * @param chave chave a removida
     * @return Retorna a chave removida ou nullptr se a chave nao esta na arvore
     */
    virtual void remover(T chave)
    {
        if (!MinhaArvoreDeBuscaBinaria<T>::contem(chave))
        {
            return;
        }
        else
        {
            Nodo<T> *auxPaiRemover = encontrarPaiPelaChave(chave);

            // remove a chave
            MinhaArvoreDeBuscaBinaria<T>::_raiz->altura = removerAuxAVL(MinhaArvoreDeBuscaBinaria<T>::_raiz, MinhaArvoreDeBuscaBinaria<T>::_raiz, chave);

            if (auxPaiRemover != nullptr)
            {
                verificarBalanceamento(auxPaiRemover);
            }
        }
        return;
    }

    /**
     * @brief Faz a rotacao Esquerda Simples
     * @param auxPai aponta para a raiz, aux raiz atual
     */
    void rotacaoE(Nodo<T> *auxPai, Nodo<T> *aux)
    {
        Nodo<T> *auxRaiz = aux->filhoDireita;

        // o aux aponta para subarvore da esquerda da nova raiz
        aux->filhoDireita = auxRaiz->filhoEsquerda;

        // atualiza a altura do aux
        if (aux->filhoDireita == nullptr)
        {
            aux->altura = 0;
        }
        else
        {
            aux->altura = (aux->filhoDireita->altura + 1);
        }

        // a nova raiz aponta para o aux
        auxRaiz->filhoEsquerda = aux;

        // atualiza altura da nova raiz;
        auxRaiz->altura = (maiorAltura(auxRaiz) + 1);

        if (auxPai->filhoDireita == aux)
        {
            auxPai->filhoDireita = auxRaiz;
        }
        else if (auxPai->filhoEsquerda == aux)
        {
            auxPai->filhoEsquerda = auxRaiz;
        }
        else
        {
            MinhaArvoreDeBuscaBinaria<T>::_raiz = auxRaiz;
        }
    }

    /**
     * @brief Faz a rotacao Direita Simples
     * @param auxPai aponta para a raiz, aux raiz atual
     */
    void rotacaoD(Nodo<T> *auxPai, Nodo<T> *aux)
    {
        Nodo<T> *auxRaiz = aux->filhoEsquerda;

        // o aux aponta para subarvore da esquerda da nova raiz
        aux->filhoEsquerda = auxRaiz->filhoDireita;

        // atualiza a altura do aux
        if (aux->filhoEsquerda == nullptr)
        {
            aux->altura = 0;
        }
        else
        {
            aux->altura = (aux->filhoEsquerda->altura + 1);
        }

        // a nova raiz aponta para o aux
        auxRaiz->filhoDireita = aux;

        // atualiza altura da nova raiz
        auxRaiz->altura = (maiorAltura(auxRaiz) + 1);

        if (auxPai->filhoDireita == aux)
        {
            auxPai->filhoDireita = auxRaiz;
        }
        else if (auxPai->filhoEsquerda == aux)
        {
            auxPai->filhoEsquerda = auxRaiz;
        }
        else
        {
            MinhaArvoreDeBuscaBinaria<T>::_raiz = auxRaiz;
        }
    }

    /**
     * @brief Faz a rotacao Esquerda-Direita
     * @param auxVo aponta para a raiz, auxPai raiz atual da segunda rotacao, aux raiz atual da primeira rotacao
     */
    void rotacaoED(Nodo<T> *auxVo, Nodo<T> *auxPai, Nodo<T> *aux)
    {
        rotacaoE(auxPai, aux);
        rotacaoD(auxVo, auxPai);
    }

    /**
     * @brief Faz a rotacao Direita-Esquerda
     * @param auxVo aponta para a raiz, auxPai raiz atual da segunda rotacao, aux raiz atual da primeira rotacao
     */
    void rotacaoDE(Nodo<T> *auxVo, Nodo<T> *auxPai, Nodo<T> *aux)
    {
        rotacaoD(auxPai, aux);
        rotacaoE(auxVo, auxPai);
    }
};
#endifs