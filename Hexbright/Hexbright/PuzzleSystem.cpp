#include"DxLib.h"
#include"PuzzleSystem.h"
#include"input.h"

#include"NormalBlock.h"

//-----------------------FlowCircle-----------------------
PuzzleSystem::FlowCircle::FlowCircle(PutPos i_blockPos,Vector2D i_drawPos)
	:blockPos(i_blockPos),drawPos(i_drawPos)
	,beginVertex(-1),endVertex(-1),flowflag(false)
	,startPos(0,0),startDir(-1),startBlock(0,0),flowend(false),speed(4.0),destination(0,0)
{
	//ゲーム開始時にのみ呼ばれるのでこれで良い
}

PuzzleSystem::FlowCircle::~FlowCircle(){}

void PuzzleSystem::FlowCircle::Draw(Vector2D center)const{
	int mode,pal;
	GetDrawBlendMode(&mode,&pal);
	//小さい丸は加算ブレンドを用いて光って表現させる
	SetDrawBlendMode(DX_BLENDMODE_ADD,255);
	for(int i=-2;i<=2;i++){
		Vector2D v=drawPos+(destination-drawPos).norm()*speed*(float)i;
		DrawCircle((int)(v.x),(int)(v.y),2,GetColor(100,100,120),TRUE);
	}
	SetDrawBlendMode(mode,pal);
}

void PuzzleSystem::FlowCircle::Update(const Stage &stage,const PutPos &cursor,const Vector2D &center){
	if(flowflag){
		//導線巡りが始まっている場合
		flowend=false;//常にfalseにする。更新時に特別なことがあればその時のみtrueとなるようにする
		//速度調整

		//位置変更
		drawPos=drawPos+(destination-drawPos).norm()*speed;
		//目的地到達の判定
		//目的地と現在位置の距離がspeedの半分以下なら到達とする
		if((destination-drawPos).size()<speed/2){
			//現在いるブロックを変更
			switch(endVertex){
			case(0)://右上の辺に進んだ
				blockPos=blockPos+PutPos::BaseVec(PutPos::RIGHTUP);
				break;
			case(1)://右の辺に進んだ
				blockPos=blockPos+PutPos::BaseVec(PutPos::RIGHT);
				break;
			case(2)://右下の辺に進んだ
				blockPos=blockPos+PutPos::BaseVec(PutPos::RIGHTDOWN);
				break;
			case(3)://左下の辺に進んだ
				blockPos=blockPos+PutPos::BaseVec(PutPos::LEFTDOWN);
				break;
			case(4)://左の辺に進んだ
				blockPos=blockPos+PutPos::BaseVec(PutPos::LEFT);
				break;
			case(5)://左上の辺に進んだ
				blockPos=blockPos+PutPos::BaseVec(PutPos::LEFTUP);
				break;
			}
			//次の目的地を設定するかの判定
			std::shared_ptr<const Block> pb=stage.GetBlock(blockPos);
			flowflag=false;//一旦導線巡りを終了させたことにし、継続可能ならtrueに戻す
			if((destination-startPos).size()>0){
				//現在の目的地がスタート地点に一致していないなら
				if(pb.get()!=nullptr){
					//次に進むブロックが存在していて……
					beginVertex=(endVertex+Hexagon::Vertexs::vnum/2)%Hexagon::Vertexs::vnum;//もといた六角形の辺から半周進めると今いる六角形の辺を表すようになる
					if(pb.get()->GetConductor(beginVertex).JudgeExist()){
						//対応する辺も存在するならば
						flowflag=true;//導線巡り継続
					}
				}
			}else{
				//一致している時は導線巡りは必ず終了させる
				flowflag=false;
			}
			//次の目的地の設定
			if(!flowflag){
				//導線巡りの終了を記録
				flowend=true;
				//位置を元に戻す
				blockPos=cursor;
				//Bootで設定される変数は戻さない

			}else{
				endVertex=pb.get()->GetConductor(beginVertex).GetOtherN(beginVertex);
				if(startDir==endVertex && startBlock==blockPos){
					//導線巡り開始時の目的辺が行き先であれば、行き先を開始場所に。
					destination=startPos;
				} else{
					//そうでないなら、行き先を辺に。
					destination=pb.get()->GetVertexPos(endVertex);
				}
			}
		}
	}else{
		//導線を巡っていない場合
		blockPos=cursor;
		drawPos=cursor.relativecoordinates(Block::BaseVector)+center;
	}
}

bool PuzzleSystem::FlowCircle::FlowEnd()const{
	return flowend;
}

bool PuzzleSystem::FlowCircle::Boot(const Stage &stage,const PutPos &cursor){
	//その場所にブロックがあり、ブロックに導線が存在するか調べる
	std::shared_ptr<const Block> pb=stage.GetBlock(cursor);
	if(pb.get()!=nullptr && pb.get()->GetConductors().size()>0){
		//発火場所を決定(テキトー)
		Block::Conductor c=pb.get()->GetConductors()[0];
		beginVertex=c.GetN(0);
		endVertex=c.GetN(1);
		startDir=endVertex;
		drawPos=pb.get()->GetVertexPos(beginVertex);
		startPos=drawPos;
		destination=pb.get()->GetVertexPos(endVertex);
		startBlock=cursor;

		//発火開始
		flowflag=true;

		return true;
	}
	return false;
}

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
		m_flowCircle.Boot(m_stage,m_cursor);
	}
	
}

void PuzzleSystem::Draw()const{
	//背景の描画

	//盤面の描画
	m_stage.Draw(m_center);
	//丸の描画
	m_flowCircle.Draw(m_center);
	//溜まっているブロック群の描画
	for(size_t i=0;i<m_savedBlock.size();i++){
		m_savedBlock[i].get()->Draw(Vector2D(750,(float)(100*i+150)));
	}

}
