#include"DxLib.h"
#include"FlowGuideCircle.h"

//-----------------------FlowGuideCircle-----------------------
FlowGuideCircle::FlowGuideCircle(PutPos i_blockPos,Vector2D i_drawPos)
	:FlowCircle(i_blockPos,i_drawPos,Block::BaseVector.size()/3,(float)1.00){}

FlowGuideCircle::~FlowGuideCircle(){}

void FlowGuideCircle::NextConductorProcess(const Stage &stage){
	//Ü‚êüˆÊ’u‚Ì’Ç‰Á
	m_pointPoss.push_back(stage.GetBlock(blockPos)->GetVertexPos(beginVertex));
}

bool FlowGuideCircle::Boot(const Stage &stage,const PutPos &cursor,const int bootVertex){
	const bool b=FlowCircle::Boot(stage,cursor,bootVertex);
	if(b){
		m_pointPoss.clear();
		m_pointPoss.push_back(stage.GetBlock(blockPos)->GetVertexPos(beginVertex));
	}
	return b;
}

void FlowGuideCircle::Draw(Vector2D center)const{
	if(flowflag){
		//“_‚Ì•`‰æ
		DrawCircle((int)(drawPos.x),(int)(drawPos.y),2,GetColor(255,255,255),TRUE);
		//Ü‚êü‚Ì•`‰æ
		unsigned int i=0;
		for(;i+1<m_pointPoss.size();i++){
			DrawLine((int)m_pointPoss[i].x,(int)m_pointPoss[i].y,(int)m_pointPoss[i+1].x,(int)m_pointPoss[i+1].y,GetColor(255,255,255),1);
		}
		DrawLine((int)m_pointPoss[i].x,(int)m_pointPoss[i].y,(int)(drawPos.x),(int)(drawPos.y),GetColor(255,255,255),1);
	}
}
