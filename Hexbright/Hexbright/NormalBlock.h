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
		:Block(center,conductors){}
	unsigned int GetColor()const;
};


#endif // !DEF_NORMALBLOCK_H
#pragma once
