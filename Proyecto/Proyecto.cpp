#include <Windows.h>
#include <mmsystem.h>
#include "CommCtrl.h"
#include <string>
#include <regex>
#include <cstdlib>
#include <iostream>
#include <time.h>
#include <cstring>
#include<cwchar> 
#include <cwctype>
#include <fstream>

using namespace std;

bool ValidarFoto = false;
wchar_t szFile2[260] = { 0 };
short x, y;
HWND combox, image, comboxCE, comboxCM, comboxCMI, calen, H1, H2, H3, H4, H5, H6, H7, H8, H9, H10, H11, H12, H13, H14, H15, H16, H17, H18, H19, H20, H21,
H22, H23, H24, H25;
HWND DW1, DW2, DW3, DW4, DW5, DW6;
static HBITMAP bmp1;
static HBITMAP bmp2;
int Quick[100];
int IDDC = 0;
string Nombres[20];
fstream servicios, listamecanico, listaclientes, listacitas, RegistroConsulta, RegistroMecanico, RegistroCliente;

struct citas {
    wchar_t Nombre[70];
    wchar_t Servicio[70];
    wchar_t Mecanico[70];
    wchar_t Hora[6];
    wchar_t Fecha[12];
    wchar_t Telefono[12];
    wchar_t status[12];
    wchar_t Motivo[70];
    wchar_t id[3];
    citas* prevct;
    citas* nextct;
};
citas* primeroct = NULL;
citas* ultimoct = NULL;
citas* auxct = NULL;
citas* aux2ct = NULL;

struct clientes {
    wchar_t nombre[70];
    wchar_t marca[30];
    wchar_t modelo[30];
    wchar_t placas[30];
    wchar_t kilometraje[30];
    wchar_t telefono[12];
    wchar_t direccion[50];
    clientes* nextc;
    clientes* prevc;
};
clientes* primeroc = NULL;
clientes* ultimoc = NULL;
clientes* auxc = NULL;


struct mecanico {
    wchar_t NombreM[80];
    wchar_t NomEmpleado[4];
    wchar_t telefonoM[12];
    wchar_t EspecialidadM[30];
    wchar_t Turno[10];
    wchar_t pic[MAX_PATH];
    wchar_t Lunes[10];
    wchar_t Martes[10];
    wchar_t Miercoles[10];
    wchar_t Jueves[10];
    wchar_t Viernes[10];
    mecanico* nextM;
    mecanico* prevM;
};
mecanico* primeroM = NULL;
mecanico* ultimoM = NULL;
mecanico* auxM = NULL;


struct servicio {
    wchar_t nombreS[70];
    wchar_t clave[10];
    wchar_t costo[20];
    wchar_t descripcion[MAX_PATH];
    servicio* nexts;
    servicio* prevs;
};
servicio* primeros = NULL;
servicio* ultimos = NULL;
servicio* auxs = NULL;

