#include"DxLib.h"
#include"VGameSystem.h"

//--------------VGameSystem---------------
VGameSystem::VGameSystem(int maxflame,int fontsize)
	://m_flame(0),
	m_maxflame(maxflame),m_timeFont(CreateFontToHandle("Eras Bold ITC",fontsize,3,-1)),m_timer(60){}

VGameSystem::~VGameSystem(){
	DeleteFontToHandle(m_timeFont);
}

/*
int VGameSystem::CalLeftSecond()const{
	//除算時の切り捨てを考慮し、試合終了になった瞬間に0と表示されるようにする
	return (m_maxflame-m_flame+59)/60;
}

bool VGameSystem::JudgeGameEnd()const{
	return m_flame>=m_maxflame;
}
//*/