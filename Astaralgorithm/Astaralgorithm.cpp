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

// >> : 0727
#define MAX_LOADSTRING 100
#define PI 3.141592
#define degreeToRadian(degree) ((degree) *PI / 180)
void aroundDraw(HDC hdc, POINT startNums, POINT endPoint, HBRUSH hBrush, HBRUSH oldBrush, priority_queue<PQNode, vector<PQNode>, greater<PQNode>>  Fvalue);
// << : 0727

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
void DrawMapAndFillStartEnd(HDC hdc, POINT rectPoint, POINT Start, POINT drawStart, POINT End, POINT drawEnd, int value, priority_queue<PQNode, vector<PQNode>, greater<PQNode>>  Fvalue);
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
    static priority_queue<int, vector<int>, greater<int>>  Fvalue;

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
            
            /*hBrush = CreateSolidBrush(RGB(255, 255, 255));
            oldBrush = (HBRUSH)SelectObject(hdc, hBrush);*/

            DrawMapAndFillStartEnd(hdc, rectPoint, Start, drawStart, End, drawEnd, value,Fvalue);

            /*value = 10;
            wsprintf(str, TEXT("%d"), value);
            TextOut(hdc, 75, 75, str, lstrlen(str));*/
            //InvalidateRect(hWnd, NULL, false);//새 이벤트 불러오기

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



void DrawMapAndFillStartEnd(HDC hdc, POINT rectPoint, POINT Start, POINT drawStart, POINT End, POINT drawEnd, int value, priority_queue<PQNode, vector<PQNode>, greater<PQNode>>  Fvalue)
{
    static bool startOK = false;
    static bool endOK = false;

    HBRUSH hBrush = CreateSolidBrush(RGB(255, 255, 255));
    HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, hBrush);

    for (int j = 0; j < 5; j++)
    {
        for (int i = 0; i < 5; i++)
        {
            DrawRectangle(hdc, rectPoint);
            rectPoint.x += 81;
            
            if (InRect(rectPoint, Start))
            {
                cout << "스타트";
                drawStart = rectPoint;
                startOK = true;
            }
            if (InRect(rectPoint, End))
            {
                cout << "엔드";
                drawEnd = rectPoint;
                endOK = true;
            }
        }
        rectPoint.x = 100;
        rectPoint.y += 80;
    }

    if (startOK) //start 그리기.
    {
        hBrush = CreateSolidBrush(RGB(0, 051, 153));
        oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
        DrawRectangle(hdc, drawStart);
        SetTextAlign(hdc, TA_CENTER);
        TextOut(hdc, drawStart.x, drawStart.y - 10, TEXT("S"), 1);
        SelectObject(hdc, oldBrush);
        DeleteObject(hBrush);
    }
    
    if (endOK) //end 그리기.
    {
        hBrush = CreateSolidBrush(RGB(153, 0, 0));
        oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
        DrawRectangle(hdc, drawEnd);
        SetTextAlign(hdc, TA_CENTER);
        TextOut(hdc, drawEnd.x, drawEnd.y - 10, TEXT("E"), 1);
        SelectObject(hdc, oldBrush);
        DeleteObject(hBrush);
    }

    if (startOK == true && endOK == true)
    {
        //주변 초록. 0727
        aroundDraw(hdc, drawStart, drawEnd, hBrush, oldBrush,Fvalue);
    }
   
}

double LengthPts(POINT rect, POINT startorend)
{
    /*startorend.x = (startorend.x - 60) / 80;
    startorend.y = (startorend.y - 60) / 80;
    return*/ 
    return(sqrt((float)(startorend.x - rect.x) * (startorend.x - rect.x) + (startorend.y - rect.y) * (startorend.y - rect.y)));
}

bool InRect(POINT rect, POINT startorend)
{
    if (LengthPts(rect, startorend) < 40)
        return true;
    else
        return false;
}

struct PQNode
{
    POINT idx;//uPos

    int Gvalue;
    int Fvalue;
};

