#ifndef DEF_FLOWGUIDECIRCLE_H
#define DEF_FLOWGUIDECIRCLE_H

#include"FlowCircle.h"

//���ۂɋN��������ǂ��Ȃ邩���V�~�����[�g����FlowCircle�B�Q�[���ɉe�����y�ڂ��Ȃ��B
class FlowGuideCircle:public FlowCircle{
	//�萔
protected:

	//�ϐ�
protected:

	//�֐�
protected:
	void NextConductorProcess(const Stage &stage);

public:
	FlowGuideCircle(PutPos i_blockPos,Vector2D i_drawPos);
	~FlowGuideCircle();
	void Draw(Vector2D center)const;
};

#endif // !DEF_FLOWGUIDECIRCLE_H
#pragma once