#include"AttackBlock.h"
#include"DxLib.h"

//-----------------------AttackBlock-----------------------
unsigned int AttackBlock::GetVertexColor()const{
	return DxLib::GetColor(128,128,255);
}

unsigned int AttackBlock::GetColor()const{
	return DxLib::GetColor(165,165,224);
}

int AttackBlock::GetBaseScore(int gameMode)const{
	if(gameMode==1){
		//スコアアタック時
		return 300;
	}
	return 300;
}
