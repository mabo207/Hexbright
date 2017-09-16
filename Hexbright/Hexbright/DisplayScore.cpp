#include"DxLib.h"
#include"DisplayRanking.h"
#include"input.h"
#include"FileRead.h"
#include<algorithm>
#include<set>

//-----------------DisplayRanking::ScoreData-----------------
DisplayRanking::ScoreData::ScoreData(const std::vector<std::string> &commastr){
	if(commastr.size()>=2){
		name=commastr[0];
		score=std::atoi(commastr[1].c_str());
	}
}

bool DisplayRanking::ScoreData::operator<(const ScoreData &otherobj)const{
	if(score>otherobj.score){
		return true;
	} else if(score<otherobj.score){
		return false;
	}
	return name<otherobj.name;
}

//-----------------DisplayRanking-----------------
DisplayRanking::DisplayRanking()
	:m_adjustY(0),m_font(CreateFontToHandle("メイリオ",size,3,-1))
{
	std::vector<std::vector<std::string>> data=CommaCutRead("ranking.csv");
	for(std::vector<std::string> &v:data){
		m_scoreData.push_back(ScoreData(v));
	}
	//ソート
	std::set<ScoreData> set;
	for(ScoreData s:m_scoreData){
		set.insert(s);
	}
	m_scoreData.clear();
	for(const ScoreData &s:set){
		m_scoreData.push_back(s);
	}
}

DisplayRanking::~DisplayRanking(){
	DeleteFontToHandle(m_font);
}

int DisplayRanking::Calculate(){
	if(keyboard_get(KEY_INPUT_UP)>0){
		m_adjustY-=3;
	}else if(keyboard_get(KEY_INPUT_DOWN)>0){
		m_adjustY+=3;
	}else if(keyboard_get(KEY_INPUT_BACK)==1){
		return -1;
	}
	return 0;
}

void DisplayRanking::Draw()const{
	int dx,dy;
	GetWindowSize(&dx,&dy);
	for(unsigned int i=0;i<m_scoreData.size();i++){
		DrawStringCenterBaseToHandle(dx/2,m_adjustY+i*(size+10)
			,(m_scoreData[i].name+"    "+to_string_0d(m_scoreData[i].score,10)).c_str(),GetColor(255,255,255),m_font,false);
	}
}
