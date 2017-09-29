#include"DxLib.h"
#include"FlowGuideCircle.h"

//-----------------------FlowGuideCircle-----------------------
FlowGuideCircle::FlowGuideCircle(PutPos i_blockPos,Vector2D i_drawPos)
	:FlowCircle(i_blockPos,i_drawPos,Block::BaseVector.size()/3,(float)1.00){}

FlowGuideCircle::~FlowGuideCircle(){}

void FlowGuideCircle::NextConductorProcess(const Stage &stage){
	//‰½‚à‚µ‚È‚¢
}

void FlowGuideCircle::Draw(Vector2D center)const{
	if(flowflag){
		DrawCircle((int)(drawPos.x),(int)(drawPos.y),2,GetColor(255,255,255),TRUE);
	}
}
