#include"DxLib.h"
#include"Flowcircle.h"

//-----------------------FlowCircle-----------------------
FlowCircle::FlowCircle(PutPos i_blockPos,Vector2D i_drawPos)
	:blockPos(i_blockPos),drawPos(i_drawPos)
	,beginVertex(-1),endVertex(-1),flowflag(false)
	,startPos(0,0),startDir(-1),startBlock(0,0),flowend(false),speed(4.0),destination(0,0)
{
	//�Q�[���J�n���ɂ̂݌Ă΂��̂ł���ŗǂ�
}

FlowCircle::~FlowCircle(){}

void FlowCircle::Draw(Vector2D center)const{
	int mode,pal;
	GetDrawBlendMode(&mode,&pal);
	//�������ۂ͉��Z�u�����h��p���Č����ĕ\��������
	SetDrawBlendMode(DX_BLENDMODE_ADD,255);
	for(int i=-2;i<=2;i++){
		Vector2D v=drawPos+(destination-drawPos).norm()*speed*(float)i;
		DrawCircle((int)(v.x),(int)(v.y),2,GetColor(100,100,120),TRUE);
	}
	SetDrawBlendMode(mode,pal);
}

void FlowCircle::Update(const Stage &stage,const PutPos &cursor,const Vector2D &center){
	if(flowflag){
		//�������肪�n�܂��Ă���ꍇ
		flowend=false;//���false�ɂ���B�X�V���ɓ��ʂȂ��Ƃ�����΂��̎��̂�true�ƂȂ�悤�ɂ���
					  //���x����

					  //�ʒu�ύX
		drawPos=drawPos+(destination-drawPos).norm()*speed;
		//�ړI�n���B�̔���
		//�ړI�n�ƌ��݈ʒu�̋�����speed�̔����ȉ��Ȃ瓞�B�Ƃ���
		if((destination-drawPos).size()<speed/2){
			//���݂���u���b�N��ύX
			switch(endVertex){
			case(0)://�E��̕ӂɐi��
				blockPos=blockPos+PutPos::BaseVec(PutPos::RIGHTUP);
				break;
			case(1)://�E�̕ӂɐi��
				blockPos=blockPos+PutPos::BaseVec(PutPos::RIGHT);
				break;
			case(2)://�E���̕ӂɐi��
				blockPos=blockPos+PutPos::BaseVec(PutPos::RIGHTDOWN);
				break;
			case(3)://�����̕ӂɐi��
				blockPos=blockPos+PutPos::BaseVec(PutPos::LEFTDOWN);
				break;
			case(4)://���̕ӂɐi��
				blockPos=blockPos+PutPos::BaseVec(PutPos::LEFT);
				break;
			case(5)://����̕ӂɐi��
				blockPos=blockPos+PutPos::BaseVec(PutPos::LEFTUP);
				break;
			}
			//���̖ړI�n��ݒ肷�邩�̔���
			std::shared_ptr<const Block> pb=stage.GetBlock(blockPos);
			flowflag=false;//��U����������I�����������Ƃɂ��A�p���\�Ȃ�true�ɖ߂�
			if((destination-startPos).size()>0){
				//���݂̖ړI�n���X�^�[�g�n�_�Ɉ�v���Ă��Ȃ��Ȃ�
				if(pb.get()!=nullptr){
					//���ɐi�ރu���b�N�����݂��Ă��āc�c
					beginVertex=(endVertex+Hexagon::Vertexs::vnum/2)%Hexagon::Vertexs::vnum;//���Ƃ����Z�p�`�̕ӂ��甼���i�߂�ƍ�����Z�p�`�̕ӂ�\���悤�ɂȂ�
					if(pb.get()->GetConductor(beginVertex).JudgeExist()){
						//�Ή�����ӂ����݂���Ȃ��
						flowflag=true;//��������p��
					}
				}
			} else{
				//��v���Ă��鎞�͓�������͕K���I��������
				flowflag=false;
			}
			//���̖ړI�n�̐ݒ�
			if(!flowflag){
				//��������̏I�����L�^
				flowend=true;
				//�ʒu�����ɖ߂�
				blockPos=cursor;
				//Boot�Őݒ肳���ϐ��͖߂��Ȃ�

			} else{
				endVertex=pb.get()->GetConductor(beginVertex).GetOtherN(beginVertex);
				if(startDir==endVertex && startBlock==blockPos){
					//��������J�n���̖ړI�ӂ��s����ł���΁A�s������J�n�ꏊ�ɁB
					destination=startPos;
				} else{
					//�����łȂ��Ȃ�A�s�����ӂɁB
					destination=pb.get()->GetVertexPos(endVertex);
				}
			}
		}
	} else{
		//�����������Ă��Ȃ��ꍇ
		blockPos=cursor;
		drawPos=cursor.relativecoordinates(Block::BaseVector)+center;
	}
}

bool FlowCircle::FlowEnd()const{
	return flowend;
}

bool FlowCircle::Boot(const Stage &stage,const PutPos &cursor){
	//���̏ꏊ�Ƀu���b�N������A�u���b�N�ɓ��������݂��邩���ׂ�
	std::shared_ptr<const Block> pb=stage.GetBlock(cursor);
	if(pb.get()!=nullptr && pb.get()->GetConductors().size()>0){
		//���Ώꏊ������(�e�L�g�[)
		Block::Conductor c=pb.get()->GetConductors()[0];
		beginVertex=c.GetN(0);
		endVertex=c.GetN(1);
		startDir=endVertex;
		drawPos=pb.get()->GetVertexPos(beginVertex);
		startPos=drawPos;
		blockPos=cursor;
		destination=pb.get()->GetVertexPos(endVertex);
		startBlock=cursor;

		//���ΊJ�n
		flowflag=true;

		return true;
	}
	return false;
}

