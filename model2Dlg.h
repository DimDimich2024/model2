
// model2Dlg.h: файл заголовка
//
#include "Drawer.h"
#pragma once


// Диалоговое окно Cmodel2Dlg
class Cmodel2Dlg : public CDialogEx
{
// Создание
public:
	Cmodel2Dlg(CWnd* pParent = nullptr);	// стандартный конструктор

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MODEL2_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// поддержка DDX/DDV


// Реализация
protected:
	HICON m_hIcon;

	// Созданные функции схемы сообщений
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	int N;
	double a;
	double b;
	double h;
	const double R = 3;
	double delta = 0.01;
	double mnozh = 1;

	int K;
	double E;
	double epsilon_max;

	
	
	
	
	double f(double ,double,double);
	double q(double, double);
	void barriers();
	void phazy();
	void phazy_2();
	void find_energy();
	void find_r();
	void find_psi();
	double find_perecech(double);



	vector <double> g;
	vector <double> g_vspom;
	vector <double> ph;
	vector <double> ph_k_ot_z;
	vector <double> r_ot_z;
	vector <double> psi;
	
	
	

	
	
	Drawer drv1;
	Drawer drv2;
	Drawer drv3;
	afx_msg void OnBnClickedButton1();
	//afx_msg void OnTimer(UINT_PTR nIDEvent);
};
