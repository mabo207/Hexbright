#include"NormalBlock.h"
#include"DxLib.h"


//---------------------NormalBlock---------------------
unsigned int NormalBlock::GetVertexColor()const{
	return DxLib::GetColor(255,110,110);
}

unsigned int NormalBlock::GetColor()const{
	return DxLib::GetColor(231,152,152);
}

int NormalBlock::GetBaseScore(int gameMode)const{
	return 400;
}
