
// model2Dlg.cpp: файл реализации
//

#include "pch.h"
#include "framework.h"
#include "model2.h"
#include "model2Dlg.h"
#include "afxdialogex.h"
#define _USE_MATH_DEFINES
#include <math.h>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Диалоговое окно Cmodel2Dlg



Cmodel2Dlg::Cmodel2Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MODEL2_DIALOG, pParent)
	, N(10)
	, a(0.1)
	, b(0.1)
	, h(50)
	, K(1)
	, E(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Cmodel2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT2, N);
	DDX_Text(pDX, IDC_EDIT3, a);
	DDX_Text(pDX, IDC_EDIT4, b);
	//DDX_Text(pDX, IDC_EDIT1, drv1);
	DDX_Text(pDX, IDC_EDIT5, h);
	//DDX_Text(pDX, IDC_EDIT6, drv2);
	DDX_Text(pDX, IDC_EDIT7, K);
	DDX_Text(pDX, IDC_EDIT8, E);
	//DDX_Text(pDX, IDC_EDIT9, drv3);
}

BEGIN_MESSAGE_MAP(Cmodel2Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON1, &Cmodel2Dlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// Обработчики сообщений Cmodel2Dlg

BOOL Cmodel2Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Задает значок для этого диалогового окна.  Среда делает это автоматически,
	//  если главное окно приложения не является диалоговым
	SetIcon(m_hIcon, TRUE);			// Крупный значок
	SetIcon(m_hIcon, FALSE);		// Мелкий значок

	// TODO: добавьте дополнительную инициализацию
	drv1.Create(GetDlgItem(IDC_EDIT1)->GetSafeHwnd());
	drv2.Create(GetDlgItem(IDC_EDIT6)->GetSafeHwnd());
	drv3.Create(GetDlgItem(IDC_EDIT9)->GetSafeHwnd());
	//SetTimer(1, 1, NULL);
	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

// При добавлении кнопки свертывания в диалоговое окно нужно воспользоваться приведенным ниже кодом,
//  чтобы нарисовать значок.  Для приложений MFC, использующих модель документов или представлений,
//  это автоматически выполняется рабочей областью.

void Cmodel2Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // контекст устройства для рисования

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Выравнивание значка по центру клиентского прямоугольника
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Нарисуйте значок
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// Система вызывает эту функцию для получения отображения курсора при перемещении
//  свернутого окна.
HCURSOR Cmodel2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void Cmodel2Dlg::barriers()
{
	//int n = 1000;

	g.clear();
	g_vspom.clear();
	bool yama = false;
	int kolvo;
	int a_vspom = a * 100;
	int b_vspom = b * 100;
	int R_vspom = R * 100;
	for (int j = 0; j < 2 * N; j++)
	{
		if (yama) kolvo = a_vspom; else kolvo = b_vspom;
		for (int i = 0; i < kolvo; i++)
		{
			if (!yama)
			{
				g_vspom.push_back(0);
			}
			else
			{
				g_vspom.push_back(-h);
			}
		}
		yama = !yama;
	}
	double r;
	if (N % 2 == 0) r = -(N / 2) * (a_vspom + b_vspom)-a_vspom/2;
	else r = -(N / 2) * (a_vspom + b_vspom) -3* a_vspom /2;
	double z = -R;
	for (double z = -R_vspom; z <= -r; z++)
	{
		if (z < r) g.push_back(0);
	}
	for (int j= 0;j <g_vspom.size(); j++)
	{
		g.push_back(g_vspom[j]);
	}
	int s = g.size();
	for (int j = s; j < 2 * R_vspom; j++)
	{
		g.push_back(0);
	}
	drv1.Draw(0,-h , R,-R , 0.01,R_vspom, g);
}

//void Cmodel2Dlg::OnTimer(UINT_PTR nIDEvent)
//{
//	CDialogEx::OnTimer(nIDEvent);
//}

double Cmodel2Dlg::f(double zed, double phi,double epsilon)
{
	int i = (zed + R) * 100;
	return (g[i] - epsilon) * cos(phi) * cos(phi) - sin(phi) * sin(phi);
	
}

void Cmodel2Dlg::phazy()
{
	
	epsilon_max = -h;
	double phi_min = 0;
	
	
	ph.clear();
	
	for (double epsilon = epsilon_max; epsilon < 0; epsilon += 0.01)
	{
		double phi = M_PI / 2;
		for (double zed = -R; zed <R-0.01; zed +=0.01)
		{
			
			double k1 = f(zed, phi, epsilon) * delta;
			double k2 = f(zed + delta / 2, phi + k1 / 2, epsilon) * delta;
			double k3 = f(zed + delta / 2, phi + k2 / 2, epsilon) * delta;
			double k4 = f(zed + delta, phi + k3, epsilon) * delta;
			phi = phi + (1. / 6.) * (k1 + 2 * k2 + 2 * k3 + k4);
		}
		if (phi < phi_min) phi_min = phi;
		
		ph.push_back(phi);
	}
	drv2.Draw(M_PI / 2 + 0.01, phi_min, 0,epsilon_max, 0.01, h*100,ph);

	int k = 0;
	double y = -(2 * k + 1) * M_PI / 2;
	while (y > phi_min)
	{
		drv2.Draw_ot_do(0, y, epsilon_max, y, epsilon_max,0, phi_min, M_PI / 2 + 0.01);
		k++;
		y = -(2 * k + 1) * M_PI / 2;
	}
	
	
}

double Cmodel2Dlg::find_perecech(double epsilon)
{

	double delta = 0.01;
	double phi = M_PI / 2;
	for (double zed = -R; zed < R - 0.01; zed += 0.01)
	{
		double k1 = f(zed, phi, epsilon) * delta;
		double k2 = f(zed + delta / 2, phi + k1 / 2, epsilon) * delta;
		double k3 = f(zed + delta / 2, phi + k2 / 2, epsilon) * delta;
		double k4 = f(zed + delta, phi + k3, epsilon) * delta;
		phi = phi + (1. / 6.) * (k1 + 2 * k2 + 2 * k3 + k4);
		//if (phi < phi_min) phi_min = phi;
	}
	return phi;

}

void Cmodel2Dlg::find_energy()
{

	double otvet = -(2 * K + 1) * M_PI / 2;
	double y;
	double x;
	double x_min = epsilon_max;
	double x_max = 0;

	double error = 10000;
	while (error > 0.105)
	{
		x = (x_max + x_min) / 2;
		y = find_perecech(x);
		if (y > otvet)
		{
			x_min = x;
		}
		else
		{
			x_max = x;
		}
		error = abs(y - otvet);
	}
	E =x;
	//E = -E;
}

void Cmodel2Dlg::phazy_2()
{
	//double phi_min = 0;
	double delta = 0.01;
	ph_k_ot_z.clear();
	double epsilon = E;
	double phi = M_PI / 2;
	for (double zed = -R; zed < R-0.01; zed +=0.01)
	{
		double k1 = f(zed, phi, epsilon) * delta;
		double k2 = f(zed + delta / 2, phi + k1 / 2, epsilon) * delta;
		double k3 = f(zed + delta / 2, phi + k2 / 2, epsilon) * delta;
		double k4 = f(zed + delta, phi + k3, epsilon) * delta;
		phi = phi + (1. / 6.) * (k1 + 2 * k2 + 2 * k3 + k4);
		//if (phi < phi_min) phi_min = phi;
		ph_k_ot_z.push_back(phi);
	}
}

double Cmodel2Dlg::q(double zed, double r)
{
	int i = (zed + R) * 100;
	return r*(1+g[i] - E) * cos(ph_k_ot_z[i]) * sin(ph_k_ot_z[i]);
	
}

void Cmodel2Dlg::find_r()
{
	//double phi_min = 0;
	double delta = 0.01;
	r_ot_z.clear();
	double epsilon = E;
	double r =1;
	for (double zed = -R; zed < R-2*delta; zed += delta)
	{
		
		double k1 = q(zed, r) * delta;
		double k2 = q(zed + delta / 2, r + k1 / 2) * delta;
		double k3 = q(zed + delta / 2, r + k2 / 2) * delta;
		double k4 = q(zed + delta, r + k3) * delta;
		r = r + (1. / 6.) * (k1 + 2 * k2 + 2 * k3 + k4);
		//if (phi < phi_min) phi_min = phi;
		r_ot_z.push_back(r);
	}
}




void Cmodel2Dlg::find_psi()
{
	//double phi_min = 0;
	double delta = 0.01;
	psi.clear();
	double max = 0, min = 10000;
	double t;
	int i;
	for (double zed = -R; zed < R-2*delta; zed += delta)
	{
		i = (zed + R) * 100;
		t = r_ot_z[i] * cos(ph_k_ot_z[i]);
		psi.push_back(t);
		if (t > max) max = t;
		if (t < min) min = t;
	}
	drv3.Draw(max,min,R, -R, delta,R*100, psi);

}



void Cmodel2Dlg::OnBnClickedButton1()
{
	// TODO: добавьте свой код обработчика уведомлений
	UpdateData(true);
	barriers();
	phazy();
	find_energy();
	phazy_2();
	find_r();
	find_psi();
	UpdateData(false);
}
