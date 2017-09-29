#include"DxLib.h"
#include"FlowCircle.h"

//-----------------------FlowCircle-----------------------
/*
加速倍率についてのメモ。
1.05くらいだと、23連鎖くらいで速さを感じ始め、30連鎖くらいで速く感じ、48連鎖くらいでめっちゃ速く感じる。
*/

FlowCircle::FlowCircle(PutPos i_blockPos,Vector2D i_drawPos,float i_baseSpeed,float i_baseAccele)
	:blockPos(i_blockPos),drawPos(i_drawPos)
	,beginVertex(-1),endVertex(-1),flowflag(false)
	,startPos(0,0),startDir(-1),startBlock(0,0),flowend(false),destination(0,0)
	,baseAccele(i_baseAccele),baseSpeed(i_baseSpeed)
{
	//ゲーム開始時にのみ呼ばれるのでこれで良い
	speed=baseSpeed;
	accele=baseAccele;
}

FlowCircle::~FlowCircle(){}

void FlowCircle::Update(const Stage &stage,const PutPos &cursor,const Vector2D &center){
	flowend=false;//常にfalseにする。更新時に特別なことがあればその時のみtrueとなるようにする
	if(flowflag){
		//導線巡りが始まっている場合
		//速度調整

		//位置変更
		drawPos=drawPos+(destination-drawPos).norm()*speed;
		//目的地到達の判定
		//目的地と現在位置の距離がspeedの半分以下なら到達とする
		if((destination-drawPos).size()<=speed/2){
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
			if(!CirclingFlag()){
				//現在の目的地がスタート地点に一致していないなら
				if(pb.get()!=nullptr){
					//次に進むブロックが存在していて……
					beginVertex=(endVertex+Hexagon::Vertexs::vnum/2)%Hexagon::Vertexs::vnum;//もといた六角形の辺から半周進めると今いる六角形の辺を表すようになる
					if(pb.get()->GetConductor(beginVertex).JudgeExist()){
						//対応する辺も存在するならば
						flowflag=true;//導線巡り継続
						speed*=accele;//加速
						NextConductorProcess(stage);//導線が変わった時に行う処理
					}
				}
			} else{
				//一致している時は導線巡りは必ず終了させる
				flowflag=false;
			}
			//次の目的地の設定
			if(!flowflag){
				//導線巡りの終了を記録
				flowend=true;
				//位置を元に戻す
				blockPos=cursor;
				//Bootで設定される変数は戻さなくてよい

			} else{
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
	} else{
		//導線を巡っていない場合
		blockPos=cursor;
		drawPos=cursor.relativecoordinates(Block::BaseVector)+center;
	}
}

bool FlowCircle::FlowEnd()const{
	return flowend;
}

bool FlowCircle::Boot(const Stage &stage,const PutPos &cursor,const int bootVertex){
	//すでに導線巡りがされている場合のみ行う
	if(!flowflag){
		//その場所にブロックがあり、ブロックに導線が存在するか調べる
		std::shared_ptr<const Block> pb=stage.GetBlock(cursor);
		if(pb.get()!=nullptr && pb.get()->GetConductor(bootVertex).JudgeExist()){
			//発火場所を決定(テキトー)
			//本来は発火する六角形辺が入力されるのでそれを含む導線を求める
			Block::Conductor c=pb.get()->GetConductor(bootVertex);
			//１つ目の六角形の経由の際にどの辺からどの辺に向かうかを求める
			//本来は発火辺をbeginVertexとし、導線情報から、導線の両端のうち発火辺でない辺をendVertexとする
			beginVertex=bootVertex;
			endVertex=c.GetOtherN(bootVertex);
			//１周したかの判定をするために、発火点がどこにあり、そのの経由の際にどの方向に向かったかを記録する。
			//なお、同じ六角形を２度以上通る回路の存在を認める必要があるのでstartBlockだけではだめ。
			startDir=endVertex;
			//startPos=drawPos;
			startPos=pb->GetVertexPos(beginVertex);
			//計算量を落とすために、予め発火点した六角形の位置を求める
			startBlock=cursor;
			//現在の小さい丸の描画位置を求める
			drawPos=pb.get()->GetVertexPos(beginVertex);
			//現在の小さい丸がどの六角形を通っているかを求める
			blockPos=cursor;
			//現在の小さい丸が向かう絶対座標を求める
			destination=pb.get()->GetVertexPos(endVertex);
			//小さい丸の速さを元に戻す
			speed=baseSpeed;

			//発火開始
			flowflag=true;

			return true;
		}
	}
	return false;
}

bool FlowCircle::CirclingFlag()const{
	return (destination-startPos).size()==0;
}

void FlowCircle::EnforceEnd(){
	flowflag=false;
}
