#ifndef DEF_DISPLAYRANKING_H
#define DEF_DISPLAYRANKING_H

#include<vector>
#include<string>

class DisplayRanking{
	//�^�E�񋓑�
	struct ScoreData{
		std::string name;
		int score;
		ScoreData(const std::vector<std::string> &commastr);
		bool operator<(const ScoreData &otherobj)const;
	};
	//�萔
	static const int size=48;

	//�ϐ�
protected:
	int m_adjustY;
	int m_font;
	std::vector<ScoreData> m_scoreData;

	//�֐�
public:
	DisplayRanking();
	~DisplayRanking();
	int Calculate();
	void Draw()const;
};

#endif // !DEF_DISPLAYRANKING_H

#pragma once
