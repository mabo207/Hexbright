#ifndef DEF_NORMALBLOCK_H
#define DEF_NORMALBLOCK_H

#include"Block.h"

//���ʂ̓��_�u���b�N
class NormalBlock:public Block{
	//�񋓑́E�^

	//�萔

	//�ϐ�
protected:

	//�֐�
protected:

public:
	NormalBlock(Vector2D center,const std::vector<Conductor> conductors)
		:Block(center,conductors){}
	unsigned int GetColor()const;
};


#endif // !DEF_NORMALBLOCK_H
#pragma once
