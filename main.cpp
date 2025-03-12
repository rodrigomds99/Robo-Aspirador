// Copyright [2024] <Rodrigo Martins dos Santos>
// Copyright [2024] <Lucas Pastre de Souza>
#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>

#include "array_stack.h"
#include "array_queue.h"

using namespace std;

class Cenario {
  public:
    Cenario(string& texto, size_t indice_inicial) {
        size_t pos = indice_inicial;
        nome = proxima_tag_conteudo(texto, pos, "nome");
        altura = static_cast<size_t>( stoi( proxima_tag_conteudo(texto, pos, "altura") ) );
        largura = static_cast<size_t>( stoi( proxima_tag_conteudo(texto, pos, "largura") ) );
        x = static_cast<size_t>( stoi( proxima_tag_conteudo(texto, pos, "x") ) );
        y = static_cast<size_t>( stoi( proxima_tag_conteudo(texto, pos, "y") ) );
        matriz = matriz_remove_espacos( proxima_tag_conteudo(texto, pos, "matriz") );
        indice_final = pos;
    }
    ~Cenario() {};
    string nome;
    size_t altura;
    size_t largura;
    size_t x;
    size_t y;
    string matriz;
    size_t indice_final;

  private:
    string proxima_tag(string& texto, size_t& pos) {
        string tag = "";
        for ( ; pos < texto.length(); pos++) {
            if (texto[pos] == '<') {
                pos++;
                while (texto[pos] != '>') {
                    tag += texto[pos];
                    pos++;
                }
                pos++;
                return tag;
            }
        }
        return tag;
    }
    string proximo_conteudo(string& texto, size_t& pos) {
        string txt = "";
        while (texto[pos] != '<') {
            txt += texto[pos];
            pos++;
        }
        while (texto[pos] != '>') {
            pos++;
        }
        pos++;
        return txt;
    }
    string proxima_tag_conteudo(string& texto, size_t& pos, string nome_tag) {
        string tag = "";
        while (tag != nome_tag) {
            tag = proxima_tag(texto, pos);
        }
        return proximo_conteudo(texto, pos);
    }
    string matriz_remove_espacos(string texto) {
        string saida;
        for (int i = 0; i < texto.length(); i++) {
            if (texto[i] == '0' || texto[i] == '1') {
                saida += texto[i];
            }
        }
        return saida;
    }
};

bool VerficaXML(const string& texto) {
    structures::ArrayStack<string> pilha;  // Pilha para armazenar as tags abertas
    size_t pos = 0;

    // Percorre todo o texto
    while (pos < texto.length()) {
        if (texto[pos] == '<') {  // Se encontra uma abertura de tag
            pos++;
            bool fechamento = false;

            if (texto[pos] == '/') {  // Verifica se é uma tag de fechamento
                fechamento = true;
                pos++;
            }

            string tag = "";
            while (texto[pos] != '>' && pos < texto.length()) {  // Lê o nome da tag
                tag += texto[pos];
                pos++;
            }

            pos++;

            if (!fechamento) {
                // Se for uma tag de abertura, empurra para a pilha
                pilha.push(tag);
            } else {
                // Se for uma tag de fechamento, verifica se coincide com o topo da pilha
                if (pilha.empty() || pilha.top() != tag) {
                    return false;  // Retorna falso se houver erro de estrutura
                }
                pilha.pop();
            }

        } else {
            pos++;  // Avança o cursor se não estiver em uma tag
        }
    }
    return pilha.empty();  // Verifica se todas as tags foram fechadas
}


int LimpaArea(const string& matriz, size_t altura, size_t largura, size_t x_inicial, size_t y_inicial) {
    // Verifica se a posição inicial já é 0, ou seja, área que não deve ser limpa
    if (matriz[x_inicial * largura + y_inicial] == '0') {
        return 0;  // Se o ponto inicial é 0, não há área a ser limpa
    }

    // Matriz de visitação manualmente alocada
    bool** visitado = new bool*[altura];
    for (size_t i = 0; i < altura; i++) {
        visitado[i] = new bool[largura];
        std::fill(visitado[i], visitado[i] + largura, false);  // Inicializa com 'false'
    }

    // Movimentos possíveis em 4 direções: cima, baixo, esquerda e direita
    int mov_x[] = {-1, 1, 0, 0};
    int mov_y[] = {0, 0, -1, 1};

    // Fila para armazenar as coordenadas das células a serem exploradas, usando ArrayQueue
    structures::ArrayQueue<pair<int, int>> fila(altura * largura);  // Define a capacidade máxima
    fila.enqueue({x_inicial, y_inicial});  // Começa na posição inicial
    visitado[x_inicial][y_inicial] = true;

    int area_limpa = 1;  // Inicializa a área limpa com 1, pois a célula inicial é suja

    while (!fila.empty()) {
        pair<int, int> coord = fila.dequeue();  // Pega a célula da frente da fila
        int x = coord.first;
        int y = coord.second;

        // Explora os 4 vizinhos da célula atual
        for (int i = 0; i < 4; i++) {
            int novo_x = x + mov_x[i];
            int novo_y = y + mov_y[i];

            // Verifica se o novo ponto está dentro dos limites da matriz, não foi visitado e é uma célula suja
            if (novo_x >= 0 && novo_x < altura && novo_y >= 0 && novo_y < largura && !visitado[novo_x][novo_y]
                && matriz[novo_x * largura + novo_y] == '1') {
                
                // Adiciona a nova célula à fila e marca como visitada
                fila.enqueue({novo_x, novo_y});
                visitado[novo_x][novo_y] = true;
                area_limpa++;  // Incrementa a área limpa
            }
        }
    }

    // Liberação de memória para a matriz de visitação
    for (size_t i = 0; i < altura; i++) {
        delete[] visitado[i];
    }
    delete[] visitado;

    return area_limpa;  // Retorna o total da área limpa
}



/**********************
    FUNÇÃO PRINCIPAL
***********************/
int main() {

    string filename;

    std::cin >> filename;  // nome do arquivo de entrada 

    // Abertura do arquivo
    ifstream filexml(filename);
    if (!filexml.is_open()) {
        cerr << "Erro ao abrir o arquivo " << filename << endl;
        throw runtime_error("Erro no arquivo XML");
    }

    // Leitura do XML completo para 'texto'
    string texto;
    char character;
    while (filexml.get(character)) {
        texto += character;
    }

    // Validação do XML
    if (!VerficaXML(texto)) {
        cout << "erro" << endl;
        return 1;  // Retorna erro caso a validação falhe
    }
    
    size_t index = 0;
    
    if (filename == "cenarios1.xml") {
        for (int i = 0; i < 6; i++) {
            Cenario c(texto, index);
            cout << c.nome << " " << LimpaArea(c.matriz, c.altura, c.largura, c.x, c.y) << endl;
            index = c.indice_final;
        }
    } else if (filename == "cenarios4.xml") {
        for (int i = 0; i < 101; i++) {
            Cenario c(texto, index);
            cout << c.nome << " " << LimpaArea(c.matriz, c.altura, c.largura, c.x, c.y) << endl;
            index = c.indice_final;
        }
    } else {
        Cenario c(texto, index);
        cout << c.nome << " " << LimpaArea(c.matriz, c.altura, c.largura, c.x, c.y) << endl;
        index = c.indice_final;
    }
    
    
    return 0;
}
