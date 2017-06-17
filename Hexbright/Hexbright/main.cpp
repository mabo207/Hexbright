#include"DxLib.h"
#include"GraphicControl.h"
#include"input.h"
#include"ToolsLib.h"

#include"Hexagon.h"

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

	Vector2D c=Vector2D(400,300),r=Vector2D(-40,0);
	Hexagon bh(c,Hexagon(c+r,r).GetPoints().GetPoint(5)-c);

	Hexagon h[7]={
		Hexagon(bh.GetPoints().GetPoint(0),r)
		,Hexagon(bh.GetPoints().GetPoint(1),r)
		,Hexagon(bh.GetPoints().GetPoint(5),r)
		,Hexagon(c,r)
		,Hexagon(bh.GetPoints().GetPoint(2),r)
		,Hexagon(bh.GetPoints().GetPoint(4),r)
		,Hexagon(bh.GetPoints().GetPoint(3),r)
	};

	unsigned int col[7]={
		GetColor(255,0,0)
		,GetColor(255,255,0)
		,GetColor(0,255,0)
		,GetColor(0,255,255)
		,GetColor(0,0,255)
		,GetColor(255,0,255)
		,GetColor(255,255,255)
	};

	//�A�v���P�[�V��������
	while(ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0) {
		//�Q�[���{��
		//�L�[���X�V
		input_update();
		//�`��
		int flag=FALSE;
		if(keyboard_get(KEY_INPUT_NUMPADENTER)>0){
			flag=TRUE;
		}
		for(int i=0;i<7;i++){
			h[i].Draw(col[i],flag);
		}
		//�v�Z����
		int index=-keyboard_get(KEY_INPUT_BACK);
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
