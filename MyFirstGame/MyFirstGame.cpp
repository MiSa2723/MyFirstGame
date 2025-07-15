// MyFirstGame.cpp : アプリケーションのエントリ ポイントを定義します。
//

#include "framework.h"
#include "MyFirstGame.h"
#include "Direct3D.h"
#include "Quad.h"
#include "Camera.h"
#include "Dice.h"

//HWND hWnd = nullptr;


#define MAX_LOADSTRING 100

const wchar_t* WIN_CLASS_NAME = L"SAMPLE GAME WINDOW";
const int WINDOW_WIDTH = 800;  //ウィンドウの幅
const int WINDOW_HEIGHT = 600; //ウィンドウの高さ   //SVGAサイズ

// グローバル変数:
HINSTANCE hInst;                                // 現在のインターフェイス
WCHAR szTitle[MAX_LOADSTRING];                  // タイトル バーのテキスト
WCHAR szWindowClass[MAX_LOADSTRING];            // メイン ウィンドウ クラス名

// このコード モジュールに含まれる関数の宣言を転送します:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

/*・hInstance：
アプリケーションのインスタンスハンドルを表す。
この値は、Windowsがアプリケーションを識別するために使用するもので、実行中のアプリケーションごとに異なる値が割り当てられる。
 
・hPrevInstance：
以前のインスタンスのハンドルを表す。16bit Windowsの互換性のために残されているが、現在のWindowsでは常にNULLが渡される。

・lpCmdLine：
コマンドライン引数の文字列へのポインタ。
この文字列を解析することで、アプリケーション起動時に指定されたオプションなどを取得できる。
 
・nCmdShow：
アプリケーションの表示状態を表す整数値。初期表示状態（最大化、最小化、通常表示など）を指示する。﻿
*/
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: ここにコードを挿入してください。

    // グローバル文字列を初期化する
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_MYFIRSTGAME, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // アプリケーション初期化の実行:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }
}



//
//  関数: MyRegisterClass()
//
//  目的: ウィンドウ クラスを登録します。
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;          //ウィンドウの動作スタイル（例：再描画のタイミングなど）
    wcex.lpfnWndProc    = WndProc;                          //ウィンドウメッセージを処理する関数
    wcex.cbClsExtra     = 0;                                //クラスに追加するメモリサイズ（通常は0）
    wcex.cbWndExtra     = 0;                                //ウィンドウに追加するメモリサイズ（通常は0）
    wcex.hInstance      = hInstance;                        //実行中のアプリケーションのインスタンスハンドル
    wcex.hIcon          = LoadIcon(NULL, IDI_APPLICATION);  //ウィンドウのアイコン
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);   //ウィンドウで使うカーソル
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW-1);         //ウィンドウの背景色
    wcex.lpszMenuName   = NULL;                             //メニューリソースの名前
    wcex.lpszClassName  = szWindowClass;                    //ウィンドウクラスの名前
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL)); //タスクバーやAlt+Tabのスイッチャーなどに表示される小さいアイコンを指定

    return RegisterClassExW(&wcex);
}

//
//   関数: InitInstance(HINSTANCE, int)
//
//   目的: インスタンス ハンドルを保存して、メイン ウィンドウを作成します
//
//   コメント:
//
//        この関数で、グローバル変数でインスタンス ハンドルを保存し、
//        メイン プログラム ウィンドウを作成および表示します。
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // グローバル変数にインスタンス ハンドルを格納する

   //ウィンドウサイズの計算
   RECT winRect = { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT };
   AdjustWindowRect(&winRect, WS_OVERLAPPEDWINDOW, FALSE);
   int winW = winRect.right - winRect.left;     //ウィンドウ幅
   int winH = winRect.bottom - winRect.top;     //ウィンドウ高さ

   HWND hWnd = CreateWindowW(szWindowClass, WIN_CLASS_NAME, WS_OVERLAPPEDWINDOW,
       CW_USEDEFAULT, 0, winW, winH, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);

   //Direct3D初期化
   HRESULT hr;
   hr = Direct3D::Initialize(WINDOW_WIDTH, WINDOW_HEIGHT, hWnd);
   if (FAILED(hr))
   {
       return 0;
   }

   HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MYFIRSTGAME));

   MSG msg;
   ZeroMemory(&msg, sizeof(msg));
   Camera::Initialize();

   /*Quad* q = new Quad();
   hr = q->Initialize();*/

   Dice* dice = new Dice();
   hr = dice->Initialize();

   if (FAILED(hr))
   {
       return 0;
   }

   // メイン メッセージ ループ:
   while (msg.message != WM_QUIT)
   {
       //メッセージあり
       if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
       {
           TranslateMessage(&msg);
           DispatchMessage(&msg);

       }
       //メッセージなし
       else
       {
           //ゲームの処理
           Camera::Update();
           Direct3D::BeginDraw();

           //描画処理
           static float angle = 0.0f;
           XMMATRIX mat = XMMatrixRotationY(XMConvertToRadians(angle));
           //q->Draw(mat);
           dice->Draw(mat);
           angle += 0.05f;

           Direct3D::EndDraw();
       }
   }

   /*q->Release();
   SAFE_DELETE(q);*/

   dice->Release();
   SAFE_DELETE(dice);

   Direct3D::Release();

   return (int)msg.wParam;

   /*〇メッセージループの仕組み
       1. メッセージの生成:
       ユーザーのクリック、キー入力、ウィンドウの移動など、何らかのイベントが発生すると、
       Windowsはそれに対応するメッセージを生成する。

       2. メッセージキューへの格納 :
       生成されたメッセージは、メッセージキューと呼ばれる、メッセージを格納する場所に追加される。
       各ウィンドウには専用のメッセージキューがある。

       3. メッセージの取得 :
       アプリケーションは、GetMessage関数を呼び出すことで、メッセージキューからメッセージを取得する。﻿

       4. メッセージのディスパッチ :
       取得したメッセージは、DispatchMessage関数によって、対応するウィンドウプロシージャにディスパッチされる。﻿

       5. ウィンドウプロシージャでの処理 :
       ウィンドウプロシージャは、メッセージの内容に基づいて、適切な処理を行う。
       例えば、ボタンがクリックされたメッセージであれば、ボタンのクリック処理を実行する。

       6. メッセージループの継続 :
       これらの処理が、アプリケーションが終了するまで繰り返される。

       ・メッセージループの役割
       イベント駆動型処理 :
       Windowsアプリケーションは、イベント駆動型で動作する。
       メッセージループは、イベント（メッセージ）が発生するたびに、対応する処理を実行するための仕組み。

       非同期処理 :
       メッセージキューを使用することで、メッセージの送信と処理を非同期に行うことができる。
       これにより、アプリケーションは、メッセージの到着を待たずに他の処理を継続できる。

       マルチタスクの実現 :
       複数のウィンドウを持つアプリケーションは、それぞれのウィンドウに対応するメッセージキューを持ち、
       メッセージループを介して処理を行う。これにより、複数のウィンドウを同時に操作することが可能になる。
   */

   UpdateWindow(hWnd);

   return TRUE;
}

