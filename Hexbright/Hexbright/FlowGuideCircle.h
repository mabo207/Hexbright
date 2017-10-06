#ifndef DEF_FLOWGUIDECIRCLE_H
#define DEF_FLOWGUIDECIRCLE_H

#include"FlowCircle.h"

//���ۂɋN��������ǂ��Ȃ邩���V�~�����[�g����FlowCircle�B�Q�[���ɉe�����y�ڂ��Ȃ��B
class FlowGuideCircle:public FlowCircle{
	//�萔
protected:

	//�ϐ�
protected:
	std::vector<Vector2D> m_pointPoss;//�܂���̐܂����W�Q

	//�֐�
protected:
	void NextConductorProcess(const Stage &stage);

public:
	FlowGuideCircle(PutPos i_blockPos,Vector2D i_drawPos);
	~FlowGuideCircle();
	bool Boot(const Stage &stage,const PutPos &cursor,const int bootVertex);//m_pointPoss������������
	void Draw(Vector2D center)const;
};

#endif // !DEF_FLOWGUIDECIRCLE_H
#pragma once
