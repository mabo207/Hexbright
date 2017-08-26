#include"AttackBlock.h"
#include"DxLib.h"

//-----------------------AttackBlock-----------------------
unsigned int AttackBlock::GetColor()const{
	return DxLib::GetColor(128,128,255);
}

int AttackBlock::GetBaseScore(int gameMode)const{
	if(gameMode==1){
		//スコアアタック時
		return 300;
	}
	return 300;
}
