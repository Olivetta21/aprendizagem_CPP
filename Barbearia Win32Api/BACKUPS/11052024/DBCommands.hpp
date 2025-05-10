#pragma once
#include "defines.h"

// Função para converter const char* para std::wstring
std::wstring charToWstring(const char* narrowString) {
	std::wstring wideString;

	if (narrowString != nullptr) {
		// Determine o tamanho necessário para a conversão
		int length = MultiByteToWideChar(CP_UTF8, 0, narrowString, -1, nullptr, 0);

		// Realize a conversão
		if (length > 0) {
			wideString.resize(length - 1); // Desconte o caractere nulo final
			MultiByteToWideChar(CP_UTF8, 0, narrowString, -1, &wideString[0], length);
		}
	}

	return wideString;
}

// Função para converter std::wstring para std::string
std::string wstringToString(const std::wstring& wideString) {
	int size_needed = WideCharToMultiByte(CP_UTF8, 0, &wideString[0], static_cast<int>(wideString.size()), nullptr, 0, nullptr, nullptr);
	std::string result(size_needed, 0);
	WideCharToMultiByte(CP_UTF8, 0, &wideString[0], static_cast<int>(wideString.size()), &result[0], size_needed, nullptr, nullptr);
	return result;
}



int erroBancoDados(const wchar_t *adicional = nullptr) {
	std::wstring erro;
	erro = charToWstring(sqlite3_errmsg(db));
	if (adicional != nullptr) erro += L"\n" + std::wstring(adicional);

	return MessageBox(0, erro.c_str(), L"ERRO SQLITE", MB_ICONWARNING | MB_OK);
}


int prepareAndDisplay(HWND hwnd, const std::string& command) {
	sqlite3_stmt* stmt = nullptr;


	if (sqlite3_prepare_v2(db, command.c_str(), -1, &stmt, 0) != SQLITE_OK) {
		MessageBox(hwnd, L"ERRO", L"Alerta", MB_ICONWARNING | MB_OK);
		return 1; // Retorna um valor negativo para indicar erro
	}

	std::wstring junto;
	while (sqlite3_step(stmt) == SQLITE_ROW) {
		junto += charToWstring((const char*)sqlite3_column_text(stmt, 0));
		junto += charToWstring((const char*)sqlite3_column_text(stmt, 1));
		junto += charToWstring((const char*)sqlite3_column_text(stmt, 2));
		junto += L"\n";
	}
	sqlite3_finalize(stmt);


	MessageBox(hwnd, junto.c_str(), L"Alerta", MB_ICONWARNING | MB_OK);

	return 2;
}