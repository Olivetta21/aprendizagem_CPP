#pragma once
#include "defines.h"
#include "objetos.hpp"


//-CONFIGURACOES JANELAS-//
#define DLGWINPERCENTMAIN 0.8


int erroBancoDados(const wchar_t*);
std::wstring charToWstring(const char*);
std::string wstringToString(const std::wstring&);





//-DEIXAR APENAS DUAS CASAS DECIMAIS-//
long double truncTwo(long double to_trunc) {
	to_trunc *= 100.0f;
	long long int trunc = to_trunc;
	long double after = trunc;
	after /= 100.0f;
	//MessageBox(0, std::wstring(std::to_wstring(to_trunc) + L"\n" + std::to_wstring(trunc) + L"\n" + std::to_wstring(after)).c_str(), L"truncamento", MB_OK);

	return after;
}



//-FUNCAO PRA RETORNAR COM SEGURANCA UMA STRING CONVERTIDA EM NUMERO-//
double wcToD(const wchar_t* wc) {
	try {
		return std::stod(wc);
	}
	catch (const std::invalid_argument& e) {
		return 0;
	}
}
double cToD(const char* c) {
	try {
		return std::stod(c);
	}
	catch (const std::invalid_argument& e) {
		return 0;
	}
}



//-TESTA STRING SE EH SOMENTE ESPACOS-//
bool isBlankC(std::string str) {
	for (const char& c : str) {
		if (!isspace(c)) return 0;
	}
	return 1;
}
bool isBlankW(std::wstring wstr) {
	for (const wchar_t& wc : wstr) {
		if (!iswspace(wc)) return 0;
	}
	return 1;
}





//-ATUALIZAR A FONTE DE ACORDO COM O TAMANHO DA TELA-//
void updateFontSize(int wide = main_areaCliente.right) {
	int fontSize = wide * FONT_TAM / 1280;

	fontePadrao = CreateFont(
		fontSize, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET,
		OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE, L"MS Courier New"
	);
}



//-HORARIO-//
std::string twoDig(short data) {
	std::string dataStr;
	if (data < 10) dataStr = "0";
	dataStr += std::to_string(data);
	return dataStr;
}
std::string getTime_now(int info) {
	static SYSTEMTIME sysTime;
	GetLocalTime(&sysTime);
	std::string tmpTime;

	switch (info){
	case 1:
		tmpTime += std::to_string(sysTime.wYear) + "-" + twoDig(sysTime.wMonth) + "-" + twoDig(sysTime.wDay) + " ";
	case 2:
		tmpTime += twoDig(sysTime.wHour) + ":" + twoDig(sysTime.wMinute) + ":" + twoDig(sysTime.wSecond);
		break;
	case 3:
		tmpTime += std::to_string(sysTime.wYear) + "-" + twoDig(sysTime.wMonth) + "-" + twoDig(sysTime.wDay);
		break;
	default:
		break;
	}

	return tmpTime;
}





//-FUNCAO PARA CENTRALIZAR A JANELA FILHA-//
void centerWinInMain(HWND hwnd, double percent = DLGWINPERCENTMAIN) {
	//Centralizando a dialogBox.
	RECT newPosDlg = { 0 };
	newPosDlg.left = main_areaTotal.left + (main_areaTotal.right * (1 - percent)) / 2;
	newPosDlg.top = main_areaTotal.top + (main_areaTotal.bottom * (1 - percent)) / 2;
	newPosDlg.right = main_areaTotal.right * percent;
	newPosDlg.bottom = main_areaTotal.bottom * percent;

	SetWindowPos(hwnd, NULL,
		newPosDlg.left, newPosDlg.top,
		newPosDlg.right, newPosDlg.bottom, NULL);
}








int getFontSize(HWND &hwin, bool HW) {
	HFONT hFont = (HFONT)SendMessage(hwin, WM_GETFONT, 0, 0);
	// Obter informações sobre a fonte

	TEXTMETRIC tm = { 0 };
	HDC hdc = GetDC(hwin);
	HFONT hOldFont = (HFONT)SelectObject(hdc, hFont);
	GetTextMetrics(hdc, &tm);
	SelectObject(hdc, hOldFont);
	ReleaseDC(hwin, hdc);

	//MessageBox(NULL, std::to_wstring(tm.tmHeight).c_str(), L"gggggg", MB_OK);
	if (HW) return tm.tmHeight;
	return tm.tmAveCharWidth;
}


















INT_PTR CALLBACK procpadrao(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
	

	switch (msg) {
	case WM_INITDIALOG: {
		centerWinInMain(hwnd);
		break;
	}
	case WM_SIZE: {
		RECT jan = { 0 };
		GetClientRect(hwnd, &jan);
		InvalidateRect(hwnd, &jan, TRUE);
		break;
	}
	case WM_CLOSE:{
		EndDialog(hwnd, 0);
		return TRUE;
	}
	}

	return FALSE;
}
INT_PTR padrao(HWND hwnd) {
	return DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(DBOX_MAIN_BLANK), hwnd, procpadrao);
}
