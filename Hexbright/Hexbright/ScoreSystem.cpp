#include"DxLib.h"
#include"ScoreSystem.h"
#include"PuzzleSystem.h"

//-----------------------------ScoreSystem-----------------------------
int ScoreSystem::CalBlockScore(std::shared_ptr<const Block> pb,int count)const{
	//����Ƃ肠�����������Ă����B���ۂ�pb�ɓ��_�f�_��Ԃ����ď�������B
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
	//�\������l�̍X�V
	m_score.Update();
	//�u���b�N�_���Q�̕\������ʒu�̍X�V�A�܂��\�����Ԃ��I�������_���Q��erase()����B

}

void ScoreSystem::AddBlockScore(const std::vector<PutPos> &blockPosVec,const Stage &stage){
/*
	int count=0;//���A���ڂȂ̂����L�^����
	for(const PutPos &pos:blockPosVec){
		//pos�ɂ���u���b�N�������߂�
		std::shared_ptr<const Block> pb=stage.GetBlock(pos);
		//�A������
		count++;//�ЂƂ܂�����
		//�u���b�N��񂩂瓾�_�����߂�
		int score=CalBlockScore(pb,count);
		//�u���b�N���_�ƕ`��ʒu���Q�ɋL�^

		//�S�̃X�R�A�ɉ��Z
		m_score.SetTarget(this->GetScore()+score,true);
	}
//*/

	//�����̃u���b�N�ɂ��ăR���{�����v�Z
	int combo=1;
	std::vector<PutPos>::const_iterator it=blockPosVec.end(),itb=blockPosVec.begin();
	it--;
	std::shared_ptr<const Block> pDelBlock=stage.GetBlock(*it);//���Z����u���b�N�̑Ώ�
	for(;it!=itb;){
		it--;
		std::shared_ptr<const Block> pb=stage.GetBlock(*it);//pDelBlock��combo�O�̃u���b�N
		if(false){
			//�A�������𖞂����Ă��Ȃ��ꍇ
			break;
		}else{
			combo++;
		}
	}
	m_combo=combo;//�R���{���̍X�V
	//���_���Z
	int score=CalBlockScore(pDelBlock,m_combo);
	m_score.SetTarget(this->GetScore()+score,true);
}

void ScoreSystem::Draw(Vector2D center)const{
	//���v�_���̕\��
	Vector2D v=Vector2D(PuzzleSystem::aPuzzleSize/(float)2.2);
	v.y=-v.y;
	v=center+v;
	DrawStringRightJustifiedToHandle((int)v.x,(int)v.y
		,"SCORE:"+to_string_0d(m_score.GetX(),10)
		,GetColor(255,255,255),m_totalScoreFont);
	//�A�����̕\��
	if(m_combo>0){
		DrawStringRightJustifiedToHandle((int)v.x,(int)v.y+GetFontSizeToHandle(m_totalScoreFont)+10
			,std::to_string(m_combo)+"COMBO",GetColor(255,255,255),m_totalScoreFont);
	}
	//�u���b�N�_���̕\��

	

}

int ScoreSystem::GetScore()const{
	return m_score.GetendX();
}

void ScoreSystem::InitFlowingPal(){
	m_combo=0;
}
