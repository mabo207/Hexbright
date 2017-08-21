#ifndef DEF_PUZZLESYSTEM_H
#define DEF_PUZZLESYSTEM_H

#include<vector>
#include"Stage.h"
#include"PutPos.h"
#include"Flowcircle.h"

//一人分のパズルシステムを表現する
class PuzzleSystem{
	//型・列挙体
protected:
	
	//定数
protected:

	//変数
protected:
	Stage m_stage;//現在の盤面
	PutPos m_cursor;//カーソル
	Vector2D m_center;//中央のマスの描画位置
	FlowCircle m_flowCircle;//導線を辿る小さな丸
	std::vector<std::shared_ptr<Block>> m_savedBlock;//次に出てくるブロック一覧

	//関数
protected:
	void AddSavedBlock();//ブロックを一つ貯める
	
public:
	PuzzleSystem();
	~PuzzleSystem();

	/*//ポインタを返す
	Stage *GetStage(){
		return &m_stage;
	}
	PutPos *GetCursor(){
		return &m_cursor;
	}
	Vector2D *GetVector2D(){
		return &m_center;
	}
	FlowCircle *GetFlowCircle(){
		return &m_flowCircle;
	}
	std::vector<std::shared_ptr<Block>> *GetSavedBlock(){
		return &m_savedBlock;
	}
	//*/
	void Update();//毎フレーム呼び出して更新する
	void Draw()const;
};

#endif // !DEF_PUZZLESYSTEM_H
#pragma once
