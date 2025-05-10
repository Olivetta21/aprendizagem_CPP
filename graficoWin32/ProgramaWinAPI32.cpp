#ifndef UNICODE
#define UNICODE
#endif

#pragma comment(lib, "comctl32.lib")

#include <windows.h>
#include <commctrl.h>
#include <string>
#include <stdlib.h>
#include "funcoes.hpp"
#include <vector>


#define CADD 1101
#define CDEL 1102
#define LADD 1201
#define LDEL 1202
#define OTHR1 1301

#define _ToWstr(w) const_cast<LPWSTR>(w)
#define _PickMoney(ldouble) (std::to_wstring(ldouble).substr(0, std::to_wstring(ldouble).find('.') + 3))
#define IDC_LISTVIEW 1001
#define BFFR_SIZE 256

#define NOME 0
#define VLR 1
#define DESC 2
#define TOT 3



int totCol = -1;
int totLin = -1;

HWND hMain;
RECT subItemRect = { 0 };
HWND hwndListView = NULL;
WCHAR buffer[BFFR_SIZE] = { 0 };
HFONT fontePadrao;

//-ATUALIZAR A FONTE DE ACORDO COM O TAMANHO DA TELA-//
void updateFontSize(int wide) {
    int fontSize = wide * 35 / 1280;

    fontePadrao = CreateFont(
        fontSize, 0, 0, 0, FW_NORMAL, TRUE, FALSE, FALSE, DEFAULT_CHARSET,
        OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY,
        DEFAULT_PITCH | FF_DONTCARE, L"MS Gothic"
    );
}




struct corteInfo {
    std::wstring nome;
    int cod;
    long double vlr, desc, tot;
    corteInfo() {
        cod = -1;
        nome = L"";
        vlr = desc = tot = 0;
    }
};
void reLVCorteAdded(HWND hwndLv, std::vector<corteInfo>& cInfo) {
    ListView_DeleteAllItems(hwndLv);
    totLin = -1;

    LVITEM lvItem;
    lvItem.mask = LVIF_TEXT;
    std::wstring tmp;
    for (corteInfo& i : cInfo) {
        lvItem.iItem = ++totLin;
        i.cod = lvItem.iItem;

        lvItem.iSubItem = NOME;
        tmp = i.nome;
        lvItem.pszText = _ToWstr(tmp.c_str());
        ListView_InsertItem(hwndLv, &lvItem);

        lvItem.iSubItem = VLR;
        tmp = _PickMoney(i.vlr);
        lvItem.pszText = _ToWstr(tmp.c_str());
        ListView_SetItem(hwndLv, &lvItem);

        lvItem.iSubItem = DESC;
        tmp = _PickMoney(i.desc);
        lvItem.pszText = _ToWstr(tmp.c_str());
        ListView_SetItem(hwndLv, &lvItem);

        lvItem.iSubItem = TOT;
        tmp = _PickMoney(i.tot);
        lvItem.pszText = _ToWstr(tmp.c_str());
        ListView_SetItem(hwndLv, &lvItem);
    }
}
void apagarEssaLinha(HWND hwndMain, HWND hwndLv, std::vector<corteInfo>& cInfo, const int lin) {
    if (cInfo.size() != 0 && lin < cInfo.size()) {
        bool sameItem = true;
        wchar_t test[256] = { 0 };
        ListView_GetItemText(hwndLv, lin, NOME, test, 256);
        if (std::wstring(test) != cInfo[lin].nome) sameItem = false;
        ListView_GetItemText(hwndLv, lin, VLR, test, 256);
        if (std::wstring(test) != std::wstring(_PickMoney(cInfo[lin].vlr))) sameItem = false;
        ListView_GetItemText(hwndLv, lin, DESC, test, 256);
        if (std::wstring(test) != std::wstring(_PickMoney(cInfo[lin].desc))) sameItem = false;
        ListView_GetItemText(hwndLv, lin, TOT, test, 256);
        if (std::wstring(test) != std::wstring(_PickMoney(cInfo[lin].tot))) sameItem = false;

             
        if (sameItem) {
            int resp = MessageBox(hwndMain, (L"Nome: " + cInfo[lin].nome + L"\nValor: " + _PickMoney(cInfo[lin].vlr) + L"\nDesconto: " + _PickMoney(cInfo[lin].desc) + L"\nTotal: " + _PickMoney(cInfo[lin].tot)).c_str(), L"Confirma exclusão?", MB_YESNO | MB_ICONWARNING);
            if (resp == IDYES) {
                std::vector<corteInfo> tmp;
                if (cInfo[lin].cod == lin) {
                    for (corteInfo& ci : cInfo) {
                        if (ci.cod != lin) {
                            tmp.push_back(ci);
                        }
                    }
                    cInfo.clear();
                    cInfo = tmp;
                }
            }
        }
    }
    reLVCorteAdded(hwndLv, cInfo);
}