//
//  関数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目的: メイン ウィンドウのメッセージを処理します。
//
//  WM_COMMAND  - アプリケーション メニューの処理
//  WM_PAINT    - メイン ウィンドウを描画する
//  WM_DESTROY  - 中止メッセージを表示して戻る
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 選択されたメニューの解析:
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
            // TODO: HDC を使用する描画コードをここに追加してください...
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

    /*〇コールバックの仕組み
        1. 親関数の定義:
        コールバック関数を引数として受け取る関数を定義する。
        この関数は、コールバック関数を呼び出すタイミングや条件を決定する。

        2. コールバック関数の定義 :
        実行したい処理を記述した関数を定義する。この関数は、親関数によって特定のタイミングで呼び出される。

        3. コールバック関数の登録 :
        親関数を呼び出す際に、引数としてコールバック関数を渡す。
        これにより、親関数はコールバック関数を認識し、適切なタイミングで呼び出すことができる。

        4. コールバックの実行 :
        親関数が実行され、定義されたタイミングでコールバック関数が呼び出される。
        この時、親関数からコールバック関数に必要な情報が渡されることもある。﻿

        〇メッセージループとコールバックの関係
        この2つは、GUIアプリケーションの動作において密接に関連している。
        メッセージループは、メッセージの取得とディスパッチを担当し、
        コールバック（特にウィンドウプロシージャ）は、実際にメッセージを処理する役割を担う。﻿
        具体的には、メッセージループがメッセージを検出し、それをウィンドウプロシージャに渡すことで、
        ユーザーインターフェースの更新やイベント処理が実現される。﻿
        つまり、メッセージループは「受け渡し役」、コールバック（ウィンドウプロシージャ）は「処理役」として、
        互いに連携してGUIアプリケーションの動作を支えている。
        */
}

// バージョン情報ボックスのメッセージ ハンドラーです。
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

//どこに書けばいいかわからなかった③
/*③CreateWindowEXの引数と戻り値の意味
〇引数
・dwExStyle：
ウィンドウの拡張スタイルを指定する。例えば、透過性やトップmost（常に最前面に表示）などを設定できる。

・lpClassName：
ウィンドウクラスの名前を指定する。これは、事前にRegisterClassEx関数で登録されたウィンドウクラス。

・lpWindowName：
ウィンドウのタイトルバーに表示されるテキストを指定する。

・dwStyle：
ウィンドウの標準的なスタイルを指定します。例えば、WS_OVERLAPPEDWINDOW、WS_CHILD、WS_VISIBLEなどがある。

・x, y：
ウィンドウの初期位置（左上隅の座標）をピクセル単位で指定する。

・nWidth, nHeight：
ウィンドウの初期サイズ（幅と高さ）をピクセル単位で指定する。

・hWndParent：
ウィンドウの親ウィンドウのハンドルを指定する。子ウィンドウを作成する場合に使用する。

・hMenu：
メニューのハンドルを指定する。通常はNULLを指定する。

・hInstance：
インスタンスハンドルを指定する。通常はアプリケーションのインスタンスハンドルを指定する。

・lpParam：
ウィンドウ作成時に渡される追加のパラメータを指定する。通常はNULLを指定する。

〇戻り値
CreateWindowEX関数は、ウィンドウの作成に成功した場合、作成されたウィンドウのハンドル（HWND）を返す。
ウィンドウの作成に失敗した場合は、NULLを返す。
*/