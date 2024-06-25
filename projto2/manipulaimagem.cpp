#include <iostream>
#include <fstream>
#include <stdio.h>
#include <cstdlib> // Para a função rand()

using namespace std;

// Função para alocar uma matriz dinamicamente
int **alocarMatriz(int linhas, int colunas) {
    int **matriz = new int *[linhas];
    for (int i = 0; i < linhas; ++i) {
        matriz[i] = new int[colunas];
    }
    return matriz;
}

// Função para desalocar uma matriz alocada dinamicamente
void desalocarMatriz(int **matriz, int linhas) {
    for (int i = 0; i < linhas; ++i) {
        delete[] matriz[i];
    }
    delete[] matriz;
}

// Função para ler uma matriz de um arquivo PGM
bool lerMatrizDeArquivo(const string &nomeArquivo, int **&matriz, int &largura, int &altura, int &maxValor) {
    ifstream arquivo(nomeArquivo);
    if (!arquivo.is_open()) {
        cout << "Erro ao abrir o arquivo " << nomeArquivo << endl;
        return false;
    }

    string linha;

    // Lendo o cabeçalho do arquivo PGM
    getline(arquivo, linha);      // Ignorando a primeira linha ("P2")
    getline(arquivo, linha);      // Ignorando a segunda linha (comentário)
    arquivo >> largura >> altura; // Lendo largura e altura
    arquivo >> maxValor;          // Lendo o valor máximo de intensidade

    // Alocar matriz dinamicamente com as dimensões lidas
    matriz = alocarMatriz(altura, largura);

    // Lendo os valores dos pixels
    for (int i = 0; i < altura; ++i) {
        for (int j = 0; j < largura; ++j) {
            arquivo >> matriz[i][j];
        }
    }

    arquivo.close();
    return true;
}

/*
* Função para ajustar o brilho da imagem usada em duas operações (clarear e escurecer a imagem)
*/ 
void ajustarBrilhoImagem(int **original, int **resultado, int largura, int altura, double fator, int maxValor) {
    for (int i = 0; i < altura; ++i) {
        for (int j = 0; j < largura; ++j) {
            resultado[i][j] = min(max(0, static_cast<int>(original[i][j] + fator)), maxValor);
        }
    }
}

/*
* Função para binarizar a imagem
*/ 
void binarizar(int **entrada, int **saida, int *linha, int *coluna, double *opcao, int *escala) {
    for (int i = 0; i < *linha; i++) {
        for (int j = 0; j < *coluna; j++) {
            saida[i][j] = (entrada[i][j] >= *opcao) ? *escala : 0;
        }
    }
}


/*
* Função para iconizar a imagem (reduzir para 64x64 pixels)
*/ 

void iconizarImagem(int **original, int **resultado, int largura, int altura) {
    int fator_linha = max(altura / 64, 1);
    int fator_coluna = max(largura / 64, 1);

    int saida_linha = min(64, altura / fator_linha);
    int saida_coluna = min(64, largura / fator_coluna);

    for (int i = 0; i < saida_linha; i++) {
        for (int j = 0; j < saida_coluna; j++) {
            int soma = 0, count = 0;
            for (int k = i * fator_linha; k < (i + 1) * fator_linha && k < altura; k++) {
                for (int l = j * fator_coluna; l < (j + 1) * fator_coluna && l < largura; l++) {
                    soma += original[k][l];
                    count++;
                }
            }
            resultado[i][j] = soma / count;
        }
    }
}
/*
* 
*/ 
// Função para criar ruídos na imagem
void criarRuidoImagem(int **original, int **resultado, int largura, int altura, int maxValor) {
    for (int i = 0; i < altura; ++i) {
        for (int j = 0; j < largura; ++j) {
            resultado[i][j] = original[i][j];
            if (rand() % 100 < 5) { // 5% de chance de aplicar ruído
                resultado[i][j] = rand() % (maxValor + 1);
            }
        }
    }
}

