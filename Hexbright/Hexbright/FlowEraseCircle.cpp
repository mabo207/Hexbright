#include"DxLib.h"
#include"FlowEraseCircle.h"

//-----------------------FlowEraseCircle-----------------------
/*
加速倍率についてのメモ。
1.05くらいだと、23連鎖くらいで速さを感じ始め、30連鎖くらいで速く感じ、48連鎖くらいでめっちゃ速く感じる。
*/

FlowEraseCircle::FlowEraseCircle(PutPos i_blockPos,Vector2D i_drawPos,std::shared_ptr<ScoreSystem> i_pScoreSystem)
	:FlowCircle(i_blockPos,i_drawPos,Block::BaseVector.size()/10,(float)1.05),m_pScoreSystem(i_pScoreSystem)
{
	//ゲーム開始時にのみ呼ばれるのでこれで良い
	speed=baseSpeed;
	accele=baseAccele;
}

FlowEraseCircle::~FlowEraseCircle(){}

void FlowEraseCircle::NextConductorProcess(const Stage &stage){
	blockPosVec.push_back(blockPos);//経由したブロックの位置情報を追加
	m_pScoreSystem->AddBlockScore(blockPosVec,stage);//点数の加算先
	speed*=accele;
}

void FlowEraseCircle::Draw(Vector2D center)const{
	if(flowflag){
		int mode,pal;
		GetDrawBlendMode(&mode,&pal);
		//小さい丸は加算ブレンドを用いて光って表現させる
		SetDrawBlendMode(DX_BLENDMODE_ADD,255);
		for(int i=-2;i<=2;i++){
			int r=2;//円の半径
			Vector2D v=drawPos+(destination-drawPos).norm()*(float)r*2*(float)i;
			DrawCircle((int)(v.x),(int)(v.y),2,GetColor(100,100,120),TRUE);
		}
		SetDrawBlendMode(mode,pal);
	}
}

bool FlowEraseCircle::Boot(const Stage &stage,const PutPos &cursor,const int bootVertex){
	//導線巡りが始まった場合のみ行う
	if(FlowCircle::Boot(stage,cursor,bootVertex)){
		//発火したので経由したブロックの位置群情報は１つめのブロックがあるだけにしておく
		blockPosVec.clear();
		blockPosVec.push_back(cursor);
		m_pScoreSystem->AddBlockScore(blockPosVec,stage);
		return true;
	}
	return false;
}
