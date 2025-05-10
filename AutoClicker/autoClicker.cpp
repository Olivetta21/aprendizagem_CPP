#include <iostream>
#include <vector>
#include <string>
#include <windows.h>
#include <chrono>
#include <thread>

#include <filesystem>
#include <fstream>


namespace fs = std::filesystem;

struct Point {
    int x, y;
};

std::vector<Point> clickPositions;
int delayBetweenClicks = 1000; // em milissegundos
int repeatCount = 1;

void simulateClick(int x, int y) {
    SetCursorPos(x, y);
    mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
    mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
}

void startClicks() {
    for (int i = 0; i < repeatCount; ++i) {
        for (const auto& pos : clickPositions) {
            simulateClick(pos.x, pos.y);
            std::this_thread::sleep_for(std::chrono::milliseconds(delayBetweenClicks));
        }
    }
}

void addClickPosition() {
    POINT p;
    std::cout << "Clique em qualquer lugar na tela para registrar a posição..." << std::endl;
    while (!(GetKeyState(VK_LBUTTON) & 0x8000)) {
        // Espera até que o botão esquerdo do mouse seja pressionado
        Sleep(100);
    }
    if (GetCursorPos(&p)) {
        clickPositions.push_back({ p.x, p.y });
        std::cout << "Posição registrada: (" << p.x << ", " << p.y << ")" << std::endl;
    }
    while (GetKeyState(VK_LBUTTON) & 0x8000) {
        // Espera até que o botão esquerdo do mouse seja liberado
        Sleep(100);
    }
}

void removeLastClick() {
    if (!clickPositions.empty()) {
        clickPositions.pop_back();
        std::cout << "Última posição de clique removida." << std::endl;
    } else {
        std::cout << "Não há posições de clique para remover." << std::endl;
    }
}

void setDelayBetweenClicks() {
    std::cout << "Digite o atraso entre os cliques em milissegundos: ";
    std::cin >> delayBetweenClicks;
}

void setRepeatCount() {
    std::cout << "Digite a quantidade de vezes para executar a cadeia de cliques: ";
    std::cin >> repeatCount;
}








void recoverInputs(std::string deOnde){
    std::ifstream local(deOnde);
    std::string linha;


     if (!local.is_open()) {
        std::cerr << "Erro ao abrir o arquivo" << std::endl;
        system("pause");
        return;
    }

    clickPositions.clear();

    while (std::getline(local, linha)) {
        Point p;
        int del = linha.find(",");
        p.x = stoi(linha.substr(0, del));
        p.y = stoi(linha.substr(del + 1));
        clickPositions.push_back(p);
    }

    std::cout << "Carregado com sucesso!\n";

    local.close();

}

void gravaInputs(std::string paraOnde){

    std::ofstream local(paraOnde);
    std::string linha;

    if (!local.is_open()) {
        std::cerr << "Erro ao abrir o arquivo" << std::endl;
        system("pause");
        return;
    }

    for (const Point &p : clickPositions){
        local << std::to_string(p.x) << "," << std::to_string(p.y) << "\n";
    }

}








int main() {
    int choice;
    do {
        std::cout << "\nMenu:\n";
        std::cout << "1- Iniciar cliques\n";
        std::cout << "2- Adicionar posição de Clique\n";
        std::cout << "3- Remover último clique\n";
        std::cout << "4- Atraso entre os cliques\n";
        std::cout << "5- Quantidade de vezes à executar\n";
        std::cout << "6- Carregar configuracao\n";
        std::cout << "7- Grava a configuracao atual\n";
        std::cout << "0- Sair\n";
        std::cout << "Escolha uma opção: ";
        std::cin >> choice;
        std::cin.ignore();

        switch (choice) {
        case 1:
            startClicks();
            break;
        case 2:
            addClickPosition();
            break;
        case 3:
            removeLastClick();
            break;
        case 4:
            setDelayBetweenClicks();
            break;
        case 5:
            setRepeatCount();
            break;
        case 6:{
            std::string from;
            std::cout << "De onde?: ";
            std::getline(std::cin, from);
            recoverInputs(from);
            break;
        }
        case 7:{
            std::string where;
            std::cout << "Para onde?: ";
            std::getline(std::cin, where);
            gravaInputs(where);
            break;
        }
        case 0:
            std::cout << "Saindo..." << std::endl;
            break;
        default:
            std::cout << "Opção inválida, tente novamente." << std::endl;
        }
    } while (choice != 0);

    return 0;
}
