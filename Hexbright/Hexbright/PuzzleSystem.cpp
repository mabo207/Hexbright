#include"DxLib.h"
#include"PuzzleSystem.h"
#include"input.h"

#include"NormalBlock.h"

//-----------------------PuzzleSystem-----------------------
PuzzleSystem::PuzzleSystem()
	:m_stage(5),m_cursor(0,0),m_center(400,300),m_flowCircle(PutPos(0,0),Vector2D(400,300))
{
	//初期化
	for(int i=0;i<5;i++){
		AddSavedBlock();
	}
}

PuzzleSystem::~PuzzleSystem(){}

void PuzzleSystem::AddSavedBlock(){
	//0～5をランダムに並べる
	//フィッシャーイエーツのアルゴリズムを用いる
	int index[Hexagon::Vertexs::vnum];
	for(int i=0;i<Hexagon::Vertexs::vnum;i++){
		index[i]=i;
	}
	for(int i=0;i<Hexagon::Vertexs::vnum;i++){
		int a=GetRand(Hexagon::Vertexs::vnum-i-1);
		int b=index[Hexagon::Vertexs::vnum-i-1];
		index[Hexagon::Vertexs::vnum-i-1]=index[a];
		index[a]=b;
	}
	//六角形に線分が追加できるかを判定しながら見ていき、ダメになったらその前の物を返す。
	std::vector<Block::Conductor> cons;
	for(unsigned int i=0;i<Hexagon::Vertexs::vnum/2;i++){
		bool flag=true;
		Block::Conductor con(index[i*2],index[i*2+1]);
		for(Block::Conductor c:cons){
			if(con.JudgeCross(c)){
				flag=false;
				break;
			}
		}
		if(flag){
			cons.push_back(con);
		}else{
			break;
		}
	}
	m_savedBlock.push_back(std::shared_ptr<Block>(new NormalBlock(m_center+m_cursor.relativecoordinates(Block::BaseVector),cons)));

}

void PuzzleSystem::Update(){
	//カーソルの更新
	if(keyboard_get(KEY_INPUT_D)==1){
		m_cursor=m_cursor+PutPos::BaseVec(PutPos::RIGHT);
	}else if(keyboard_get(KEY_INPUT_X)==1){
		m_cursor=m_cursor+PutPos::BaseVec(PutPos::RIGHTDOWN);
	}else if(keyboard_get(KEY_INPUT_Z)==1){
		m_cursor=m_cursor+PutPos::BaseVec(PutPos::LEFTDOWN);
	}else if(keyboard_get(KEY_INPUT_A)==1){
		m_cursor=m_cursor+PutPos::BaseVec(PutPos::LEFT);
	}else if(keyboard_get(KEY_INPUT_W)==1){
		m_cursor=m_cursor+PutPos::BaseVec(PutPos::LEFTUP);
	}else if(keyboard_get(KEY_INPUT_E)==1){
		m_cursor=m_cursor+PutPos::BaseVec(PutPos::RIGHTUP);
	}
	//丸の更新
	m_flowCircle.Update(m_stage,m_cursor,m_center);
	//入力受付
	if(keyboard_get(KEY_INPUT_NUMPADENTER)==1){
		//ブロックを置く
		if(m_stage.PutBlock(m_cursor,m_savedBlock[0],m_center)){
			//先頭のブロックを置けた場合は
			//先頭のブロックを取り除く
			m_savedBlock.erase(m_savedBlock.begin());
			//ブロックを１つ追加する
			AddSavedBlock();
		}
	}else if(keyboard_get(KEY_INPUT_BACK)==1){
		//起動
		m_flowCircle.Boot(m_stage,m_cursor);
	}else if(keyboard_get(KEY_INPUT_R)==1){
		//時計回り回転
		m_savedBlock[0].get()->Turn(1);
	}else if(keyboard_get(KEY_INPUT_Q)==1){
		//反時計回り回転
		m_savedBlock[0].get()->Turn(5);//-1を入れると%の仕様で0->5とならず0->3となる。
	}
	
}

void PuzzleSystem::Draw()const{
	//背景の描画

	//盤面の描画
	m_stage.Draw(m_center);
	//カーソルの描画(先頭のブロックを白く表示)
	m_savedBlock[0].get()->Draw(m_center+m_cursor.relativecoordinates(Block::BaseVector),GetColor(255,255,255),GetColor(255,255,255));
	//丸の描画
	m_flowCircle.Draw(m_center);
	//溜まっているブロック群の描画
	for(size_t i=0;i<m_savedBlock.size();i++){
		m_savedBlock[i].get()->Draw(Vector2D(750,(float)(100*i+150)));
	}

}
