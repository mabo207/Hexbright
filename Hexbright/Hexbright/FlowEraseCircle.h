#ifndef DEF_FLOWERASECIRCLE_H
#define DEF_FLOWERASECIRCLE_H

#include"FlowCircle.h"

//�u���b�N�̓�����H�鏬������
class FlowEraseCircle:public FlowCircle{
	//�萔
protected:

	//�ϐ�
protected:

public:
	std::vector<PutPos> blockPosVec;//�o�R�����u���b�N�̈ʒu�Q(�擪�ɋ߂��قǏ��߂ɒʂ����u���b�N�ɂȂ�)
	std::shared_ptr<ScoreSystem> m_pScoreSystem;//�_���̉��Z��

	 //�֐�
protected:
	void NextConductorProcess(const Stage &stage);

public:
	FlowEraseCircle(PutPos i_blockPos,Vector2D i_drawPos,std::shared_ptr<ScoreSystem> i_pScoreSystem);
	~FlowEraseCircle();
	void Draw(Vector2D center)const;
	bool Boot(const Stage &stage,const PutPos &cursor,const int bootVertex);
};

#endif // !DEF_FLOWERASECIRCLE_H
#pragma once
