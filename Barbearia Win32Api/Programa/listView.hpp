//#pragma once
//#include "defines.h"
//#include <Windows.h>
//#include <vector>
//#include <string>
//#include <CommCtrl.h>
//
//#define _ToWstr(w) const_cast<LPWSTR>(w)
//#define _PickMoney(ldouble) (std::to_wstring(ldouble).substr(0, std::to_wstring(ldouble).find('.') + 3))
//
//#define NOME 0
//#define VLR 1
//#define DESC 2
//#define TOT 3
//
//
//
//void reLVCorteAdded(HWND hwndLv, std::vector<corteInfo>& cInfo) {
//    ListView_DeleteAllItems(hwndLv);
//    int totLin = -1;
//
//    LVITEM lvItem;
//    lvItem.mask = LVIF_TEXT;
//    std::wstring tmp;
//    for (corteInfo& i : cInfo) {
//        //Apaga a ListView e redesenha ela com as informacoes do vetor.
//        lvItem.iItem = ++totLin;
//        i.cod = lvItem.iItem;
//
//        lvItem.iSubItem = NOME;
//        tmp = i.nome;
//        lvItem.pszText = _ToWstr(tmp.c_str());
//        ListView_InsertItem(hwndLv, &lvItem);
//
//        lvItem.iSubItem = VLR;
//        tmp = _PickMoney(i.vlr);
//        lvItem.pszText = _ToWstr(tmp.c_str());
//        ListView_SetItem(hwndLv, &lvItem);
//
//        lvItem.iSubItem = DESC;
//        tmp = _PickMoney(i.desc);
//        lvItem.pszText = _ToWstr(tmp.c_str());
//        ListView_SetItem(hwndLv, &lvItem);
//
//        lvItem.iSubItem = TOT;
//        tmp = _PickMoney(i.tot);
//        lvItem.pszText = _ToWstr(tmp.c_str());
//        ListView_SetItem(hwndLv, &lvItem);
//    }
//
//    //Sempre que essa funcao for executada, avisar que o valor total deve ser atualizado.
//}
//void apagarEssaLinha(HWND hwndMain, HWND hwndLv, std::vector<corteInfo>& cInfo, const int lin) {
//    //Verifica se a linha esta no intervalo do vetor, se o vetor nao eh vazio e se todas as informacoes lidas sao de fato as que foi selecionada.
//    if (cInfo.size() != 0 && lin < cInfo.size()) {
//        bool sameItem = true;
//        wchar_t test[256] = { 0 };
//        ListView_GetItemText(hwndLv, lin, NOME, test, 256);
//        if (std::wstring(test) != cInfo[lin].nome) sameItem = false;
//        ListView_GetItemText(hwndLv, lin, VLR, test, 256);
//        if (std::wstring(test) != std::wstring(_PickMoney(cInfo[lin].vlr))) sameItem = false;
//        ListView_GetItemText(hwndLv, lin, DESC, test, 256);
//        if (std::wstring(test) != std::wstring(_PickMoney(cInfo[lin].desc))) sameItem = false;
//        ListView_GetItemText(hwndLv, lin, TOT, test, 256);
//        if (std::wstring(test) != std::wstring(_PickMoney(cInfo[lin].tot))) sameItem = false;
//		if (cInfo[lin].cod != lin) sameItem = false; 
//
//
//        if (sameItem) {
//            int resp = MessageBox(hwndMain, (L"Nome: " + cInfo[lin].nome + L"\nValor: " + _PickMoney(cInfo[lin].vlr) + L"\nDesconto: " + _PickMoney(cInfo[lin].desc) + L"\nTotal: " + _PickMoney(cInfo[lin].tot)).c_str(), L"Confirma exclusão?", MB_YESNO | MB_ICONWARNING);
//            if (resp == IDYES) {
//                std::vector<corteInfo> tmp;
//				for (const corteInfo& ci : cInfo) {
//					if (ci.cod != lin) {
//						//Passa tudo pro vetor temporario, excluindo o que esta na linha recebida.
//						tmp.push_back(ci);
//					}
//				}
//				cInfo.clear();
//				cInfo = tmp;
//            }
//        }
//    }
//    reLVCorteAdded(hwndLv, cInfo);
//}
//
//
//
//
//
//
//HWND gerarListView(HWND hwnd) {
//    //Criar o controle ListView.
//    HWND hwndListView = CreateWindow(WC_LISTVIEW, L"", WS_VISIBLE | WS_CHILD | LVS_REPORT,
//        100, 10, 400, 200, hwnd, (HMENU)LISTVIEW_CORTES, NULL, NULL);
//
//
//    //Adicionar colunas ao ListView
//    LVCOLUMN lvColumn;
//    lvColumn.mask = LVCF_TEXT | LVCF_WIDTH | LVCF_SUBITEM | LVS_AUTOARRANGE;
//
//    lvColumn.pszText = _ToWstr(L"Nome");
//    lvColumn.cx = 150;
//    lvColumn.iSubItem = NOME;
//    ListView_InsertColumn(hwndListView, NOME, &lvColumn);
//
//    lvColumn.pszText = _ToWstr(L"Valor");
//    lvColumn.cx = 150 ;
//    lvColumn.iSubItem = VLR;
//    ListView_InsertColumn(hwndListView, VLR, &lvColumn);
//
//    lvColumn.pszText = _ToWstr(L"Desconto");
//    lvColumn.cx = 150;
//    lvColumn.iSubItem = DESC;
//    ListView_InsertColumn(hwndListView, DESC, &lvColumn);
//    
//    lvColumn.pszText = _ToWstr(L"Total");
//    lvColumn.cx = 150;
//    lvColumn.iSubItem = TOT;
//    ListView_InsertColumn(hwndListView, TOT, &lvColumn);
//
//
//    // Habilitar notificação de duplo clique
//    ListView_SetExtendedListViewStyle(hwndListView, LVS_EX_DOUBLEBUFFER | LVS_EX_FULLROWSELECT);
//    
//    return hwndListView;
//}
////std::wstring selecionarItem(HWND hList, int iLinha) {
////    if (iLinha < 0) return std::wstring(L"NULO");
////
////    LVITEM lvItem;
////    lvItem.mask = LVIF_TEXT;
////    lvItem.iItem = iLinha;
////    lvItem.iSubItem = 0;
////    lvItem.pszText = buffer;
////    lvItem.cchTextMax = BFFR_SIZE;
////
////    ListView_GetItem(hList, &lvItem);
////
////    return std::wstring(buffer);
////}