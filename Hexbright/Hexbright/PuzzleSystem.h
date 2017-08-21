#ifndef DEF_PUZZLESYSTEM_H
#define DEF_PUZZLESYSTEM_H

#include<vector>
#include"Stage.h"
#include"PutPos.h"
#include"Flowcircle.h"

//��l���̃p�Y���V�X�e����\������
class PuzzleSystem{
	//�^�E�񋓑�
protected:
	
	//�萔
protected:

	//�ϐ�
protected:
	Stage m_stage;//���݂̔Ֆ�
	PutPos m_cursor;//�J�[�\��
	Vector2D m_center;//�����̃}�X�̕`��ʒu
	FlowCircle m_flowCircle;//������H�鏬���Ȋ�
	std::vector<std::shared_ptr<Block>> m_savedBlock;//���ɏo�Ă���u���b�N�ꗗ

	//�֐�
protected:
	void AddSavedBlock();//�u���b�N������߂�
	
public:
	PuzzleSystem();
	~PuzzleSystem();

	/*//�|�C���^��Ԃ�
	Stage *GetStage(){
		return &m_stage;
	}
	PutPos *GetCursor(){
		return &m_cursor;
	}
	Vector2D *GetVector2D(){
		return &m_center;
	}
	FlowCircle *GetFlowCircle(){
		return &m_flowCircle;
	}
	std::vector<std::shared_ptr<Block>> *GetSavedBlock(){
		return &m_savedBlock;
	}
	//*/
	void Update();//���t���[���Ăяo���čX�V����
	void Draw()const;
};

#endif // !DEF_PUZZLESYSTEM_H
#pragma once