//---CONTROLE ONDE ACONTECE A EDICAO, BLOQUEANDO OUTRAS JANELAS---//
HWND lvHwnd; int lin; int col;
INT_PTR CALLBACK procCxEdit(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    static HWND hEdit = NULL;

    switch (msg) {
    case WM_INITDIALOG: {

        RECT lvNaTela = { 0 };
        GetWindowRect(lvHwnd, &lvNaTela);
        subItemRect.left += lvNaTela.left; subItemRect.top += lvNaTela.top;

        SetWindowPos(hwnd, NULL, subItemRect.left - 25, subItemRect.top, subItemRect.right + 25, subItemRect.bottom, NULL);

        hEdit = CreateWindow(L"EDIT", buffer, WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL, 25, 0, subItemRect.right, subItemRect.bottom, hwnd, NULL, NULL, NULL);
        HWND bttok = CreateWindow(L"BUTTON", L"OK", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 0, 0, 25, subItemRect.bottom, hwnd, (HMENU)101, NULL, NULL);
        


        SendMessage(hEdit, WM_SETFONT, (WPARAM)fontePadrao, FALSE);
        SendMessage(bttok, WM_SETFONT, (WPARAM)fontePadrao, FALSE);

        SetFocus(hEdit);
        break;
    }
    case WM_COMMAND: {
        switch (LOWORD(wParam)) {
        case 101:
            GetWindowText(hEdit, buffer, BFFR_SIZE);
            ListView_SetItemText(lvHwnd, lin, col, buffer);
            EndDialog(hwnd, 0);
            return TRUE;
        }
        break;
    }
    case WM_CTLCOLORDLG: {
        return (INT_PTR)GetStockObject(COLOR_BACKGROUND);
        break;
    }
    case WM_CLOSE:
        EndDialog(hwnd, 0);
        //PostQuitMessage(0);
        return TRUE;
    }

    return FALSE;
}
void criarCxEdit(HWND hwnd, HWND _lvHwnd, int _lin, int _col) {
    lvHwnd = _lvHwnd; lin = _lin; col = _col;
    DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(DBOX_MAIN_BLANK), hwnd, procCxEdit);
}




