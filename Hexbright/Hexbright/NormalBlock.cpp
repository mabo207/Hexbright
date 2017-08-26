#include"NormalBlock.h"
#include"DxLib.h"


//---------------------NormalBlock---------------------
unsigned int NormalBlock::GetColor()const{
	return DxLib::GetColor(255,128,128);
}

int NormalBlock::GetBaseScore(int gameMode)const{
	return 400;
}
