#include"ConnectBlock.h"
#include"DxLib.h"

//-----------------------ConnectBlock-----------------------
unsigned int ConnectBlock::GetVertexColor()const{
	return DxLib::GetColor(255,255,64);
}

unsigned int ConnectBlock::GetColor()const{
	return DxLib::GetColor(200,200,112);
}

int ConnectBlock::GetBaseScore(int gameMode)const{
	return 100;
}