/*
* Função para aplicar filtro passa baixa
*/ 
void FiltroPassaBaixa(int **original, int **resultado, int largura, int altura, int maxValor) {
    for (int i = 0; i < altura; i++) {
        resultado[i][0] = original[i][0];
        resultado[i][largura - 1] = original[i][largura - 1];
    }
    for (int j = 0; j < largura; j++) {
        resultado[0][j] = original[0][j];
        resultado[altura - 1][j] = original[altura - 1][j];
    }

    for (int i = 1; i < altura - 1; i++) {
        for (int j = 1; j < largura - 1; j++) {
            int soma = 0;
            for (int k = i - 1; k <= i + 1; k++) {
                for (int l = j - 1; l <= j + 1; l++) {
                    soma += original[k][l];
                }
            }
            resultado[i][j] = soma / 9;
            resultado[i][j] = min(max(resultado[i][j], 0), maxValor);
        }
    }
}

/*
* Função para encontrar a imagem negativa
*/ 
void imagemNegativa(int **original, int **resultado, int largura, int altura, int maxValor) {
    for (int i = 0; i < altura; ++i) {
        for (int j = 0; j < largura; ++j) {
            resultado[i][j] = max(0, maxValor - original[i][j]);
        }
    }
}

/*
* Função para escrever a matriz resultante em um arquivo PGM (usada em todas opções)
*/ 
bool escreverMatrizParaArquivo(const string &nomeArquivo, int **matriz, int largura, int altura, int maxValor) {
    ofstream arquivo(nomeArquivo);
    if (!arquivo.is_open()) {
        cout << "Erro ao criar o arquivo " << nomeArquivo << endl;
        return false;
    }

    arquivo << "P2" << endl;
    arquivo << "# Arquivo gerado pelo programa" << endl;
    arquivo << largura << " " << altura << endl;
    arquivo << maxValor << endl;

    for (int i = 0; i < altura; ++i) {
        for (int j = 0; j < largura; ++j) {
            arquivo << matriz[i][j] << " ";
        }
        arquivo << endl;
    }

    arquivo.close();
    return true;
}

/*
* Função para mostrar o menu de opções
*/ 

void mostrarMenu() {
    cout << "Menu de Operações:" << endl;
    cout << "==================" << endl;
    cout << "1. Ler imagem de entrada (formato PGM)" << endl;
    cout << "2. Escurecer imagem" << endl;
    cout << "3. Clarear imagem" << endl;
    cout << "4. Binarizar imagem" << endl;
    cout << "5. Iconizar imagem" << endl;
    cout << "6. Criar ruídos na imagem" << endl;
    cout << "7. Aplicar filtro para suavizar imagem" << endl;
    cout << "8. Encontrar imagem negativa" << endl;
    cout << "9. Sair" << endl;
    cout << "==================" << endl;
    cout << "Escolha uma opção: ";
}

    

