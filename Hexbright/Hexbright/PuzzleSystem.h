#ifndef DEF_PUZZLESYSTEM_H
#define DEF_PUZZLESYSTEM_H

#include<vector>
#include"Stage.h"
#include"PutPos.h"
#include"FlowEraseCircle.h"
#include"FlowGuideCircle.h"
#include"ScoreSystem.h"

//一人分のパズルシステムを表現する
class PuzzleSystem{
	//型・列挙体
protected:
	
	//定数
protected:

public:
	static const Vector2D aPuzzleSize;//１人分の画面の大きさ

	//変数
protected:
	Stage m_stage;//現在の盤面
	PutPos m_cursor;//カーソル
	int m_bootVertex;//発火点となる辺
	Vector2D m_center;//中央のマスの描画位置
	std::shared_ptr<ScoreSystem> m_pScore;//スコア
	FlowEraseCircle m_flowCircle;//導線を辿る小さな丸
	std::vector<std::shared_ptr<Block>> m_savedBlock;//次に出てくるブロック一覧
	int m_flame;//現在のスタートからのフレーム数

	FlowGuideCircle m_flowGuideCircle;//導線巡りガイド

	//パズル全体の管理クラスが持っておくべきかもな変数
	//時間計測を行うための変数(ポーズや通信ラグにも対応できる仕様)

	//描画用変数
	int m_timeFont;//時間表示用のフォントハンドル(パズル全体の管理クラスが持っておくべきかも)

	//関数
protected:
	void AddSavedBlock();//ブロックを一つ貯める
	void TurnBootVertex(int n);//n回だけ時計回りに発火点を回転させる。n=0でも、現在の位置に発火辺がなければn=1と同じ挙動をする（時計回り方向で一番近い発火辺に移動する）
	
public:
	PuzzleSystem();
	~PuzzleSystem();

	void Update();//毎フレーム呼び出して更新する
	void Draw()const;

	int GetScore()const;
};

#endif // !DEF_PUZZLESYSTEM_H
#pragma once
