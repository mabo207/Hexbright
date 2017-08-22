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
	,m_blockScoreFont(CreateFontToHandle("FAMania",8,1,-1)){}

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
}

void ScoreSystem::Draw(Vector2D center)const{
	//���v�_���̕\��
	Vector2D v=Vector2D(PuzzleSystem::aPuzzleSize/(float)2.2);
	v.y=-v.y;
	v=center+v;
	v.x-=GetDrawFormatStringWidthToHandle(m_totalScoreFont,"SCORE:%010d",m_score.GetX());
	DrawFormatStringToHandle((int)v.x,(int)v.y,GetColor(255,255,255),m_totalScoreFont,"SCORE:%010d",m_score.GetX());
	//�u���b�N�_���̕\��

}

int ScoreSystem::GetScore()const{
	return m_score.GetendX();
}
