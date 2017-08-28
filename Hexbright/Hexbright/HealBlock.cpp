#include"HealBlock.h"
#include"DxLib.h"

//-----------------------HealBlock-----------------------
unsigned int HealBlock::GetVertexColor()const{
	return DxLib::GetColor(128,255,128);
}

int HealBlock::GetBaseScore(int gameMode)const{
	if(gameMode==1){
		//スコアアタック時
		return 300;
	}
	return 300;
}
