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
	unsigned int GetColor()const;//�u���b�N�̎�ނɂ���Č��肷��F�R�[�h���擾����B�������f�t�H���g�ł�GetColor(160,160,160)�̊D�F�Ƃ�50%�����Ƃ���B
	unsigned int GetVertexColor()const;
	int GetBaseScore(int gameMode)const;//�u���b�N�̎�ނɂ���Ċ�{���_�����肷��B�Ȃ��A�X�R�A�A�^�b�N��VS���[�h���Ŋ�{���_��ς��邩������Ȃ��̂ň�����n���悤�ɂ��Ă���B
};




#endif // !DEF_HEALBLOCK_H
#pragma once
