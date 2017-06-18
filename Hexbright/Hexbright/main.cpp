#include"DxLib.h"
#include"GraphicControl.h"
#include"input.h"
#include"ToolsLib.h"

#include<time.h>
#include"NormalBlock.h"
#include"Stage.h"
#include"PuzzleSystem.h"

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

	Vector2D c=Vector2D(400,300),r=Vector2D(0,-40);
	Hexagon bh(c,Hexagon(c+r,r).GetPoints().GetPoint(5)-c);

	unsigned int col[7]={
		GetColor(255,0,0)
		,GetColor(255,255,0)
		,GetColor(0,255,0)
		,GetColor(0,255,255)
		,GetColor(0,0,255)
		,GetColor(255,0,255)
		,GetColor(255,255,255)
	};

	Hexagon h[7]={
		Hexagon(bh.GetPoints().GetPoint(0),r)
		,Hexagon(bh.GetPoints().GetPoint(1),r)
		,Hexagon(bh.GetPoints().GetPoint(5),r)
		,Hexagon(c,r)
		,Hexagon(bh.GetPoints().GetPoint(2),r)
		,Hexagon(bh.GetPoints().GetPoint(4),r)
		,Hexagon(bh.GetPoints().GetPoint(3),r)
	};
	
	std::vector<std::shared_ptr<Block>> b={
		std::shared_ptr<Block>(new NormalBlock(bh.GetPoints().GetPoint(0),std::vector<Block::Conductor>{Block::Conductor(1,2)}))
		,std::shared_ptr<Block>(new NormalBlock(bh.GetPoints().GetPoint(1),std::vector<Block::Conductor>{Block::Conductor(4,2)}))
		,std::shared_ptr<Block>(new NormalBlock(bh.GetPoints().GetPoint(5),std::vector<Block::Conductor>{Block::Conductor(0,1),Block::Conductor(2,3)}))
		,std::shared_ptr<Block>(new NormalBlock(c,std::vector<Block::Conductor>{Block::Conductor(0,5),Block::Conductor(1,2),Block::Conductor(3,4)}))
		,std::shared_ptr<Block>(new NormalBlock(bh.GetPoints().GetPoint(2),std::vector<Block::Conductor>{Block::Conductor(3,4)}))
		,std::shared_ptr<Block>(new NormalBlock(bh.GetPoints().GetPoint(4),std::vector<Block::Conductor>{Block::Conductor(0,5),Block::Conductor(1,4),Block::Conductor(2,3)}))
		,std::shared_ptr<Block>(new NormalBlock(bh.GetPoints().GetPoint(3),std::vector<Block::Conductor>{Block::Conductor(2,4),Block::Conductor(1,5)}))
	};

	
	Stage st(4);

	PuzzleSystem puzzle;
	SRand(123456);
	
	//アプリケーション動作
	while(ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0) {
		//ゲーム本体
		//キー情報更新
		input_update();
		//描画
		puzzle.Draw();
		puzzle.Update();
		//計算処理
		int index=-keyboard_get(KEY_INPUT_ESCAPE);
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