//---PROC PRINCIPAL, AQUI EH TRATADO O DOUBLECLICK---//
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    static HWND bttns[5] = { 0 };
    static std::vector<corteInfo> vecCInfo;
    

    switch (uMsg) {
    case WM_CREATE: {
        //botoes
        bttns[0] = CreateWindow(L"BUTTON", L"C ADD", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 350, 10, 50, 20, hwnd, (HMENU)CADD, NULL, NULL);
        bttns[1] = CreateWindow(L"BUTTON", L"C DEL", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 400, 10, 50, 20, hwnd, (HMENU)CDEL, NULL, NULL);
        bttns[2] = CreateWindow(L"BUTTON", L"L ADD", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 350, 40, 50, 20, hwnd, (HMENU)LADD, NULL, NULL);
        bttns[3] = CreateWindow(L"BUTTON", L"L DEL", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 400, 40, 50, 20, hwnd, (HMENU)LDEL, NULL, NULL);
        bttns[4] = CreateWindow(L"BUTTON", L"OTHR1", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 350, 70, 50, 20, hwnd, (HMENU)OTHR1, NULL, NULL);

        // Inicializar a biblioteca Common Controls
        INITCOMMONCONTROLSEX icex;
        icex.dwSize = sizeof(INITCOMMONCONTROLSEX);
        icex.dwICC = ICC_LISTVIEW_CLASSES;
        InitCommonControlsEx(&icex);

        // Criar o controle ListView
        hwndListView = CreateWindow(WC_LISTVIEW, L"", WS_VISIBLE | WS_CHILD | LVS_REPORT,
            50, 10, 400, 200, hwnd, (HMENU)IDC_LISTVIEW, NULL, NULL);


        // Adicionar colunas ao ListView
        LVCOLUMN lvColumn;
        lvColumn.mask = LVCF_TEXT | LVCF_WIDTH | LVCF_SUBITEM;

        lvColumn.pszText = _ToWstr(L"Nome");
        lvColumn.cx = 150;
        lvColumn.iSubItem = ++totCol;
        ListView_InsertColumn(hwndListView, totCol, &lvColumn);

        lvColumn.pszText = _ToWstr(L"Idade");
        lvColumn.cx = 80;
        lvColumn.iSubItem = ++totCol;
        ListView_InsertColumn(hwndListView, totCol, &lvColumn);

        lvColumn.pszText = _ToWstr(L"Altura");
        lvColumn.cx = 80;
        lvColumn.iSubItem = ++totCol;
        ListView_InsertColumn(hwndListView, totCol, &lvColumn);

        // Adicionar itens ao ListView
        LVITEM lvItem;
        lvItem.mask = LVIF_TEXT | LVS_AUTOARRANGE;

        for (int i = 0; i < 50; ++i) {
            lvItem.iItem = ++totLin;
            lvItem.iSubItem = 0;
            std::wstring tmp = L" - Nome"; tmp += std::to_wstring(i) + L" - ";

            lvItem.pszText = _ToWstr(tmp.c_str());
            ListView_InsertItem(hwndListView, &lvItem);

            lvItem.iSubItem = 1;
            tmp = std::to_wstring(20 + i);
            lvItem.pszText = _ToWstr(tmp.c_str());
            ListView_SetItem(hwndListView, &lvItem);

            lvItem.iSubItem = 2;
            tmp = std::to_wstring(160 + i* 2);
            lvItem.pszText = _ToWstr(tmp.c_str());
            ListView_SetItem(hwndListView, &lvItem);
        }

        // Habilitar notificação de duplo clique
        ListView_SetExtendedListViewStyle(hwndListView, LVS_EX_DOUBLEBUFFER | LVS_EX_FULLROWSELECT);
        break;
    }
    case WM_NOTIFY: {
        NMHDR* pNMHDR = reinterpret_cast<NMHDR*>(lParam);
        if (pNMHDR->idFrom == IDC_LISTVIEW) {
            NMLISTVIEW* pnmlv = (NMLISTVIEW*)lParam;
            NMITEMACTIVATE* pNMIA = reinterpret_cast<NMITEMACTIVATE*>(lParam);

            int clickedColumn = pnmlv->iSubItem;

            if (pNMIA->iItem < 0 || clickedColumn < 0) return FALSE;

            if (pNMHDR->code == NM_DBLCLK) {
                LVITEM lvItem;
                lvItem.mask = LVIF_TEXT;
                lvItem.iItem = pNMIA->iItem;
                lvItem.iSubItem = clickedColumn;
                lvItem.pszText = buffer;
                lvItem.cchTextMax = BFFR_SIZE;

                ListView_GetItem(pNMIA->hdr.hwndFrom, &lvItem);
                ListView_GetSubItemRect(pNMIA->hdr.hwndFrom, lvItem.iItem, lvItem.iSubItem, LVIR_LABEL, &subItemRect);

                subItemRect.right -= subItemRect.left; subItemRect.bottom -= subItemRect.top;


                //criarCxEdit(hwnd, pNMHDR->hwndFrom, lvItem.iItem, lvItem.iSubItem);
                apagarEssaLinha(hwnd, pNMIA->hdr.hwndFrom, vecCInfo, lvItem.iItem);

            }
        }
        break;
    }
    case WM_COMMAND: {
        switch (LOWORD(wParam)) {
        case CADD: {
            LVCOLUMN lvColumn;
            lvColumn.mask = LVCF_TEXT | LVCF_WIDTH | LVCF_SUBITEM;

            lvColumn.iSubItem = ++totCol;
            std::wstring ttmp;
            ttmp = (std::wstring(L"Adicionado") + std::to_wstring(totCol));

            lvColumn.pszText = _ToWstr(ttmp.c_str());
            lvColumn.cx = 150;
            ListView_InsertColumn(hwndListView, totCol, &lvColumn);
            break;
        }
        case CDEL: {
            if (totCol >= 0) ListView_DeleteColumn(hwndListView, totCol--);
            if (totCol < 0) {
                ListView_DeleteAllItems(hwndListView);
                totLin = -1;
            }
            break;
        }
        case LADD: {


            LVITEM lvItem;
            lvItem.mask = LVIF_TEXT;
            lvItem.iItem = ++totLin;
            lvItem.iSubItem = 0;

            //MessageBox(hwnd, L"L C", (std::to_wstring(totLin) + std::wstring(L" - ") + std::to_wstring(totCol)).c_str(), MB_OK);

            std::wstring tmp = L"L:" + std::to_wstring(totLin) + L" C:" + std::to_wstring(totCol);

            lvItem.pszText = _ToWstr(L"");
            ListView_InsertItem(hwndListView, &lvItem);

            lvItem.pszText = _ToWstr(tmp.c_str());
            lvItem.iSubItem = totCol;
            ListView_SetItem(hwndListView, &lvItem);

            break;
        }
        case LDEL: {
            if (totLin >= 0) ListView_DeleteItem(hwndListView, totLin--/2);
            break;
        }
        case OTHR1: {
            vecCInfo.clear();
            for (int i = 0; i < 10; i++) {
                corteInfo cInfo;
                cInfo.nome = L"Nome" + std::to_wstring(i + 1);
                cInfo.vlr = i * 3.2;
                cInfo.desc = i * 0.23;
                cInfo.tot = ((i * 3.2) - (i * 0.23));

                vecCInfo.push_back(cInfo);
            }
            reLVCorteAdded(hwndListView, vecCInfo);
            break;
        }
        }
        break;
    }
    case WM_SIZE: {
        RECT tela = { 0 };
        GetClientRect(hMain, &tela);

        updateFontSize(tela.right);
    
        SetWindowPos(hwndListView, NULL, 10, 10, tela.right - 300, tela.bottom - 50, NULL);
        SendMessage(hwndListView, WM_SETFONT, (WPARAM)fontePadrao, FALSE);

        for (int i = 0; i < 4; i++) {
            SetWindowPos(bttns[0], NULL, tela.right - 100, 10, 50, 20, NULL);
            SetWindowPos(bttns[1], NULL, tela.right - 50, 10, 50, 20, NULL);
            SetWindowPos(bttns[2], NULL, tela.right - 100, 30, 50, 20, NULL);
            SetWindowPos(bttns[3], NULL, tela.right - 50, 30, 50, 20, NULL);
            SetWindowPos(bttns[4], NULL, tela.right - 100, 50, 50, 20, NULL);
        }

        RECT lvRc = { 0 };
        GetClientRect(hwndListView, &lvRc);
        for (int i = 0; i < totCol + 1; i++) {
            ListView_SetColumnWidth(hwndListView, i, lvRc.right / (totCol + 1));
        }
        ListView_EnsureVisible(hwndListView, 0, FALSE);

        InvalidateRect(hMain, &tela, TRUE);
        break;
    }
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}



//---MAIN---//
int WINAPI WinMain(HINSTANCE _In_ hInstance, HINSTANCE _In_opt_ hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow) {
    // Registrar a classe da janela
    WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, WindowProc, 0L, 0L,
                     GetModuleHandle(NULL), NULL, NULL, NULL, NULL,
                     L"ListViewWindowClass", NULL };

    wc.hbrBackground = (HBRUSH)COLOR_BACKGROUND;
    RegisterClassEx(&wc);

    // Criar a janela
    hMain = CreateWindow(wc.lpszClassName, L"Exemplo de ListView", WS_OVERLAPPEDWINDOW,
        100, 100, 500, 400, NULL, NULL, wc.hInstance, NULL);

    // Exibir a janela
    ShowWindow(hMain, nCmdShow);
    UpdateWindow(hMain);

    // Loop de mensagem principal
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    // Retornar saída do programa
    return (int)msg.wParam;
}




