#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <windows.h>

float gerarNumeroAleatorio(float min, float max) {
    return min + (max - min) * (rand() / (float)RAND_MAX);
}

class Sensor {
private:
    float nivelAgua;
    float nivelPotassio;
    float nivelCalcio;

public:
    Sensor() {
        nivelAgua = gerarNumeroAleatorio(0.85f, 1.15f);
        nivelPotassio = gerarNumeroAleatorio(0.66f, 0.83f);
        nivelCalcio = gerarNumeroAleatorio(0.44f, 0.56f);
    }

    float getNivelAgua() const {
        return nivelAgua;
    }

    float getNivelPotassio() const {
        return nivelPotassio;
    }

    float getNivelCalcio() const {
        return nivelCalcio;
    }
};

class PontoMonitorado {
private:
    float nivelIdealAgua = 1.0;
    float nivelIdealPotassio = 0.75;
    float nivelIdealCalcio = 0.5;
    int idSensor;

public:
    PontoMonitorado(Sensor* sensor, int idSensor) : idSensor(idSensor) {
        analisaNutrientes(sensor);
    }

    void analisaNutrientes(Sensor* sensor) {
        system("cls");

        std::cout << "Analisando sensor " << idSensor << ":" << std::endl;

        std::cout << "Nivel de agua: " << sensor->getNivelAgua() << std::endl;
        std::cout << "Nivel de Potassio: " << sensor->getNivelPotassio() << std::endl;
        std::cout << "Nivel de Calcio: " << sensor->getNivelCalcio() << std::endl << std::endl;

        if (sensor->getNivelAgua() > nivelIdealAgua + 0.1 * nivelIdealAgua) {
            std::cout << "O nivel de agua esta acima do normal" << std::endl;
            std::cout << "Considere reduzir a quantidade de agua aplicada no local" << std::endl;
        }
        else if (sensor->getNivelAgua() < nivelIdealAgua - 0.1 * nivelIdealAgua) {
            std::cout << "O nivel de agua esta abaixo do normal" << std::endl;
            std::cout << "Considere aumentar a quantidade de agua aplicada no local" << std::endl;
        }
        else {
            std::cout << "O nivel de agua esta ideal" << std::endl;
        }

        if (sensor->getNivelPotassio() > nivelIdealPotassio + 0.1 * nivelIdealPotassio) {
            std::cout << "O nivel de potassio esta acima do normal" << std::endl;
            std::cout << "Considere reduzir a quantidade aplicada no local" << std::endl;
        }
        else if (sensor->getNivelPotassio() < nivelIdealPotassio - 0.1 * nivelIdealPotassio) {
            std::cout << "O nivel de potassio esta abaixo do normal" << std::endl;
            std::cout << "Considere aumentar a quantidade de potassio aplicada no local" << std::endl;
        }
        else {
            std::cout << "O nivel de potassio esta ideal" << std::endl;
        }

        if (sensor->getNivelCalcio() > nivelIdealCalcio + 0.1 * nivelIdealCalcio) {
            std::cout << "O nivel de calcio esta acima do normal" << std::endl;
            std::cout << "Considere reduzir a quantidade de calcio aplicada no local" << std::endl;
        }
        else if (sensor->getNivelCalcio() < nivelIdealCalcio - 0.1 * nivelIdealCalcio) {
            std::cout << "O nivel de calcio esta abaixo do normal" << std::endl;
            std::cout << "Considere aumentar a quantidade de calcio aplicada no local" << std::endl;
        }
        else {
            std::cout << "O nivel de calcio esta ideal" << std::endl;
        }

        std::cout << "\nPressione Enter para continuar...";
        std::cin.ignore();
        std::cin.get();
    }
};

class GerenciaDados {
private:
    int idNutri;

public:
    GerenciaDados(int idNutri) : idNutri(idNutri) {
    }
    
