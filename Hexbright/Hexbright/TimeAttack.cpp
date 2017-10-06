#include"DxLib.h"
#include"TimeAttack.h"


//-------------------TimeAttack-------------------
TimeAttack::TimeAttack()
	:VGameSystem(180*60,32),
	m_puzzle(std::shared_ptr<PuzzleSystem>(new PuzzleSystem())),
	m_phase(Phase::BEFORESTART),
	m_nameInputer(",",0)//,m_timer1(0),m_timer2(6*60)
{
	m_timer.SetTimer(4,true);
}

TimeAttack::~TimeAttack(){}

int TimeAttack::VCalculate(){
	//���ʏ���
	//m_timer1++;
	m_timer.Update();
		//�w�i�̍X�V
	//�i�K���ɕ��򂷂鏈��
	switch(m_phase){
	case(Phase::BEFORESTART):
		//if(m_timer1>=m_timer2){
		if(m_timer.JudgeEnd()){
			//�Q�[�����n�܂鎞�ԂɂȂ�����
			m_phase=Phase::PLAYING;
			m_timer.SetTimer(30,true);
		}
		break;
	case(Phase::PLAYING):
		//�c�莞�Ԃ̍X�V
		//m_flame++;
		//�p�Y���̍X�V
		m_puzzle->Update();
		
		//---------------------------------�f�o�b�O�R�[�h---------------------------------
		if(keyboard_get(KEY_INPUT_L)>=60){
			m_timer.EnforceEnd();
		}
		//---------------------------------�f�o�b�O�R�[�h�I��---------------------------------
		
		//if(JudgeGameEnd()){
		if(m_timer.JudgeEnd()){
			//�Q�[�����I��鎞�ԂɂȂ�����
			m_phase=Phase::GAMEEND;
			m_timer.SetTimer(0,true);
		}
		break;
	case(Phase::GAMEEND):
		//�L�[���͂��󂯕t���Ȃ�
		input_erase();
		//�p�Y���̍X�V
		m_puzzle->Update();
		//�I������
		if(!m_puzzle->GetFlowFlag()){
			//FlowEraseCircle�̓������肪�I��������
			m_phase=Phase::RESULT;
			m_timer.SetTimer(2,true);
		}
		break;
	case(Phase::RESULT):
		if(m_timer.JudgeEnd()){
			//�Q�[���I����ʂ���鎞�ԂɂȂ�����
			m_phase=Phase::NAMEINPUT;
		}
		break;
	case(Phase::NAMEINPUT):
		m_nameInputer.Update();
		if(!m_nameInputer.GetInputFlag()){
			//���O���͂��I�������
			return -1;
		}
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
	//�P�[�X���Ƃ̕`��
	switch(this->m_phase)
	{
	case(Phase::BEFORESTART):
	{
		//�w�i���Â߂�
		int mode,pal,x,y;
		GetDrawBlendMode(&mode,&pal);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA,128);
		GetWindowSize(&x,&y);
		DrawBox(0,0,x,y,GetColor(0,0,0),TRUE);
		SetDrawBlendMode(mode,pal);//�`��ݒ�����ɖ߂�
		//�J�n�܂ł̎��Ԃ̕\��
		if(m_timer.GetLeftCounter(true)<=3){
			DrawStringCenterBaseToHandle(x/2,y/2,std::to_string(m_timer.GetLeftCounter(true)).c_str(),GetColor(255,255,255),m_timeFont,true);
		}
		break;
	}
	case(Phase::GAMEEND):
	{
		//�w�i���Â߂�
		int mode,pal,x,y;
		GetDrawBlendMode(&mode,&pal);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA,128);
		GetWindowSize(&x,&y);
		DrawBox(0,0,x,y,GetColor(0,0,0),TRUE);
		SetDrawBlendMode(mode,pal);//�`��ݒ�����ɖ߂�
		//FINISH!�̕\��
		DrawStringCenterBaseToHandle(x/2,y/2,"FINISH!!",GetColor(255,255,255),m_timeFont,true);
		break;
	}
		break;
	case(Phase::RESULT):
	{
		//�w�i���Â߂�
		int mode,pal,x,y;
		GetDrawBlendMode(&mode,&pal);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA,128);
		GetWindowSize(&x,&y);
		DrawBox(0,0,x,y,GetColor(0,0,0),TRUE);
		SetDrawBlendMode(mode,pal);//�`��ݒ�����ɖ߂�
		//�X�R�A�̕\��
		DrawStringCenterBaseToHandle(x/2,y/2
			,("SCORE:"+to_string_0d(m_puzzle->GetScore(),10)).c_str(),GetColor(255,255,255),m_timeFont,true);
		break;
	}
	case(Phase::NAMEINPUT):
	{
		//�w�i���Â߂�
		int mode,pal,x,y;
		GetDrawBlendMode(&mode,&pal);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA,128);
		GetWindowSize(&x,&y);
		DrawBox(0,0,x,y,GetColor(0,0,0),TRUE);
		SetDrawBlendMode(mode,pal);//�`��ݒ�����ɖ߂�
		//�X�R�A�̕\��
		DrawStringCenterBaseToHandle(x/2,y/2
			,("SCORE:"+to_string_0d(m_puzzle->GetScore(),10)).c_str(),GetColor(255,255,255),m_timeFont,true);
		//���͂������O�̕\��
		DrawStringToHandle(x/4,y/2+GetFontSizeToHandle(m_timeFont)
			,("name:"+m_nameInputer.GetString()).c_str(),GetColor(255,255,255),m_timeFont,true);
		DrawLine(x/4,y/2+GetFontSizeToHandle(m_timeFont)*2+5,x*3/4,y/2+GetFontSizeToHandle(m_timeFont)*2+5,GetColor(255,255,255),3);
		break;
	}
	default:
		break;
	}

	//�c�莞�Ԃ̕`��
	switch(m_phase){
	case(Phase::PLAYING):
	case(Phase::RESULT):
		DrawCircle((int)PuzzleSystem::aPuzzleSize.x,(int)PuzzleSystem::aPuzzleSize.y,(int)PuzzleSystem::aPuzzleSize.y*1/5,GetColor(255,255,255),FALSE,2);//�g
		DrawStringRightJustifiedToHandle((int)PuzzleSystem::aPuzzleSize.x,(int)PuzzleSystem::aPuzzleSize.y-GetFontSizeToHandle(m_timeFont),to_string_0d(m_timer.GetLeftCounter(true),3),GetColor(255,255,255),m_timeFont);
	}
}
