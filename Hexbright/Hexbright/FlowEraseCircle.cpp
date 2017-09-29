#include"DxLib.h"
#include"FlowEraseCircle.h"

//-----------------------FlowEraseCircle-----------------------
/*
�����{���ɂ��Ẵ����B
1.05���炢���ƁA23�A�����炢�ő����������n�߁A30�A�����炢�ő��������A48�A�����炢�ł߂����ᑬ��������B
*/

FlowEraseCircle::FlowEraseCircle(PutPos i_blockPos,Vector2D i_drawPos,std::shared_ptr<ScoreSystem> i_pScoreSystem)
	:FlowCircle(i_blockPos,i_drawPos,Block::BaseVector.size()/10,(float)1.05),m_pScoreSystem(i_pScoreSystem)
{
	//�Q�[���J�n���ɂ̂݌Ă΂��̂ł���ŗǂ�
	speed=baseSpeed;
	accele=baseAccele;
}

FlowEraseCircle::~FlowEraseCircle(){}

void FlowEraseCircle::NextConductorProcess(const Stage &stage){
	blockPosVec.push_back(blockPos);//�o�R�����u���b�N�̈ʒu����ǉ�
	m_pScoreSystem->AddBlockScore(blockPosVec,stage);//�_���̉��Z��
	speed*=accele;
}

void FlowEraseCircle::Draw(Vector2D center)const{
	if(flowflag){
		int mode,pal;
		GetDrawBlendMode(&mode,&pal);
		//�������ۂ͉��Z�u�����h��p���Č����ĕ\��������
		SetDrawBlendMode(DX_BLENDMODE_ADD,255);
		for(int i=-2;i<=2;i++){
			int r=2;//�~�̔��a
			Vector2D v=drawPos+(destination-drawPos).norm()*(float)r*2*(float)i;
			DrawCircle((int)(v.x),(int)(v.y),2,GetColor(100,100,120),TRUE);
		}
		SetDrawBlendMode(mode,pal);
	}
}

bool FlowEraseCircle::Boot(const Stage &stage,const PutPos &cursor,const int bootVertex){
	//�������肪�n�܂����ꍇ�̂ݍs��
	if(FlowCircle::Boot(stage,cursor,bootVertex)){
		//���΂����̂Ōo�R�����u���b�N�̈ʒu�Q���͂P�߂̃u���b�N�����邾���ɂ��Ă���
		blockPosVec.clear();
		blockPosVec.push_back(cursor);
		m_pScoreSystem->AddBlockScore(blockPosVec,stage);
		return true;
	}
	return false;
}
