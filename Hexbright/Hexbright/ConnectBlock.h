#ifndef DEF_CONNECTBLOCK_H
#define DEF_CONNECTBLOCK_H

#include"Block.h"

//�����Ƃ��ז��u���b�N�𑗂链�_�u���b�N
class ConnectBlock:public Block{
	//�񋓑́E�^

	//�萔

	//�ϐ�
protected:

	//�֐�
protected:

public:
	ConnectBlock(Vector2D center,const std::vector<Conductor> conductors)
		:Block(center,conductors,Feature::connect){}
	unsigned int GetColor()const;
};




#endif // !DEF_ATTACKBLOCK_H
#pragma once
