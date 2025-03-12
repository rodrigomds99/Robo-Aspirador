// Copyright [2024] <Rodrigo Martins dos Santos>
// Copyright [2024] <Lucas Pastre de Souza>
#ifndef STRUCTURES_ARRAY_STACK_H
#define STRUCTURES_ARRAY_STACK_H

#include <cstdint>  // para usar o tipo std::size_t
#include <stdexcept>  // para lançar exceções padrão do C++

namespace structures {

template<typename T>
//! Classe que implementa uma Pilha (Stack) usando um array
class ArrayStack {
 public:
    //! Construtor padrão
    ArrayStack();

    //! Construtor que permite definir o tamanho máximo da pilha
    explicit ArrayStack(std::size_t max);

    //! Destrutor
    ~ArrayStack();

    //! Adiciona um elemento ao topo da pilha
    void push(const T& data);

    //! Remove e retorna o elemento do topo da pilha
    T pop();

    //! Retorna o elemento do topo da pilha sem removê-lo
    T& top();

    //! Remove todos os elementos da pilha
    void clear();

    //! Retorna o número de elementos na pilha
    std::size_t size();

    //! Retorna a capacidade máxima da pilha
    std::size_t max_size();

    //! Verifica se a pilha está vazia
    bool empty();

    //! Verifica se a pilha está cheia
    bool full();

 private:
    T* contents;  // Array que armazena os elementos da pilha
    int top_;  // Índice do topo da pilha (inicia em -1)
    std::size_t max_size_;  // Capacidade máxima da pilha

    static const auto DEFAULT_SIZE = 10u;  // Tamanho padrão da pilha caso não seja especificado
};

}  // namespace structures

#endif


// Implementação do construtor padrão, que define o tamanho máximo como o DEFAULT_SIZE
template<typename T>
structures::ArrayStack<T>::ArrayStack() {
    max_size_ = DEFAULT_SIZE;  // Define a capacidade máxima como tamanho padrão
    contents = new T[max_size_];  // Aloca o array para os elementos da pilha
    top_ = -1;  // Define o índice do topo como -1 (pilha vazia)
}

// Implementação do construtor com tamanho definido pelo usuário
template<typename T>
structures::ArrayStack<T>::ArrayStack(std::size_t max) {
    max_size_ = max;  // Define a capacidade máxima com o valor fornecido
    contents = new T[max_size_];  // Aloca o array para os elementos da pilha
    top_ = -1;  // Define o índice do topo como -1 (pilha vazia)
}

// Destrutor que libera a memória alocada para a pilha
template<typename T>
structures::ArrayStack<T>::~ArrayStack() {
    delete [] contents;  // Libera o array da pilha
}

// Função que adiciona um novo elemento no topo da pilha
template<typename T>
void structures::ArrayStack<T>::push(const T& data) {
    if (full()) {  // Verifica se a pilha está cheia
        throw std::out_of_range("pilha cheia");  // Lança exceção se a pilha estiver cheia
    } else {
        top_ = top_ + 1;  // Incrementa o índice do topo
        contents[top_] = data;  // Armazena o elemento no novo topo
    }
}

// Função que remove e retorna o elemento do topo da pilha
template<typename T>
T structures::ArrayStack<T>::pop() {
    if (empty()) {  // Verifica se a pilha está vazia
        throw std::out_of_range("pilha vazia");  // Lança exceção se a pilha estiver vazia
    } else {
        top_ = top_ - 1;  // Decrementa o índice do topo
        return contents[top_+1];  // Retorna o elemento que estava no topo
    }
}

// Função que retorna o elemento do topo sem removê-lo
template<typename T>
T& structures::ArrayStack<T>::top() {
    if (empty()) {  // Verifica se a pilha está vazia
        throw std::out_of_range("ERRO: pilha vazia ao tentar acessar o topo!");
    } else {
        return contents[top_];  // Retorna o elemento no topo
    }
}

// Função que esvazia a pilha
template<typename T>
void structures::ArrayStack<T>::clear() {
    top_ = -1;  // Define o índice do topo como -1, esvaziando a pilha
}

// Função que retorna o número de elementos na pilha
template<typename T>
std::size_t structures::ArrayStack<T>::size() {
    return static_cast<std::size_t>(top_ + 1);  // Retorna o número de elementos
}

// Função que retorna a capacidade máxima da pilha
template<typename T>
std::size_t structures::ArrayStack<T>::max_size() {
    return max_size_;  // Retorna a capacidade máxima
}

// Função que verifica se a pilha está vazia
template<typename T>
bool structures::ArrayStack<T>::empty() {
    return top_ == -1;  // Retorna verdadeiro se o índice do topo for -1
}

// Função que verifica se a pilha está cheia
template<typename T>
bool structures::ArrayStack<T>::full() {
    return top_ == static_cast<int>(max_size_ - 1);  // Verdadeiro se o topo alcançar a capacidade máxima
}
