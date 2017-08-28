#ifndef DEF_NORMALBLOCK_H
#define DEF_NORMALBLOCK_H

#include"Block.h"

//普通の得点ブロック
class NormalBlock:public Block{
	//列挙体・型

	//定数

	//変数
protected:

	//関数
protected:

public:
	NormalBlock(Vector2D center,const std::vector<Conductor> conductors)
		:Block(center,conductors,Feature::normal){}
	unsigned int GetVertexColor()const;
	int GetBaseScore(int gameMode)const;//ブロックの種類によって基本得点が決定する。なお、スコアアタックかVSモードかで基本得点を変えるかもしれないので引数を渡すようにしている。
};


#endif // !DEF_NORMALBLOCK_H
#pragma once
