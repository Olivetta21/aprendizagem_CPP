#pragma once
#pragma comment(lib, "comctl32.lib")
#ifndef UNICODE
#define UNICODE
#endif
#include "sqlite3.h"
#include <Windows.h>
#include <Windowsx.h>
#include <CommCtrl.h>
#include <vector>
#include <string>
#include <chrono>
#include <random>

//Gerador de números aleatórios-------------------------------------//
std::mt19937 gen(9);
std::uniform_int_distribution<int> distribution(1, 6);


#define WIN32_LEAN_AND_MEAN

//NEXT 1011
//NEXT 2014

//-DIMENSOES-//
#define W_MAINWINDOW 1280
#define H_MAINWINDOW 720
#define W_BTTN 150
#define H_BTTN 50
#define FONT_TAM 20

//-ID DOS BOTOES-//
#define BTTN_MAIN_EXCORTE					1001
#define BTTN_MAIN_EXVENDA					1002
#define BTTN_MAIN_RELATORIO					1003
#define BTTN_MAIN_RELATORIOCORRETO			1009
#define BTTN_MAIN_CORTECORRETA				1008
#define BTTN_DBOX_CONFIRMAR					2001
#define BTTN_DBOX_CANCELAR					2002
#define BTTN_DBOX_SELECORTE					2003
#define BTTN_DBOX_SELECPROD					2004
#define BTTN_DBOX_SELECBARB					2005
#define BTTN_DBOX_MANDECORT					2010
#define BTTN_DBOX_MANDEVEND					2011


//-ID DOS MENUS-//
#define HMENU_MAIN_BARBEIRO					1004
#define HMENU_MAIN_CORTE					1005
#define HMENU_MAIN_PRODUTO					1006

//-ID DAS DIALOG BOXES-//
#define DBOX_MAIN_BLANK						1007
#define DBOX_MAIN_BLANK_WIN					1010
#define DBOX_BLANK_SELECBARB				2007
#define DBOX_BLANK_SELECORTE				2008
#define DBOX_BLANK_SELECPROD				2009

//-ID DAS LISTAS DE ROLAGENS VERTICAIS-//
#define LIST_DBOX_SELECTION					2006

//-ID LISTVIEW-//
#define LSITVIEW_ADDCORTES					2012
#define LISTVIEW_SELPESSOA					2013 


//-CONFIFGURACAO PADRAO DAS DIALOGBOXES-//
#define DBOX_PADRAO_UPPER DIALOG 10, 10, 100, 100 STYLE WS_OVERLAPPED | DS_MODALFRAME
#define DBOX_PADRAO_DOWN FONT 20, "MS Gothic" BEGIN CONTROL "", LIST_DBOX_SELECTION, "LISTBOX", WS_TABSTOP | WS_VSCROLL | WS_HSCROLL | WS_BORDER | LBS_NOTIFY | LBS_HASSTRINGS | LBS_STANDARD, 1, 0, 98, 50 PUSHBUTTON "Confirmar", BTTN_DBOX_CONFIRMAR, 10 , 80, 40, 10 PUSHBUTTON "Cancelar", BTTN_DBOX_CANCELAR, 50 , 80, 40, 10 END



#define BFFR_SIZE 256


//-MACROS PARA FUNCOES-//
#define _ToWstr(wchar) const_cast<LPWSTR>(wchar)
#define _PickMoney(ldouble) (std::to_wstring(ldouble).substr(0, std::to_wstring(ldouble).find('.') + 3))
#define _PickMoneyM(ldouble) (std::to_string(ldouble).substr(0, std::to_string(ldouble).find('.') + 3))







//-VARIAVEIS GLOBAIS-//
sqlite3* db = nullptr;


HANDLE hTimer = NULL;
unsigned long long int timePassed = 0;

//int passed = 0;
//
//short secnds = 0;
//SYSTEMTIME sysLocalTime;

std::vector<HWND> main_vecBttns, main_vecLabl;


HINSTANCE  main_hinstance;
HWND NULLHWND = nullptr, main_hwnd, relogio_hwnd,
listView___hwnd,
main_vlrCaixa, main_vlrVenda, main_vlrCorte;
RECT main_areaCliente, main_areaTotal;
HMENU main_hmenu;
HFONT fontePadrao;

HWND timedMsg;// CreateWindow(L"STATIC", L"", WS_CHILD, 0, 0, 0, 0, main_hwnd, 0, NULL, NULL);
bool atualizaValor = true;

int bttnsNewWSize = 0, bttnsNewHSize = 0;

long double last_vlr_Cortes = 0, last_vlr_Vendas = 0, vlr_Vendas = 0, vlr_Cortes = 0;
wchar_t buffer[BFFR_SIZE] = { 0 };

