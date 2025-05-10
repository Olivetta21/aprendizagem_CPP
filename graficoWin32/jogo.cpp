#include <windows.h>
#include <windowsx.h>
#include <random>




//Variaveis globais------------------------------------------------------------------------------------------------------------
struct windowconfig {
    HWND hMainWin;
    int X = 1900;
    int Y = 1000;
    int style = WS_OVERLAPPEDWINDOW;
    RECT clientW = { 0, 0, X, Y};
    HDC hdc;
};
windowconfig winCfg;

std::mt19937 gen(0);
std::uniform_int_distribution<int> randX(0, winCfg.X);
std::uniform_int_distribution<int> randY(0, winCfg.Y);
std::uniform_int_distribution<int> randRGB(0, 1);

bool vKey[256] = { 0 };
MSG msg = { 0 };
//-----------------------------------------------------------------------------------------------------------------------------



void initGame() {
    winCfg.hdc = GetDC(winCfg.hMainWin);
}
void updateGame() {


    RECT crecttemp;
    GetClientRect(winCfg.hMainWin, &crecttemp);
    if (vKey[VK_CONTROL]) PostMessage(winCfg.hMainWin, WM_DESTROY, 0, 0);
}
void drawGame() {

    SetPixel(winCfg.hdc, randX(gen), randY(gen), (randRGB(gen)) ? RGB(255,0, 0) : RGB(0, 255, 0));
}
void closeGame() {

}








LRESULT CALLBACK WinProc(HWND, UINT, WPARAM, LPARAM);

//Funcao Principal-------------------------------------------------------------------------------------------------------------
int APIENTRY WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow) {
    // Registrar a classe da janela
    WNDCLASSW wc = { 0 };
    wc.hbrBackground = (HBRUSH)COLOR_WINDOW + 1;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hInstance = hInstance;
    wc.lpszClassName = L"BasicWindow";
    wc.lpfnWndProc = WinProc;

    RegisterClassW(&wc);

    // Criar a janela
    winCfg.hMainWin = CreateWindow("BasicWindow", "Jogo",
        winCfg.style, CW_USEDEFAULT, CW_USEDEFAULT,
        0, 0,
        NULL, NULL, hInstance, NULL);

    AdjustWindowRectEx(&winCfg.clientW, GetWindowStyle(winCfg.hMainWin), GetMenu(winCfg.hMainWin) != NULL, GetWindowExStyle(winCfg.hMainWin));
    winCfg.clientW.right -= winCfg.clientW.left;
    winCfg.clientW.bottom -= winCfg.clientW.top;
    MoveWindow(winCfg.hMainWin,
        GetSystemMetrics(SM_CXSCREEN) / 2 - (winCfg.clientW.right / 2), GetSystemMetrics(SM_CYSCREEN) / 2 - (winCfg.clientW.bottom / 2),
        winCfg.clientW.right, winCfg.clientW.bottom, TRUE);
    ShowWindow(winCfg.hMainWin, nCmdShow);
    UpdateWindow(winCfg.hMainWin);


    initGame();

    do {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else {
            updateGame();
            drawGame();
        }
    } while (msg.message != WM_QUIT);

    closeGame();

    return int(&msg.wParam);
}
//-----------------------------------------------------------------------------------------------------------------------------



// Gerenciador de mensagens do sistema-----------------------------------------------------------------------------------------
LRESULT CALLBACK WinProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_KEYDOWN:
        vKey[lParam] = true;
        break;
    case WM_KEYUP:
        vKey[lParam] = false;
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    default:
        return (DefWindowProc(hwnd, msg, wParam, lParam));
    }

    return 0;
}
//-----------------------------------------------------------------------------------------------------------------------------
