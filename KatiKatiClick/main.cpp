#include "DxLib.h"
#include "SceneFile/AbstractScene.h"
#include "SceneFile/SceneManager.h"
#include "SceneFile/TitleScene.h"
#include "SceneFile/ResultScene.h"
#include "UtilityFile/FPS.h"
#include "UtilityFile/MouseInput.h"
#include "UtilityFile/Define.h"

// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int
	nCmdShow)
{
	// ウィンドウのタイトルを"KatiKatiDefense"に変更
	SetMainWindowText("KatiKatiDefense");
	ChangeWindowMode(TRUE);

	SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32);	//画面サイズ指定

	//アイコンの設定
	SetWindowIconID(101);


	if (DxLib_Init() == -1) return -1;	// DXライブラリの初期化処理
	//SetBackgroundColor(119, 136, 153);

	SetDrawScreen(DX_SCREEN_BACK);	// 描画先画面を裏にする
	SetMouseDispFlag(FALSE);		// マウスカーソル非表示

	SceneManager SceneManager(dynamic_cast<AbstractScene*>(new TitleScene()));
	FPS fp;
	//ループ前にFPS計測を初期化
	fp.Reset_FPS();

	//ゲームループ
	while (ProcessMessage() != -1)
	{
		//fps固定
		fp.FPSUpdate();
		//入力更新処理
		MouseInput::Update();
		SceneManager.Update();
		SceneManager.Draw();

		if (SceneManager.Change() == nullptr) {
			break;
		}

	}

	DxLib_End(); // DXライブラリ使用の終了処理

	return 0; // ソフトの終了

}