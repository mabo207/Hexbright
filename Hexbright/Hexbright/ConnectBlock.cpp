#include"ConnectBlock.h"
#include"DxLib.h"

//-----------------------ConnectBlock-----------------------
unsigned int ConnectBlock::GetVertexColor()const{
	return DxLib::GetColor(196,196,64);
}

int ConnectBlock::GetBaseScore(int gameMode)const{
	return 100;
}
