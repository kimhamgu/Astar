// Astaralgorithm.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "Astaralgorithm.h"
#include <vector>
#include <iostream>
#include <queue>
#include <map>
#include <list>
#include <windows.h>

using namespace std;

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

#pragma region 구글
//static POINT myPosition;
//
//struct Node
//{
//    POINT currentLocation; // 현재 위치
//    POINT prevLocation; // 이전 위치
//};
//
//struct Heuristic
//{
//    int movingDist; // 현재까지 이동한 거리
//    float predictionDist; // 휴리스틱 가중치(노드와 도착지간의 직선거리)
//};
//
////이진트리에서 검색할때 사용하는 용도
//bool operator < (const POINT& lhs, const POINT& rhs)
//{
//    if (lhs.x == rhs.x)
//        return lhs.y < rhs.y;
//
//    return lhs.x < rhs.x;
//}
//
////우선순위큐에서 heap구조를 만들 때 Node정보는 무시하게 하는 용도로 연산자오버로딩
//bool operator < (const Node& lhs, const Node& rhs)
//{
//    return false;
//}
//
////우선 순위큐에서 가장 짧은 경로가 될 노드임을 판단하기 위해서
//// 현재까지 이동한 거리 + 휴리스틱 가중치 값이 가장 작은것이 루트노드가 되게한다.
//bool operator < (const Heuristic& lhs, const Heuristic& rhs)
//{
//    return (lhs.movingDist + lhs.predictionDist) < (rhs.movingDist + rhs.predictionDist);
//}
//
////도착지점 x,y 좌표를 매개변수로 받는다.
//vector<POINT> Astar(int targetX, int targetY)
//{
//    //최종적으로 이동할 경로를 저장하는 곳.
//    vector<POINT> resutPath;
//
//    //priority_queue<int, vector<int>, greater<int>> pq; 이것처럼 작성된 것.
//    // 작은 값부터 앞에 있다.
//    //openQ : 가능성 있는 노드를 찾는다. (휴리스틱 가중치 기준으로 정렬돼있음)
//    priority_queue<pair<Heuristic, Node>, vector<pair<Heuristic, Node>>, greater<
//        pair<Heuristic, Node>>> openQ;
//
//    //closeQ : 탐색 경로에서 이전에 방문한 적 있는 노드들을 저장해둠. 
//    //<key, value> key값 찾기.
//    map<POINT, POINT> closeQ; // key: 현재위치, value: 이전 위치
//
//    // 큐에 내 위치를 넣고 시작한다.
//    // Heuristic과 Node를 한쌍으로 묶어서 관리.
//    pair<Heuristic, Node> first;
//
//    first.second.currentLocation = { myPosition.x,myPosition.y }; // =Node.currentLocation.
//    first.second.prevLocation = { -1,-1 };
//    first.first.movingDist = 0; // 현재까지 이동한 거리.
//    first.first.predictionDist = -1;
//
//    openQ.push(first);
//
//    //AStarAlgorithmCount: BFS탐색과 비교하기 위해서 최종 경로를 찾을때까지 
//    //루프반복한 횟수를 측정한다.
//    int AStarAlgorithmCount = 0;
//
//    //가능성있는 노드가 있을때동안 반복한다.
//    while (!openQ.empty())
//    {
//        AStarAlgorithmCount++;
//
//        Node currentNode = openQ.top().second;
//        Heuristic currentHeuristic = openQ.top().first;
//        openQ.pop();
//
//        if (closeQ.find(currentNode.currentLocation) != closeQ.end())
//            continue;
//
//        closeQ.insert({ currentNode.currentLocation,
//                        currentNode.prevLocation });
//
//        int x = currentNode.currentLocation.x;
//        int y = currentNode.currentLocation.y;
//
//        //목적지에 도착했을때 반복문 중지.
//        if (x == targetX && y == targetY)
//            break;
//
//        for (int i = 0; i < 4; i++)
//        {
//            int nextY = y + dy[i];
//        }
//    }
//
//}
#pragma endregion

