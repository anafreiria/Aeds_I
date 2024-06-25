
/*
 * File:   main.cpp
 * Author: Ana Flávia Freiria Rodrigues
 *
 * Created on 13 de maio de 2024, 16:06
 */

/*
 * Projeto para armazenar informações em registro de dados.
 */

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <math.h>

using namespace std;

// Declaração da struct que conterá as informações de cada veículo.

typedef struct
{
    string modelo;
    string marca;
    string tipo;
    int ano;
    int km;
    float pot;
    string comb;
    string cambio;
    string direcao;
    string cor;
    int portas;
    string placa;
    float valor;
    bool valido;
} Veiculo;

int main()
{
    // Tamnho máximo do meu arquivo definido
    const int TAM = 100;
    Veiculo vetorVeiculo[TAM];

    // Abertura de arquivo para leitura.
    ifstream arquivo("veiculo.txt");
    if (!arquivo.is_open())
    {
        cout << "Erro ao abrir o arquivo. " << endl;
        return 1;
    }

    int i = 0;

    // Leitura de arquivo.
    while (i < TAM && arquivo >> vetorVeiculo[i].modelo >> vetorVeiculo[i].marca >> vetorVeiculo[i].tipo >> vetorVeiculo[i].ano >> vetorVeiculo[i].km >>
                          vetorVeiculo[i].pot >> vetorVeiculo[i].comb >> vetorVeiculo[i].cambio >> vetorVeiculo[i].direcao >> vetorVeiculo[i].cor >>
                          vetorVeiculo[i].portas >> vetorVeiculo[i].placa >> vetorVeiculo[i].valor)
    {
        if (vetorVeiculo[i].modelo == "FIM")
        {
            break;
        }
        vetorVeiculo[i].valido = true;
        i++;
    }

    // Aqui, minha variável recebe a quantidade total de veiculos do arquivo após a leitura, que é feita até o modelo ser a palavra FIM.
    int opcao, qtdeVeiculos = i;
    arquivo.close();

    do
    {
        // Menu de opções.
        cout << "-----------Menu-----------:" << endl;
        cout << "1. Adicionar novo veiculo " << endl;
        cout << "2. Busca de veiculo" << endl;
        cout << "3. Relatório banco de dados" << endl;
        cout << "4. Sair" << endl;
        cout << "---------------------------:" << endl;
        cout << "   Escolha uma opcao: " << endl;
        cin >> opcao;

        // Aqui, declarei as variáveis que necessitei durante a criação do programa, cada uma com seu tipo determinado.
        string placa, tipo, cambio, tipoBusca, tipoCombustivel, placaBarato, placaCaro;
        int posVeiculo = -1, valorMax, valorMin, resposta, novoVeic = -1, qtdeCinco = 0;
        float contadorTipo = 0, contadorComb = 0, valorBarato = 10000000.00, valorCaro = 0, somaKm = 0, valorPrest = 0, valorSeguro = 0;

        // Começo switch case, que irá realizar cada operação pedida no programa.
        switch (opcao)
        {
            // Adicionar novo veículo.
        case 1:
            // Verificando se tem algum veiculo no vetor que já foi apagado para adicionar um novo veiculo no lugar dele.
            for (i = 0; i < qtdeVeiculos; i++)
            {
                if (vetorVeiculo[i].valido == false)
                {
                    novoVeic = i;
                    break;
                }
            }
            // Caso não tenha nenhum falso, o programa adicionará o novo caro na ultima posição.
            if (novoVeic == -1)
                novoVeic = qtdeVeiculos;
            // Verifica se o vetor já esta lotado, caso esteja, não realiza a operação.
            if (qtdeVeiculos >= TAM)
            {
                cout << "O vetor de registros está cheio, tente novamente:" << endl;
                cout << endl;
                break;
            }
            // Pede as informações para a inclusão do novo veiculo.
            cout << endl;
            cout << "Digite o modelo: " << endl;
            cin >> vetorVeiculo[novoVeic].modelo;
            cout << "Digite a marca: " << endl;
            cin >> vetorVeiculo[novoVeic].marca;
            cout << "Digite o tipo : " << endl;
            cin >> vetorVeiculo[novoVeic].tipo;
            cout << "Digite o ano do veiculo : " << endl;
            cin >> vetorVeiculo[novoVeic].ano;
            cout << "Digite a kilometragem: " << endl;
            cin >> vetorVeiculo[novoVeic].km;
            cout << "Digite a potência do motor: " << endl;
            cin >> vetorVeiculo[novoVeic].pot;
            cout << "Digite o combustível : " << endl;
            cin >> vetorVeiculo[novoVeic].comb;
            cout << "Digite o tipo de câmbio: " << endl;
            cin >> vetorVeiculo[novoVeic].cambio;
            cout << "Digite o tipo de direção: " << endl;
            cin >> vetorVeiculo[novoVeic].direcao;
            cout << "Digite a cor do veiculo : " << endl;
            cin >> vetorVeiculo[novoVeic].cor;
            cout << "Digite a quantidade de portas: " << endl;
            cin >> vetorVeiculo[novoVeic].portas;
            cout << "Digite a placa: " << endl;
            cin >> vetorVeiculo[novoVeic].placa;
            cout << "Digite um valor: " << endl;
            cin >> vetorVeiculo[novoVeic].valor;
            vetorVeiculo[novoVeic].valido = true;
            qtdeVeiculos++;
            break;

        case 2:
            // Menu de opções caso o usuário queira buscar um veículo no arquivo.
            int busca;
            cout << "------------------------" << endl;
            cout << "1. Busca por placa: " << endl;
            cout << "2. Busca pelo tipo: " << endl;
            cout << "3. Busca pelo câmbio: " << endl;
            cout << "4. Busca por uma faixa de valores: " << endl;
            cout << "5. Sair" << endl;
            cout << "------------------------" << endl;
            cout << "   Escolha uma opcao : ";
            cin >> busca;

            // Inicia um novo switch case dentro de um anterior, visto que o usuário faz 2 escolhas em 2 menus diferentes.
            switch (busca)
            {

            case 1: // Busca por placa
                cout << "Digite a placa: " << endl;
                cin >> placa;
                for (i = 0; i < qtdeVeiculos; i++)
                {
                    if (vetorVeiculo[i].placa == placa)
                        posVeiculo = i;
                }

                if (posVeiculo == -1)
                {
                    cout << "Placa não encontrada!!!" << endl;
                }
                else
                {
                    cout << vetorVeiculo[posVeiculo].modelo << " " << vetorVeiculo[posVeiculo].marca << " " << vetorVeiculo[posVeiculo].tipo << " " << vetorVeiculo[posVeiculo].ano << " " << vetorVeiculo[posVeiculo].km << " " << vetorVeiculo[posVeiculo].pot
                         << " " << vetorVeiculo[posVeiculo].comb << " " << vetorVeiculo[posVeiculo].cambio << " " << vetorVeiculo[posVeiculo].direcao << " " << vetorVeiculo[posVeiculo].cor << " " << vetorVeiculo[posVeiculo].portas << " " << vetorVeiculo[posVeiculo].placa
                         << " " << vetorVeiculo[posVeiculo].valor << " " << endl;

                    cout << "Você deseja excluir esse carro do banco de dados? " << endl;
                    cout << "Digite 1 para excluir e 2 para não excluir" << endl;

                    // Se o usuário digitar sim, essa repetição faz o carro ser "excluido" (receber false no vetorveiculo[i].valido).
                    cin >> resposta;
                    if (resposta == 1)
                    {
                        vetorVeiculo[posVeiculo].valido = false;

                        cout << "Veículo excluído" << endl;
                    }
                }

                break;

            case 2: // Busca o veículo por tipo.
                cout << "Digite o tipo: " << endl;
                cin >> tipo;
                for (i = 0; i < qtdeVeiculos; i++)
                {

                    if (vetorVeiculo[i].tipo == tipo && vetorVeiculo[i].valido == true)
                    {
                        cout << vetorVeiculo[i].modelo << " " << vetorVeiculo[i].marca << " " << vetorVeiculo[i].tipo << " " << vetorVeiculo[i].ano << " " << vetorVeiculo[i].km << " " << vetorVeiculo[i].pot
                             << " " << vetorVeiculo[i].comb << " " << vetorVeiculo[i].cambio << " " << vetorVeiculo[i].direcao << " " << vetorVeiculo[i].cor << " " << vetorVeiculo[i].portas << " " << vetorVeiculo[i].placa
                             << " " << vetorVeiculo[i].valor << " " << endl;
                        posVeiculo = i;
                    }
                }
                // Caso nenhum veículo tenha sido encontrado, o valor da variavel fica inalterado, assim, posso escrever para o usúario essa informção.
                if (posVeiculo == -1)
                    cout << "Carro não encontrado!!! " << endl;

                break;
            case 3: // Busca do veiculo por seu cambio.
                cout << "Digite o câmbio: " << endl;
                cin >> cambio;
                for (i = 0; i < qtdeVeiculos; i++)
                {

                    if (vetorVeiculo[i].cambio == cambio && vetorVeiculo[i].valido == true)
                    {
                        cout << vetorVeiculo[i].modelo << " " << vetorVeiculo[i].marca << " " << vetorVeiculo[i].tipo << " " << vetorVeiculo[i].ano << " " << vetorVeiculo[i].km << " " << vetorVeiculo[i].pot
                             << " " << vetorVeiculo[i].comb << " " << vetorVeiculo[i].cambio << " " << vetorVeiculo[i].direcao << " " << vetorVeiculo[i].cor << " " << vetorVeiculo[i].portas << " " << vetorVeiculo[i].placa
                             << " " << vetorVeiculo[i].valor << " " << endl;
                        posVeiculo = i;
                    }
                }
                // Caso nenhum veículo tenha sido encontrado, o valor da variavel fica inalterado, assim, posso escrever para o usúario essa informção.
                if (posVeiculo == -1)
                    cout << "Carro não encontrado!!!" << endl;
                break;

            case 4: // Busca de veiculos dentro de uma faixa de valores.
                cout << "Digite o valor mínimo: " << endl;
                cin >> valorMin;
                cout << "Digite o valor máximo: " << endl;
                cin >> valorMax;

                for (i = 0; i < qtdeVeiculos; i++)
                { // Procurando valores dentro do intervalo determinado
                    if (vetorVeiculo[i].valor >= valorMin && vetorVeiculo[i].valor <= valorMax && vetorVeiculo[i].valido == true)
                    {
                        cout << vetorVeiculo[i].modelo << " " << vetorVeiculo[i].marca << " " << vetorVeiculo[i].tipo << " " << vetorVeiculo[i].ano << " " << vetorVeiculo[i].km << " " << vetorVeiculo[i].pot
                             << " " << vetorVeiculo[i].comb << " " << vetorVeiculo[i].cambio << " " << vetorVeiculo[i].direcao << " " << vetorVeiculo[i].cor << " " << vetorVeiculo[i].portas << " " << vetorVeiculo[i].placa
                             << " " << vetorVeiculo[i].valor << " " << endl;
                        posVeiculo = i;
                    }
                }
                // Caso nenhum veículo tenha sido encontrado, o valor da variavel fica inalterado, assim, posso escrever para o usúario essa informção.
                if (posVeiculo == -1)
                    cout << "Carros nessa faixa de valor não foram encontrados" << endl;
                break;

            default:
                break;
            }
            break;
        case 3: // Relatório de Dados.

            cout << "Digite o tipo procurado para saber a porcentagem de carros desse tipo:" << endl;
            cin >> tipoBusca;

            for (i = 0; i < qtdeVeiculos; i++)
            {
                if (vetorVeiculo[i].tipo == tipoBusca && vetorVeiculo[i].valido == true)
                    contadorTipo = contadorTipo + 1;
            }
            contadorTipo = 100 * (contadorTipo / qtdeVeiculos);

            cout << "Digite o tipo de combustível:" << endl;
            cin >> tipoCombustivel;

            for (i = 0; i < qtdeVeiculos; i++)
            {
                if (vetorVeiculo[i].comb == tipoCombustivel && vetorVeiculo[i].valido == true)
                    contadorComb = contadorComb + 1;
            }
            contadorComb = 100 * (contadorComb / qtdeVeiculos);

            cout << endl;
            cout << " Informações do Banco de Dados " << endl;
            cout << endl;
            cout << " -A porcetagem de carros do tipo " << tipoBusca << " é de " << contadorTipo << "%." << endl;
            cout << " -A porcetagem de carros que usam combustível " << tipoCombustivel << " é de " << contadorComb << "%." << endl;

            // Procura o carro mais barato com potência 1.0.
            for (i = 0; i < qtdeVeiculos; i++)
            {
                if (vetorVeiculo[i].pot == 1.0 && vetorVeiculo[i].valido == true)
                {
                    if (vetorVeiculo[i].valor < valorBarato)
                    {
                        valorBarato = vetorVeiculo[i].valor;
                        placaBarato = vetorVeiculo[i].placa;
                    }
                }
            }
            // Calculo valor da prestação do financiamento desse carro.
            valorPrest = (valorBarato * (pow(1.0113, 60))) / 60;
            cout << " -O valor do carro mais barato com motor 1.0 é R$" << valorBarato << " e a placa dele é: " << placaBarato << endl;
            cout << " -O valor da prestação mensal para o finaciamento do veículo mais barato é R$" << valorPrest << "." << endl;

            // Procura no vetor os carros com direção hidráulica e câmbio automático.
            for (i = 0; i < qtdeVeiculos; i++)
            {
                if (vetorVeiculo[i].direcao == "Hidráulica" && vetorVeiculo[i].valido == true && vetorVeiculo[i].cambio == "Automático")
                {
                    if (vetorVeiculo[i].valor > valorCaro)
                    {
                        valorCaro = vetorVeiculo[i].valor;
                        placaCaro = vetorVeiculo[i].placa;
                    }
                }
            }
            // Calculo do valor do seguro.
            valorSeguro = valorCaro * 0.066;
            cout << " -O valor do seguro do carro mais caro com direção hidraulica e câmbio automático é R$" << valorSeguro << endl;
            cout << " -O valor do carro mais caro com direção hidraulica e câmbio automático é R$" << valorCaro << " e a placa dele é: " << placaCaro << endl;

            // Verifica a quantidade de veiculos com 5 anos ou mais e faz o somatório para posteriormente fazer a média.
            for (i = 0; i < qtdeVeiculos; i++)
            {
                if (vetorVeiculo[i].ano <= 2019 && vetorVeiculo[i].valido == true)
                {
                    qtdeCinco++;
                    somaKm = somaKm + vetorVeiculo[i].km;
                }
            }

            somaKm = somaKm / qtdeCinco;
            cout << " -A quantidade de veículos com 5 anos ou mais é " << qtdeCinco << " e a média da kilometragem desses carros é de " << fixed << setprecision(2) << somaKm << "Km." << endl;
            break;

        // Finaliza o programa.
        case 4:
            break;
        default:

            cout << "Opção inválida" << endl;
        }
    } while (opcao != 4); // Condição de parada do programa.

    // Abre o arquivo para escrita depois das alterações.
    ofstream arquivoEscrita("veiculo.txt");
    for (i = 0; i < qtdeVeiculos; i++)
    {
        if (vetorVeiculo[i].valido == true)
        {
            arquivoEscrita << vetorVeiculo[i].modelo << " " << vetorVeiculo[i].marca << " " << vetorVeiculo[i].tipo << " " << vetorVeiculo[i].ano << " " << vetorVeiculo[i].km << " " << vetorVeiculo[i].pot << " " << vetorVeiculo[i].comb << " " << vetorVeiculo[i].cambio << " " << vetorVeiculo[i].direcao << " " << vetorVeiculo[i].cor << " " << vetorVeiculo[i].portas << " " << vetorVeiculo[i].placa << " " << vetorVeiculo[i].valor;
            arquivoEscrita << endl;
        }
    }
    // Escreve sempre no final do arquivo a palavra FIM que é a condição de parada do programa para que ele possa ser utilizado em qualquer tamanho de arquivo que respeite essa condição.
    arquivoEscrita << "FIM";

    // Fechamento do arquivo.
    arquivoEscrita.close();
    cout << qtdeVeiculos <<endl;
    return 0;
}
