#ifndef DEF_VGAMESYSTEM_H

#include"ToolsLib.h"

//�Q�[���S�̂��Ǘ�������A�Q�[���̔w�i��`�悵���肷��V�X�e��
//�^�C���A�^�b�N���ΐ킩�ŕς��̂Ŋ��N���X��݂���
class VGameSystem{
	//�^�E�񋓑�

	//�萔

	//�ϐ�
protected:
	Timer m_timer;//�^�C�}�[
	//int m_flame;//�o�ߎ���
	const int m_maxflame;//��������

	//�t�H���g��
	int m_timeFont;//�c�莞�Ԃ�`�悷��t�H���g

	//�֐�
protected:
	//int CalLeftSecond()const;//�c�莞��(�b)���v�Z����֐�
	//bool JudgeGameEnd()const;//�����I���𔻒肷��֐�

public:
	VGameSystem(int maxflame,int fontsize);
	~VGameSystem();
	virtual int VCalculate()=0;
	virtual void VDraw()const=0;
};

#endif // !DEF_GAMESYSTEM_H
#pragma once
