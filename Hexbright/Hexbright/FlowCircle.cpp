#include"DxLib.h"
#include"FlowCircle.h"

//-----------------------FlowCircle-----------------------
/*
�����{���ɂ��Ẵ����B
1.05���炢���ƁA23�A�����炢�ő����������n�߁A30�A�����炢�ő��������A48�A�����炢�ł߂����ᑬ��������B
*/

FlowCircle::FlowCircle(PutPos i_blockPos,Vector2D i_drawPos,float i_baseSpeed,float i_baseAccele)
	:blockPos(i_blockPos),drawPos(i_drawPos)
	,beginVertex(-1),endVertex(-1),flowflag(false)
	,startPos(0,0),startDir(-1),startBlock(0,0),flowend(false),destination(0,0)
	,baseAccele(i_baseAccele),baseSpeed(i_baseSpeed)
{
	//�Q�[���J�n���ɂ̂݌Ă΂��̂ł���ŗǂ�
	speed=baseSpeed;
	accele=baseAccele;
}

FlowCircle::~FlowCircle(){}

void FlowCircle::Update(const Stage &stage,const PutPos &cursor,const Vector2D &center){
	flowend=false;//���false�ɂ���B�X�V���ɓ��ʂȂ��Ƃ�����΂��̎��̂�true�ƂȂ�悤�ɂ���
	if(flowflag){
		//�������肪�n�܂��Ă���ꍇ
		//���x����

		//�ʒu�ύX
		drawPos=drawPos+(destination-drawPos).norm()*speed;
		//�ړI�n���B�̔���
		//�ړI�n�ƌ��݈ʒu�̋�����speed�̔����ȉ��Ȃ瓞�B�Ƃ���
		if((destination-drawPos).size()<=speed/2){
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
			if(!CirclingFlag()){
				//���݂̖ړI�n���X�^�[�g�n�_�Ɉ�v���Ă��Ȃ��Ȃ�
				if(pb.get()!=nullptr){
					//���ɐi�ރu���b�N�����݂��Ă��āc�c
					beginVertex=(endVertex+Hexagon::Vertexs::vnum/2)%Hexagon::Vertexs::vnum;//���Ƃ����Z�p�`�̕ӂ��甼���i�߂�ƍ�����Z�p�`�̕ӂ�\���悤�ɂȂ�
					if(pb.get()->GetConductor(beginVertex).JudgeExist()){
						//�Ή�����ӂ����݂���Ȃ��
						flowflag=true;//��������p��
						speed*=accele;//����
						NextConductorProcess(stage);//�������ς�������ɍs������
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
				//Boot�Őݒ肳���ϐ��͖߂��Ȃ��Ă悢

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

bool FlowCircle::Boot(const Stage &stage,const PutPos &cursor,const int bootVertex){
	//���łɓ������肪����Ă���ꍇ�̂ݍs��
	if(!flowflag){
		//���̏ꏊ�Ƀu���b�N������A�u���b�N�ɓ��������݂��邩���ׂ�
		std::shared_ptr<const Block> pb=stage.GetBlock(cursor);
		if(pb.get()!=nullptr && pb.get()->GetConductor(bootVertex).JudgeExist()){
			//���Ώꏊ������(�e�L�g�[)
			//�{���͔��΂���Z�p�`�ӂ����͂����̂ł�����܂ޓ��������߂�
			Block::Conductor c=pb.get()->GetConductor(bootVertex);
			//�P�ڂ̘Z�p�`�̌o�R�̍ۂɂǂ̕ӂ���ǂ̕ӂɌ������������߂�
			//�{���͔��Εӂ�beginVertex�Ƃ��A������񂩂�A�����̗��[�̂������ΕӂłȂ��ӂ�endVertex�Ƃ���
			beginVertex=bootVertex;
			endVertex=c.GetOtherN(bootVertex);
			//�P���������̔�������邽�߂ɁA���Γ_���ǂ��ɂ���A���̂̌o�R�̍ۂɂǂ̕����Ɍ������������L�^����B
			//�Ȃ��A�����Z�p�`���Q�x�ȏ�ʂ��H�̑��݂�F�߂�K�v������̂�startBlock�����ł͂��߁B
			startDir=endVertex;
			//startPos=drawPos;
			startPos=pb->GetVertexPos(beginVertex);
			//�v�Z�ʂ𗎂Ƃ����߂ɁA�\�ߔ��Γ_�����Z�p�`�̈ʒu�����߂�
			startBlock=cursor;
			//���݂̏������ۂ̕`��ʒu�����߂�
			drawPos=pb.get()->GetVertexPos(beginVertex);
			//���݂̏������ۂ��ǂ̘Z�p�`��ʂ��Ă��邩�����߂�
			blockPos=cursor;
			//���݂̏������ۂ���������΍��W�����߂�
			destination=pb.get()->GetVertexPos(endVertex);
			//�������ۂ̑��������ɖ߂�
			speed=baseSpeed;

			//���ΊJ�n
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
