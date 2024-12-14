
// model2.h: главный файл заголовка для приложения PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "включить pch.h до включения этого файла в PCH"
#endif

#include "resource.h"		// основные символы


// Cmodel2App:
// Сведения о реализации этого класса: model2.cpp
//

class Cmodel2App : public CWinApp
{
public:
	Cmodel2App();

// Переопределение
public:
	virtual BOOL InitInstance();

// Реализация

	DECLARE_MESSAGE_MAP()
};

extern Cmodel2App theApp;
