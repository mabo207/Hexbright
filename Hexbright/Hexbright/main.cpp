#include"DxLib.h"
#include"GraphicControl.h"
#include"input.h"
#include"ToolsLib.h"

#include<time.h>
#include"NormalBlock.h"
#include"Stage.h"
#include"PuzzleSystem.h"

int WINAPI WinMain(HINSTANCE,HINSTANCE,LPSTR,int){
	//dx���C�u�����̏�����
	//��ʃ��[�h�̐ݒ�
	SetGraphMode(800,600,16);
	//�^�C�g�����j���[����
	SetMainWindowText("Hexbright");
	//�E�C���h�E�T�C�Y�̕ύX
	SetWindowSizeExtendRate(1.0);
	//�E�C���h�E�T�C�Y�̕ύX���ł���悤�ɂ���
	SetWindowSizeChangeEnableFlag(TRUE);
	//�A�C�R���̐ݒ�
	SetWindowIconID(101);

	if(ChangeWindowMode(TRUE) != 0) {
		return 0;
	}
	if(DxLib_Init() != 0) {
		return 0;
	}
	if(SetDrawScreen(DX_SCREEN_BACK) != 0) {
		DxLib_End();
		return 0;
	}

	//���͋@�\�̏�����
	InitInputControler();

	Vector2D c=Vector2D(400,300),r=Vector2D(0,-40);
	Hexagon bh(c,Hexagon(c+r,r).GetPoints().GetPoint(5)-c);

	unsigned int col[7]={
		GetColor(255,0,0)
		,GetColor(255,255,0)
		,GetColor(0,255,0)
		,GetColor(0,255,255)
		,GetColor(0,0,255)
		,GetColor(255,0,255)
		,GetColor(255,255,255)
	};

	Hexagon h[7]={
		Hexagon(bh.GetPoints().GetPoint(0),r)
		,Hexagon(bh.GetPoints().GetPoint(1),r)
		,Hexagon(bh.GetPoints().GetPoint(5),r)
		,Hexagon(c,r)
		,Hexagon(bh.GetPoints().GetPoint(2),r)
		,Hexagon(bh.GetPoints().GetPoint(4),r)
		,Hexagon(bh.GetPoints().GetPoint(3),r)
	};
	
	std::vector<std::shared_ptr<Block>> b={
		std::shared_ptr<Block>(new NormalBlock(bh.GetPoints().GetPoint(0),std::vector<Block::Conductor>{Block::Conductor(1,2)}))
		,std::shared_ptr<Block>(new NormalBlock(bh.GetPoints().GetPoint(1),std::vector<Block::Conductor>{Block::Conductor(4,2)}))
		,std::shared_ptr<Block>(new NormalBlock(bh.GetPoints().GetPoint(5),std::vector<Block::Conductor>{Block::Conductor(0,1),Block::Conductor(2,3)}))
		,std::shared_ptr<Block>(new NormalBlock(c,std::vector<Block::Conductor>{Block::Conductor(0,5),Block::Conductor(1,2),Block::Conductor(3,4)}))
		,std::shared_ptr<Block>(new NormalBlock(bh.GetPoints().GetPoint(2),std::vector<Block::Conductor>{Block::Conductor(3,4)}))
		,std::shared_ptr<Block>(new NormalBlock(bh.GetPoints().GetPoint(4),std::vector<Block::Conductor>{Block::Conductor(0,5),Block::Conductor(1,4),Block::Conductor(2,3)}))
		,std::shared_ptr<Block>(new NormalBlock(bh.GetPoints().GetPoint(3),std::vector<Block::Conductor>{Block::Conductor(2,4),Block::Conductor(1,5)}))
	};

	
	Stage st(4);

	PuzzleSystem puzzle;
	SRand(123456);
	
	//�A�v���P�[�V��������
	while(ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0) {
		//�Q�[���{��
		//�L�[���X�V
		input_update();
		//�`��
		puzzle.Draw();
		puzzle.Update();
		//�v�Z����
		int index=-keyboard_get(KEY_INPUT_ESCAPE);
		//�I�����o
		if(index<0){
			break;
		}
	}

	//�I������
	DeleteInputControler();//���͋@�\�̉��

	DxLib_End();

	return 0;
}
