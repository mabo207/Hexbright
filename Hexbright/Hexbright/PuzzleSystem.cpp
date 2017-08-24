#include"DxLib.h"
#include"PuzzleSystem.h"
#include"input.h"
#include<set>

#include"NormalBlock.h"

//-----------------------PuzzleSystem-----------------------
const Vector2D PuzzleSystem::aPuzzleSize=Vector2D(800,600);

PuzzleSystem::PuzzleSystem()
	:m_stage(5),m_cursor(0,0),m_bootVertex(0),m_center(aPuzzleSize/2),m_flowCircle(PutPos(0,0),m_center),m_score()
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

void PuzzleSystem::TurnBootVertex(int n){
	//今のカーソル位置にブロックがあるかを判定
	std::shared_ptr<const Block> pb=m_stage.GetBlock(m_cursor);
	if(pb.get()!=nullptr && !pb->GetConductors().empty()){
		//ブロックがあり、ブロック内に導線が存在する場合
		//導線が通っているブロックの辺番号を格納する
		std::vector<Block::Conductor> cVec=pb->GetConductors();
		std::set<int> set;
		for(Block::Conductor c:cVec){
			set.insert(c.GetN(0));
			set.insert(c.GetN(1));
		}
		//m_bootVertexに時計回り方向で一番近い位置を求める
		std::set<int>::const_iterator it=set.lower_bound(m_bootVertex);
		//回転させる
		if(it!=set.end() && *it==m_bootVertex){
			//m_bootVertexの位置に発火点が存在していた場合(n回だけ回転させる)

		}else{
			//m_bootVertexの位置に発火点が存在していない場合(反時計回りならn回,時計回りならn-1回だけ回転させる)
			if(n==0){
				//n=1の時と同じ処理をさせる
				n=1;
			}
			if(n>0){
				//n>0の時は、itに値を加えていく関係、またn-1回だけ回転させる関係上、一旦ひとつ前にイテレータを戻す。it!=set.end()が保証される。
				if(it==set.begin()){
					it=set.end();
				}
				it--;
			}
		}
		if(n<0){
			for(int i=0;i>n;i--){
				if(it==set.begin()){
					it=set.end();
				}
				it--;
			}
		}else if(n>0){
			for(int i=0;i<n;i++){
				it++;
				if(it==set.end()){
					it=set.begin();
				}
			}
		}
		//移動先の辺番号を格納
		m_bootVertex=*it;
	}else{
		//ブロックがない場合
		m_bootVertex=(m_bootVertex+Hexagon::Vertexs::vnum+n)%Hexagon::Vertexs::vnum;
	}
}

void PuzzleSystem::Update(){
	//丸の更新
	m_flowCircle.Update(m_stage,m_cursor,m_center);
	m_score.Update();
	if(m_flowCircle.FlowEnd()){
		//ちょうど導線巡りが終了したら
		//得点加算処理
		m_score.AddBlockScore(m_flowCircle.blockPosVec,m_stage);
		//妨害送信処理

		//ブロック消去処理
		m_stage.EraseBlocks(m_flowCircle.blockPosVec);
	}
	//カーソルの更新
	if(keyboard_get(KEY_INPUT_D)==1){
		m_cursor=m_cursor+PutPos::BaseVec(PutPos::RIGHT);
		//発火点の更新
		TurnBootVertex(0);
	}else if(keyboard_get(KEY_INPUT_X)==1){
		m_cursor=m_cursor+PutPos::BaseVec(PutPos::RIGHTDOWN);
		//発火点の更新
		TurnBootVertex(0);
	}else if(keyboard_get(KEY_INPUT_Z)==1){
		m_cursor=m_cursor+PutPos::BaseVec(PutPos::LEFTDOWN);
		//発火点の更新
		TurnBootVertex(0);
	}else if(keyboard_get(KEY_INPUT_A)==1){
		m_cursor=m_cursor+PutPos::BaseVec(PutPos::LEFT);
		//発火点の更新
		TurnBootVertex(0);
	}else if(keyboard_get(KEY_INPUT_W)==1){
		m_cursor=m_cursor+PutPos::BaseVec(PutPos::LEFTUP);
		//発火点の更新
		TurnBootVertex(0);
	}else if(keyboard_get(KEY_INPUT_E)==1){
		m_cursor=m_cursor+PutPos::BaseVec(PutPos::RIGHTUP);
		//発火点の更新
		TurnBootVertex(0);
	}
	//ブロック回転入力受付(発火点も回転)
	if(keyboard_get(KEY_INPUT_R)==1){
		//時計回り回転
		m_savedBlock[0].get()->Turn(1);
		//発火点も時計回りに回転
		TurnBootVertex(1);
	}else if(keyboard_get(KEY_INPUT_Q)==1){
		//反時計回り回転
		m_savedBlock[0].get()->Turn(Hexagon::Vertexs::vnum-1);//-1を入れると%の仕様で0->5とならず0->3となる。
		//発火点も反時計回りに回転
		TurnBootVertex(-1);
	}
	//マップ変更入力受付
	if(keyboard_get(KEY_INPUT_NUMPADENTER)==1){
		//ブロックを置く
		if(m_stage.PutBlock(m_cursor,m_savedBlock[0],m_center)){
			//先頭のブロックを置けた場合は
			//先頭のブロックを取り除く
			m_savedBlock.erase(m_savedBlock.begin());
			//ブロックを１つ追加する
			AddSavedBlock();
			//発火点の更新
			TurnBootVertex(0);
		}
	}else if(keyboard_get(KEY_INPUT_BACK)==1){
		//起動
		m_flowCircle.Boot(m_stage,m_cursor,m_bootVertex);
	}
	//発火点変更入力受付
	if(keyboard_get(KEY_INPUT_1)%10==1){
		//反時計回り回転
		TurnBootVertex(-1);
	}else if(keyboard_get(KEY_INPUT_4)%10==1){
		//時計回り回転
		TurnBootVertex(1);
	}
}

void PuzzleSystem::Draw()const{
	//背景の描画

	//盤面の描画
	m_stage.Draw(m_center);
	//カーソルの描画(先頭のブロックを白く表示)
	Vector2D v=m_center+m_cursor.relativecoordinates(Block::BaseVector);//カーソル描画と発火点描画で用いる
	m_savedBlock[0].get()->Draw(v,GetColor(255,255,255),GetColor(255,255,255));
	//発火点の描画
	v=Block::GetVertexPos(m_bootVertex,v);
	DrawCircle((int)v.x,(int)v.y,3,GetColor(128,128,255),TRUE);
	//丸の描画
	m_flowCircle.Draw(m_center);
	//溜まっているブロック群の描画
	for(size_t i=0;i<m_savedBlock.size();i++){
		m_savedBlock[i].get()->Draw(Vector2D(aPuzzleSize.x-50,(float)(aPuzzleSize.y*(i/6.0+1/4.0))));
	}
	//得点の描画
	m_score.Draw(m_center);
}
