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
		:Block(center,conductors,Feature::normal){}
	unsigned int GetColor()const;
	int GetBaseScore(int gameMode)const;//�u���b�N�̎�ނɂ���Ċ�{���_�����肷��B�Ȃ��A�X�R�A�A�^�b�N��VS���[�h���Ŋ�{���_��ς��邩������Ȃ��̂ň�����n���悤�ɂ��Ă���B
};


#endif // !DEF_NORMALBLOCK_H
#pragma once
