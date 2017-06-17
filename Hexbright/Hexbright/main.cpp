#include"DxLib.h"
#include"GraphicControl.h"
#include"input.h"
#include"ToolsLib.h"

#include"Hexagon.h"

int WINAPI WinMain(HINSTANCE,HINSTANCE,LPSTR,int){
	//dxライブラリの初期化
	//画面モードの設定
	SetGraphMode(800,600,16);
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

	Vector2D c=Vector2D(400,300),r=Vector2D(-40,0);
	Hexagon bh(c,Hexagon(c+r,r).GetPoints().GetPoint(5)-c);

	Hexagon h[7]={
		Hexagon(bh.GetPoints().GetPoint(0),r)
		,Hexagon(bh.GetPoints().GetPoint(1),r)
		,Hexagon(bh.GetPoints().GetPoint(5),r)
		,Hexagon(c,r)
		,Hexagon(bh.GetPoints().GetPoint(2),r)
		,Hexagon(bh.GetPoints().GetPoint(4),r)
		,Hexagon(bh.GetPoints().GetPoint(3),r)
	};

	unsigned int col[7]={
		GetColor(255,0,0)
		,GetColor(255,255,0)
		,GetColor(0,255,0)
		,GetColor(0,255,255)
		,GetColor(0,0,255)
		,GetColor(255,0,255)
		,GetColor(255,255,255)
	};

	//アプリケーション動作
	while(ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0) {
		//ゲーム本体
		//キー情報更新
		input_update();
		//描画
		int flag=FALSE;
		if(keyboard_get(KEY_INPUT_NUMPADENTER)>0){
			flag=TRUE;
		}
		for(int i=0;i<7;i++){
			h[i].Draw(col[i],flag);
		}
		//計算処理
		int index=-keyboard_get(KEY_INPUT_BACK);
		//終了検出
		if(index<0){
			break;
		}
	}

	//終了処理
	DeleteInputControler();//入力機構の解放

	DxLib_End();

	return 0;
}
