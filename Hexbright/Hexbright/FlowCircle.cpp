#include"DxLib.h"
#include"Flowcircle.h"

//-----------------------FlowCircle-----------------------
FlowCircle::FlowCircle(PutPos i_blockPos,Vector2D i_drawPos)
	:blockPos(i_blockPos),drawPos(i_drawPos)
	,beginVertex(-1),endVertex(-1),flowflag(false)
	,startPos(0,0),startDir(-1),startBlock(0,0),flowend(false),speed(4.0),destination(0,0)
{
	//ゲーム開始時にのみ呼ばれるのでこれで良い
}

FlowCircle::~FlowCircle(){}

void FlowCircle::Draw(Vector2D center)const{
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

void FlowCircle::Update(const Stage &stage,const PutPos &cursor,const Vector2D &center){
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
				//Bootで設定される変数は戻さない

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

bool FlowCircle::Boot(const Stage &stage,const PutPos &cursor){
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
		blockPos=cursor;
		destination=pb.get()->GetVertexPos(endVertex);
		startBlock=cursor;

		//発火開始
		flowflag=true;

		return true;
	}
	return false;
}

