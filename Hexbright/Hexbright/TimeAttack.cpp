#include"DxLib.h"
#include"TimeAttack.h"

//-------------------TimeAttack-------------------
TimeAttack::TimeAttack()
	:VGameSystem(180*60,32),
	m_puzzle(std::shared_ptr<PuzzleSystem>(new PuzzleSystem())),
	m_phase(Phase::BEFORESTART),
	m_timer1(0),m_timer2(6*60)
{

}

TimeAttack::~TimeAttack(){}

int TimeAttack::VCalculate(){
	//���ʏ���
	m_timer1++;
		//�w�i�̍X�V
	//�i�K���ɕ��򂷂鏈��
	switch(m_phase){
	case(Phase::BEFORESTART):
		if(m_timer1>=m_timer2){
			//�Q�[�����n�܂鎞�ԂɂȂ�����
			m_phase=Phase::PLAYING;
		}
		break;
	case(Phase::PLAYING):
		//�c�莞�Ԃ̍X�V
		m_flame++;
		//�p�Y���̍X�V
		m_puzzle->Update();
		if(JudgeGameEnd()){
			//�Q�[�����I��鎞�ԂɂȂ�����
			m_phase=Phase::GAMEEND;
			m_timer2=m_timer1+5*60;
		}
		break;
	case(Phase::GAMEEND):
		if(m_timer1>=m_timer2){
			//�Q�[���I����ʂ���鎞�ԂɂȂ�����
			//m_phase=Phase::RESULT;//�{��������
			return -1;//�ꉞ�\�t�g�E�F�A���I��������
		}
		break;
	case(Phase::RESULT):
		break;
	case(Phase::NAMEINPUT):
		break;
	default:
		//�����ɗ���ꍇ�̓G���[�ƌ��Ȃ���B�����^�C���A�^�b�N�I���M����Ԃ�
		return -2;
	}
	return 0;
}

void TimeAttack::VDraw()const{
	//�w�i�̕`��
	
	//�S�v���C���[�̃p�Y�������̕`��
	m_puzzle->Draw();
	//�c�莞�Ԃ̕`��
	DrawCircle((int)PuzzleSystem::aPuzzleSize.x,(int)PuzzleSystem::aPuzzleSize.y,(int)PuzzleSystem::aPuzzleSize.y*1/5,GetColor(255,255,255),FALSE,2);//�g
	DrawStringRightJustifiedToHandle((int)PuzzleSystem::aPuzzleSize.x,(int)PuzzleSystem::aPuzzleSize.y-GetFontSizeToHandle(m_timeFont),to_string_0d(CalLeftSecond(),3),GetColor(255,255,255),m_timeFont);
}
