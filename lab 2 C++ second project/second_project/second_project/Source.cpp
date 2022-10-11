
#include <Windows.h>


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
    wc.hCursor = LoadCursor(NULL, IDC_UPARROW); // дескриптор курсора
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




LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;
    static POINTS Start,endCoord, lastCoord;
    static BOOL lastCoordCondition = FALSE;
    RECT px;
    POINT observe, coord;
    HPEN redPen;

  

    switch (uMsg)

    {
    case WM_RBUTTONDOWN:  //зажатие правой кнопки мыши
    {
        SetCapture(hwnd);
        GetClientRect(hwnd, &px);
        observe.x = px.left;
        observe.y = px.top;

        coord.x = px.right + 1;
        coord.y = px.bottom + 1;
        ClientToScreen(hwnd, &observe);
        ClientToScreen(hwnd, &coord);

        SetRect(&px, observe.x, observe.y, coord.x, coord.y);
        ClipCursor(&px);
        Start = MAKEPOINTS(lParam);
        break;
    }
    case WM_MOUSEMOVE:  //ƒвижение курсора
    {
        if (wParam & MK_RBUTTON)
        {
            HDC hdc = GetDC(hwnd);
            redPen = CreatePen(PS_DASH, 1, RGB(0xFF, 0, 0));
            SelectObject(hdc, redPen);
            SetROP2(hdc, R2_NOTXORPEN);

            if (lastCoordCondition)
            {
                MoveToEx(hdc, Start.x, Start.y, (LPPOINT)NULL);
                LineTo(hdc, lastCoord.x, lastCoord.y);
            }
            endCoord = MAKEPOINTS(lParam);
            MoveToEx(hdc, Start.x, Start.y, (LPPOINT)NULL);
            LineTo(hdc, endCoord.x, endCoord.y);

            lastCoordCondition = TRUE;
            lastCoord = endCoord;
            ReleaseDC(hwnd, hdc);
            break;
        }
    }
    case WM_RBUTTONUP: //отжатие
    {
        lastCoordCondition = FALSE;
        ClipCursor(NULL);
        ReleaseCapture();
        break;
    }

    case WM_DESTROY:
    {
    
        PostQuitMessage(NULL);
        break;
    }
    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
           

    }

    return NULL;
}


