#include"DxLib.h"
#include"VGameSystem.h"

//--------------VGameSystem---------------
VGameSystem::VGameSystem(int maxflame,int fontsize)
	:m_flame(0),m_maxflame(maxflame),m_timeFont(CreateFontToHandle("Eras Bold ITC",fontsize,3,-1)){}

VGameSystem::~VGameSystem(){
	DeleteFontToHandle(m_timeFont);
}

int VGameSystem::CalLeftSecond()const{
	//���Z���̐؂�̂Ă��l�����A�����I���ɂȂ����u�Ԃ�0�ƕ\�������悤�ɂ���
	return (m_maxflame-m_flame+59)/60;
}

bool VGameSystem::JudgeGameEnd()const{
	return m_flame>=m_maxflame;
}
