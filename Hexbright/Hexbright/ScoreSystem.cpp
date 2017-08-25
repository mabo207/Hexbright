#include"DxLib.h"
#include"ScoreSystem.h"
#include"PuzzleSystem.h"

//-----------------------------ScoreSystem-----------------------------
int ScoreSystem::CalBlockScore(std::shared_ptr<const Block> pb,int count)const{
	//現状とりあえずこうしておく。実際はpbに得点素点を返させて処理する。
	return 400*count;
}

ScoreSystem::ScoreSystem()
	:m_score(0,60,Easing::TYPE_IN,Easing::FUNCTION_EXPO,3.0)
	,m_totalScoreFont(CreateFontToHandle("Eras Bold ITC",32,4,-1))
	,m_blockScoreFont(CreateFontToHandle("FAMania",8,1,-1))
{
	InitFlowingPal();
}

ScoreSystem::~ScoreSystem(){
	DeleteFontToHandle(m_totalScoreFont);
	DeleteFontToHandle(m_blockScoreFont);
}

void ScoreSystem::Update(){
	//表示する値の更新
	m_score.Update();
	//ブロック点数群の表示する位置の更新、また表示期間が終わったら点数群をerase()する。

}

void ScoreSystem::AddBlockScore(const std::vector<PutPos> &blockPosVec,const Stage &stage){
/*
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
		m_score.SetTarget(this->GetScore()+score,true);
	}
//*/

	//末尾のブロックについてコンボ数を計算
	int combo=1;
	std::vector<PutPos>::const_iterator it=blockPosVec.end(),itb=blockPosVec.begin();
	it--;
	std::shared_ptr<const Block> pDelBlock=stage.GetBlock(*it);//加算するブロックの対象
	for(;it!=itb;){
		it--;
		std::shared_ptr<const Block> pb=stage.GetBlock(*it);//pDelBlockのcombo個前のブロック
		if(false){
			//連鎖条件を満たしていない場合
			break;
		}else{
			combo++;
		}
	}
	m_combo=combo;//コンボ数の更新
	//得点加算
	int score=CalBlockScore(pDelBlock,m_combo);
	m_score.SetTarget(this->GetScore()+score,true);
}

void ScoreSystem::Draw(Vector2D center)const{
	//合計点数の表示
	Vector2D v=Vector2D(PuzzleSystem::aPuzzleSize/(float)2.2);
	v.y=-v.y;
	v=center+v;
	DrawStringRightJustifiedToHandle((int)v.x,(int)v.y
		,"SCORE:"+to_string_0d(m_score.GetX(),10)
		,GetColor(255,255,255),m_totalScoreFont);
	//連鎖数の表示
	if(m_combo>0){
		DrawStringRightJustifiedToHandle((int)v.x,(int)v.y+GetFontSizeToHandle(m_totalScoreFont)+10
			,std::to_string(m_combo)+"COMBO",GetColor(255,255,255),m_totalScoreFont);
	}
	//ブロック点数の表示

	

}

int ScoreSystem::GetScore()const{
	return m_score.GetendX();
}

void ScoreSystem::InitFlowingPal(){
	m_combo=0;
}
