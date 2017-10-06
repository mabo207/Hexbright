#ifndef DEF_TIMEATTACK_H

#include"VGameSystem.h"
#include"PuzzleSystem.h"
#include"input.h"
#include<memory>

//�^�C���A�^�b�N�̃V�X�e���̎���
class TimeAttack:public VGameSystem{
	//�^�E�񋓑�
protected:
	//�Q�[���i�K������
	struct Phase{
		enum Kind{
			BEFORESTART,
			PLAYING,
			GAMEEND,
			RESULT,
			NAMEINPUT,
			END
		};
		static Kind link(int num){
			if(num<0 || num>END){
				return END;
			}
			return static_cast<Kind>(num);
		}
	};
	//�萔

	//�ϐ�
protected:
	std::shared_ptr<PuzzleSystem> m_puzzle;//�������p�Y���͂P����
	Phase::Kind m_phase;//���݂̃Q�[���i�K
	InputSingleCharStringControler m_nameInputer;//���O���͗p
	//int m_timer1,m_timer2;//�^�C�}�[

	//�֐�
protected:

public:
	TimeAttack();
	~TimeAttack();
	int VCalculate();
	void VDraw()const;

};


#endif // !DEF_TIMEATTACK_H
#pragma once