LRESULT CALLBACK windowprocessforwindow1(HWND handleforwindow1, UINT message, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK windowprocessforwindow2(HWND handleforwindow1, UINT message, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK windowprocessforwindow3(HWND handleforwindow1, UINT message, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK windowprocessforwindow4(HWND handleforwindow1, UINT message, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK windowprocessforwindow5(HWND handleforwindow1, UINT message, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK windowprocessforwindow6(HWND handleforwindow1, UINT message, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK windowprocessforwindow7(HWND handleforwindow1, UINT message, WPARAM wParam, LPARAM lParam);
#define createwindowbuttoninwindow1 101
#define createwindowbuttoninwindow2 201
#define createwindowbuttoninwindow3 301
#define createwindowbuttoninwindow4 401
#define createwindowbuttoninwindow5 501
#define createwindowbuttoninwindow6 601
#define createwindowbuttoninwindow7 701
#define ANCHO 600
#define ALTO 700
#define STT_NOMBRE 310

bool window1open, window2open, window3open, window4open, window5open, window6open, window7open = false;
bool windowclass1registeredbefore, windowclass2registeredbefore,
windowclass3registeredbefore, windowclass4registeredbefore, windowclass5registeredbefore, windowclass6registeredbefore, windowclass7registeredbefore = false;

enum windowtoopenenumt { none, window2, window3, window4, window5, window6, window7 };

windowtoopenenumt windowtoopenenum = none;

void createwindow2(WNDCLASSEX& wc, HWND& hwnd, HINSTANCE hInst, int nShowCmd);
void createwindow3(WNDCLASSEX& wc, HWND& hwnd, HINSTANCE hInst, int nShowCmd);
void createwindow4(WNDCLASSEX& wc, HWND& hwnd, HINSTANCE hInst, int nShowCmd);
void createwindow5(WNDCLASSEX& wc, HWND& hwnd, HINSTANCE hInst, int nShowCmd);
void createwindow6(WNDCLASSEX& wc, HWND& hwnd, HINSTANCE hInst, int nShowCmd);
void createwindow7(WNDCLASSEX& wc, HWND& hwnd, HINSTANCE hInst, int nShowCmd);

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nShowCmd)
{
    bool endprogram = false;
    WNDCLASSEX windowclassforwindow2;
    WNDCLASSEX windowclassforwindow3;
    WNDCLASSEX windowclassforwindow4;
    WNDCLASSEX windowclassforwindow5;
    WNDCLASSEX windowclassforwindow6;
    WNDCLASSEX windowclassforwindow7;
    HWND handleforwindow2;
    HWND handleforwindow3;
    HWND handleforwindow4;
    HWND handleforwindow5;
    HWND handleforwindow6;
    HWND handleforwindow7;
    //create window 1
    MSG msg;
    WNDCLASSEX windowclassforwindow1;
    ZeroMemory(&windowclassforwindow1, sizeof(WNDCLASSEX));
    windowclassforwindow1.cbClsExtra = NULL;
    windowclassforwindow1.cbSize = sizeof(WNDCLASSEX);
    windowclassforwindow1.cbWndExtra = NULL;
    windowclassforwindow1.hbrBackground = (HBRUSH)0;
    windowclassforwindow1.hCursor = LoadCursor(NULL, IDC_ARROW);
    windowclassforwindow1.hIcon = NULL;
    windowclassforwindow1.hIconSm = NULL;
    windowclassforwindow1.hInstance = hInst;
    windowclassforwindow1.lpfnWndProc = (WNDPROC)windowprocessforwindow1;
    windowclassforwindow1.lpszClassName = L"window class 1";
    windowclassforwindow1.lpszMenuName = NULL;
    windowclassforwindow1.style = CS_HREDRAW | CS_VREDRAW;

    if (!RegisterClassEx(&windowclassforwindow1))
    {
        int nResult = GetLastError();
        MessageBox(NULL,
            L"Window class creation failed",
            L"Window Class Failed",
            MB_ICONERROR);
    }

    HWND handleforwindow1 = CreateWindowEx(NULL,
        windowclassforwindow1.lpszClassName,
        L"Agencia de autos Hernandez",
        WS_OVERLAPPEDWINDOW,
        0,
        0,
        500,
        600,
        NULL,
        NULL,
        hInst,
        NULL                /* No Window Creation data */
    );

    if (!handleforwindow1)
    {
        int nResult = GetLastError();

        MessageBox(NULL,
            L"Window creation failed",
            L"Window Creation Failed",
            MB_ICONERROR);
    }

    ShowWindow(handleforwindow1, nShowCmd);
    bool endloop = false;
    while (endloop == false) {
        if (GetMessage(&msg, NULL, 0, 0))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        if (windowtoopenenum != none) {
            switch (windowtoopenenum) {
            case window2:
                if (window2open == false) {
                    createwindow2(windowclassforwindow2, handleforwindow2, hInst, nShowCmd);
                }
                break;
            case window3:
                if (window3open == false) {
                    createwindow3(windowclassforwindow3, handleforwindow3, hInst, nShowCmd);
                }
                break;
            case window4:
                if (window4open == false) {
                    createwindow4(windowclassforwindow4, handleforwindow4, hInst, nShowCmd);
                }
                break;
            case window5:
                if (window5open == false) {
                    createwindow5(windowclassforwindow5, handleforwindow5, hInst, nShowCmd);
                }
                break;
            case window6:
                if (window6open == false) {
                    createwindow6(windowclassforwindow6, handleforwindow6, hInst, nShowCmd);
                }
                break;
            case window7:
                if (window7open == false) {
                    createwindow7(windowclassforwindow7, handleforwindow7, hInst, nShowCmd);
                }
                break;
            }
            windowtoopenenum = none;
        }
        if (window1open == false && window2open == false && window3open == false && window4open == false && window5open == false && window6open == false && window7open == false)
            endloop = true;

    }

}

void createwindow2(WNDCLASSEX& wc, HWND& hwnd, HINSTANCE hInst, int nShowCmd) {
    if (windowclass2registeredbefore == false) {
        ZeroMemory(&wc, sizeof(WNDCLASSEX));
        wc.cbClsExtra = NULL;
        wc.cbSize = sizeof(WNDCLASSEX);
        wc.cbWndExtra = NULL;
        wc.hbrBackground = (HBRUSH)5;
        wc.hCursor = LoadCursor(NULL, IDC_ARROW);
        wc.hIcon = NULL;
        wc.hIconSm = NULL;
        wc.hInstance = hInst;
        wc.lpfnWndProc = (WNDPROC)windowprocessforwindow2;
        wc.lpszClassName = L"wc2";
        wc.lpszMenuName = NULL;
        wc.style = CS_HREDRAW | CS_VREDRAW;

        if (!RegisterClassEx(&wc))
        {
            int nResult = GetLastError();
            MessageBox(NULL,
                L"Window class creation failed",
                L"Window Class Failed",
                MB_ICONERROR);
        }
        else
            windowclass2registeredbefore = true;
    }
    hwnd = CreateWindowEx(NULL,
        wc.lpszClassName,
        L"Registro de paquetes de servicio",
        WS_OVERLAPPEDWINDOW,
        50,
        50,
        500,
        400,
        NULL,
        NULL,
        hInst,
        NULL                /* No Window Creation data */
    );

    if (!hwnd)
    {
        int nResult = GetLastError();

        MessageBox(NULL,
            L"Window creation failed",
            L"Window Creation Failed",
            MB_ICONERROR);
    }

    ShowWindow(hwnd, nShowCmd);
}
void createwindow3(WNDCLASSEX& wc, HWND& hwnd, HINSTANCE hInst, int nShowCmd) {
    if (windowclass3registeredbefore == false) {
        ZeroMemory(&wc, sizeof(WNDCLASSEX));
        wc.cbClsExtra = NULL;
        wc.cbSize = sizeof(WNDCLASSEX);
        wc.cbWndExtra = NULL;
        wc.hbrBackground = (HBRUSH)5;
        wc.hCursor = LoadCursor(NULL, IDC_ARROW);
        wc.hIcon = NULL;
        wc.hIconSm = NULL;
        wc.hInstance = hInst;
        wc.lpfnWndProc = (WNDPROC)windowprocessforwindow3;
        wc.lpszClassName = L"NUEVA CITA";
        wc.lpszMenuName = NULL;
        wc.style = CS_HREDRAW | CS_VREDRAW;

        if (!RegisterClassEx(&wc))
        {
            int nResult = GetLastError();
            MessageBox(NULL,
                L"Window class creation failed",
                L"Window Class Failed",
                MB_ICONERROR);
        }
        else
            windowclass3registeredbefore = true;
    }
    hwnd = CreateWindowEx(NULL,
        wc.lpszClassName,
        L"Registro de Mecanico",
        WS_OVERLAPPEDWINDOW,
        100,
        50,
        900,
        400,
        NULL,
        NULL,
        hInst,
        NULL
    );

    if (!hwnd)
    {
        int nResult = GetLastError();

        MessageBox(NULL,
            L"Window creation failed",
            L"Window Creation Failed",
            MB_ICONERROR);
    }

    ShowWindow(hwnd, nShowCmd);
}
void createwindow4(WNDCLASSEX& wc, HWND& hwnd, HINSTANCE hInst, int nShowCmd) {
    if (windowclass4registeredbefore == false) {
        ZeroMemory(&wc, sizeof(WNDCLASSEX));
        wc.cbClsExtra = NULL;
        wc.cbSize = sizeof(WNDCLASSEX);
        wc.cbWndExtra = NULL;
        wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
        wc.hCursor = LoadCursor(NULL, IDC_ARROW);
        wc.hIcon = NULL;
        wc.hIconSm = NULL;
        wc.hInstance = hInst;
        wc.lpfnWndProc = (WNDPROC)windowprocessforwindow4;
        wc.lpszClassName = L"window class 4";
        wc.lpszMenuName = NULL;
        wc.style = CS_HREDRAW | CS_VREDRAW;

        if (!RegisterClassEx(&wc))
        {
            int nResult = GetLastError();
            MessageBox(NULL,
                L"Window class creation failed",
                L"Window Class Failed",
                MB_ICONERROR);
        }
        else
            windowclass4registeredbefore = true;
    }
    hwnd = CreateWindowEx(NULL,
        wc.lpszClassName,
        L"Registro de citas",
        WS_OVERLAPPEDWINDOW |
        WS_VISIBLE,
        200,
        210,
        550,
        480,
        NULL,
        NULL,
        hInst,
        (PVOID)NULL                /* No Window Creation data */
    );

    if (!hwnd)
    {
        int nResult = GetLastError();

        MessageBox(NULL,
            L"Window creation failed",
            L"Window Creation Failed",
            MB_ICONERROR);
    }

    ShowWindow(hwnd, nShowCmd);
}
void createwindow5(WNDCLASSEX& wc, HWND& hwnd, HINSTANCE hInst, int nShowCmd) {
    if (windowclass5registeredbefore == false) {
        ZeroMemory(&wc, sizeof(WNDCLASSEX));
        wc.cbClsExtra = NULL;
        wc.cbSize = sizeof(WNDCLASSEX);
        wc.cbWndExtra = NULL;
        wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
        wc.hCursor = LoadCursor(NULL, IDC_ARROW);
        wc.hIcon = NULL;
        wc.hIconSm = NULL;
        wc.hInstance = hInst;
        wc.lpfnWndProc = (WNDPROC)windowprocessforwindow5;
        wc.lpszClassName = L"window class 5";
        wc.lpszMenuName = NULL;
        wc.style = CS_HREDRAW | CS_VREDRAW;

        if (!RegisterClassEx(&wc))
        {
            int nResult = GetLastError();
            MessageBox(NULL,
                L"Window class creation failed",
                L"Window Class Failed",
                MB_ICONERROR);
        }
        else
            windowclass5registeredbefore = true;
    }
    hwnd = CreateWindowEx(NULL,
        wc.lpszClassName,
        L"Registro de pacientes",
        WS_OVERLAPPEDWINDOW |
        WS_VISIBLE,
        0,
        0,
        540,
        600,
        NULL,
        NULL,
        hInst,
        (PVOID)NULL                /* No Window Creation data */
    );

    if (!hwnd)
    {
        int nResult = GetLastError();

        MessageBox(NULL,
            L"Window creation failed",
            L"Window Creation Failed",
            MB_ICONERROR);
    }

    ShowWindow(hwnd, nShowCmd);
}
void createwindow6(WNDCLASSEX& wc, HWND& hwnd, HINSTANCE hInst, int nShowCmd) {
    if (windowclass6registeredbefore == false) {
        ZeroMemory(&wc, sizeof(WNDCLASSEX));
        wc.cbClsExtra = NULL;
        wc.cbSize = sizeof(WNDCLASSEX);
        wc.cbWndExtra = NULL;
        wc.hbrBackground = (HBRUSH)5;
        wc.hCursor = LoadCursor(NULL, IDC_ARROW);
        wc.hIcon = NULL;
        wc.hIconSm = NULL;
        wc.hInstance = hInst;
        wc.lpfnWndProc = (WNDPROC)windowprocessforwindow6;
        wc.lpszClassName = L"window class 6";
        wc.lpszMenuName = NULL;
        wc.style = CS_HREDRAW | CS_VREDRAW;

        if (!RegisterClassEx(&wc))
        {
            int nResult = GetLastError();
            MessageBox(NULL,
                L"Window class creation failed",
                L"Window Class Failed",
                MB_ICONERROR);
        }
        else
            windowclass6registeredbefore = true;
    }
    hwnd = CreateWindowEx(NULL,
        wc.lpszClassName,
        L"Consulta",
        WS_OVERLAPPEDWINDOW |
        WS_VISIBLE,
        200,
        25,
        600,
        520,
        NULL,
        NULL,
        hInst,
        (PVOID)NULL                /* No Window Creation data */
    );

    if (!hwnd)
    {
        int nResult = GetLastError();

        MessageBox(NULL,
            L"Window creation failed",
            L"Window Creation Failed",
            MB_ICONERROR);
    }

    ShowWindow(hwnd, nShowCmd);
}
void createwindow7(WNDCLASSEX& wc, HWND& hwnd, HINSTANCE hInst, int nShowCmd) {
    if (windowclass7registeredbefore == false) {
        ZeroMemory(&wc, sizeof(WNDCLASSEX));
        wc.cbClsExtra = NULL;
        wc.cbSize = sizeof(WNDCLASSEX);
        wc.cbWndExtra = NULL;
        wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
        wc.hCursor = LoadCursor(NULL, IDC_ARROW);
        wc.hIcon = NULL;
        wc.hIconSm = NULL;
        wc.hInstance = hInst;
        wc.lpfnWndProc = (WNDPROC)windowprocessforwindow7;
        wc.lpszClassName = L"window class 7";
        wc.lpszMenuName = NULL;
        wc.style = CS_HREDRAW | CS_VREDRAW;

        if (!RegisterClassEx(&wc))
        {
            int nResult = GetLastError();
            MessageBox(NULL,
                L"Window class creation failed",
                L"Window Class Failed",
                MB_ICONERROR);
        }
        else
            windowclass7registeredbefore = true;
    }
    hwnd = CreateWindowEx(NULL,
        wc.lpszClassName,
        L"ELIMINAR",
        WS_OVERLAPPEDWINDOW |
        WS_VISIBLE,
        100,
        200,
        640,
        550,
        NULL,
        NULL,
        hInst,
        (PVOID)NULL                /* No Window Creation data */
    );

    if (!hwnd)
    {
        int nResult = GetLastError();

        MessageBox(NULL,
            L"Window creation failed",
            L"Window Creation Failed",
            MB_ICONERROR);
    }

    ShowWindow(hwnd, nShowCmd);
}
bool valNombre(string nom);
bool ValidarNumeroTelefono(string nom);
bool ValidarNumerodeempleado(string numero);
bool ValidarLleno(string dato);
bool validarprecio(string precio);
bool valCodigo(string Valcod);
void guardarServicios(HWND Ghwnd);
void guardarMecanicos(HWND Ghwnd);
void guardarClientes(HWND Ghwnd);
void guardarCitas(HWND Ghwnd);
void cargarServicios(HWND Chwnd);
void cargarClientes(HWND Chwnd);
void cargarCitas(HWND Chwnd);
void cargarMecanicos(HWND Chwnd);
void Quicksort(int* arr, int izq, int der);
void EscribirRegistroMecanico();
void heapSort(string* array, int size);
void heapify(string* array, int iterationSize);
void EscribirRegistroCliente(int contador);
void recuperarID();
bool validarprecio2(string str);
bool validarplascas(string placas);

LRESULT CALLBACK windowprocessforwindow1(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {

    switch (message) {
    case WM_CREATE: {
        recuperarID();
        cargarServicios(hwnd);
        cargarClientes(hwnd);
        cargarMecanicos(hwnd);
        cargarCitas(hwnd);
        window1open = true;
        x = (ANCHO / 2) - 150;
        CreateWindowEx(NULL, L"BUTTON", L"NUEVO SERVICIO", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 120, 50, 200, 40,
            hwnd, (HMENU)createwindowbuttoninwindow2, GetModuleHandle(NULL), NULL);
        CreateWindowEx(NULL, L"BUTTON", L"REGISTRO DE MECANICOS", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 120, 120, 200, 40,
            hwnd, (HMENU)createwindowbuttoninwindow3, GetModuleHandle(NULL), NULL);
        CreateWindowEx(NULL, L"BUTTON", L"REGISTRO DE CITAS", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 120, 190, 200, 40,
            hwnd, (HMENU)createwindowbuttoninwindow4, GetModuleHandle(NULL), NULL);
        CreateWindowEx(NULL, L"BUTTON", L"REGISTRO DE CLIENTES", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 120, 260, 200, 40,
            hwnd, (HMENU)createwindowbuttoninwindow5, GetModuleHandle(NULL), NULL);
        CreateWindowEx(NULL, L"BUTTON", L"CONSULTA DE CITAS", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 120, 330, 200, 40,
            hwnd, (HMENU)createwindowbuttoninwindow6, GetModuleHandle(NULL), NULL);
        CreateWindowEx(NULL, L"BUTTON", L"SALIR", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 120, 400, 200, 40,
            hwnd, (HMENU)createwindowbuttoninwindow7, GetModuleHandle(NULL), NULL);
        break;
    }
    case WM_COMMAND: {
        switch LOWORD(wParam) {
        case 110:
            EscribirRegistroMecanico();
            system("C://Users//carlo//source//repos//Proyecto//Proyecto//Registros//registroMecanico.txt");
            break;
        case 111: {
            int cont = 1;
            for (int x = 0; x < 20; x++) {
                Nombres[x] = " ";
            }
            Nombres[0] = "";
            auxc = primeroc;
            do {
                wchar_t Nom[70];
                wcscpy_s(Nom, auxc->nombre);
                wstring ws(Nom);
                string str(ws.begin(), ws.end());
                Nombres[cont] = str;
                cont++;
                auxc = auxc->nextc;
            } while (auxc != primeroc);
            heapSort(Nombres, cont);
            EscribirRegistroCliente(cont);
            system("C://Users//carlo//source//repos//Proyecto//Proyecto//Registros//registroCliente.txt");
            
        }
            break;
        case createwindowbuttoninwindow2:
            windowtoopenenum = window2;
            break;
        case createwindowbuttoninwindow3:
            windowtoopenenum = window3;
            break;
        case createwindowbuttoninwindow4:
            windowtoopenenum = window4;
            break;
        case createwindowbuttoninwindow5:
            windowtoopenenum = window5;
            break;
        case createwindowbuttoninwindow6:
            windowtoopenenum = window6;
            break;
        case createwindowbuttoninwindow7:
            guardarServicios(hwnd);
            guardarMecanicos(hwnd);
            guardarClientes(hwnd);
            guardarCitas(hwnd);
            window1open = false;
            window2open = false;
            window3open = false;
            window4open = false;
            window5open = false;
            window6open = false;
            window7open = false;

            break;
        }
        break;
    }
    case WM_DESTROY: {

        window1open = false;
        window2open = false;
        window3open = false;
        window4open = false;
        window5open = false;
        window6open = false;
        window7open = false;

        break;
    }
    }
    return DefWindowProc(hwnd, message, wParam, lParam);
}

//=============================================== PANTALLA DE REGISTRO DE SERVICIO ==================================================

LRESULT CALLBACK windowprocessforwindow2(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
    case WM_CREATE: {
        window2open = true;
        CreateWindow(WC_STATIC, L"INGRESE LOS DATOS CORRESPONDIENTES", WS_CHILD | WS_VISIBLE | WS_BORDER, 20, 20, 300, 20, hwnd, (HMENU)NULL,
            GetModuleHandle(NULL), NULL);
        CreateWindow(WC_STATIC, L"Nombre del paquete: ", WS_CHILD | WS_VISIBLE, 20, 80, 180, 20, hwnd, (HMENU)NULL,
            GetModuleHandle(NULL), NULL);
        CreateWindow(WC_EDIT, L"", WS_CHILD | WS_VISIBLE | WS_BORDER, 200, 80, 260, 20, hwnd, (HMENU)202,
            GetModuleHandle(NULL), NULL);
        CreateWindow(WC_STATIC, L"Clave: ", WS_CHILD | WS_VISIBLE, 20, 130, 180, 20, hwnd, (HMENU)NULL,
            GetModuleHandle(NULL), NULL);
        CreateWindow(WC_EDIT, L"", WS_CHILD | WS_VISIBLE | WS_BORDER, 200, 130, 70, 20, hwnd, (HMENU)203,
            GetModuleHandle(NULL), NULL);
        CreateWindow(WC_STATIC, L"Costo: ", WS_CHILD | WS_VISIBLE, 20, 105, 180, 20, hwnd, (HMENU)NULL,
            GetModuleHandle(NULL), NULL);
        CreateWindow(WC_EDIT, L"", WS_CHILD | WS_VISIBLE | WS_BORDER, 200, 105, 70, 20, hwnd, (HMENU)204,
            GetModuleHandle(NULL), NULL);
        CreateWindow(WC_STATIC, L"Descripción: ", WS_CHILD | WS_VISIBLE, 20, 160, 330, 20, hwnd, (HMENU)NULL,
            GetModuleHandle(NULL), NULL);
        CreateWindow(WC_EDIT, L"", WS_CHILD | WS_VISIBLE | WS_BORDER, 20, 180, 440, 80, hwnd, (HMENU)205,
            GetModuleHandle(NULL), NULL);
        CreateWindowEx(NULL, L"BUTTON", L"GUARDAR", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
            180, 280, 100, 50, hwnd, (HMENU)206, GetModuleHandle(NULL), NULL);
        break;
    }
    case WM_COMMAND: {
        switch LOWORD(wParam) {
        case 206: {
            //validar nombre de la especialidad
            wchar_t nombreV[70] = { 0 };
            GetDlgItemText(hwnd, 202, nombreV, 70);
            wstring ws(nombreV);
            string str(ws.begin(), ws.end());
            //validar clave
            wchar_t claveE[10];
            GetDlgItemText(hwnd, 203, claveE, 10);
            wstring ws2(claveE);
            string str2(ws2.begin(), ws2.end());
            //validar costo
            wchar_t costo[20];
            GetDlgItemText(hwnd, 204, costo, 20);
            wstring ws3(costo);
            string  str3(ws3.begin(), ws3.end());
            //descripcion
            wchar_t Descrp[MAX_PATH];
            GetDlgItemText(hwnd, 205, Descrp, MAX_PATH);
            wstring ws4(Descrp);
            string str4(ws4.begin(), ws4.end());
            if (valNombre(str) && valCodigo(str2) && validarprecio(str3) && ValidarLleno(str4)&&validarprecio2(str3)) {
                servicio* nuevoservicio = new servicio;
                wcscpy_s(nuevoservicio->nombreS, nombreV);
                wcscpy_s(nuevoservicio->clave, claveE);
                wcscpy_s(nuevoservicio->costo, costo);
                wcscpy_s(nuevoservicio->descripcion, Descrp);
                if (primeros == NULL) {
                    primeros = nuevoservicio;
                    primeros->nexts = primeros;
                    primeros->prevs = primeros;
                    ultimos = primeros;
                }
                else {
                    ultimos->nexts = nuevoservicio;
                    nuevoservicio->nexts = primeros;
                    nuevoservicio->prevs = ultimos;
                    ultimos = nuevoservicio;
                    primeros->prevs = ultimos;
                }
                MessageBox(NULL, L"Todos los datos han sido guardados correctamente", L"Especialidad dada de alta", MB_OK);
                DestroyWindow(hwnd);
            }
            else {
                MessageBox(NULL, L"Revise bien los datos", L"ERROR", MB_ICONEXCLAMATION);

            }

        }
                break;
        default:
            break;
        }
        break;
    }
    case WM_DESTROY: {
        window2open = false;
        break;
    }
    }
    return DefWindowProc(hwnd, message, wParam, lParam);
}

//=============================================== PANTALLA DE REGISTRO DE MECANICOS ==================================================
wchar_t Turno[2][10] = { L"DIA", L"TARDE" };
wchar_t dia[2][3] = { L"SI",L"NO" };

LRESULT CALLBACK windowprocessforwindow3(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {

    switch (message) {

    case WM_CREATE:
        CreateWindowEx(NULL, L"BUTTON", L"Ver", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 10, 20, 50, 25,
            hwnd, (HMENU)110, GetModuleHandle(NULL), NULL);
        window3open = true;
        CreateWindow(WC_STATIC, L"LLENE LOS DATOS CORRESPONDIENTES", WS_CHILD | WS_VISIBLE, 150, 10, 280, 20, hwnd, (HMENU)NULL,
            GetModuleHandle(NULL), NULL);
        CreateWindow(WC_STATIC, L"Nombre del completo: ", WS_CHILD | WS_VISIBLE, 20, 60, 150, 20, hwnd, (HMENU)NULL,
            GetModuleHandle(NULL), NULL);
        CreateWindow(WC_EDIT, L"", WS_CHILD | WS_VISIBLE | WS_BORDER, 175, 60, 365, 20, hwnd, (HMENU)302,
            GetModuleHandle(NULL), NULL);
        CreateWindow(WC_STATIC, L"No.Empleado: ", WS_CHILD | WS_VISIBLE, 20, 100, 100, 20, hwnd, (HMENU)NULL,
            GetModuleHandle(NULL), NULL);
        CreateWindow(WC_EDIT, L"", WS_CHILD | WS_VISIBLE | WS_BORDER, 120, 100, 40, 20, hwnd, (HMENU)303,
            GetModuleHandle(NULL), NULL);
        CreateWindow(WC_STATIC, L"Tel: ", WS_CHILD | WS_VISIBLE, 180, 100, 60, 20, hwnd, (HMENU)NULL,
            GetModuleHandle(NULL), NULL);
        CreateWindow(WC_EDIT, L"", WS_CHILD | WS_VISIBLE | WS_BORDER, 210, 100, 90, 20, hwnd, (HMENU)304,
            GetModuleHandle(NULL), NULL);
        CreateWindow(WC_STATIC, L"Especialidad: ", WS_CHILD | WS_VISIBLE, 20, 140, 90, 20, hwnd, (HMENU)NULL,
            GetModuleHandle(NULL), NULL);
        auxs = primeros;
        if (auxs != NULL) {
            combox = CreateWindow(WC_COMBOBOX, NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | CBS_DROPDOWNLIST | CBS_HASSTRINGS | EN_VSCROLL | CBS_DROPDOWNLIST,
                110, 140, 150, 160, hwnd, (HMENU)305, GetModuleHandle(NULL), NULL);
            do {
                SendMessage(combox, CB_ADDSTRING, 0, (LPARAM)auxs->nombreS);
                auxs = auxs->nexts;
            } while (auxs != primeros);
        }
        CreateWindow(WC_STATIC, L"Turno: ", WS_CHILD | WS_VISIBLE, 20, 180, 60, 20, hwnd, (HMENU)NULL,
            GetModuleHandle(NULL), NULL);
        combox = CreateWindow(WC_COMBOBOX, NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | CBS_DROPDOWNLIST | CBS_HASSTRINGS | EN_VSCROLL | CBS_DROPDOWNLIST,
            70, 180, 90, 270, hwnd, (HMENU)306, GetModuleHandle(NULL), NULL);
        for (int i = 0; i < 2; i++) {
            SendMessage(combox, CB_ADDSTRING, 0, (LPARAM)Turno[i]);
        }
        CreateWindow(WC_STATIC, L"Que dia Labora: ", WS_CHILD | WS_VISIBLE, 250, 220, 150, 20, hwnd, (HMENU)NULL,
            GetModuleHandle(NULL), NULL);
        CreateWindow(WC_STATIC, L"LUNES             MARTES             MIERCOLES             JUEVES             VERNES ", WS_CHILD | WS_VISIBLE, 20, 250, 540, 20, hwnd, (HMENU)NULL,
            GetModuleHandle(NULL), NULL);
        combox = CreateWindow(WC_COMBOBOX, NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | CBS_DROPDOWNLIST | CBS_HASSTRINGS | EN_VSCROLL | CBS_DROPDOWNLIST,
            20, 270, 60, 60, hwnd, (HMENU)307, GetModuleHandle(NULL), NULL);
        for (int i = 0; i < 2; i++) {
            SendMessage(combox, CB_ADDSTRING, 0, (LPARAM)dia[i]);
        }
        combox = CreateWindow(WC_COMBOBOX, NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | CBS_DROPDOWNLIST | CBS_HASSTRINGS | EN_VSCROLL | CBS_DROPDOWNLIST,
            120, 270, 60, 60, hwnd, (HMENU)308, GetModuleHandle(NULL), NULL);
        for (int i = 0; i < 2; i++) {
            SendMessage(combox, CB_ADDSTRING, 0, (LPARAM)dia[i]);
        }
        combox = CreateWindow(WC_COMBOBOX, NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | CBS_DROPDOWNLIST | CBS_HASSTRINGS | EN_VSCROLL | CBS_DROPDOWNLIST,
            240, 270, 60, 60, hwnd, (HMENU)309, GetModuleHandle(NULL), NULL);
        for (int i = 0; i < 2; i++) {
            SendMessage(combox, CB_ADDSTRING, 0, (LPARAM)dia[i]);
        }
        combox = CreateWindow(WC_COMBOBOX, NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | CBS_DROPDOWNLIST | CBS_HASSTRINGS | EN_VSCROLL | CBS_DROPDOWNLIST,
            360, 270, 60, 60, hwnd, (HMENU)310, GetModuleHandle(NULL), NULL);
        for (int i = 0; i < 2; i++) {
            SendMessage(combox, CB_ADDSTRING, 0, (LPARAM)dia[i]);
        }
        combox = CreateWindow(WC_COMBOBOX, NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | CBS_DROPDOWNLIST | CBS_HASSTRINGS | EN_VSCROLL | CBS_DROPDOWNLIST,
            460, 270, 60, 60, hwnd, (HMENU)311, GetModuleHandle(NULL), NULL);
        for (int i = 0; i < 2; i++) {
            SendMessage(combox, CB_ADDSTRING, 0, (LPARAM)dia[i]);
        }
        CreateWindowEx(NULL, L"BUTTON", L"Subir Foto", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 630, 310, 80, 30,
            hwnd, (HMENU)312, GetModuleHandle(NULL), NULL);
        CreateWindowEx(NULL, L"BUTTON", L"Guardar", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 730, 310, 80, 30,
            hwnd, (HMENU)313, GetModuleHandle(NULL), NULL);
        break;
    case WM_COMMAND:
        switch LOWORD(wParam) {
        case 110:
            if (primeroM!=NULL) {
                EscribirRegistroMecanico();
                system("C://Users//carlo//source//repos//Proyecto//Proyecto//Registros//registroMecanico.txt");
            }
            break;
        case 312: {
            HWND image2 = NULL;
            OPENFILENAME ofn;
            wchar_t szFile[260] = { 0 };
            ZeroMemory(&ofn, sizeof(ofn));
            ofn.lStructSize = sizeof(ofn);
            ofn.hwndOwner = image2;
            ofn.lpstrFile = szFile;
            ofn.lpstrFile[0] = '\0';
            ofn.nMaxFile = sizeof(szFile);
            ofn.lpstrFilter = L"Imagenes bmp\0*.bmp\0";
            ofn.nFilterIndex = 1;
            ofn.lpstrFileTitle = NULL;
            ofn.nMaxFileTitle = 0;
            ofn.lpstrInitialDir = NULL;
            ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
            if (GetOpenFileName(&ofn) == TRUE) {
                SendMessage(image, WM_SETTEXT, 0, (LPARAM)ofn.lpstrFile);
                wcscpy_s(szFile2, ofn.lpstrFile);

                image = CreateWindow(WC_STATIC, L"", WS_VISIBLE | WS_CHILD | SS_BITMAP | SS_REALSIZECONTROL | WS_BORDER,
                    620, 60, 190, 220, hwnd, NULL, GetModuleHandle(NULL), NULL);
                bmp1 = (HBITMAP)SendMessage(image, STM_GETIMAGE, IMAGE_BITMAP, 0);
                bmp2 = (HBITMAP)LoadImage(NULL, szFile, IMAGE_BITMAP, 200, 210, LR_LOADFROMFILE);
                SendMessage(image, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bmp2);
                ValidarFoto = true;

            }
            else {
                MessageBox(hwnd, L"No eligío un archivo", L"Aviso", MB_ICONEXCLAMATION);
                SendMessage(hwnd, WM_SETTEXT, 0, (LPARAM)"");
                ValidarFoto = false;
            }


        }
                break;
        case 313: {
            //========================================== VALIDAR NOMBRE ====================================================
            wchar_t nombre[80] = { 0 };
            GetDlgItemText(hwnd, 302, nombre, 80);
            wstring ws(nombre);
            string str(ws.begin(), ws.end());

            //========================================== VALIDAR NO. DE EMPLEADO ===========================================
            wchar_t NumeroEmpleado[4];
            GetDlgItemText(hwnd, 303, NumeroEmpleado, 4);
            wstring ws2(NumeroEmpleado);
            string str2(ws2.begin(), ws2.end());

            //========================================== VALIDAR NUMERO DE TELEFONO ========================================
            wchar_t NumeroTel[12];
            GetDlgItemText(hwnd, 304, NumeroTel, 12);
            wstring ws3(NumeroTel);
            string str3(ws3.begin(), ws3.end());
            //========================================== Validar Especialidad ==============================================
            wchar_t Especialidad[30];
            GetDlgItemText(hwnd, 305, Especialidad, 30);
            wstring ws4(Especialidad);
            string str4(ws4.begin(), ws4.end());
            //========================================== Validar turno =====================================================
            wchar_t Turno[10];
            GetDlgItemText(hwnd, 306, Turno, 10);
            wstring ws5(Turno);
            string str5(ws5.begin(), ws5.end());
            //========================================== Dias ===============================================================
            wchar_t DiasV[5][3];
            GetDlgItemText(hwnd, 307, DiasV[0], 3);
            GetDlgItemText(hwnd, 308, DiasV[1], 3);
            GetDlgItemText(hwnd, 309, DiasV[2], 3);
            GetDlgItemText(hwnd, 310, DiasV[3], 3);
            GetDlgItemText(hwnd, 311, DiasV[4], 3);
            if (valNombre(str) && ValidarNumerodeempleado(str2) && ValidarNumeroTelefono(str3) && ValidarLleno(str4) && ValidarLleno(str5) && ValidarFoto) {
                mecanico* NuevoMecanico = new mecanico;
                wcscpy_s(NuevoMecanico->NombreM, nombre);
                wcscpy_s(NuevoMecanico->NomEmpleado, NumeroEmpleado);
                wcscpy_s(NuevoMecanico->telefonoM, NumeroTel);
                wcscpy_s(NuevoMecanico->EspecialidadM, Especialidad);
                wcscpy_s(NuevoMecanico->Turno, Turno);
                wcscpy_s(NuevoMecanico->pic, szFile2);
                wcscpy_s(NuevoMecanico->Lunes, DiasV[0]);
                wcscpy_s(NuevoMecanico->Martes, DiasV[1]);
                wcscpy_s(NuevoMecanico->Miercoles, DiasV[2]);
                wcscpy_s(NuevoMecanico->Jueves, DiasV[3]);
                wcscpy_s(NuevoMecanico->Viernes, DiasV[4]);
                if (primeroM == NULL) {
                    primeroM = NuevoMecanico;
                    primeroM->nextM = primeroM;
                    primeroM->prevM = primeroM;
                    ultimoM = primeroM;
                }
                else {
                    ultimoM->nextM = NuevoMecanico;
                    NuevoMecanico->nextM = primeroM;
                    NuevoMecanico->prevM = ultimoM;
                    ultimoM = NuevoMecanico;
                    primeroM->prevM = ultimoM;
                }
                MessageBox(NULL, L"Todos los datos han sido guardados correctamente", L"Especialidad dada de alta", MB_OK);
                DestroyWindow(hwnd);
            }
            else {
                MessageBox(NULL, L"Revise bien los datos", L"ERROR", MB_ICONEXCLAMATION);
            }
        }
                break;
        default:
            break;
        }
        break;
    case WM_DESTROY:
        window3open = false;
        break;
    }
    return DefWindowProc(hwnd, message, wParam, lParam);
}

//=============================================== INGRESO DE CITAS ===================================================================
wchar_t HorasD[2][6] = { L"8:00", L"12:00" };
wchar_t HorasT[2][6] = { L"12:00", L"4:00" };

LRESULT CALLBACK windowprocessforwindow4(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
    case WM_CREATE:
        window4open = true;
        CreateWindow(WC_STATIC, L"REGISTRO DE CITAS", WS_CHILD | WS_VISIBLE | WS_BORDER, 235, 10, 160, 20, hwnd, (HMENU)NULL,
            GetModuleHandle(NULL), NULL);
        CreateWindow(WC_STATIC, L"CLIENTE: ", WS_CHILD | WS_VISIBLE, 20, 60, 70, 20, hwnd, (HMENU)NULL,
            GetModuleHandle(NULL), NULL);
        auxc = primeroc;
        if (auxc != NULL) {
            combox = CreateWindow(WC_COMBOBOX, NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | CBS_DROPDOWNLIST | CBS_HASSTRINGS | EN_VSCROLL | CBS_DROPDOWNLIST,
                95, 60, 300, 160, hwnd, (HMENU)402, GetModuleHandle(NULL), NULL);
            do {
                SendMessage(combox, CB_ADDSTRING, 0, (LPARAM)auxc->nombre);
                auxc = auxc->nextc;
            } while (auxc != primeroc);
        }
        CreateWindow(WC_STATIC, L"ELEGIR SERVICIO: ", WS_CHILD | WS_VISIBLE, 20, 90, 170, 20, hwnd, (HMENU)NULL,
            GetModuleHandle(NULL), NULL);
        auxs = primeros;
        if (auxs != NULL) {
            comboxCE = CreateWindow(WC_COMBOBOX, NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | CBS_DROPDOWNLIST | CBS_HASSTRINGS | EN_VSCROLL | CBS_DROPDOWNLIST,
                150, 85, 300, 160, hwnd, (HMENU)403, GetModuleHandle(NULL), NULL);
            do {
                SendMessage(comboxCE, CB_ADDSTRING, 0, (LPARAM)auxs->nombreS);
                auxs = auxs->nexts;
            } while (auxs != primeros);

        }
        CreateWindowEx(NULL, L"BUTTON", L"BUSCAR", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 450, 85, 70, 20,
            hwnd, (HMENU)441, GetModuleHandle(NULL), NULL);


        break;
    case WM_COMMAND:
        switch LOWORD(wParam) {
        case 441:
            wchar_t buscaservicio[50];
            GetDlgItemText(hwnd, 403, buscaservicio, 50);
            DestroyWindow(comboxCM); DestroyWindow(comboxCMI);
            comboxCM = CreateWindow(WC_STATIC, L"ESPECIALISTAS: ", WS_CHILD | WS_VISIBLE, 20, 120, 120, 20, hwnd, (HMENU)NULL,
                GetModuleHandle(NULL), NULL);
            comboxCMI = CreateWindow(WC_COMBOBOX, NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | CBS_DROPDOWNLIST | CBS_HASSTRINGS | EN_VSCROLL | CBS_DROPDOWNLIST,
                150, 115, 220, 160, hwnd, (HMENU)405, GetModuleHandle(NULL), NULL);
            auxM = primeroM;
            do {
                if (wcscmp(buscaservicio, auxM->EspecialidadM) == 0) {
                    SendMessage(comboxCMI, CB_ADDSTRING, 0, (LPARAM)auxM->NombreM);
                }
                auxM = auxM->nextM;
            } while (auxM != primeroM);
            CreateWindowEx(NULL, L"BUTTON", L"BUSCAR", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 380, 115, 70, 20,
                hwnd, (HMENU)442, GetModuleHandle(NULL), NULL);

            break;
        case 442:
            wchar_t NombreMecanico[70];
            GetDlgItemText(hwnd, 405, NombreMecanico, 70);
            auxM = primeroM;
            DestroyWindow(H1); DestroyWindow(H2); DestroyWindow(H3); DestroyWindow(H4); DestroyWindow(H5); DestroyWindow(H6); DestroyWindow(H7); DestroyWindow(H8);
            DestroyWindow(H9); DestroyWindow(image); DestroyWindow(calen); DestroyWindow(H10); DestroyWindow(H11); DestroyWindow(H12); DestroyWindow(H13);
            do {
                if (wcscmp(NombreMecanico, auxM->NombreM) == 0) {
                    H1 = CreateWindow(WC_STATIC, L"Atiende los dias", WS_CHILD | WS_VISIBLE, 220, 150, 530, 20, hwnd, (HMENU)NULL,
                        GetModuleHandle(NULL), NULL);
                    H12 = CreateWindow(WC_STATIC, L"Lunes:            Martes:            Miercoles:            Jueves:           Viernes:       ", WS_CHILD | WS_VISIBLE, 20, 180, 530, 20, hwnd, (HMENU)NULL,
                        GetModuleHandle(NULL), NULL);
                    H2 = CreateWindow(WC_STATIC, auxM->Lunes, WS_CHILD | WS_VISIBLE, 70, 180, 15, 20, hwnd, (HMENU)NULL,
                        GetModuleHandle(NULL), NULL);
                    H3 = CreateWindow(WC_STATIC, auxM->Martes, WS_CHILD | WS_VISIBLE, 165, 180, 20, 20, hwnd, (HMENU)NULL,
                        GetModuleHandle(NULL), NULL);
                    H4 = CreateWindow(WC_STATIC, auxM->Miercoles, WS_CHILD | WS_VISIBLE, 280, 180, 15, 20, hwnd, (HMENU)NULL,
                        GetModuleHandle(NULL), NULL);
                    H5 = CreateWindow(WC_STATIC, auxM->Jueves, WS_CHILD | WS_VISIBLE, 380, 180, 15, 20, hwnd, (HMENU)NULL,
                        GetModuleHandle(NULL), NULL);
                    H6 = CreateWindow(WC_STATIC, auxM->Viernes, WS_CHILD | WS_VISIBLE, 475, 180, 15, 20, hwnd, (HMENU)NULL,
                        GetModuleHandle(NULL), NULL);
                    H7 = CreateWindow(WC_STATIC, L"TURNO: ", WS_CHILD | WS_VISIBLE, 180, 210, 70, 20, hwnd, (HMENU)NULL,
                        GetModuleHandle(NULL), NULL);
                    H8 = CreateWindow(WC_STATIC, auxM->Turno, WS_CHILD | WS_VISIBLE, 240, 210, 70, 20, hwnd, (HMENU)NULL,
                        GetModuleHandle(NULL), NULL);
                    H9 = CreateWindow(WC_STATIC, L"HORA DE LA CITA: ", WS_CHILD | WS_VISIBLE, 180, 240, 130, 20, hwnd, (HMENU)405,
                        GetModuleHandle(NULL), NULL);
                    if (wcscmp(auxM->Turno, L"DIA") == 0) {
                        H10 = CreateWindow(WC_COMBOBOX, NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | CBS_DROPDOWNLIST | CBS_HASSTRINGS | EN_VSCROLL | CBS_DROPDOWNLIST,
                            300, 235, 60, 60, hwnd, (HMENU)406, GetModuleHandle(NULL), NULL);
                        for (short x = 0; x < 3; x++) {
                            SendMessage(H10, CB_ADDSTRING, 0, (LPARAM)HorasD[x]);
                        }
                    }
                    if (wcscmp(auxM->Turno, L"TARDE") == 0) {
                        H10 = CreateWindow(WC_COMBOBOX, NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | CBS_DROPDOWNLIST | CBS_HASSTRINGS | EN_VSCROLL | CBS_DROPDOWNLIST,
                            300, 235, 60, 60, hwnd, (HMENU)406, GetModuleHandle(NULL), NULL);
                        for (short x = 0; x < 3; x++) {
                            SendMessage(H10, CB_ADDSTRING, 0, (LPARAM)HorasT[x]);
                        }
                    }
                    H13 = CreateWindow(WC_STATIC, L"Fecha de cita: ", WS_CHILD | WS_VISIBLE, 180, 270, 100, 20, hwnd, (HMENU)NULL,
                        GetModuleHandle(NULL), NULL);
                    calen = CreateWindowEx(NULL, DATETIMEPICK_CLASS, TEXT("DateTime"), WS_VISIBLE | WS_BORDER | WS_CHILD |
                        WS_CHILD, 280, 270, 90, 20, hwnd, (HMENU)407, GetModuleHandle(NULL), NULL);
                    image = CreateWindow(WC_STATIC, L"", WS_VISIBLE | WS_CHILD | SS_BITMAP | SS_REALSIZECONTROL | WS_BORDER,
                        20, 210, 150, 160, hwnd, NULL, GetModuleHandle(NULL), NULL);
                    bmp1 = (HBITMAP)SendMessage(image, STM_GETIMAGE, IMAGE_BITMAP, 0);
                    bmp2 = (HBITMAP)LoadImage(NULL, auxM->pic, IMAGE_BITMAP, 150, 160, LR_LOADFROMFILE);
                    SendMessage(image, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bmp2);
                    H11 = CreateWindowEx(NULL, L"BUTTON", L"GUARDAR", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 430, 390, 90, 40,
                        hwnd, (HMENU)443, GetModuleHandle(NULL), NULL);
                }
                auxM = auxM->nextM;
            } while (auxM != primeroM);
            break;
        case 443: {
            wchar_t Nombre[70];
            wchar_t Servicio[70];
            wchar_t Mecanico[70];
            wchar_t Hora[6];
            wchar_t Fecha[12];
            wchar_t Telefono[12];
            GetDlgItemText(hwnd, 402, Nombre, 70);
            GetDlgItemText(hwnd, 403, Servicio, 70);
            GetDlgItemText(hwnd, 405, Mecanico, 70);
            GetDlgItemText(hwnd, 406, Hora, 6);
            GetDlgItemText(hwnd, 407, Fecha, 12);
            auxc = primeroc;
            do {
                if (wcscmp(Nombre, auxc->nombre) == 0) {
                    wcscpy_s(Telefono, auxc->telefono);
                }
                auxc = auxc->nextc;
            } while (auxc != primeroc);
            wstring ws(Nombre);
            string str(ws.begin(), ws.end());
            wstring ws1(Servicio);
            string str1(ws1.begin(), ws1.end());
            wstring ws2(Mecanico);
            string str2(ws2.begin(), ws2.end());
            wstring ws3(Hora);
            string str3(ws3.begin(), ws3.end());
            wstring ws4(Fecha);
            string str4(ws4.begin(), ws4.end());
            if (ValidarLleno(str) && ValidarLleno(str1) && ValidarLleno(str2) && ValidarLleno(str3) && ValidarLleno(str4)) {
                citas* nuevacita = new citas;
                IDDC++;
                wstring cn = to_wstring(IDDC);
                const wchar_t* geneidci = cn.c_str();
                wcscpy_s(nuevacita->Nombre, Nombre);
                wcscpy_s(nuevacita->Servicio, Servicio);
                wcscpy_s(nuevacita->Mecanico, Mecanico);
                wcscpy_s(nuevacita->Hora, Hora);
                wcscpy_s(nuevacita->Fecha, Fecha);
                wcscpy_s(nuevacita->Telefono, Telefono);
                wcscpy_s(nuevacita->status, L"Activa");
                wcscpy_s(nuevacita->Motivo, L"Sin Motivo");
                wcscpy_s(nuevacita->id, geneidci);
                if (primeroct == NULL) {
                    primeroct = nuevacita;
                    primeroct->nextct = primeroct;
                    primeroct->prevct = primeroct;
                    ultimoct = primeroct;
                }
                else {
                    ultimoct->nextct = nuevacita;
                    nuevacita->nextct = primeroct;
                    nuevacita->prevct = ultimoct;
                    ultimoct = nuevacita;
                    primeroct->prevct = ultimoct;
                }
                MessageBox(NULL, L"Todos los datos han sido guardados correctamente", L"Evento dado de alta", MB_OK);
                DestroyWindow(hwnd);
            }
            else {
                MessageBox(hwnd, L"Verifique bien los datos", L"Aviso", MB_ICONEXCLAMATION);
            }
        }
                break;
        default:
            break;
        }
        break;
    case WM_DESTROY:
        window4open = false;
        break;
    }
    return DefWindowProc(hwnd, message, wParam, lParam);
}

//=============================================== REGISTRO DE CLIENTES ===============================================================

LRESULT CALLBACK windowprocessforwindow5(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
    case WM_CREATE: {
        window5open = true;
        CreateWindowEx(NULL, L"BUTTON", L"Ver", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 10, 20, 50, 25,
            hwnd, (HMENU)111, GetModuleHandle(NULL), NULL);
        CreateWindow(WC_STATIC, L"REGISTRO DE CLIENTES", WS_CHILD | WS_VISIBLE | WS_BORDER, 20, 10, 180, 20, hwnd, (HMENU)NULL,
            GetModuleHandle(NULL), NULL);
        CreateWindow(WC_STATIC, L"Nombre completo: ", WS_CHILD | WS_VISIBLE, 20, 60, 150, 20, hwnd, (HMENU)NULL,
            GetModuleHandle(NULL), NULL);
        CreateWindow(WC_EDIT, L"", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, 155, 60, 350, 20, hwnd, (HMENU)502,
            GetModuleHandle(NULL), NULL);
        CreateWindow(WC_STATIC, L"Marca: ", WS_CHILD | WS_VISIBLE, 315, 220, 90, 20, hwnd, (HMENU)NULL,
            GetModuleHandle(NULL), NULL);
        CreateWindow(WC_EDIT, L"", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, 370, 220, 110, 20, hwnd, (HMENU)503,
            GetModuleHandle(NULL), NULL);
        CreateWindow(WC_STATIC, L"Modelo: ", WS_CHILD | WS_VISIBLE, 20, 185, 90, 20, hwnd, (HMENU)NULL,
            GetModuleHandle(NULL), NULL);
        CreateWindow(WC_EDIT, L"", WS_CHILD | WS_VISIBLE | WS_BORDER, 155, 185, 110, 20, hwnd, (HMENU)504,
            GetModuleHandle(NULL), NULL);
        CreateWindow(WC_STATIC, L"Placas: ", WS_CHILD | WS_VISIBLE, 315, 185, 60, 20, hwnd, (HMENU)NULL,
            GetModuleHandle(NULL), NULL);
        CreateWindow(WC_EDIT, L"", WS_CHILD | WS_VISIBLE | WS_BORDER, 370, 185, 110, 20, hwnd, (HMENU)505,
            GetModuleHandle(NULL), NULL);
        CreateWindow(WC_STATIC, L"Kilometraje: ", WS_CHILD | WS_VISIBLE, 20, 220, 120, 20, hwnd, (HMENU)NULL,
            GetModuleHandle(NULL), NULL);
        CreateWindow(WC_EDIT, L"", WS_CHILD | WS_VISIBLE | WS_BORDER, 155, 220, 110, 20, hwnd, (HMENU)506,
            GetModuleHandle(NULL), NULL);
        CreateWindow(WC_STATIC, L"Teléfono: ", WS_CHILD | WS_VISIBLE, 20, 150, 120, 20, hwnd, (HMENU)NULL,
            GetModuleHandle(NULL), NULL);
        CreateWindow(WC_EDIT, L"", WS_CHILD | WS_VISIBLE | WS_BORDER, 155, 150, 110, 20, hwnd, (HMENU)507,
            GetModuleHandle(NULL), NULL);
        CreateWindow(WC_STATIC, L"Dirección: ", WS_CHILD | WS_VISIBLE, 20, 95, 90, 20, hwnd, (HMENU)NULL,
            GetModuleHandle(NULL), NULL);
        CreateWindow(WC_EDIT, L"", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, 155, 95, 350, 40, hwnd, (HMENU)508,
            GetModuleHandle(NULL), NULL);
        CreateWindowEx(NULL, L"BUTTON", L"Guardar", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 220, 340, 80, 40,
            hwnd, (HMENU)509, GetModuleHandle(NULL), NULL);
    }
                  break;
    case WM_COMMAND:
        switch LOWORD(wParam) {
        case 111: {
            if (primeroc!=NULL) {
                int cont = 1;
                for (int x = 0; x < 20; x++) {
                    Nombres[x] = " ";
                }
                Nombres[0] = "";
                auxc = primeroc;
                do {
                    wchar_t Nom[70];
                    wcscpy_s(Nom, auxc->nombre);
                    wstring ws(Nom);
                    string str(ws.begin(), ws.end());
                    Nombres[cont] = str;
                    cont++;
                    auxc = auxc->nextc;
                } while (auxc != primeroc);
                heapSort(Nombres, cont);
                EscribirRegistroCliente(cont);
                system("C://Users//carlo//source//repos//Proyecto//Proyecto//Registros//registroCliente.txt");
            }
        }
        case 509: {
            wchar_t nombre[70];
            wchar_t marca[30];
            wchar_t modelo[30];
            wchar_t placas[30];
            wchar_t kilometraje[30];
            wchar_t telefono[12];
            wchar_t direccion[90];
            GetDlgItemText(hwnd, 502, nombre, 70);
            GetDlgItemText(hwnd, 503, marca, 30);
            GetDlgItemText(hwnd, 504, modelo, 30);
            GetDlgItemText(hwnd, 505, placas, 30);
            GetDlgItemText(hwnd, 506, kilometraje, 30);
            GetDlgItemText(hwnd, 507, telefono, 12);
            GetDlgItemText(hwnd, 508, direccion, 90);
            wstring ws(nombre);
            string str(ws.begin(), ws.end());
            wstring ws1(marca);
            string str1(ws1.begin(), ws1.end());
            wstring ws2(modelo);
            string str2(ws2.begin(), ws2.end());
            wstring ws3(placas);
            string str3(ws3.begin(), ws3.end());
            wstring ws4(kilometraje);
            string str4(ws4.begin(), ws4.end());
            wstring ws5(telefono);
            string str5(ws5.begin(), ws5.end());
            wstring ws6(direccion);
            string str6(ws6.begin(), ws6.end());
            if (valNombre(str) && valNombre(str1) && ValidarLleno(str2) && ValidarLleno(str3) && validarprecio(str4) && ValidarNumeroTelefono(str5) && ValidarLleno(str6)&&validarplascas(str3)) {
                clientes* nuevocliente = new clientes;
                wcscpy_s(nuevocliente->nombre, nombre);
                wcscpy_s(nuevocliente->marca, marca);
                wcscpy_s(nuevocliente->modelo, modelo);
                wcscpy_s(nuevocliente->placas, placas);
                wcscpy_s(nuevocliente->kilometraje, kilometraje);
                wcscpy_s(nuevocliente->telefono, telefono);
                wcscpy_s(nuevocliente->direccion, direccion);

                if (primeroc == NULL) {
                    primeroc = nuevocliente;
                    primeroc->nextc = primeroc;
                    primeroc->prevc = primeroc;
                    ultimoc = primeroc;
                }
                else {
                    ultimoc->nextc = nuevocliente;
                    nuevocliente->nextc = primeroc;
                    nuevocliente->prevc = ultimoc;
                    ultimoc = nuevocliente;
                    primeroc->prevc = ultimoc;
                }
                MessageBox(NULL, L"Todos los datos han sido guardados correctamente", L"Especialidad dada de alta", MB_OK);
                DestroyWindow(hwnd);
            }
            else {
                MessageBox(NULL, L"Revise los datos", L"ERROR", MB_ICONERROR);

            }
        }

                break;
        default:
            break;
        }
        break;
    case WM_DESTROY:
        window5open = false;
        break;
    }
    return DefWindowProc(hwnd, message, wParam, lParam);

}

//=============================================== CONSULTA DE CITAS ==================================================================

wchar_t opcion[4][15] = {L"Mecanico",L"Semana",L"Especialidad",L"Editar" };
wchar_t mes[12][12] = { L"Enero",L"Febrero",L"Marzo",L"Abril",L"Mayo",L"Junio",L"Julio",L"Agosto",L"Septiembre",L"Octubre",L"Noviembre",L"Diciembre" };
wchar_t estado[2][12] = { L"Cancelada",L"Realizada" };

LRESULT CALLBACK windowprocessforwindow6(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
    case WM_CREATE: {
        window6open = true;
        CreateWindow(WC_STATIC, L"Cosultar citas", WS_CHILD | WS_VISIBLE, 240, 10, 100, 20, hwnd, (HMENU)NULL,
            GetModuleHandle(NULL), NULL);
        CreateWindow(WC_STATIC, L"Buscar por: ", WS_CHILD | WS_VISIBLE, 20, 40, 100, 20, hwnd, (HMENU)NULL,
            GetModuleHandle(NULL), NULL);
        combox = CreateWindow(WC_COMBOBOX, NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | CBS_DROPDOWNLIST | CBS_HASSTRINGS | EN_VSCROLL | CBS_DROPDOWNLIST,
            110, 40, 140, 100, hwnd, (HMENU)611, GetModuleHandle(NULL), NULL);
        for (int i = 0; i < 4; i++) {
            SendMessage(combox, CB_ADDSTRING, 0, (LPARAM)opcion[i]);
        }
        CreateWindowEx(NULL, L"BUTTON", L"Ok", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 260, 40, 35, 20,
            hwnd, (HMENU)612, GetModuleHandle(NULL), NULL);

        break;
    }
    case WM_COMMAND: {
        switch LOWORD(wParam) {
        case 612: {
            wchar_t getopcion[15];
            GetDlgItemText(hwnd, 611, getopcion, 15);
            DestroyWindow(H1); DestroyWindow(H2); DestroyWindow(H3); DestroyWindow(H4); DestroyWindow(H5); DestroyWindow(H6); DestroyWindow(H7); DestroyWindow(H8); DestroyWindow(H9); DestroyWindow(H10);
            DestroyWindow(H11); DestroyWindow(H12); DestroyWindow(H13); DestroyWindow(H14); DestroyWindow(H15); DestroyWindow(H16); DestroyWindow(H17); DestroyWindow(H18); DestroyWindow(H19); DestroyWindow(H20);
            DestroyWindow(H21); DestroyWindow(H22); DestroyWindow(H23); DestroyWindow(H24);
            if (wcscmp(getopcion, L"Mecanico") == 0) {
                H1 = CreateWindow(WC_STATIC, L"Num Mec: ", WS_CHILD | WS_VISIBLE, 20, 70, 85, 20, hwnd, (HMENU)NULL,
                    GetModuleHandle(NULL), NULL);
                H2 = CreateWindow(WC_COMBOBOX, NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | CBS_DROPDOWNLIST | CBS_HASSTRINGS | EN_VSCROLL | CBS_DROPDOWNLIST,
                    110, 70, 120, 160, hwnd, (HMENU)613, GetModuleHandle(NULL), NULL);
                auxM = primeroM;
                do {
                    SendMessage(H2, CB_ADDSTRING, 0, (LPARAM)auxM->NomEmpleado);
                    auxM = auxM->nextM;
                } while (auxM != primeroM);
                H3 = CreateWindowEx(NULL, L"BUTTON", L"Buscar", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 235, 70, 60, 20,
                    hwnd, (HMENU)614, GetModuleHandle(NULL), NULL);
                DestroyWindow(H4);
                DestroyWindow(H5);
                DestroyWindow(H6);
                DestroyWindow(H7);
                DestroyWindow(H8);
            }
            if (wcscmp(getopcion, L"Semana") == 0) {
                H1 = CreateWindow(WC_STATIC, L"Selecciona el lunes de la semana que se desea ver: ", WS_CHILD | WS_VISIBLE, 20, 70, 250, 20, hwnd, (HMENU)NULL,
                    GetModuleHandle(NULL), NULL);
                H2 = CreateWindowEx(NULL, DATETIMEPICK_CLASS, TEXT("DateTime"), WS_VISIBLE | WS_BORDER | WS_CHILD |
                    WS_CHILD, 20, 100, 90, 20, hwnd, (HMENU)615, GetModuleHandle(NULL), NULL);
                H3 = CreateWindowEx(NULL, L"BUTTON", L"Buscar", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 245, 70, 60, 20,
                    hwnd, (HMENU)616, GetModuleHandle(NULL), NULL);
            }
            if (wcscmp(getopcion, L"Especialidad") == 0) {
                H1 = CreateWindow(WC_STATIC, L"Especialidad: ", WS_CHILD | WS_VISIBLE, 20, 70, 130, 20, hwnd, (HMENU)NULL,
                    GetModuleHandle(NULL), NULL);
                H2 = CreateWindow(WC_COMBOBOX, NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | CBS_DROPDOWNLIST | CBS_HASSTRINGS | EN_VSCROLL | CBS_DROPDOWNLIST,
                    150, 70, 120, 160, hwnd, (HMENU)617, GetModuleHandle(NULL), NULL);
                auxs = primeros;
                do {
                    SendMessage(H2, CB_ADDSTRING, 0, (LPARAM)auxs->nombreS);
                    auxs = auxs->nexts;
                } while (auxs != primeros);
                H3 = CreateWindowEx(NULL, L"BUTTON", L"Buscar", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 275, 70, 60, 20,
                    hwnd, (HMENU)618, GetModuleHandle(NULL), NULL);
            }
            if (wcscmp(getopcion, L"Editar") == 0) {
                H1 = CreateWindow(WC_STATIC, L"Numero de cita: ", WS_CHILD | WS_VISIBLE, 20, 70, 120, 20, hwnd, (HMENU)NULL,
                    GetModuleHandle(NULL), NULL);
                H2 = CreateWindow(WC_EDIT, L"", WS_CHILD | WS_VISIBLE | WS_BORDER, 130, 70, 35, 20, hwnd, (HMENU)619,
                    GetModuleHandle(NULL), NULL);
                H3 = CreateWindowEx(NULL, L"BUTTON", L"Buscar", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 170, 70, 60, 20,
                    hwnd, (HMENU)620, GetModuleHandle(NULL), NULL);
            }
            break;
        }
        case 614: {
            wchar_t getcedula[15];
            GetDlgItemText(hwnd, 613, getcedula, 15);
            auxM = primeroM;
            do {
                if (wcscmp(getcedula, auxM->NomEmpleado) == 0) {
                    H4 = CreateWindow(WC_STATIC, auxM->NombreM, WS_CHILD | WS_VISIBLE, 20, 100, 300, 20, hwnd, (HMENU)621,
                        GetModuleHandle(NULL), NULL);
                    H5 = CreateWindow(WC_STATIC, auxM->EspecialidadM, WS_CHILD | WS_VISIBLE, 20, 120, 200, 20, hwnd, (HMENU)NULL,
                        GetModuleHandle(NULL), NULL);
                    H6 = CreateWindow(WC_STATIC, L"Seleccione el mes: ", WS_CHILD | WS_VISIBLE, 20, 140, 140, 20, hwnd, (HMENU)NULL,
                        GetModuleHandle(NULL), NULL);
                    H7 = CreateWindow(WC_COMBOBOX, NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | CBS_DROPDOWNLIST | CBS_HASSTRINGS | EN_VSCROLL | CBS_DROPDOWNLIST,
                        160, 140, 80, 240, hwnd, (HMENU)622, GetModuleHandle(NULL), NULL);
                    for (int i = 0; i < 12; i++) {
                        SendMessage(H7, CB_ADDSTRING, 0, (LPARAM)mes[i]);
                    }
                    H8 = CreateWindowEx(NULL, L"BUTTON", L"Buscar", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 240, 140, 60, 20,
                        hwnd, (HMENU)623, GetModuleHandle(NULL), NULL);

                }
                auxM = auxM->nextM;
            } while (auxM != primeroM);
            break;
        }
        case 616: {
            short diaNum;
            wchar_t getfecha[30];
            GetDlgItemText(hwnd, 615, getfecha, 30);
            wstring fecha1(getfecha);
            string fechaC1(fecha1.begin(), fecha1.end());
            wstring fecha2(getfecha);
            string fechaC2(fecha2.begin(), fecha2.end());
            wstring fecha3(getfecha);
            string fechaC3(fecha3.begin(), fecha3.end());
            wstring fecha4(getfecha);
            string fechaC(fecha4.begin(), fecha4.end());
            wstring fecha5(getfecha);
            string fechaC5(fecha5.begin(), fecha5.end());
            string Dia(fechaC1, 0, 2);
            diaNum = atoi(Dia.c_str());
            diaNum++;
            wstring DiaNum = to_wstring(diaNum);
            string conver(DiaNum.begin(), DiaNum.end());
            if (strlen(conver.c_str()) > 1) {
                fecha2[0] = conver[0];
                fecha2[1] = conver[1];
            }
            else {
                fecha2[0] = '0';
                fecha2[1] = conver[0];
            }
            diaNum++;
            wstring DiaNum1 = to_wstring(diaNum);
            string conver1(DiaNum1.begin(), DiaNum1.end());
            if (strlen(conver1.c_str()) > 1) {
                fecha3[0] = conver1[0];
                fecha3[1] = conver1[1];
            }
            else {
                fecha3[0] = '0';
                fecha3[1] = conver1[0];
            }
            diaNum++;
            wstring DiaNum2 = to_wstring(diaNum);
            string conver2(DiaNum2.begin(), DiaNum2.end());
            if (strlen(conver2.c_str()) > 1) {
                fecha4[0] = conver2[0];
                fecha4[1] = conver2[1];
            }
            else {
                fecha4[0] = '0';
                fecha4[1] = conver2[0];
            }
            diaNum++;
            wstring DiaNum3 = to_wstring(diaNum);
            string conver3(DiaNum3.begin(), DiaNum3.end());
            if (strlen(conver3.c_str()) > 1) {
                fecha5[0] = conver3[0];
                fecha5[1] = conver3[1];
            }
            else {
                fecha5[0] = '0';
                fecha5[1] = conver3[0];
            }
            const wchar_t* VF1 = fecha1.c_str();
            const wchar_t* VF2 = fecha2.c_str();
            const wchar_t* VF3 = fecha3.c_str();
            const wchar_t* VF4 = fecha4.c_str();
            const wchar_t* VF5 = fecha5.c_str();
            auxct = primeroct;
            RegistroConsulta.open("C://Users//carlo//source//repos//Proyecto//Proyecto//Registros//RegistroConsulta.txt", ios::in | ios::out | ios::trunc);
            do {
                if ((wcscmp(auxct->Fecha, VF1) == 0) || (wcscmp(auxct->Fecha, VF2) == 0) || (wcscmp(auxct->Fecha, VF3) == 0) || (wcscmp(auxct->Fecha, VF4) == 0) || (wcscmp(auxct->Fecha, VF5) == 0)) {
                    wstring ws1(auxct->Fecha);
                    string date(ws1.begin(), ws1.end());
                    RegistroConsulta << "Fecha de la cita: " << date << "\n";
                    wstring ws2(auxct->Hora);
                    string Hora(ws2.begin(), ws2.end());
                    RegistroConsulta << "Hora de la cita: " << Hora << "\n";
                    wstring ws4(auxct->Mecanico);
                    string mec(ws4.begin(), ws4.end());
                    RegistroConsulta << "Mecanico: " << mec;
                    wstring esp(auxct->Servicio);
                    string Eespecialidad(esp.begin(), esp.end());
                    RegistroConsulta << "\tServicio: " << Eespecialidad << "\n";
                    wstring ws5(auxct->Nombre);
                    string paciente(ws5.begin(), ws5.end());
                    RegistroConsulta << "Cliente: " << paciente << "\n";
                    wstring ws6(auxct->Telefono);
                    string phone(ws6.begin(), ws6.end());
                    RegistroConsulta << "Telefono: " << phone << "\n";
                    wstring ws7(auxct->status);
                    string estado(ws7.begin(), ws7.end());
                    RegistroConsulta << "Estado: " << estado << "\n";
                    wstring ws8(auxct->Motivo);
                    string motivo(ws8.begin(), ws8.end());
                    RegistroConsulta << "Motivo: " << motivo << "\n";
                    RegistroConsulta << "====================================================================================================================================";
                    RegistroConsulta << "\n";
                }
                auxct = auxct->nextct;
            } while (auxct != primeroct);
            RegistroConsulta.close();
            system("C://Users//carlo//source//repos//Proyecto//Proyecto//Registros//RegistroConsulta.txt");
            break;
        }
        case 618: {
            H4 = CreateWindow(WC_STATIC, L"Selecciona el lunes de la semana que se desea ver: ", WS_CHILD | WS_VISIBLE, 20, 110, 350, 20, hwnd, (HMENU)NULL,
                GetModuleHandle(NULL), NULL);
            H5 = CreateWindowEx(NULL, DATETIMEPICK_CLASS, TEXT("DateTime"), WS_VISIBLE | WS_BORDER | WS_CHILD |
                WS_CHILD, 370, 110, 90, 20, hwnd, (HMENU)6181, GetModuleHandle(NULL), NULL);
            H6 = CreateWindowEx(NULL, L"BUTTON", L"Buscar", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 460, 110, 60, 20,
                hwnd, (HMENU)6182, GetModuleHandle(NULL), NULL);
            break;
        }
        case 620: {
            wchar_t getnumero[3];
            GetDlgItemText(hwnd, 619, getnumero, 3);
            auxct = primeroct;
            do {
                if (wcscmp(getnumero, auxct->id) == 0) {
                    H4 = CreateWindow(WC_STATIC, L"Nombre: ", WS_CHILD | WS_VISIBLE, 20, 120, 100, 20, hwnd, (HMENU)NULL,
                        GetModuleHandle(NULL), NULL);
                    H5 = CreateWindow(WC_STATIC, auxct->Nombre, WS_CHILD | WS_VISIBLE, 100, 120, 320, 20, hwnd, (HMENU)6201,
                        GetModuleHandle(NULL), NULL);
                    H6 = CreateWindow(WC_STATIC, L"Mecanico: ", WS_CHILD | WS_VISIBLE, 20, 140, 100, 20, hwnd, (HMENU)NULL,
                        GetModuleHandle(NULL), NULL);
                    H7 = CreateWindow(WC_STATIC, auxct->Mecanico, WS_CHILD | WS_VISIBLE, 100, 140, 320, 20, hwnd, (HMENU)NULL,
                        GetModuleHandle(NULL), NULL);
                    H8 = CreateWindow(WC_STATIC, L"Servicio: ", WS_CHILD | WS_VISIBLE, 20, 160, 90, 20, hwnd, (HMENU)NULL,
                        GetModuleHandle(NULL), NULL);
                    H9 = CreateWindow(WC_STATIC, auxct->Servicio, WS_CHILD | WS_VISIBLE, 100, 160, 320, 20, hwnd, (HMENU)NULL,
                        GetModuleHandle(NULL), NULL);                  
                    H11 = CreateWindow(WC_STATIC, L"Fecha: ", WS_CHILD | WS_VISIBLE, 20, 180, 70, 20, hwnd, (HMENU)NULL,
                        GetModuleHandle(NULL), NULL);
                    H12 = CreateWindow(WC_STATIC, auxct->Fecha, WS_CHILD | WS_VISIBLE, 75, 180, 90, 20, hwnd, (HMENU)NULL,
                        GetModuleHandle(NULL), NULL);
                    H13 = CreateWindow(WC_STATIC, L"Hora: ", WS_CHILD | WS_VISIBLE, 240, 180, 60, 20, hwnd, (HMENU)NULL,
                        GetModuleHandle(NULL), NULL);
                    H14 = CreateWindow(WC_STATIC, auxct->Hora, WS_CHILD | WS_VISIBLE, 280, 180, 60, 20, hwnd, (HMENU)NULL,
                        GetModuleHandle(NULL), NULL);
                    H15 = CreateWindow(WC_STATIC, L"Estatus: ", WS_CHILD | WS_VISIBLE, 20, 210, 80, 20, hwnd, (HMENU)NULL,
                        GetModuleHandle(NULL), NULL);
                    H16 = CreateWindow(WC_COMBOBOX, NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | CBS_DROPDOWNLIST | CBS_HASSTRINGS | EN_VSCROLL | CBS_DROPDOWNLIST,
                        90, 210, 100, 60, hwnd, (HMENU)6202, GetModuleHandle(NULL), NULL);
                    for (short x = 0; x < 2; x++) {
                        SendMessage(H16, CB_ADDSTRING, 0, (LPARAM)estado[x]);
                    }
                    H17 = CreateWindow(WC_STATIC, L"Motivo: ", WS_CHILD | WS_VISIBLE, 20, 240, 80, 20, hwnd, (HMENU)NULL,
                        GetModuleHandle(NULL), NULL);
                    H18 = CreateWindow(WC_EDIT, auxct->Motivo, WS_CHILD | WS_VISIBLE | WS_BORDER, 20, 260, 400, 40, hwnd, (HMENU)6203,
                        GetModuleHandle(NULL), NULL);
                    H24 = CreateWindowEx(NULL, L"BUTTON", L"Guardar", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 340, 430, 80, 30,
                        hwnd, (HMENU)6210, GetModuleHandle(NULL), NULL);

                    break;
                }
                auxct = auxct->nextct;
            } while (auxct != primeroct);
            int prueba;
            break;
        }
        case 623: {
            wchar_t getmes[12];
            GetDlgItemText(hwnd, 622, getmes, 12);
            wchar_t getNombreMed[70];
            GetDlgItemText(hwnd, 621, getNombreMed, 70);
            auxct = primeroct;
            string getmes1;
            RegistroConsulta.open("C://Users//carlo//source//repos//Proyecto//Proyecto//Registros//RegistroConsulta.txt", ios::in | ios::out | ios::trunc);
            do {
                if (wcscmp(getmes, L"Enero") == 0) {
                    getmes1 = "01";
                }
                if (wcscmp(getmes, L"Febrero") == 0) {
                    getmes1 = "02";
                }
                if (wcscmp(getmes, L"Marzo") == 0) {
                    getmes1 = "03";
                }
                if (wcscmp(getmes, L"Abril") == 0) {
                    getmes1 = "04";
                }
                if (wcscmp(getmes, L"Mayo") == 0) {
                    getmes1 = "05";
                }
                if (wcscmp(getmes, L"Junio") == 0) {
                    getmes1 = "06";
                }
                if (wcscmp(getmes, L"Julio") == 0) {
                    getmes1 = "07";
                }
                if (wcscmp(getmes, L"Agosto") == 0) {
                    getmes1 = "08";
                }
                if (wcscmp(getmes, L"Septiembre") == 0) {
                    getmes1 = "09";
                }
                if (wcscmp(getmes, L"Octubre") == 0) {
                    getmes1 = "10";
                }
                if (wcscmp(getmes, L"Noviembre") == 0) {
                    getmes1 = "11";
                }
                if (wcscmp(getmes, L"Diciembre") == 0) {
                    getmes1 = "12";
                }
                wstring fecha(auxct->Fecha);
                string fechaC(fecha.begin(), fecha.end());
                string MesC(fechaC, 3, 2);
                short mc, mv;
                mc = atoi(getmes1.c_str());
                mv = atoi(MesC.c_str());
                if ((getmes1 == MesC) && (wcscmp(getNombreMed, auxct->Mecanico) == 0)) {
                    wstring ws1(auxct->Fecha);
                    string date(ws1.begin(), ws1.end());
                    RegistroConsulta << "Fecha de la cita: " << date << "\n";
                    wstring ws2(auxct->Hora);
                    string Hora(ws2.begin(), ws2.end());
                    RegistroConsulta << "Hora de la cita: " << Hora << "\n";
                    wstring ws4(auxct->Mecanico);
                    string mec(ws4.begin(), ws4.end());
                    RegistroConsulta << "Mecanico: " << mec;
                    wstring esp(auxct->Servicio);
                    string Eespecialidad(esp.begin(), esp.end());
                    RegistroConsulta << "\tServicio: " << Eespecialidad << "\n";
                    wstring ws5(auxct->Nombre);
                    string paciente(ws5.begin(), ws5.end());
                    RegistroConsulta << "Cliente: " << paciente << "\n";
                    wstring ws6(auxct->Telefono);
                    string phone(ws6.begin(), ws6.end());
                    RegistroConsulta << "Telefono: " << phone << "\n";
                    wstring ws7(auxct->status);
                    string estado(ws7.begin(), ws7.end());
                    RegistroConsulta << "Estado: " << estado << "\n";
                    wstring ws8(auxct->Motivo);
                    string motivo(ws8.begin(), ws8.end());
                    RegistroConsulta << "Motivo: " << motivo << "\n";
                    RegistroConsulta << "====================================================================================================================================";
                    RegistroConsulta << "\n";
                }
                auxct = auxct->nextct;
            } while (auxct != primeroct);
            RegistroConsulta.close();
            system("C://Users//carlo//source//repos//Proyecto//Proyecto//Registros//RegistroConsulta.txt");
            break;
        }
        case 6182: {
            short diaNum;
            wchar_t ge[50];
            wchar_t dt[30];
            GetDlgItemText(hwnd, 617, ge, 50);
            GetDlgItemText(hwnd, 6181, dt, 30);
            wstring fecha1(dt);
            string fechaC1(fecha1.begin(), fecha1.end());
            wstring fecha2(dt);
            string fechaC2(fecha2.begin(), fecha2.end());
            wstring fecha3(dt);
            string fechaC3(fecha3.begin(), fecha3.end());
            wstring fecha4(dt);
            string fechaC(fecha4.begin(), fecha4.end());
            wstring fecha5(dt);
            string fechaC5(fecha5.begin(), fecha5.end());
            string Dia(fechaC1, 0, 2);
            diaNum = atoi(Dia.c_str());
            diaNum++;
            wstring DiaNum = to_wstring(diaNum);
            string conver(DiaNum.begin(), DiaNum.end());
            if (strlen(conver.c_str()) > 1) {
                fecha2[0] = conver[0];
                fecha2[1] = conver[1];
            }
            else {
                fecha2[0] = '0';
                fecha2[1] = conver[0];
            }
            diaNum++;
            wstring DiaNum1 = to_wstring(diaNum);
            string conver1(DiaNum1.begin(), DiaNum1.end());
            if (strlen(conver1.c_str()) > 1) {
                fecha3[0] = conver1[0];
                fecha3[1] = conver1[1];
            }
            else {
                fecha3[0] = '0';
                fecha3[1] = conver1[0];
            }
            diaNum++;
            wstring DiaNum2 = to_wstring(diaNum);
            string conver2(DiaNum2.begin(), DiaNum2.end());
            if (strlen(conver2.c_str()) > 1) {
                fecha4[0] = conver2[0];
                fecha4[1] = conver2[1];
            }
            else {
                fecha4[0] = '0';
                fecha4[1] = conver2[0];
            }
            diaNum++;
            wstring DiaNum3 = to_wstring(diaNum);
            string conver3(DiaNum3.begin(), DiaNum3.end());
            if (strlen(conver3.c_str()) > 1) {
                fecha5[0] = conver3[0];
                fecha5[1] = conver3[1];
            }
            else {
                fecha5[0] = '0';
                fecha5[1] = conver3[0];
            }
            const wchar_t* VF1 = fecha1.c_str();
            const wchar_t* VF2 = fecha2.c_str();
            const wchar_t* VF3 = fecha3.c_str();
            const wchar_t* VF4 = fecha4.c_str();
            const wchar_t* VF5 = fecha5.c_str();
            auxct = primeroct;
            RegistroConsulta.open("C://Users//carlo//source//repos//Proyecto//Proyecto//Registros//RegistroConsulta.txt", ios::in | ios::out | ios::trunc);
            do {
                if ((wcscmp(auxct->Servicio, ge) == 0) && ((wcscmp(auxct->Fecha, VF1) == 0) || (wcscmp(auxct->Fecha, VF2) == 0) || (wcscmp(auxct->Fecha, VF3) == 0) || (wcscmp(auxct->Fecha, VF4) == 0) || (wcscmp(auxct->Fecha, VF5) == 0))) {
                    wstring ws1(auxct->Fecha);
                    string date(ws1.begin(), ws1.end());
                    RegistroConsulta << "Fecha de la cita: " << date << "\n";
                    wstring ws2(auxct->Hora);
                    string Hora(ws2.begin(), ws2.end());
                    RegistroConsulta << "Hora de la cita: " << Hora << "\n";
                    wstring ws4(auxct->Mecanico);
                    string mec(ws4.begin(), ws4.end());
                    RegistroConsulta << "Mecanico: " << mec;
                    wstring esp(auxct->Servicio);
                    string Eespecialidad(esp.begin(), esp.end());
                    RegistroConsulta << "\tServicio: " << Eespecialidad << "\n";
                    wstring ws5(auxct->Nombre);
                    string paciente(ws5.begin(), ws5.end());
                    RegistroConsulta << "Cliente: " << paciente << "\n";
                    wstring ws6(auxct->Telefono);
                    string phone(ws6.begin(), ws6.end());
                    RegistroConsulta << "Telefono: " << phone << "\n";
                    wstring ws7(auxct->status);
                    string estado(ws7.begin(), ws7.end());
                    RegistroConsulta << "Estado: " << estado << "\n";
                    wstring ws8(auxct->Motivo);
                    string motivo(ws8.begin(), ws8.end());
                    RegistroConsulta << "Motivo: " << motivo << "\n";
                    RegistroConsulta << "====================================================================================================================================";
                    RegistroConsulta << "\n";
                }
                auxct = auxct->nextct;
            } while (auxct != primeroct);
            RegistroConsulta.close();
            system("C://Users//carlo//source//repos//Proyecto//Proyecto//Registros//RegistroConsulta.txt");
            break;
        }
        case 6210: {
            wchar_t nombre[70];
            wchar_t estado[12];
            wchar_t motivo[70];
            GetDlgItemText(hwnd, 6201, nombre, 70);
            GetDlgItemText(hwnd, 6202, estado, 12);
            GetDlgItemText(hwnd, 6203, motivo, 70);
            auxct = primeroct;
            do {
                if (wcscmp(nombre,auxct->Nombre)==0) {
                    wcscpy_s(auxct->status, estado);
                    wcscpy_s(auxct->Motivo, motivo);
                    break;
                }
                auxct = auxct->nextct;
            } while (auxct != primeroct);
            DestroyWindow(hwnd);
            break;
        }


        }
    }
    case WM_DESTROY: {
        window6open = false;
        break;
    }
                  
    }
    return DefWindowProc(hwnd, message, wParam, lParam);
}


LRESULT CALLBACK windowprocessforwindow7(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {

    switch (message) {
    case WM_CREATE:
        window7open = true;
        break;
    case WM_DESTROY:
        window7open = false;
        break;
    case WM_COMMAND:
        break;
    }
    return DefWindowProc(hwnd, message, wParam, lParam);


}


bool valCodigo(string Valcod) {
    regex miRegex("[A-Z]{3}[0-9]{3}");
    if (regex_match(Valcod, miRegex)) {
        return true;
    }
    else {
        return false;
    }
}

bool valNombre(string nom) {
    regex miRegex2("[ ]*");
    if (regex_match(nom, miRegex2)) {
        return false;
    }
    else {
        regex miRegex("[a-zA-ZÑñ ]*");
        if (regex_match(nom, miRegex)) {
            return true;
        }
        else {
            return false;
        }
    }
}

bool ValidarNumerodeempleado(string numero) {
    regex miRegex("[0-9]{3}");
    if (regex_match(numero, miRegex)) {
        return true;
    }
    else {
        return false;
    }


}

bool ValidarNumeroTelefono(string nom) {
    if (strlen(nom.c_str()) == 10) {
        regex miRegex("^[0-9]{10}$");
        if (regex_match(nom, miRegex)) {
            return true;
        }
        else {
            return false;
        }
    }
    else {
        return false;
    }

}

bool ValidarLleno(string dato) {
    regex miRegex2("[ ]*");
    if (regex_match(dato, miRegex2)) {
        return false;
    }
    else {
        return true;
    }

}

bool validarprecio(string precio) {
    regex miRegex2("[ ]*");
    if (regex_match(precio, miRegex2)) {
        return false;
    }
    else {
        regex miRegex("[0-9.]*");
        if (regex_match(precio, miRegex)) {
            return true;
        }
        else {
            return false;
        }
    }
}

void guardarServicios(HWND Ghwnd) {

    servicios.open("C://Users//carlo//source//repos//Proyecto//Proyecto//Registros//servicios.bin", ios::out | ios::trunc | ios::binary);

    if (primeros != NULL) {

        if (!servicios.is_open()) {
            MessageBox(Ghwnd, L"No se cargo el archivo de la lista", L"Error", MB_ICONASTERISK);
        }
        else {

            auxs = primeros;
            do {
                servicios.write(reinterpret_cast<char*> (auxs), sizeof(servicio));
                auxs = auxs->nexts;

            } while (auxs != primeros);

            MessageBox(Ghwnd, L"Guardado de lista de servicios exitoso", L"ok", MB_OK);


        }
    }

    servicios.close();
}

void cargarServicios(HWND Chwnd) {
    servicios.open("C://Users//carlo//source//repos//Proyecto//Proyecto//Registros//servicios.bin", ios::in);
    if (!servicios.is_open()) {
        MessageBox(Chwnd, L"No se cargo el archivo de la lista", L"Error", MB_ICONASTERISK);
    }
    else {

        while (!servicios.eof()) {
            servicio* nuevoservicio = new servicio;
            servicios.read(reinterpret_cast<char*>(nuevoservicio), sizeof(servicio));
            if (!servicios.eof()) {
                if (primeros == NULL) {
                    primeros = nuevoservicio;
                    primeros->nexts = primeros;
                    primeros->prevs = primeros;
                    ultimos = primeros;
                }
                else {
                    ultimos->nexts = nuevoservicio;
                    nuevoservicio->nexts = primeros;
                    nuevoservicio->prevs = ultimos;
                    ultimos = nuevoservicio;
                    primeros->prevs = ultimos;
                }
            }
        }
    }
    servicios.close();
}

void guardarMecanicos(HWND Ghwnd) {

    listamecanico.open("C://Users//carlo//source//repos//Proyecto//Proyecto//Registros//mecanicos.bin", ios::out | ios::trunc | ios::binary);

    if (primeroM != NULL) {

        if (!listamecanico.is_open()) {
            MessageBox(Ghwnd, L"No se cargo el archivo de la lista", L"Error", MB_ICONASTERISK);
        }
        else {

            auxM = primeroM;
            do {
                listamecanico.write(reinterpret_cast<char*> (auxM), sizeof(mecanico));
                auxM = auxM->nextM;

            } while (auxM != primeroM);

            MessageBox(Ghwnd, L"Guardado de lista de mecanicos exitoso", L"ok", MB_OK);


        }
    }

    listamecanico.close();
}

void cargarMecanicos(HWND Chwnd) {
    listamecanico.open("C://Users//carlo//source//repos//Proyecto//Proyecto//Registros//mecanicos.bin", ios::in);
    if (!listamecanico.is_open()) {
        MessageBox(Chwnd, L"No se cargo el archivo de la lista", L"Error", MB_ICONASTERISK);
    }
    else {

        while (!listamecanico.eof()) {
            mecanico* NuevoMecanico = new mecanico;
            listamecanico.read(reinterpret_cast<char*>(NuevoMecanico), sizeof(mecanico));
            if (!listamecanico.eof()) {
                if (primeroM == NULL) {
                    primeroM = NuevoMecanico;
                    primeroM->nextM = primeroM;
                    primeroM->prevM = primeroM;
                    ultimoM = primeroM;
                }
                else {
                    ultimoM->nextM = NuevoMecanico;
                    NuevoMecanico->nextM = primeroM;
                    NuevoMecanico->prevM = ultimoM;
                    ultimoM = NuevoMecanico;
                    primeroM->prevM = ultimoM;
                }
            }
        }
    }
    listamecanico.close();
}

void guardarClientes(HWND Ghwnd) {
    listaclientes.open("C://Users//carlo//source//repos//Proyecto//Proyecto//Registros//clientes.bin", ios::out | ios::trunc | ios::binary);
    if (primeroc != NULL) {
        if (!listaclientes.is_open()) {
            MessageBox(Ghwnd, L"No se cargo el archivo de la lista", L"Error", MB_ICONASTERISK);
        }
        else {
            auxc = primeroc;
            do {
                listaclientes.write(reinterpret_cast<char*> (auxc), sizeof(clientes));
                auxc = auxc->nextc;
            } while (auxc != primeroc);
            MessageBox(Ghwnd, L"Guardado de lista de clientes exitoso", L"ok", MB_OK);
        }
    }
    listaclientes.close();
}

void cargarClientes(HWND Chwnd) {
    listaclientes.open("C://Users//carlo//source//repos//Proyecto//Proyecto//Registros//clientes.bin", ios::in);
    if (!listaclientes.is_open()) {
        MessageBox(Chwnd, L"No se cargo el archivo de la lista", L"Error", MB_ICONASTERISK);
    }
    else {

        while (!listaclientes.eof()) {
            clientes* nuevocliente = new clientes;
            listaclientes.read(reinterpret_cast<char*>(nuevocliente), sizeof(clientes));
            if (!listaclientes.eof()) {
                if (primeroc == NULL) {
                    primeroc = nuevocliente;
                    primeroc->nextc = primeroc;
                    primeroc->prevc = primeroc;
                    ultimoc = primeroc;
                }
                else {
                    ultimoc->nextc = nuevocliente;
                    nuevocliente->nextc = primeroc;
                    nuevocliente->prevc = ultimoc;
                    ultimoc = nuevocliente;
                    primeroc->prevc = ultimoc;
                }
            }
        }
    }
    listaclientes.close();
}

void guardarCitas(HWND Ghwnd) {
    listacitas.open("C://Users//carlo//source//repos//Proyecto//Proyecto//Registros//citas.bin", ios::out | ios::trunc | ios::binary);
    if (primeroct != NULL) {
        if (!listacitas.is_open()) {
            MessageBox(Ghwnd, L"No se cargo el archivo de la lista", L"Error", MB_ICONASTERISK);
        }
        else {
            auxct = primeroct;
            do {
                listacitas.write(reinterpret_cast<char*> (auxct), sizeof(citas));
                auxct = auxct->nextct;
            } while (auxct != primeroct);
            MessageBox(Ghwnd, L"Guardado de lista de citas exitoso", L"ok", MB_OK);
        }
    }
    listacitas.close();
}

void cargarCitas(HWND Chwnd) {
    listacitas.open("C://Users//carlo//source//repos//Proyecto//Proyecto//Registros//citas.bin", ios::in);
    if (!listacitas.is_open()) {
        MessageBox(Chwnd, L"No se cargo el archivo de la lista", L"Error", MB_ICONASTERISK);
    }
    else {

        while (!listacitas.eof()) {
            citas* nuevacita = new citas;
            listacitas.read(reinterpret_cast<char*>(nuevacita), sizeof(citas));
            if (!listacitas.eof()) {
                if (primeroct == NULL) {
                    primeroct = nuevacita;
                    primeroct->nextct = primeroct;
                    primeroct->prevct = primeroct;
                    ultimoct = primeroct;
                }
                else {
                    ultimoct->nextct = nuevacita;
                    nuevacita->nextct = primeroct;
                    nuevacita->prevct = ultimoct;
                    ultimoct = nuevacita;
                    primeroct->prevct = ultimoct;
                }
            }
        }
    }
    listacitas.close();
}

void Quicksort(int* arr, int izq, int der) {
    int i = izq, j = der, tmp;
    int p = arr[(izq + der) / 2];
    while (i <= j) {

        while (arr[i] < p) i++;
        while (arr[j] > p)j--;
        if (i <= j) {
            tmp = arr[i];
            arr[i] = arr[j];
            arr[j] = tmp;
            i++; j--;
        }
    }
    if (izq < j) {
        Quicksort(arr, izq, j);
    }
    if (i < der) {
        Quicksort(arr, i, der);
    }
}

void EscribirRegistroMecanico() {
    fstream RegistroMecanico;
    auxM = primeroM;
    int quickInd = 0;

    do {
        wstring con(auxM->NomEmpleado);
        string conver(con.begin(), con.end());
        Quick[quickInd] = atoi(conver.c_str());
        quickInd++;
        auxM = auxM->nextM;
    } while (auxM != primeroM);
    RegistroMecanico.open("C://Users//carlo//source//repos//Proyecto//Proyecto//Registros//registroMecanico.txt", ios::in | ios::out | ios::trunc);
    Quicksort(Quick, 0, quickInd);
    if (quickInd > 4) {
        for (x = 0; x <= quickInd; x++) {
            wstring cn = to_wstring(Quick[x]);
            const wchar_t* compced = cn.c_str();
            auxM = primeroM;
            do {
                if (wcscmp(compced, auxM->NomEmpleado) == 0) {
                    wstring ws(auxM->NombreM);
                    string Nombre(ws.begin(), ws.end());
                    RegistroMecanico << "Mecanico: " << Nombre << "\n";
                    wstring ws1(auxM->EspecialidadM);
                    string Especialidad(ws1.begin(), ws1.end());
                    RegistroMecanico << "Especialidad: " << Especialidad << "\n";
                    wstring ws2(auxM->NomEmpleado);
                    string Numero(ws2.begin(), ws2.end());
                    RegistroMecanico << "Numero de empleado: " << Numero << "\n";
                    wstring ws3(auxM->telefonoM);
                    string telefono(ws3.begin(), ws3.end());
                    RegistroMecanico << "Num.Telefono: " << telefono << "\n";
                    wstring ws9(auxM->Turno);
                    string turno(ws9.begin(), ws9.end());
                    RegistroMecanico << "Turno: " << turno << "\n";
                    RegistroMecanico << "\tAtiende los dias" << "\n";
                    wstring ws4(auxM->Lunes);
                    string Lunes(ws4.begin(), ws4.end());
                    wstring ws5(auxM->Martes);
                    string Martes(ws5.begin(), ws5.end());
                    wstring ws6(auxM->Miercoles);
                    string Miercoles(ws6.begin(), ws6.end());
                    wstring ws7(auxM->Jueves);
                    string Jueves(ws7.begin(), ws7.end());
                    wstring ws8(auxM->Viernes);
                    string Viernes(ws8.begin(), ws8.end());
                    RegistroMecanico << "Lunes: " << Lunes << "\tMarter: " << Martes << "\tMiercoles: " << Miercoles << "\tJueves: " << Jueves << "\tViernes: " << Viernes << "\n";
                    RegistroMecanico << "===========================================================================================================================================================";
                    RegistroMecanico << "\n";


                }
                auxM = auxM->nextM;
            } while (auxM != primeroM);

        }
    }
    RegistroMecanico.close();
}

void heapify(string* array, int iterationSize) {
    int i, par, node;
    for (i = 1; i <= iterationSize; i++) {
        node = i; par = (int)node / 2;
        while (par >= 1) {
            if (array[par] < array[node]) {
                swap(array[par], array[node]);
            }
            node = par;
            par = (int)node / 2;
        }
    }
}

void heapSort(string* array, int size) {
    for (int i = size; i >= 1; i--) {
        heapify(array, i);
        swap(array[1], array[i]);
    }
}

void EscribirRegistroCliente(int contador) {
 RegistroCliente.open("C://Users//carlo//source//repos//Proyecto//Proyecto//Registros//registroCliente.txt", ios::in | ios::out | ios::trunc);
 for (int x = 0; x <= contador;x++) {
     auxc = primeroc;
     do {
         wchar_t Nom[70];
         wcscpy_s(Nom, auxc->nombre);
         wstring ws(Nom);
         string nombre(ws.begin(), ws.end());
         if (Nombres[x]==nombre) {
             wstring ws(auxc->nombre);
             string Nombre(ws.begin(), ws.end());
             RegistroCliente << "Nombre: " << Nombre<<"\n";
             wstring ws1(auxc->marca);
             string Marca(ws1.begin(), ws1.end());
             wstring ws2(auxc->modelo);
             string Modelo(ws2.begin(), ws2.end());
             wstring ws3(auxc->placas);
             string Placas(ws3.begin(), ws3.end());
             RegistroCliente << "Marca: " << Marca << "\t" << "Modelo: " << Modelo << "\t" << "Placas: " << Placas << "\n";
             wstring ws4(auxc->kilometraje);
             string Kilometraje(ws4.begin(), ws4.end());
             wstring ws5(auxc->telefono);
             string Telefono(ws5.begin(), ws5.end());
             RegistroCliente << "Kilometraje: " << Kilometraje << "\t" << "Telefono: " << Telefono<<"\n";
             wstring ws6(auxc->direccion);
             string Direccion(ws6.begin(), ws6.end());
             RegistroCliente << "Direccion: " << Direccion << "\n";
             RegistroCliente <<"==================================================================================================================" << "\n";
         }
         auxc = auxc->nextc;
     } while (auxc != primeroc);
 }
 RegistroCliente.close();
}

void recuperarID() {
    if (primeroct != NULL) {
        auxct = primeroct;
        auxct = auxct->prevct;
        wstring con(auxct->id);
        string conver(con.begin(), con.end());
        IDDC = atoi(conver.c_str());
    }
}
bool validarprecio2(string str) {
    int precioint = atoi(str.c_str());
    if (precioint > 0) {
        return true;
    }
    else {
        return false;
    }

}
bool validarplascas(string placas) {
    regex miRegex("[A-Z]{3}[-][0-9]{3}");
    if (regex_match(placas, miRegex)) {
        return true;
    }
    else {
        return false;
    }
}