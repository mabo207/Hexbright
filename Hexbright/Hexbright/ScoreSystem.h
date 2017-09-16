#ifndef DEF_SCORESYSTEM_H
#define DEF_SCORESYSTEM_H

#include<vector>

#include"PutPos.h"
#include"Stage.h"
#include"ToolsLib.h"

//スコアを管理し、それに関する数値を表示するクラス
class ScoreSystem{
	//型
protected:
	//ブロック点数の描画要素
	struct BlockScorePos{
		//定数
	protected:
		static const double singleDegree;//SingleBlockScore()におけるposのdegreeの初期化値
		static const int singleFlame;//SingleBlockScore()におけるposのflameの初期化値
		static const double bonusRate;//BonusScore()ではSingleBlockScore()より何倍長く表示させるか
		//変数
	public:
		std::string score;//点数
		PositionControl pos;//表示位置
		//関数
	protected:
		BlockScorePos(const std::string &i_score,PositionControl i_pos);
	public:
		~BlockScorePos();
		virtual void Draw(int font)const;
		//静的関数
		static std::shared_ptr<BlockScorePos> SingleBlockScore(int i_score,Vector2D v);//1つの導線によって得られる点数の表示
	};
	struct BonusScorePos:public BlockScorePos{
		BonusScorePos(const std::string &i_score,PositionControl i_pos):BlockScorePos(i_score,i_pos){}
		void Draw(int font)const;
		static std::shared_ptr<BlockScorePos> BonusScore(int i_score,Vector2D v);//周回後のボーナスによって得られる点数の表示
	};

	//定数

	//変数
protected:
	Easing m_score;//現在の得点表示。
	
	//導線巡り中のみ初期状態ではなくなる変数
	int m_combo;//連鎖数
	//そのうち、AddBlockScore()での計算をラクにするための途中経過を残しておくだけの変数
	int m_flowingScore;//現在の導線巡りで稼いでいる得点

	//描画用の変数
	std::vector<std::shared_ptr<BlockScorePos>> m_scoreTexts;//ブロックの点数の表示
	
	//フォント
	const int m_totalScoreFont;//合計得点を表示するためのフォント
	const int m_blockScoreFont;//ブロックの得点を表示するためのフォント

	//関数
protected:
	virtual int CalBlockScore(std::shared_ptr<const Block> pb,int count)const;//ブロックを消去した時に得られる得点を計算する。キャラによって変更できるように仮想関数とするが、モブキャラの得点計算はこれによって行う。
	void InitFlowingPal();//導線巡り中のみ使用する値を初期化する

public:
	ScoreSystem();
	~ScoreSystem();
	void Update();//表示するものの更新（位置や数値など）
	void AddBlockScore(const std::vector<PutPos> &blockPosVec,const Stage &stage);//末尾にあるブロックのスコアを加算する。blockPosVecに要素が１つだけ追加されたという前提のもと使用される。
	void AddFlowEndScore(bool circlingFlag,const Vector2D &flowCirclePos);//周回終了時に１周成功判定を行ってボーナススコアを加算する。初期化も行う。
	void Draw(Vector2D center)const;//表示関数
	int GetScore()const;//現在の得点を返す(m_score.endxの値)
	
};

#endif // !DEF_SCORESYSTEM_H
#pragma once
