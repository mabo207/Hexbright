#include"DxLib.h"
#include"Title.h"
#include"input.h"
#include"TimeAttack.h"

//-----------------Title-----------------
Title::Title()
	:m_process(0),m_font(CreateFontToHandle("メイリオ",64,3,-1)){}

Title::~Title(){
	DeleteFontToHandle(m_font);
}

int Title::Calculate(){
	int index=0;
	switch(m_process){
	case(0):
		if(keyboard_get(KEY_INPUT_NUMPADENTER)==1 || keyboard_get(KEY_INPUT_BACK)==1){
			//段階移行
			m_process=1;
			m_game=std::shared_ptr<VGameSystem>(new TimeAttack());
		}else if(keyboard_get(KEY_INPUT_L)==1){
			m_ranking=std::shared_ptr<DisplayRanking>(new DisplayRanking());
			m_process=2;
		}
		break;
	case(1):
		index=m_game->VCalculate();
		if(index<0){
			//段階移行
			m_process=0;
			m_game=std::shared_ptr<VGameSystem>(nullptr);
		}
		break;
	case(2):
		index=m_ranking->Calculate();
		if(index<0){
			//段階移行
			m_process=0;
			m_ranking=std::shared_ptr<DisplayRanking>(nullptr);
		}
		break;
	default:
		break;
	}
	return 0;
}

void Title::Draw()const{
	switch(m_process){
	case(0):
	{
		int dx,dy;
		GetWindowSize(&dx,&dy);
		DrawStringCenterBaseToHandle(dx/2,dy/2,"PRESS 4 or 3 BUTTON",GetColor(255,255,255),m_font,true);
	}
		break;
	case(1):
		m_game->VDraw();
		break;
	case(2):
		m_ranking->Draw();
		break;
	default:
		break;
	}
}