// >> : 0726
void DrawRectangle(HDC hdc, POINT point);
double LengthPts(POINT rect, POINT startorend);
bool InRect(POINT rect, POINT startorend);
void DrawMapAndFillStartEnd(HDC hdc, POINT rectPoint, POINT Start, POINT drawStart, POINT End, POINT drawEnd, HBRUSH hBrush, HBRUSH oldBrush, int value);
// << : 0726

#ifdef UNICODE

#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console") 

#else

#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console") 

#endif

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_ASTARALGORITHM, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_ASTARALGORITHM));

    MSG msg;

    // 기본 메시지 루프입니다:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}

//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ASTARALGORITHM));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_ASTARALGORITHM);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    HBRUSH hBrush, oldBrush;
    static POINT Start, End; // 마우스로 시작점 끝점 저장할
    static bool startCheck = false; // 스타트 찍고 엔드 점 찍으려고 체크.
    static bool endCheck = false; // 스타트 찍고 엔드 점 찍으려고 체크.
    static bool StartisInside = false;
    static bool EndisInside = false;
    static POINT rectPoint;
    static POINT drawStart;
    static POINT drawEnd;
    static int value;

    switch (message)
    {
    case WM_LBUTTONDOWN:
        {
            if (!startCheck) // 첫번째 마우스 클릭.
            {
                Start.x = LOWORD(lParam);
                Start.y = HIWORD(lParam);

                startCheck = true;
            }
            else
            {
                if (!endCheck) // 두번째 마우스 클릭까지만. 3번째 클릭부터의 좌표는 안 들어감.
                {
                    End.x = LOWORD(lParam);
                    End.y = HIWORD(lParam);

                    endCheck = true;
                }
            }

            cout << "start : " << Start.x << ", " << Start.y << endl;
            cout << "end : " << End.x << ", " << End.y << endl;
            InvalidateRect(hWnd, NULL, true);//새 이벤트 불러오기

        }
        break;

    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            rectPoint = { 100,100 };
            TCHAR str[3];
            // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
            
            hBrush = CreateSolidBrush(RGB(255, 255, 255));
            oldBrush = (HBRUSH)SelectObject(hdc, hBrush);

            DrawMapAndFillStartEnd(hdc, rectPoint, Start, drawStart, End, drawEnd, hBrush, oldBrush, value);

            value = 10;
            wsprintf(str, TEXT("%d"), value);
            TextOut(hdc, 75, 75, str, lstrlen(str));

            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

void DrawRectangle(HDC hdc, POINT point)
{
    Rectangle(hdc, point.x - 40, point.y - 40, point.x + 40, point.y + 40);
}

void DrawMapAndFillStartEnd(HDC hdc, POINT rectPoint, POINT Start, POINT drawStart, POINT End, POINT drawEnd, HBRUSH hBrush, HBRUSH oldBrush, int value)
{
    for (int j = 0; j < 5; j++)
    {
        for (int i = 0; i < 5; i++)
        {
            DrawRectangle(hdc, rectPoint);
            rectPoint.x += 79;
            
            if (InRect(rectPoint, Start))
            {
                cout << "스타트";

                drawStart = rectPoint;
            }
            if (InRect(rectPoint, End))
            {
                cout << "엔드";

                drawEnd = rectPoint;
            }
        }
        rectPoint.x = 100;
        rectPoint.y += 79;
    }

    hBrush = CreateSolidBrush(RGB(0, 051, 153));
    oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
    DrawRectangle(hdc, drawStart);
    SelectObject(hdc, oldBrush);
    DeleteObject(hBrush);

    hBrush = CreateSolidBrush(RGB(153, 0, 0));
    oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
    DrawRectangle(hdc, drawEnd);
    SelectObject(hdc, oldBrush);
    DeleteObject(hBrush);
}

double LengthPts(POINT rect, POINT startorend)
{
    return(sqrt((float)(startorend.x - rect.x) * (startorend.x - rect.x) + (startorend.y - rect.y) * (startorend.y - rect.y)));
}

bool InRect(POINT rect, POINT startorend)
{
    if (LengthPts(rect, startorend) < 40)
        return true;
    else
        return false;
}