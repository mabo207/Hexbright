#ifndef DEF_CONNECTBLOCK_H
#define DEF_CONNECTBLOCK_H

#include"Block.h"

//消すとお邪魔ブロックを送る得点ブロック
class ConnectBlock:public Block{
	//列挙体・型

	//定数

	//変数
protected:

	//関数
protected:

public:
	ConnectBlock(Vector2D center,const std::vector<Conductor> conductors)
		:Block(center,conductors,Feature::connect){}
	unsigned int GetVertexColor()const;
	int GetBaseScore(int gameMode)const;//ブロックの種類によって基本得点が決定する。なお、スコアアタックかVSモードかで基本得点を変えるかもしれないので引数を渡すようにしている。
};




#endif // !DEF_ATTACKBLOCK_H
#pragma once
