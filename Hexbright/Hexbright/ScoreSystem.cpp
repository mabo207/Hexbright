#include"DxLib.h"
#include"ScoreSystem.h"
#include"PuzzleSystem.h"

//-----------------------------ScoreSystem::BlockScorePos-----------------------------
const double ScoreSystem::BlockScorePos::singleDegree=14;
const int ScoreSystem::BlockScorePos::singleFlame=30;
const double ScoreSystem::BlockScorePos::bonusRate=2;

ScoreSystem::BlockScorePos::BlockScorePos(const std::string &i_score,PositionControl i_pos)
	:score(i_score),pos(i_pos){}

ScoreSystem::BlockScorePos::~BlockScorePos(){}

void ScoreSystem::BlockScorePos::Draw(int font)const{
	DrawStringCenterBaseToHandle(pos.GetX(),pos.GetY(),score.c_str()
		,GetColor(255,255,255),font,true,GetColor(0,0,0));
}

std::shared_ptr<ScoreSystem::BlockScorePos> ScoreSystem::BlockScorePos::SingleBlockScore(int i_score,Vector2D v){
	std::shared_ptr<BlockScorePos> pb(new BlockScorePos(
		std::to_string(i_score)
		,PositionControl((int)v.x,(int)v.y,singleFlame,Easing::TYPE_OUT,Easing::FUNCTION_EXPO,singleDegree)
	));
	//�ړ���̌���
	pb->pos.SetTarget(pb->pos.GetX(),pb->pos.GetY()-(int)(Block::BaseVector.size()*(float)0.75),true);
	return pb;
}

//-----------------------------ScoreSystem::BonusScorePos-----------------------------
void ScoreSystem::BonusScorePos::Draw(int font)const{
	int fontsize=GetFontSizeToHandle(font);
	//��̕���(BONUS!!)��`��
	DrawStringCenterBaseToHandle(pos.GetX(),pos.GetY()-fontsize,"BONUS!!"
		,GetColor(255,255,0),font,false,GetColor(0,0,0));
	//���̕���(score)��`��
	DrawStringCenterBaseToHandle(pos.GetX(),pos.GetY(),score.c_str()
		,GetColor(255,255,255),font,false,GetColor(0,0,0));
}

std::shared_ptr<ScoreSystem::BlockScorePos> ScoreSystem::BonusScorePos::BonusScore(int i_score,Vector2D v){
	std::shared_ptr<BlockScorePos> pb(new BonusScorePos(
		std::to_string(i_score)
		,PositionControl((int)v.x,(int)v.y,(int)(singleFlame*bonusRate),Easing::TYPE_OUT,Easing::FUNCTION_EXPO,singleFlame*bonusRate)
	));
	//�ړ���̌���
	pb->pos.SetTarget(pb->pos.GetX(),pb->pos.GetY()-(int)(Block::BaseVector.size()*(float)0.75),true);
	return pb;
}

//-----------------------------ScoreSystem-----------------------------
int ScoreSystem::CalBlockScore(std::shared_ptr<const Block> pb,int count)const{
	//����Ƃ肠�����������Ă����B���ۂ̓L�����N�^�[�̐����ɂ���ĕω������邵�A�X�R�A�A�^�b�N��VS���[�h���̈�������������^����B
	return pb->GetBaseScore(1)*count;
}

ScoreSystem::ScoreSystem()
	:m_score(0,60,Easing::TYPE_IN,Easing::FUNCTION_EXPO,3.0)
	,m_totalScoreFont(CreateFontToHandle("Eras Bold ITC",32,4,-1))
	,m_blockScoreFont(CreateFontToHandle("FAMania",10,1,DX_FONTTYPE_EDGE))
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
	for(std::vector<std::shared_ptr<BlockScorePos>>::const_iterator it=m_scoreTexts.begin();it!=m_scoreTexts.end();){
		if(it->get()->pos.GetEndFlag()){
			//�\�����Ԃ��߂����ꍇ
			it=m_scoreTexts.erase(it);
		}else{
			it->get()->pos.Update();
			it++;
		}
	}
}

void ScoreSystem::AddBlockScore(const std::vector<PutPos> &blockPosVec,const Stage &stage){
/*//�R���{���̌v�Z�A���S���Y���BAddBlockScore()�̎g�p����鐧��������Am_combo��1�ɂ��邩�C���N�������g���邩�ŏ������ł���̂ŊȒP�ɂ���B
	//�����̃u���b�N�ɂ��ăR���{�����v�Z
	int combo=1;
	std::vector<PutPos>::const_iterator it=blockPosVec.end(),itb=blockPosVec.begin();
	it--;
	std::shared_ptr<const Block> pDelBlock=stage.GetBlock(*it);//���Z����u���b�N�̑Ώ�
	for(;it!=itb;){
		it--;
		std::shared_ptr<const Block> pb=stage.GetBlock(*it);//pDelBlock��combo�O�̃u���b�N
		if(!pDelBlock->JudgeConnect(*pb.get())){
			//�A�������𖞂����Ă��Ȃ��ꍇ
			break;
		}else{
			combo++;
		}
	}
	m_combo=combo;//�R���{���̍X�V
//*/
	//�����̃u���b�N�ɂ��ăR���{�𑝂₷���̔���
	std::vector<PutPos>::const_iterator it=blockPosVec.end(),itb=blockPosVec.begin();
	it--;
	std::shared_ptr<const Block> pDelBlock=stage.GetBlock(*it);//���Z����u���b�N�̑Ώ�
	if(it!=blockPosVec.begin()){
		it--;
		std::shared_ptr<const Block> pb=stage.GetBlock(*it);//pDelBlock��1�O�̃u���b�N
		if(pDelBlock->JudgeConnect(*pb.get())){
			//�A�������𖞂����Ă���ꍇ
			m_combo++;
		}else{
			//�A�������𖞂����Ă��Ȃ�
			m_combo=1;
		}
	}else{
		//�n�߂̂P�߂͕K��1�R���{�ڂɂ���K�v������
		m_combo=1;
	}
	//���Z�X�R�A�̌v�Z
	const int score=CalBlockScore(pDelBlock,m_combo);
	//�u���b�N�P�̂̃X�R�A�̕\���ݒ�
	m_scoreTexts.push_back(BlockScorePos::SingleBlockScore(score,pDelBlock->GetPos()));
	//�X�R�A���Z
	m_score.SetTarget(this->GetScore()+score,true);//�X�R�A�ɉ��Z
	m_flowingScore+=score;//�������蒆�ɉ҂����X�R�A�ɂ����Z
}

void ScoreSystem::AddFlowEndScore(bool circlingFlag,const Vector2D &flowCirclePos){
	//�P���������̔���
	if(circlingFlag){
		const int addScore=m_flowingScore/2;
		m_scoreTexts.push_back(BonusScorePos::BonusScore(addScore,flowCirclePos));
		m_score.SetTarget(this->GetScore()+addScore,true);//����ɂ��X�R�A�̔��������Z
	}
	//��������ɂ��Ă̕ϐ��̏�����
	InitFlowingPal();
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
	for(const std::shared_ptr<BlockScorePos> &pb:m_scoreTexts){
		pb->Draw(m_blockScoreFont);
	}
	

}

int ScoreSystem::GetScore()const{
	return m_score.GetendX();
}

void ScoreSystem::InitFlowingPal(){
	m_combo=0;
	m_flowingScore=0;
}
