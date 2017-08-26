#ifndef DEF_ATTACKBLOCK_H
#define DEF_ATTACKBLOCK_H

#include"Block.h"

//消すとお邪魔ブロックを送る得点ブロック
class AttackBlock:public Block{
	//列挙体・型

	//定数

	//変数
protected:

	//関数
protected:

public:
	AttackBlock(Vector2D center,const std::vector<Conductor> conductors)
		:Block(center,conductors,Feature::attack){}
	unsigned int GetColor()const;
};




#endif // !DEF_ATTACKBLOCK_H
#pragma once
