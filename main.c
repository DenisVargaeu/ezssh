#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <windows.h>  // pre GUI

// Forward deklar·cie tvojich existuj˙cich funkciÌ (doplnÌö podæa potreby)
void create_new_connection(const char* existing);
void start_connection(const char* name);
void start_connectionnw(const char* name);
void print_info(const char* name);
void edit_connection(const char* name);
void delete_connection(const char* name);
void list_connections(void);

// GUI funkcie (prid·me niûöie)
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
void RunGUI(HINSTANCE hInstance);

// Globalne handle pre GUI
HWND hwndNameInput, hwndOutput;

int main(int argc, char** argv) {
    if (argc >= 2 && strcmp(argv[1], "-gui") == 0) {
        // Spusti GUI (WinAPI)
        HINSTANCE hInstance = GetModuleHandle(NULL);
        RunGUI(hInstance);
        return 0;
    }

    if (argc < 2) {
        printf("Usage:\n");
        printf("  ezssh -n             create a new save\n");
        printf("  ezssh -c   <name>    connect to a save \n");
        printf("  ezssh --c  <name>    connect to a save in new window \n");
        printf("  ezssh -in  <name>    show info about save\n");
        printf("  ezssh -e   <name>    edit save\n");
        printf("  ezssh -d   <name>    delete save\n");
        printf("  ezssh -l             list of saves\n");
        printf("  ezssh -v             version of programm\n");
        printf("  ezssh -gui           open GUI menu (BETASs)\n");
        printf("  version: 1.0.0\n");
        printf("  Denis Varga denisvarga.eu\n");
        return 0;
    }

    if (strcmp(argv[1], "-n") == 0) {
        create_new_connection(NULL);
    }
    else if (strcmp(argv[1], "-c") == 0 && argc == 3) {
        start_connection(argv[2]);
    }
    else if (strcmp(argv[1], "--c") == 0 && argc == 3) {
        start_connectionnw(argv[2]);
    }
    else if (strcmp(argv[1], "-in") == 0 && argc == 3) {
        print_info(argv[2]);
    }
    else if (strcmp(argv[1], "-e") == 0 && argc == 3) {
        edit_connection(argv[2]);
    }
    else if (strcmp(argv[1], "-d") == 0 && argc == 3) {
        delete_connection(argv[2]);
    }
    else if (strcmp(argv[1], "-l") == 0) {
        list_connections();
    }
    else if (strcmp(argv[1], "-v") == 0) {
        printf(" Ezssh version BETA 1.0.10 \n");
        printf(" Denis Varga denisvarga.eu \n");
        printf(" build:  11\n");
        printf(" Support to 7.29.2025 \n");
        printf(" DV studio \n");
    }
    else {
        printf("Invalid arguments.\n");
    }

    return 0;
}

// ------------- TU ZA»ÕNA K”D PRE GUI ----------------

#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <stdio.h>
#include <string.h>

// Forward declarations of your existing functions
void create_new_connection(const char* existing);
void start_connection(const char* name);
void start_connectionnw(const char* name);
void print_info(const char* name);
void edit_connection(const char* name);
void delete_connection(const char* name);
void list_connections(void);

// Global HWNDs
HWND hwndNameInput, hwndOutput;

// Helper functions for Unicode GUI
void GetEditText(HWND hwndEdit, wchar_t* buffer, int size) {
    GetWindowTextW(hwndEdit, buffer, size);
}

void AppendOutput(const wchar_t* text) {
    int length = GetWindowTextLengthW(hwndOutput);
    SendMessageW(hwndOutput, EM_SETSEL, length, length);
    SendMessageW(hwndOutput, EM_REPLACESEL, FALSE, (LPARAM)text);
    SendMessageW(hwndOutput, EM_REPLACESEL, FALSE, (LPARAM)L"\r\n");
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
    case WM_COMMAND:
        switch (LOWORD(wParam)) {
        case 1: { // Connect
            wchar_t wname[128] = { 0 };
            GetEditText(hwndNameInput, wname, sizeof(wname) / sizeof(wchar_t));
            if (wcslen(wname) == 0) {
                AppendOutput(L"Zadaj meno pripojenia!");
            }
            else {
                AppendOutput(L"Sp˙öùam pripojenie...");
                // Tu treba prekonvertovaù wname na char*, alebo upraviù funkciu na wchar_t
                // Pre jednoduch˝ test z konverziou na ASCII:
                char name[128];
                wcstombs(name, wname, sizeof(name));
                start_connection(name);
            }
            break;
        }
        case 2: {
            AppendOutput(L"Sp˙öùam tvorbu novÈho pripojenia...");
            create_new_connection(NULL);
            break;
        }
        case 3: {
            wchar_t wname[128] = { 0 };
            GetEditText(hwndNameInput, wname, sizeof(wname) / sizeof(wchar_t));
            if (wcslen(wname) == 0) {
                AppendOutput(L"Zadaj meno pre info!");
            }
            else {
                wchar_t msg[256];
                swprintf(msg, 256, L"Zobrazenie info pre: %s", wname);
                AppendOutput(msg);
                // Rovnak˝ konvert na ASCII ak treba
                char name[128];
                wcstombs(name, wname, sizeof(name));
                print_info(name);
            }
            break;
        }
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProcW(hwnd, uMsg, wParam, lParam);
}

void RunGUI(HINSTANCE hInstance) {
    const wchar_t CLASS_NAME[] = L"EzSSHWindowClass";

    WNDCLASSW wc = { 0 };
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;

    if (!RegisterClassW(&wc)) {
        MessageBoxW(NULL, L"Nepodarilo sa zaregistrovaù triedu okna!", L"Chyba", MB_OK | MB_ICONERROR);
        return;
    }

    HWND hwnd = CreateWindowExW(
        0,
        CLASS_NAME,
        L"EzSSH Menu",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 420, 260,
        NULL,
        NULL,
        hInstance,
        NULL
    );

    if (!hwnd) {
        MessageBoxW(NULL, L"Nepodarilo sa vytvoriù okno!", L"Chyba", MB_OK | MB_ICONERROR);
        return;
    }

    ShowWindow(hwnd, SW_SHOWDEFAULT);

    CreateWindowW(L"STATIC", L"Meno pripojenia:", WS_VISIBLE | WS_CHILD, 20, 20, 120, 20, hwnd, NULL, hInstance, NULL);
    hwndNameInput = CreateWindowW(L"EDIT", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 150, 20, 220, 20, hwnd, NULL, hInstance, NULL);

    CreateWindowW(L"BUTTON", L"Pripojiù", WS_VISIBLE | WS_CHILD, 20, 60, 100, 30, hwnd, (HMENU)1, hInstance, NULL);
    CreateWindowW(L"BUTTON", L"NovÈ pripojenie", WS_VISIBLE | WS_CHILD, 140, 60, 130, 30, hwnd, (HMENU)2, hInstance, NULL);
    CreateWindowW(L"BUTTON", L"Zobraziù info", WS_VISIBLE | WS_CHILD, 290, 60, 110, 30, hwnd, (HMENU)3, hInstance, NULL);

    hwndOutput = CreateWindowW(L"EDIT", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_MULTILINE | ES_AUTOVSCROLL, 20, 100, 380, 110, hwnd, NULL, hInstance, NULL);

    MSG msg = { 0 };
    while (GetMessageW(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }
}
