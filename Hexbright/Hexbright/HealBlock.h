#ifndef DEF_HEALBLOCK_H
#define DEF_HEALBLOCK_H

#include"Block.h"

//�����Ƃ��ז��u���b�N�𑗂链�_�u���b�N
class HealBlock:public Block{
	//�񋓑́E�^

	//�萔

	//�ϐ�
protected:

	//�֐�
protected:

public:
	HealBlock(Vector2D center,const std::vector<Conductor> conductors)
		:Block(center,conductors,Feature::heal){}
	unsigned int GetColor()const;
};




#endif // !DEF_HEALBLOCK_H
#pragma once
