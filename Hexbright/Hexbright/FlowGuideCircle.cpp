#include"DxLib.h"
#include"FlowGuideCircle.h"

//-----------------------FlowGuideCircle-----------------------
FlowGuideCircle::FlowGuideCircle(PutPos i_blockPos,Vector2D i_drawPos)
	:FlowCircle(i_blockPos,i_drawPos,Block::BaseVector.size()/10,(float)1.00){}

FlowGuideCircle::~FlowGuideCircle(){}

void FlowGuideCircle::NextConductorProcess(const Stage &stage){
	//‰½‚à‚µ‚È‚¢
}

void FlowGuideCircle::Draw(Vector2D center)const{
	DrawCircle((int)(drawPos.x),(int)(drawPos.y),1,GetColor(255,255,255),TRUE);
}
