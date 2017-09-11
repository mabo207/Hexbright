#include"DxLib.h"
#include"TimeAttack.h"

//-------------------TimeAttack-------------------
TimeAttack::TimeAttack()
	:VGameSystem(180*60,32),
	m_puzzle(std::shared_ptr<PuzzleSystem>(new PuzzleSystem())),
	m_phase(Phase::BEFORESTART)//,m_timer1(0),m_timer2(6*60)
{
	m_timer.SetTimer(6,true);
}

TimeAttack::~TimeAttack(){}

int TimeAttack::VCalculate(){
	//共通処理
	//m_timer1++;
	m_timer.Update();
		//背景の更新
	//段階毎に分岐する処理
	switch(m_phase){
	case(Phase::BEFORESTART):
		//if(m_timer1>=m_timer2){
		if(m_timer.JudgeEnd()){
			//ゲームが始まる時間になったら
			m_phase=Phase::PLAYING;
			m_timer.SetTimer(180,true);
		}
		break;
	case(Phase::PLAYING):
		//残り時間の更新
		//m_flame++;
		//パズルの更新
		m_puzzle->Update();
		//if(JudgeGameEnd()){
		if(m_timer.JudgeEnd()){
			//ゲームが終わる時間になったら
			m_phase=Phase::GAMEEND;
			//m_timer2=m_timer1+5*60;
			m_timer.SetTimer(5,true);
		}
		break;
	case(Phase::GAMEEND):
		//if(m_timer1>=m_timer2){
		if(m_timer.JudgeEnd()){
			//ゲーム終了画面を閉じる時間になったら
			//m_phase=Phase::RESULT;//本来こっち
			return -1;//一応ソフトウェアを終了させる
		}
		break;
	case(Phase::RESULT):
		break;
	case(Phase::NAMEINPUT):
		break;
	default:
		//ここに来る場合はエラーと見なせる。即刻タイムアタック終了信号を返す
		return -2;
	}
	return 0;
}

void TimeAttack::VDraw()const{
	//背景の描画
	
	//全プレイヤーのパズル部分の描画
	m_puzzle->Draw();
	//残り時間の描画
	DrawCircle((int)PuzzleSystem::aPuzzleSize.x,(int)PuzzleSystem::aPuzzleSize.y,(int)PuzzleSystem::aPuzzleSize.y*1/5,GetColor(255,255,255),FALSE,2);//枠
	DrawStringRightJustifiedToHandle((int)PuzzleSystem::aPuzzleSize.x,(int)PuzzleSystem::aPuzzleSize.y-GetFontSizeToHandle(m_timeFont),to_string_0d(m_timer.GetLeftCounter(true),3),GetColor(255,255,255),m_timeFont);
}