int main() {

    cout <<"\e[1m" << "Trabalho de AEDS - Edição de Imagens"  << "\e[0m" << endl;
    cout <<"\e[1m" << "Professor: Paulo Alexandre Bressan" << "\e[0m" << endl;
    cout <<"\e[1m" << "Por : Ana Flávia Freiria Rodrigues e Raissa Nunes Peret | RA : 2024.1.08.001 e 2024.1.08.021 " << "\e[0m" << endl << endl;
    
    //Variáveis utilizadas
    bool imagemCarregada = false;
    int largura, altura, maxValor, opcao;
    int **matrizOriginal = nullptr; //Criada como global
    int **matrizComRuido = nullptr; //Criada como global
    int **matrizAuxRuido = nullptr; //Criada como global
    string existeRuido = "";

    while (true) {
        mostrarMenu();
        cin >> opcao;

        switch (opcao) {
            case 1: { //Leitura do arquivo de imagem original
                string nomeArquivoEntrada;
                cout << "Informe o nome do arquivo de entrada (formato PGM): ";
                cin >> nomeArquivoEntrada;
                //Verificação de êxito na leitura da imagem
                if (lerMatrizDeArquivo(nomeArquivoEntrada, matrizOriginal, largura, altura, maxValor)) {
                    imagemCarregada = true;
                    cout << "Imagem carregada com sucesso!\n" << endl;
                }
                break;
            }
            case 2: {
                //Mensagem de alerta caso o usuário não tenha carregado nenhuma imagem
                if (!imagemCarregada) {
                    cout << "Por favor, carregue uma imagem primeiro (opção 1)." << endl;
                    break;
                }
                double fatorEscurecer;
                cout << "Informe o fator para escurecer a imagem: ";
                cin >> fatorEscurecer;
                //Criação de uma matriz para armazenar o resultado da operação, alocada na memória
                int **imagemEscurecida = alocarMatriz(altura, largura);
                //Execução da função
                ajustarBrilhoImagem(matrizOriginal, imagemEscurecida, largura, altura, -fatorEscurecer, maxValor);

                //Escrita da matriz no arquivo
                string nomeArquivoSaida = "imagem_escurecida.pgm";
                escreverMatrizParaArquivo(nomeArquivoSaida, imagemEscurecida, largura, altura, maxValor);
                desalocarMatriz(imagemEscurecida, altura);
                cout << "Imagem escurecida foi salva em " << nomeArquivoSaida << endl;
                break;
            }
            case 3: {
                //Mensagem de alerta caso o usuário não tenha carregado nenhuma imagem
                if (!imagemCarregada) {
                    cout << "Por favor, carregue uma imagem primeiro (opção 1)." << endl;
                    break;
                }
                double fatorClarear;
                cout << "Informe o fator para clarear a imagem: ";
                cin >> fatorClarear;
                //Criação de uma matriz para armazenar o resultado da operação, alocada na memória
                int **imagemClareada = alocarMatriz(altura, largura);
                //Execução da função
                ajustarBrilhoImagem(matrizOriginal, imagemClareada, largura, altura, fatorClarear, maxValor);
                string nomeArquivoSaida = "imagem_clareada.pgm";

                //Escrita da matriz no arquivo
                escreverMatrizParaArquivo(nomeArquivoSaida, imagemClareada, largura, altura, maxValor);
                desalocarMatriz(imagemClareada, altura);
                cout << "Imagem clareada foi salva em " << nomeArquivoSaida << endl;
                break;
            }
            case 4: {
                //Mensagem de alerta caso o usuário não tenha carregado nenhuma imagem
                if (!imagemCarregada) {
                    cout << "Por favor, carregue uma imagem primeiro (opção 1)." << endl;
                    break;
                }
                double fatorBinarizar;
                cout << "Informe o fator para binarizar a imagem: ";
                cin >> fatorBinarizar;
                int escala = maxValor;
                //Criação de uma matriz para armazenar o resultado da operação, alocada na memória
                int **imagemBinarizada = alocarMatriz(altura, largura);
                //Execução da função
                binarizar(matrizOriginal, imagemBinarizada, &altura, &largura, &fatorBinarizar, &escala);

                //Escrita da matriz no arquivo
                string nomeArquivoSaida = "imagem_binarizada.pgm";
                escreverMatrizParaArquivo(nomeArquivoSaida, imagemBinarizada, largura, altura, maxValor);
                desalocarMatriz(imagemBinarizada, altura);
                cout << "Imagem binarizada foi salva em " << nomeArquivoSaida << endl;
                break;
            }
            case 5: {
                //Mensagem de alerta caso o usuário não tenha carregado nenhuma imagem
                if (!imagemCarregada) {
                    cout << "Por favor, carregue uma imagem primeiro (opção 1)." << endl;
                    break;
                }
                //Criação de uma matriz para armazenar o resultado da operação, alocada na memória
                int **matrizIcone = alocarMatriz(64, 64);
                //Execução da função
                iconizarImagem(matrizOriginal, matrizIcone, largura, altura);

                //Escrita da matriz no arquivo
                string nomeArquivoSaida = "imagem_icone.pgm";
                escreverMatrizParaArquivo(nomeArquivoSaida, matrizIcone, 64, 64, maxValor);
                desalocarMatriz(matrizIcone, 64);
                cout << "Imagem iconizada foi salva em " << nomeArquivoSaida << endl;
                break;
            }
            case 6: {
                //Mensagem de alerta caso o usuário não tenha carregado nenhuma imagem
                if (!imagemCarregada) {
                    cout << "Por favor, carregue uma imagem primeiro (opção 1)." << endl;
                    break;
                }
                //Nesse caso, a matriz teve de ser criada como variável global para ser usada na próxima operação
                matrizComRuido = alocarMatriz(altura, largura);
                //Execução da função
                criarRuidoImagem(matrizOriginal, matrizComRuido, largura, altura, maxValor);
                string nomeArquivoSaida = "imagem_ruido.pgm";
                //Variável que vai auxiliar a próxima opção.
                existeRuido = nomeArquivoSaida;
                //Escrita da matriz no arquivo
                escreverMatrizParaArquivo(nomeArquivoSaida, matrizComRuido, largura, altura, maxValor);
                desalocarMatriz(matrizComRuido, altura);
                cout << "Imagem com ruídos foi salva em " << nomeArquivoSaida << endl;
                break;
            }
            case 7: {
                //Mensagem de alerta caso o usuário não tenha carregado nenhuma imagem
                if (!imagemCarregada) {
                    cout << "Por favor, carregue uma imagem primeiro (opção 1)." << endl;
                    break;
                }

                //Condição para confirmar se já foi criada a versão da imagem com ruídos
                if (existeRuido == "") {
                    cout << "A imagem selecionada não possui versão com ruídos" << endl;
                    break;
                }
                //Criação de uma matriz para armazenar o resultado da operação, alocada na memória
                int **matrizSuavizada = alocarMatriz(altura, largura);
                lerMatrizDeArquivo(existeRuido, matrizAuxRuido, largura, altura, maxValor);
                //Execução da função
                FiltroPassaBaixa(matrizAuxRuido, matrizSuavizada, largura, altura, maxValor);

                //Escrita da matriz no arquivo
                string nomeArquivoSaida = "imagem_suavizada.pgm";
                escreverMatrizParaArquivo(nomeArquivoSaida, matrizSuavizada, largura, altura, maxValor);
                desalocarMatriz(matrizSuavizada, altura);
                cout << "Imagem suavizada foi salva em " << nomeArquivoSaida << endl;
                break;
            }
            case 8: {
                //Mensagem de alerta caso o usuário não tenha carregado nenhuma imagem
                if (!imagemCarregada) {
                    cout << "Por favor, carregue uma imagem primeiro (opção 1)." << endl;
                    break;
                }
                //Criação de uma matriz para armazenar o resultado da operação, alocada na memória
                int **matrizNegativa = alocarMatriz(altura, largura);
                //Execução da função
                imagemNegativa(matrizOriginal, matrizNegativa, largura, altura, maxValor);

                //Escrita da matriz no arquivo
                string nomeArquivoSaida = "imagem_negativa.pgm";
                escreverMatrizParaArquivo(nomeArquivoSaida, matrizNegativa, largura, altura, maxValor);
                desalocarMatriz(matrizNegativa, altura);
                cout << "Imagem negativa foi salva em " << nomeArquivoSaida << endl;
                break;
            }
            case 9: {
                //Estrutura de encerramento de programa e desalocamento da matriz original que estava alocada na memória para as operações
                if (matrizOriginal != nullptr) {
                    desalocarMatriz(matrizOriginal, altura);
                }
                cout << "Encerrando o programa." << endl;
                return 0;
            }
            default:
                cout << "Opção inválida! Tente novamente." << endl;
        }
    }
}
