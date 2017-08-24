#ifndef DEF_FLOWCIRCLE_H
#define DEF_FLOWCIRCLE_H

#include"Block.h"
#include"PutPos.h"
#include"Stage.h"
#include<vector>

//�u���b�N�̓�����H�鏬������
class FlowCircle{
	//�萔
protected:
	const float baseSpeed;//�X�s�[�h�̊�{�l
	const float baseAccele;//�����{���̊�{�l

	//�ϐ�
protected:
	Vector2D startPos;//�����H�肪�n�܂����ꏊ(���̏ꏊ�̎��ӂɂ��ǂ蒅������H��I��)(��Έʒu)
	int startDir;//�����H�肪�n�܂������̖ړI�Ӕԍ�
	PutPos startBlock;//�����H�肪�n�܂������̃u���b�N�̈ʒu(���̏�񂪔������startPos�ɋ߂Â��Ă��邩���肷��΂悢(�v�Z�ʍ팸))
	bool flowend;//FlowEnd()���Ԃ��l
	float speed;//����
	float accele;//�����{��
	Vector2D destination;//�ړ���̕`����W(��Έʒu)

	 //�V�X�e���p�ϐ�
public:
	PutPos blockPos;//�ǂ̃u���b�N�̏ꏊ�ɂ��邩
	Vector2D drawPos;//�ǂ̕`��ʒu�ɂ��邩(��Έʒu)
	int beginVertex,endVertex;//�ǂ̕ӂ���ǂ̕ӂɌ������Ă��邩
	bool flowflag;//���ݓ�����H�郂�[�h�ɂȂ��Ă��邩�ǂ���
	std::vector<PutPos> blockPosVec;//�o�R�����u���b�N�̈ʒu�Q(�擪�ɋ߂��قǏ��߂ɒʂ����u���b�N�ɂȂ�)

	 //�֐�
public:
	FlowCircle(PutPos i_blockPos,Vector2D i_drawPos);
	~FlowCircle();
	void Draw(Vector2D center)const;
	//void Update(PuzzleSystem *system);//�ϐ��̍X�V
	void Update(const Stage &stage,const PutPos &cursor,const Vector2D &center);//�ϐ��̍X�V
	bool FlowEnd()const;//�����H��̏I���������̂�true��Ԃ�
	bool Boot(const Stage &stage,const PutPos &cursor,const int bootVertex);//����������J�n������(���s����false��Ԃ�)
};

#endif // !DEF_FLOWCIRCLE_H
#pragma once
