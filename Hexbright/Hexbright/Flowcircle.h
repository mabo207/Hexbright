#ifndef DEF_FLOWCIRCLE_H
#define DEF_FLOWCIRCLE_H

#include"Block.h"
#include"PutPos.h"
#include"Stage.h"
#include"ScoreSystem.h"
#include<vector>

//����������镨�̂̒�`
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
	
	//�֐�
protected:
	virtual void NextConductorProcess(const Stage &stage)=0;//���ɐi�ޓ��������݂��Ă��鎞�ɒǉ��ōs������

public:
	FlowCircle(PutPos i_blockPos,Vector2D i_drawPos,float i_baseSpeed,float i_baseAccele);
	~FlowCircle();
	virtual void Draw(Vector2D center)const=0;
	void Update(const Stage &stage,const PutPos &cursor,const Vector2D &center);//�ϐ��̍X�V
	bool FlowEnd()const;//�����H��̏I���������̂�true��Ԃ�
	virtual bool Boot(const Stage &stage,const PutPos &cursor,const int bootVertex);//����������J�n������(���s����false��Ԃ�)
	bool CirclingFlag()const;//�������肪�P���������𔻒肷��֐�

};

#endif // !DEF_FLOWCIRCLE_H
#pragma once
