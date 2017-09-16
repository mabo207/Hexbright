#ifndef DEF_VGAMESYSTEM_H

#include"ToolsLib.h"

//ゲーム全体を管理したり、ゲームの背景を描画したりするシステム
//タイムアタックか対戦かで変わるので基底クラスを設ける
class VGameSystem{
	//型・列挙体

	//定数

	//変数
protected:
	Timer m_timer;//タイマー
	//int m_flame;//経過時間
	const int m_maxflame;//試合時間

	//フォント等
	int m_timeFont;//残り時間を描画するフォント

	//関数
protected:
	//int CalLeftSecond()const;//残り時間(秒)を計算する関数
	//bool JudgeGameEnd()const;//試合終了を判定する関数

public:
	VGameSystem(int maxflame,int fontsize);
	~VGameSystem();
	virtual int VCalculate()=0;
	virtual void VDraw()const=0;
};

#endif // !DEF_GAMESYSTEM_H
#pragma once
