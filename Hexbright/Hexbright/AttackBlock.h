#ifndef DEF_ATTACKBLOCK_H
#define DEF_ATTACKBLOCK_H

#include"Block.h"

//�����Ƃ��ז��u���b�N�𑗂链�_�u���b�N
class AttackBlock:public Block{
	//�񋓑́E�^

	//�萔

	//�ϐ�
protected:

	//�֐�
protected:

public:
	AttackBlock(Vector2D center,const std::vector<Conductor> conductors)
		:Block(center,conductors,Feature::attack){}
	unsigned int GetColor()const;
};




#endif // !DEF_ATTACKBLOCK_H
#pragma once
