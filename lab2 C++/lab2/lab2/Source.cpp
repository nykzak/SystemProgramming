#include <windows.h> 


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

// ”правл€юща€ функци€:
int WINAPI WinMain(HINSTANCE hInst, // дескриптор экземпл€ра приложени€
    HINSTANCE hPrevInst, // не используем
    LPSTR lpCmdLine, // не используем
    int nCmdShow) // режим отображени€ окошка
{
    
    TCHAR szClassName[] = "Lab2"; // строка с именем класса
    HWND hMainWnd; // создаЄм дескриптор будущего окошка
    MSG msg; // создЄм экземпл€р структуры MSG дл€ обработки сообщений
    WNDCLASSEX wc; // создаЄм экземпл€р, дл€ обращени€ к членам класса WNDCLASSEX
    wc.cbSize = sizeof(wc); // размер структуры (в байтах)
    wc.style = CS_HREDRAW | CS_VREDRAW; // стиль класса окошка
    wc.lpfnWndProc = WndProc; // указатель на пользовательскую функцию
    wc.lpszMenuName = NULL; // указатель на им€ меню (у нас его нет)
    wc.lpszClassName = szClassName; // указатель на им€ класса
    wc.cbWndExtra = NULL; // число освобождаемых байтов в конце структуры
    wc.cbClsExtra = NULL; // число освобождаемых байтов при создании экземпл€ра приложени€
    wc.hIcon = (HICON)LoadImage(NULL, "ico.ico", IMAGE_ICON, 0, 0, LR_LOADFROMFILE);
    wc.hIconSm = (HICON)LoadImage(NULL, "ico.ico", IMAGE_ICON, 0, 0, LR_LOADFROMFILE);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW); // дескриптор курсора
    wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); // дескриптор кисти дл€ закраски фона окна
    wc.hInstance = hInst; // указатель на строку, содержащую им€ меню, примен€емого дл€ класса

    if (!RegisterClassEx(&wc)) {

        MessageBox(NULL, "Ќе получилось зарегистрировать класс!", "ќшибка", MB_OK);
        return NULL; 
    }

    // ‘ункци€, создающа€ окошко:
    hMainWnd = CreateWindow(
        szClassName, 
        "Sergey_Pavlov70982", 
        WS_OVERLAPPEDWINDOW | WS_VSCROLL, // режимы отображени€ окошка
        CW_USEDEFAULT, // позици€ окошка по оси х
        NULL, // позици€ окошка по оси у (раз дефолт в х, то писать не нужно)
        CW_USEDEFAULT, // ширина окошка
        NULL, // высота окошка (раз дефолт в ширине, то писать не нужно)
        (HWND)NULL, // дескриптор родительского окна
        NULL, // дескриптор меню
        HINSTANCE(hInst), // дескриптор экземпл€ра приложени€
        NULL); // ничего не передаЄм из WndProc

    if (!hMainWnd) {
        MessageBox(NULL, "Ќе получилось создать окно!", "ќшибка", MB_OK);
        return NULL;
    }

    ShowWindow(hMainWnd, nCmdShow); 
    UpdateWindow(hMainWnd); 
    while (GetMessage(&msg, NULL, NULL, NULL)) {
        TranslateMessage(&msg); // интерпретируем сообщени€
        DispatchMessage(&msg); // передаЄм сообщени€ обратно ќ—
    }
    return msg.wParam; // возвращаем код выхода из приложени€
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    HFONT styleFont;

    HDC hdc;
    TCHAR Array1[50];
    TCHAR Array2[50];
    WORD xPosition1, yPosition1, Volume1, xPosition2, yPosition2, Volume2;

    xPosition1 = LOWORD(lParam);
    yPosition1 = HIWORD(lParam);
    xPosition2 = LOWORD(lParam);
    yPosition2 = HIWORD(lParam);

    hdc = GetDC(hWnd);

    styleFont = CreateFont(60, 0, 0, 5, 200, 1, 1, 0, 
                DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, 
                CLIP_DEFAULT_PRECIS, PROOF_QUALITY,
                DEFAULT_PITCH | FF_MODERN,
                ("Arial"));

    (HFONT)SelectObject(hdc, styleFont);

    switch (uMsg) {

    case WM_LBUTTONDOWN:
        Volume1 = wsprintf(Array1, TEXT("(%d, %d)"), xPosition1, yPosition1);
        TextOut(hdc, xPosition1, yPosition1, Array1, Volume1);
        break;

    case WM_RBUTTONDOWN:
        Volume2 = wsprintf(Array2, TEXT("(Click)"), xPosition2, yPosition2);
        TextOut(hdc, xPosition2, yPosition2, Array2, Volume2);
        break;

    case WM_DESTROY:
    {

        PostQuitMessage(NULL);
        break;
    }

    default:
        return DefWindowProc(hWnd, uMsg, wParam, lParam);
       
    }
    return NULL;
}