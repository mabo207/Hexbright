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
/*//コンボ数の計算アルゴリズム。AddBlockScore()の使用される制約条件より、m_comboを1にするかインクリメントするかで処理ができるので簡単にする。
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
//*/
	//末尾のブロックについてコンボを増やすかの判定
	std::vector<PutPos>::const_iterator it=blockPosVec.end(),itb=blockPosVec.begin();
	it--;
	std::shared_ptr<const Block> pDelBlock=stage.GetBlock(*it);//加算するブロックの対象
	if(it!=blockPosVec.begin()){
		it--;
		std::shared_ptr<const Block> pb=stage.GetBlock(*it);//pDelBlockの1個前のブロック
		if(true){
			//連鎖条件を満たしている場合
			m_combo++;
		}else{
			//連鎖条件を満たしていない
			m_combo=1;
		}
	}else{
		//始めの１つめは必ず1コンボ目にする必要がある
		m_combo=1;
	}
	//加算スコアの計算
	int score=CalBlockScore(pDelBlock,m_combo);
	//ブロック単体のスコアの表示設定

	//スコア加算
	m_score.SetTarget(this->GetScore()+score,true);//スコアに加算
	m_flowingScore+=score;//導線巡り中に稼いだスコアにも加算
}

void ScoreSystem::AddFlowEndScore(bool circlingFlag){
	//１周したかの判定
	if(circlingFlag){
		m_score.SetTarget(this->GetScore()+m_flowingScore/2,true);//周回によるスコアの半分を加算
	}
	//導線巡りについての変数の初期化
	InitFlowingPal();
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
	m_flowingScore=0;
}