    void obtemNutriTerreno(const std::vector<Sensor>& sensores) {
        do {
            system("cls");

            std::cout << "Selecione um nutriente a ser analisado:" << std::endl;
            std::cout << "[1] - Agua" << std::endl;
            std::cout << "[2] - Potassio" << std::endl;
            std::cout << "[3] - Calcio" << std::endl;
            std::cin >> idNutri;

            if (idNutri < 1 || idNutri > 3) {
                std::cout << "Opcao invalida. Digite novamente." << std::endl;
            }
        } while (idNutri < 1 || idNutri > 3);

        std::cout << "Niveis do nutriente selecionado em todos os sensores:" << std::endl;
        for (int i = 0; i < sensores.size(); i++) {
            float nivelNutriente = 0.0;

            // Determine qual nutriente selecionado exibir
            if (idNutri == 1) {
                nivelNutriente = sensores[i].getNivelAgua();
            } else if (idNutri == 2) {
                nivelNutriente = sensores[i].getNivelPotassio();
            } else if (idNutri == 3) {
                nivelNutriente = sensores[i].getNivelCalcio();
            }

            std::cout << "Sensor " << (i + 1) << ": " << nivelNutriente << std::endl;
        }

        std::cout << "\nPressione Enter para continuar...";
        std::cin.ignore();
        std::cin.get();
    }
};

class Exibicao {
public:
    Exibicao() {
        int numSensores = 3; // Numero de sensores no sistema
        std::vector<Sensor> sensores(numSensores);

        int opcaoExib;

        do {
            system("cls");

            std::cout << "+-----------------------+" << std::endl;
            std::cout << "|        Sistema        |" << std::endl;
            std::cout << "|       de medicao      |" << std::endl;
            std::cout << "|      de nutrientes    |" << std::endl;
            std::cout << "+-----------------------+" << std::endl << std::endl;

            std::cout << "-Selecione o que deseja analisar: "<< std::endl;
            std::cout << " (1)- Status geral do terreno. "<< std::endl;
            std::cout << " (2)- Todos dados por ponto especifico. "<< std::endl;
            std::cout << " (3)- Nutriente em todos sensores. "<< std::endl;
            std::cout << " (0)- Sair" << std::endl << std::endl;
            
            std::cin >> opcaoExib;

            switch (opcaoExib) {
                case 1:
                    // Implemente a opcao 1 - Status geral do terreno
                    obtemStatusTerreno(sensores);
                    break;
                case 2:
                    for (int i = 0; i < numSensores; i++) {
                        PontoMonitorado ponto(&sensores[i], i + 1);
                    }
                    break;
                case 3:
                    // Implemente a opcao 3 - Nutriente em todos os sensores
                    {
                        GerenciaDados dados(0);
                        dados.obtemNutriTerreno(sensores);
                    }
                    break;
                case 0:
                    std::cout << "Saindo do programa..." << std::endl;
                    break;
                default:
                    std::cout << "Opcao invalida. Tente novamente." << std::endl;
                    break;
            }

        } while (opcaoExib != 0);
    }
    
    void obtemStatusTerreno(const std::vector<Sensor>& sensores) {
        // Inicializa as variaveis para o status geral do terreno
        bool statusAguaIdeal = true;
        bool statusPotassioIdeal = true;
        bool statusCalcioIdeal = true;

        for (const Sensor& sensor : sensores) {
            // Obtem os valores do sensor atual
            float nivelAgua = sensor.getNivelAgua();
            float nivelPotassio = sensor.getNivelPotassio();
            float nivelCalcio = sensor.getNivelCalcio();

            // Verifica o status da agua
            if (nivelAgua < 0.9 || nivelAgua > 1.1) {
                statusAguaIdeal = false;
            }

            // Verifica o status do potassio
            if (nivelPotassio < 0.67 || nivelPotassio > 0.82) {
                statusPotassioIdeal = false;
            }

            // Verifica o status do calcio
            if (nivelCalcio < 0.45 || nivelCalcio > 0.55) {
                statusCalcioIdeal = false;
            }
        }

        // Exibe o status geral com base nos resultados
        std::cout << "Status geral do terreno:" << std::endl;
        if (statusAguaIdeal) {
            std::cout << "Nivel de agua: Ideal" << std::endl;
        } else {
            std::cout << "Nivel de agua: Nao ideal" << std::endl;
        }

        if (statusPotassioIdeal) {
            std::cout << "Nivel de potassio: Ideal" << std::endl;
        } else {
            std::cout << "Nivel de potassio: Nao ideal" << std::endl;
        }

        if (statusCalcioIdeal) {
            std::cout << "Nivel de calcio: Ideal" << std::endl;
        } else {
            std::cout << "Nivel de calcio: Nao ideal" << std::endl;
        }

        std::cout << "\nPressione Enter para continuar...";
        std::cin.ignore();
        std::cin.get();
    }
};

int main() {
    Exibicao exib;
    return 0;
}
