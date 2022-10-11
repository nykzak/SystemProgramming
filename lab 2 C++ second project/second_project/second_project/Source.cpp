
#include <Windows.h>


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

// ����������� �������:
int WINAPI WinMain(HINSTANCE hInst, // ���������� ���������� ����������
    HINSTANCE hPrevInst, // �� ����������
    LPSTR lpCmdLine, // �� ����������
    int nCmdShow) // ����� ����������� ������
{

    TCHAR szClassName[] = "Lab2"; // ������ � ������ ������
    HWND hMainWnd; // ������ ���������� �������� ������
    MSG msg; // ����� ��������� ��������� MSG ��� ��������� ���������
    WNDCLASSEX wc; // ������ ���������, ��� ��������� � ������ ������ WNDCLASSEX
    wc.cbSize = sizeof(wc); // ������ ��������� (� ������)
    wc.style = CS_HREDRAW | CS_VREDRAW; // ����� ������ ������
    wc.lpfnWndProc = WndProc; // ��������� �� ���������������� �������
    wc.lpszMenuName = NULL; // ��������� �� ��� ���� (� ��� ��� ���)
    wc.lpszClassName = szClassName; // ��������� �� ��� ������
    wc.cbWndExtra = NULL; // ����� ������������� ������ � ����� ���������
    wc.cbClsExtra = NULL; // ����� ������������� ������ ��� �������� ���������� ����������
    wc.hIcon = (HICON)LoadImage(NULL, "ico.ico", IMAGE_ICON, 0, 0, LR_LOADFROMFILE);
    wc.hIconSm = (HICON)LoadImage(NULL, "ico.ico", IMAGE_ICON, 0, 0, LR_LOADFROMFILE);
    wc.hCursor = LoadCursor(NULL, IDC_UPARROW); // ���������� �������
    wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); // ���������� ����� ��� �������� ���� ����
    wc.hInstance = hInst; // ��������� �� ������, ���������� ��� ����, ������������ ��� ������

    if (!RegisterClassEx(&wc)) {

        MessageBox(NULL, "�� ���������� ���������������� �����!", "������", MB_OK);
        return NULL;
    }

    // �������, ��������� ������:
    hMainWnd = CreateWindow(
        szClassName,
        "Sergey_Pavlov70982",
        WS_OVERLAPPEDWINDOW | WS_VSCROLL, // ������ ����������� ������
        CW_USEDEFAULT, // ������� ������ �� ��� �
        NULL, // ������� ������ �� ��� � (��� ������ � �, �� ������ �� �����)
        CW_USEDEFAULT, // ������ ������
        NULL, // ������ ������ (��� ������ � ������, �� ������ �� �����)
        (HWND)NULL, // ���������� ������������� ����
        NULL, // ���������� ����
        HINSTANCE(hInst), // ���������� ���������� ����������
        NULL); // ������ �� ������� �� WndProc

    if (!hMainWnd) {
        MessageBox(NULL, "�� ���������� ������� ����!", "������", MB_OK);
        return NULL;
    }

    ShowWindow(hMainWnd, nCmdShow);
    UpdateWindow(hMainWnd);
   


    while (GetMessage(&msg, NULL, NULL, NULL)) {
        TranslateMessage(&msg); // �������������� ���������
        DispatchMessage(&msg); // ������� ��������� ������� ��
   
    }
    return msg.wParam; // ���������� ��� ������ �� ����������
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
    case WM_RBUTTONDOWN:  //������� ������ ������ ����
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
    case WM_MOUSEMOVE:  //�������� �������
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
    case WM_RBUTTONUP: //�������
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


