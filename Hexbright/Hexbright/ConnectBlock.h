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
	unsigned int GetVertexColor()const;
	int GetBaseScore(int gameMode)const;//�u���b�N�̎�ނɂ���Ċ�{���_�����肷��B�Ȃ��A�X�R�A�A�^�b�N��VS���[�h���Ŋ�{���_��ς��邩������Ȃ��̂ň�����n���悤�ɂ��Ă���B
};




#endif // !DEF_ATTACKBLOCK_H
#pragma once
