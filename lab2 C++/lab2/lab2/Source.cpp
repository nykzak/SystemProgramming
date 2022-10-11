#include <windows.h> 


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
    wc.hCursor = LoadCursor(NULL, IDC_ARROW); // ���������� �������
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