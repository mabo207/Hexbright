#include"DxLib.h"
#include"GraphicControl.h"
#include"input.h"
#include"ToolsLib.h"

#include"Title.h"
#include<memory>
#include"PuzzleSystem.h"

int WINAPI WinMain(HINSTANCE,HINSTANCE,LPSTR,int){
	//dxライブラリの初期化
	//画面モードの設定(一応こんな感じ)
	SetGraphMode((int)PuzzleSystem::aPuzzleSize.x,(int)PuzzleSystem::aPuzzleSize.y,16);
	//タイトルメニュー文字
	SetMainWindowText("Hexbright");
	//ウインドウサイズの変更
	SetWindowSizeExtendRate(1.0);
	//ウインドウサイズの変更をできるようにする
	SetWindowSizeChangeEnableFlag(TRUE);
	//アイコンの設定
	SetWindowIconID(101);

	if(ChangeWindowMode(TRUE) != 0) {
		return 0;
	}
	if(DxLib_Init() != 0) {
		return 0;
	}
	if(SetDrawScreen(DX_SCREEN_BACK) != 0) {
		DxLib_End();
		return 0;
	}

	//入力機構の初期化
	InitInputControler();

	
	std::shared_ptr<Title> title(new Title());
	SRand(123456);
	
	//アプリケーション動作
	while(ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0) {
		//ゲーム本体
		//キー情報更新
		input_update();
		//描画
		title->Draw();
		//計算処理
		int index=title->Calculate();
		//終了検出
		if(index<0 || keyboard_get(KEY_INPUT_ESCAPE)>0){
			break;
		}
	}

	//終了処理
	DeleteInputControler();//入力機構の解放

	DxLib_End();

	return 0;
}
