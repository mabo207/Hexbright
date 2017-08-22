#ifndef DEF_SCORESYSTEM_H
#define DEF_SCORESYSTEM_H

#include<vector>

#include"PutPos.h"
#include"Stage.h"

//スコアを管理し、それに関する数値を表示するクラス
class ScoreSystem{
	//型

	//定数

	//変数
protected:
	int m_score;//現在の得点
	

	//描画用の変数
	int m_displayScore;//SCORE:の後に表示する数値。m_scoreに収束するよう更新される。

	//フォント
	const int m_totalScoreFont;//合計得点を表示するためのフォント
	const int m_blockScoreFont;//ブロックの得点を表示するためのフォント

	//関数
protected:
	virtual int CalBlockScore(std::shared_ptr<const Block> pb,int count)const;//ブロックを消去した時に得られる得点を計算する。キャラによって変更できるように仮想関数とするが、モブキャラの得点計算はこれによって行う。

public:
	ScoreSystem();
	~ScoreSystem();
	void Update();//表示するものの更新（位置や数値など）
	void AddBlockScore(const std::vector<PutPos> &blockPosVec,const Stage &stage);//スコアを追加する
	void Draw(Vector2D center)const;//表示関数

};

#endif // !DEF_SCORESYSTEM_H
#pragma once
