#include <iostream>
#include <cstdlib>
#include <ctime>
#include <clocale>
#include <windows.h>
#include "menu.h"
#include "renderer.h"

int main() 
{
    SetConsoleOutputCP(866);
    SetConsoleCP(866);
    setlocale(LC_ALL, "ru");
    srand((unsigned)time(nullptr));

    Renderer::hideCursor();      

    Menu menu;
    menu.run();

    Renderer::showCursor();
    system("cls");
    std::cout << "\nСпасибо за игру!\n";
    system("pause");
    return 0;
    
}