void aroundDraw(POINT startNums, POINT endPoint)
{
    priority_queue<PQNode, vector<PQNode>, greater<PQNode>>  pq;
    vector<vector<int> > best(5, vector<int>(5, INT32_MAX)); // 5x5 5칸 만들고, 그 안을 vector<int>(5,0)으로 채운다  vector<int>(5,0) : vector를 5칸 만들고, 그 안을 0으로 채운다.
    //INT32_MAX 인트가 가질 수 있는 최대값. 처음 넣었을때 비교할 값을 넣어주기 위해.

    vector<vector<bool> > close(5, vector<bool>(5, false));

    POINT around[] =
    {   
        {0, -1},    // UP
        {0,1},      // DOWN
        {1,0},      // RIGHT
        {-1,0},     // LEFT
        {1,-1},     // RIGHT UP
        {-1,-1},    // LEFT UP
        {1,1},      // RIGHT DOWN
        {-1,1}      // LEFT DOWN
    };

    int cost[] = //G값에 더해주는
    {
        10,
        10,
        10,
        10,
        14,
        14,
        14,
        14,
    };

    enum Dir
    {
         UP,
         DOWN,
         RIGHT,
         LEFT,
         RIGHTUP,
         LEFTUP,
         RIGHTDOWN,
         LEFTDOWN,
         END,
    };

    POINT start = { startNums.x,startNums.y };
    POINT dest = { endPoint.x,endPoint.y };

    int Hvalue = 10 * abs(start.x - dest.x) + 10 * abs(start.y - dest.y);
    int Gvalue = 0;
    int Fvalue = Hvalue + Gvalue;

    PQNode node = { startNums, Gvalue, Fvalue };


    map<POINT, POINT> parent; //어디서 왔는지.
    parent[start] = start; //초기화, (parent의 parent는 자기자신.)

    pq.push(node); // 초기화.

    while (pq.empty()!=true)
    {

    }


    struct Node
    {
        POINT point[9] = {};
        int G[9] = { 0 };
        int H[9] = { 0 };
        int F[9] = { 0 };
    };

    while (!Fvalue.empty()) //Fvalue 비우기. 0727
    {
        Fvalue.pop();
    }

    Node Astar;
    TCHAR str[128];
    double angle = 360 / 8;
    angle = degreeToRadian(angle);
    POINT point[9] = {};
    POINT maxF;

    for (int i = 0; i < 8; i++)
    {
        if (i % 2 == 0)
        {
            Astar.G[i] += 10;

            Astar.point[i].x = startNums.x + 80 * sin(angle * i);
            Astar.point[i].y = startNums.y + 80 * cos(angle * i);

            if (((abs(-(Astar.point[i].x - endPoint.x)) / 79) == (abs(-(Astar.point[i].y - endPoint.y)) / 80)))
            {
                Astar.H[i] += 14 * (abs(-(Astar.point[i].x - endPoint.x)) / 79);
            }

            if (((abs(-(Astar.point[i].x - endPoint.x)) / 79) > (abs(-(Astar.point[i].y - endPoint.y)) / 80)))
            {
                Astar.H[i] += 14 * (abs(-(Astar.point[i].y - endPoint.y)) / 80);

                Astar.H[i] += 10 * ((abs(-(Astar.point[i].x - endPoint.x)) / 79) - (abs(-(Astar.point[i].y - endPoint.y)) / 80));
            }

            if (((abs(-(Astar.point[i].x - endPoint.x)) / 79) < (abs(-(Astar.point[i].y - endPoint.y)) / 80)))
            {
                Astar.H[i] += 14 * (abs(-(Astar.point[i].x - endPoint.x)) / 79);

                Astar.H[i] += 10 * ((abs(-(Astar.point[i].y - endPoint.y)) / 80) - (abs(-(Astar.point[i].x - endPoint.x)) / 79));

                //std::cout << Astar.point[i].x << "," << Astar.point[i].y;
            }

            Astar.F[i] = Astar.G[i] + Astar.H[i];

            Fvalue.push(Astar.F[i]);

            /*Astar.H[i] += 10 * (abs(Astar.point[i].x - endPoint.x) / 80) ;
            Astar.H[i] += 14 * (abs(Astar.point[i].y - endPoint.y) / 80) ;*/

            /*hBrush = CreateSolidBrush(RGB(0, 153, 0));
            oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
            DrawRectangle(hdc, Astar.point[i]);*/
            
            //TextOut(hdc, Astar->point[i].x, Astar->point[i].y - 10, TEXT("test"), 4);
            SetTextAlign(hdc, TA_CENTER);
            wsprintf(str, TEXT("%d"), Astar.G[i]);
            TextOut(hdc, Astar.point[i].x - 15, Astar.point[i].y - 20, str, lstrlen(str));

            SetTextAlign(hdc, TA_CENTER);
            wsprintf(str, TEXT("%d"), Astar.H[i]);
            TextOut(hdc, Astar.point[i].x + 15, Astar.point[i].y - 20, str, lstrlen(str));

            SetTextAlign(hdc, TA_CENTER);
            wsprintf(str, TEXT("%d"), Astar.F[i]);
            TextOut(hdc, Astar.point[i].x, Astar.point[i].y + 20, str, lstrlen(str));

            //SelectObject(hdc, oldBrush);
           // DeleteObject(hBrush);

        }

        if (i % 2 == 1)
        {
            Astar.G[i] += 14;

            Astar.point[i].x = startNums.x + sqrt(pow(80, 2)+ pow(80, 2)) * sin(angle * i);
            Astar.point[i].y = startNums.y + sqrt(pow(80, 2) + pow(80, 2)) * cos(angle * i);

            if (((abs(-(Astar.point[i].x - endPoint.x)) / 79) == (abs(-(Astar.point[i].y - endPoint.y)) / 80)))
            {
                Astar.H[i] += 14 * (abs(-(Astar.point[i].x - endPoint.x)) / 79);
            }

            if (((abs(-(Astar.point[i].x - endPoint.x)) / 79) > (abs(-(Astar.point[i].y - endPoint.y)) / 80)))
            {
                Astar.H[i] += 14 * (abs(-(Astar.point[i].y - endPoint.y)) / 80);

                Astar.H[i] += 10 * ((abs(-(Astar.point[i].x - endPoint.x)) / 79) - (abs(-(Astar.point[i].y - endPoint.y)) / 80));
            }

            if (((abs(-(Astar.point[i].x - endPoint.x)) / 79) < (abs(-(Astar.point[i].y - endPoint.y)) / 80)))
            {
                Astar.H[i] += 14 * (abs(-(Astar.point[i].x - endPoint.x)) / 79);

                Astar.H[i] += 10 * ((abs(-(Astar.point[i].y - endPoint.y)) / 80) - (abs(-(Astar.point[i].x - endPoint.x)) / 79));

                std::cout << Astar.point[i].x << "," << Astar.point[i].y;
            }

            Astar.F[i] = Astar.G[i] + Astar.H[i];
            Fvalue.push(Astar.F[i]);

           /* hBrush = CreateSolidBrush(RGB(0, 153, 0));
            oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
            DrawRectangle(hdc, Astar.point[i]);*/

            SetTextAlign(hdc, TA_CENTER);
            wsprintf(str, TEXT("%d"), Astar.G[i]);
            TextOut(hdc, Astar.point[i].x - 15, Astar.point[i].y - 20, str, lstrlen(str));

            SetTextAlign(hdc, TA_CENTER);
            wsprintf(str, TEXT("%d"), Astar.H[i]);
            TextOut(hdc, Astar.point[i].x + 15, Astar.point[i].y - 20, str, lstrlen(str));

            SetTextAlign(hdc, TA_CENTER);
            wsprintf(str, TEXT("%d"), Astar.F[i]);
            TextOut(hdc, Astar.point[i].x, Astar.point[i].y + 20, str, lstrlen(str));

            SelectObject(hdc, oldBrush);
            DeleteObject(hBrush);
        }
    }

    for (int i = 0; i < 8; i++)
    {
        if (Astar.F[i] == Fvalue.top())
        {
            if (Astar.point[i].x + 1 == endPoint.x)
            {
                if (Astar.point[i].y == endPoint.y)
                {
                    cout << "stop";

                    break;
                }
            }

            maxF = Astar.point[i];
            Sleep(1000);

            hBrush = CreateSolidBrush(RGB(0, 153, 0));
            oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
            DrawRectangle(hdc, Astar.point[i]);
            SelectObject(hdc, oldBrush);
            DeleteObject(hBrush);

            aroundDraw(hdc, maxF, endPoint, hBrush, oldBrush, Fvalue);

            /*SetTextAlign(hdc, TA_CENTER);
            wsprintf(str, TEXT("%d"), Astar.G[i]);
            TextOut(hdc, Astar.point[i].x - 15, Astar.point[i].y - 20, str, lstrlen(str));

            SetTextAlign(hdc, TA_CENTER);
            wsprintf(str, TEXT("%d"), Astar.H[i]);
            TextOut(hdc, Astar.point[i].x + 15, Astar.point[i].y - 20, str, lstrlen(str));

            SetTextAlign(hdc, TA_CENTER);
            wsprintf(str, TEXT("%d"), Astar.F[i]);
            TextOut(hdc, Astar.point[i].x, Astar.point[i].y + 20, str, lstrlen(str));*/

            
        }
    }

}

