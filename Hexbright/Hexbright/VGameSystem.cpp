#include"DxLib.h"
#include"VGameSystem.h"

//--------------VGameSystem---------------
VGameSystem::VGameSystem(int maxflame,int fontsize)
	:m_flame(0),m_maxflame(maxflame),m_timeFont(CreateFontToHandle("Eras Bold ITC",fontsize,3,-1)){}

VGameSystem::~VGameSystem(){
	DeleteFontToHandle(m_timeFont);
}

int VGameSystem::CalLeftSecond()const{
	//œŽZŽž‚ÌØ‚èŽÌ‚Ä‚ðl—¶‚µAŽŽ‡I—¹‚É‚È‚Á‚½uŠÔ‚É0‚Æ•\Ž¦‚³‚ê‚é‚æ‚¤‚É‚·‚é
	return (m_maxflame-m_flame+59)/60;
}

bool VGameSystem::JudgeGameEnd()const{
	return m_flame>=m_maxflame;
}
