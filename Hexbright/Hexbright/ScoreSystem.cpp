#include"DxLib.h"
#include"ScoreSystem.h"
#include"PuzzleSystem.h"

//-----------------------------ScoreSystem-----------------------------
int ScoreSystem::CalBlockScore(std::shared_ptr<const Block> pb,int count)const{
	//現状とりあえずこうしておく。実際はpbに得点素点を返させて処理する。
	return 400*count;
}

ScoreSystem::ScoreSystem()
	:m_score(0),m_displayScore(0)
	,m_totalScoreFont(CreateFontToHandle("Eras Bold ITC",32,4,-1))
	,m_blockScoreFont(CreateFontToHandle("FAMania",8,1,-1)){}

ScoreSystem::~ScoreSystem(){
	DeleteFontToHandle(m_totalScoreFont);
	DeleteFontToHandle(m_blockScoreFont);
}

void ScoreSystem::Update(){
	//表示する値の更新
	m_displayScore=min(m_score,m_displayScore+23);//23はテキトー。良い感じの表示になるような値にすればよい
	//ブロック点数群の表示する位置の更新、また表示期間が終わったら点数群をerase()する。

}

void ScoreSystem::AddBlockScore(const std::vector<PutPos> &blockPosVec,const Stage &stage){
	int count=0;//何連鎖目なのかを記録する
	for(const PutPos &pos:blockPosVec){
		//posにあるブロック情報を求める
		std::shared_ptr<const Block> pb=stage.GetBlock(pos);
		//連鎖判定
		count++;//ひとまずこう
		//ブロック情報から得点を求める
		int score=CalBlockScore(pb,count);
		//ブロック得点と描画位置情報群に記録

		//全体スコアに加算
		m_score+=score;
	}
}

void ScoreSystem::Draw(Vector2D center)const{
	//合計点数の表示
	Vector2D v=Vector2D(PuzzleSystem::aPuzzleSize/(float)2.2);
	v.y=-v.y;
	v=center+v;
	v.x-=GetDrawFormatStringWidthToHandle(m_totalScoreFont,"SCORE:%010d",m_displayScore);
	DrawFormatStringToHandle((int)v.x,(int)v.y,GetColor(255,255,255),m_totalScoreFont,"SCORE:%010d",m_displayScore);
	//ブロック点数の表示

}
