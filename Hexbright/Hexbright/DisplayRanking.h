#ifndef DEF_DISPLAYRANKING_H
#define DEF_DISPLAYRANKING_H

#include<vector>
#include<string>

class DisplayRanking{
	//Œ^E—ñ‹“‘Ì
	struct ScoreData{
		std::string name;
		int score;
		ScoreData(const std::vector<std::string> &commastr);
		bool operator<(const ScoreData &otherobj)const;
	};
	//’è”
	static const int size=48;

	//•Ï”
protected:
	int m_adjustY;
	int m_font;
	std::vector<ScoreData> m_scoreData;

	//ŠÖ”
public:
	DisplayRanking();
	~DisplayRanking();
	int Calculate();
	void Draw()const;
};

#endif // !DEF_DISPLAYRANKING_H

#pragma once
