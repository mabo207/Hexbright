#ifndef DEF_TITLE_H
#define DEF_TITLE_H

#include<memory>
#include"VGameSystem.h"
#include"DisplayRanking.h"

//�^�C�g�����
class Title{
	//�^�E�񋓑�

	//�萔

	//�ϐ�
protected:
	std::shared_ptr<VGameSystem> m_game;
	std::shared_ptr<DisplayRanking> m_ranking;
	int m_process;//0:�^�C�g�� 1:�Q�[�� 2:�����L���O�\��

	int m_font;

	//�֐�
public:
	Title();
	~Title();
	int Calculate();
	void Draw()const;

};


#endif // !DEF_TITLE_H
#pragma once
