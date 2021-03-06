#include"Block.h"
#include"DxLib.h"

//-------------------Conductor-------------------
Block::Conductor::Conductor():n0(-1),n1(-1){}

Block::Conductor::Conductor(int i_n0,int i_n1){
	if(i_n0==i_n1 || i_n0<0 || i_n0>=Hexagon::Vertexs::vnum || i_n1<0 || i_n1>=Hexagon::Vertexs::vnum){
		//点が一致してるか、入力番号が0以上5以下でなかったら存在しない導線にする
		n0=-1,n1=-1;
	}else{
		//n0<n1となるように代入
		n0=min(i_n0,i_n1);
		n1=i_n0+i_n1-n0;
	}
}

void Block::Conductor::turn(int n){
	//番号をどちらもnずらす
	//this=Conductor((n0+n)%Hexagon::Vertexs::vnum,(n1+n)%Hexagon::Vertexs::vnum);
	n0=(n0+n)%Hexagon::Vertexs::vnum;
	n1=(n1+n)%Hexagon::Vertexs::vnum;
}

bool Block::Conductor::JudgeCross(const Conductor &otherobj)const{
	//一致している点番号があったら交差とみなす
	if(this->n0==otherobj.n0 || this->n1==otherobj.n0 || this->n0==otherobj.n1 || this->n1==otherobj.n1){
		return true;
	}
	//一致している点番号はないのでthisから見て同じ側にあるotherobjの点の数を調べて偶数なら交差しない
	return ((n0-otherobj.n0)*(n1-otherobj.n0)*(n0-otherobj.n1)*(n1-otherobj.n1)<0);
}

int Block::Conductor::GetN(int i)const{
	switch(i){
	case(0):
		return n0;
	case(1):
		return n1;
	}
	return -1;
}

int Block::Conductor::GetOtherN(int n)const{
	if(n==n0 || n==n1){
		return n0+n1-n;
	}
	return -1;
}

bool Block::Conductor::JudgeExist()const{
	return !(n0<0 || n0>=Hexagon::Vertexs::vnum || n1<0 || n1>=Hexagon::Vertexs::vnum);
}

//-------------------Block-------------------
const int Block::lineThick=5;
const unsigned int Block::lineColor=DxLib::GetColor(64,64,64);
const Vector2D Block::BaseVector=Vector2D(0,-48);

Block::Block(std::shared_ptr<Hexagon> shape,const std::vector<Conductor> &conductors,Feature i_feature)
	:m_shape(shape),m_conductors(conductors),m_feature(i_feature){}

Block::Block(Vector2D center,const std::vector<Conductor> &conductors,Feature i_feature)
	:m_shape(std::shared_ptr<Hexagon>(new Hexagon(center,BaseVector))),m_conductors(conductors),m_feature(i_feature){}

Block::~Block(){}

unsigned int Block::GetColor()const{
	int red,green,blue;
	GetColor2(GetVertexColor(),&red,&green,&blue);
	return DxLib::GetColor(red/2+80,green/2+80,blue/2+80);
}

void Block::Draw()const{
	/*
	//正六角形の描画
	m_shape.get()->Draw(GetColor(),128);
	//導線の描画
	Hexagon::Vertexs vs=m_shape.get()->GetPoints();
	for(Conductor c:m_conductors){
		Vector2D v0=(vs.GetPoint(c.GetN(0))+vs.GetPoint((c.GetN(0)+1)%Hexagon::Vertexs::vnum))/2
			,v1=(vs.GetPoint(c.GetN(1))+vs.GetPoint((c.GetN(1)+1)%Hexagon::Vertexs::vnum))/2;
		DrawLine((int)(v0.x),(int)(v0.y),(int)(v1.x),(int)(v1.y),lineColor,lineThick);
	}
	//*/
	Draw(m_shape->GetCenter());
}

void Block::Draw(Vector2D pos)const{
	Draw(pos,GetColor(),GetVertexColor(),lineColor,255,lineThick);
}

void Block::Draw(Vector2D pos,unsigned int vertexColor,unsigned int conductorColor,int alpha)const{
	Draw(pos,GetColor(),vertexColor,conductorColor,alpha,lineThick);
}

void Block::Draw(Vector2D pos,unsigned int inColor,unsigned int vertexColor,unsigned int conductorColor,int alpha,int conductorThick)const{
	//正六角形の描画
	m_shape.get()->Draw(pos,inColor,alpha,vertexColor,3);
	//導線の描画
	int mode,pal;
	GetDrawBlendMode(&mode,&pal);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA,(mode==DX_BLENDMODE_ALPHA?pal:255)*alpha/255);
	Hexagon::Vertexs vs=m_shape.get()->GetPoints(pos);
	for(Conductor c:m_conductors){
		Vector2D v0=(vs.GetPoint(c.GetN(0))+vs.GetPoint((c.GetN(0)+1)%Hexagon::Vertexs::vnum))/2
			,v1=(vs.GetPoint(c.GetN(1))+vs.GetPoint((c.GetN(1)+1)%Hexagon::Vertexs::vnum))/2;
		DrawLine((int)(v0.x),(int)(v0.y),(int)(v1.x),(int)(v1.y),conductorColor,conductorThick);
	}
	SetDrawBlendMode(mode,pal);
}

Block::Conductor Block::GetConductor(int n)const{
	for(Conductor c:m_conductors){
		if(n==c.GetN(0) || n==c.GetN(1)){
			return c;
		}
	}
	return Conductor();
}

Vector2D Block::GetVertexPos(int n)const{
	//return (m_shape.get()->GetPoints().GetPoint((n+Hexagon::Vertexs::vnum)%Hexagon::Vertexs::vnum)+m_shape.get()->GetPoints().GetPoint((n+Hexagon::Vertexs::vnum+1)%Hexagon::Vertexs::vnum))/2;
	return GetVertexPos(n,m_shape->GetCenter());
}

Vector2D Block::GetPos()const{
	return m_shape.get()->GetCenter();
}

void Block::Turn(int n){
	//存在する導線を回転させる
	for(Conductor &c:m_conductors){
		c.turn(n);
	}
	
}

bool Block::JudgeConnect(const Block &otherobj)const{
	return (this->GetFeature().kind & otherobj.GetFeature().kind)!=0;
}

Vector2D Block::GetVertexPos(int n,Vector2D center){
	return (Hexagon::GetPoints(center,BaseVector).GetPoint((n+Hexagon::Vertexs::vnum)%Hexagon::Vertexs::vnum)+Hexagon::GetPoints(center,BaseVector).GetPoint((n+Hexagon::Vertexs::vnum+1)%Hexagon::Vertexs::vnum))/2;
}
