#include "Input/Input.h"
#include "Platform/WinApp.h"
#include "Platform/DirectXCommon.h"
//#include "2d/SpriteCommon.h"
#include "2d/Sprite.h"
#include "3d/Model.h"
#include "3d/Object3d.h"

// windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// コンソールへの文字出力
	OutputDebugStringA("Hellow,DirectX!!\n");

#pragma region 基盤システムの初期化

	// WindowsAPIの初期化
	WinApp* winApp = nullptr;
	winApp = new WinApp();
	winApp->Initialize();

	// DirectXの初期化
	DirectXCommon* dXCommon = nullptr;
	dXCommon = new DirectXCommon();
	dXCommon->Initialize(winApp);

	// 入力の初期化
	Input* input = nullptr;
	input = new Input();
	input->Initialize(winApp);

	// スプライト共通部の初期化
	/*SpriteCommon* spriteCommon = nullptr;
	spriteCommon = new SpriteCommon();
	spriteCommon->Initialize();*/

#pragma endregion 基盤システムの初期化

#pragma region 最初のシーンの初期化

	// スプライト
	Sprite* sprite = new Sprite();
	//sprite->Initialize(spriteCommon);
	Sprite title;
	SpriteCommon spriteCommon_;
	spriteCommon_ = sprite->SpriteCommonCreate(dXCommon->GetDevice(), 1280, 720);
	sprite->SpriteCommonLoadTexture(spriteCommon_, 0, L"Resources/mario.jpg", dXCommon->GetDevice());
	title.SpriteCreate(dXCommon->GetDevice(), 1280, 720);
	title.SetTexNumber(0);

	// タイトルの大きさの設定
	title.SetPosition(XMFLOAT3(300, 100, 0));
	title.SetScale(XMFLOAT2(414 * 0.5, 410 * 0.5));
	title.SpriteTransferVertexBuffer(title);
	title.SpriteUpdate(title, spriteCommon_);

	// スプライト用パイプライン生成呼び出し
	PipelineSet spritePipelineSet = sprite->SpriteCreateGraphicsPipeline(dXCommon->GetDevice());

	// 3Dオブジェクト静的初期化
	Object3d::StaticInitialize(dXCommon->GetDevice(), WinApp::window_width, WinApp::window_height );
	// OBJからモデルデータを読み込む
	Model* model = Model::LoadFromOBJ("kagi");
	// 3Dオブジェクト生成
	Object3d* object3d = Object3d::Create();
	// オブジェクトにモデルをひも付ける
	object3d->SetModel(model);
	object3d->SetPosition(XMFLOAT3(0, -20, 0));
	object3d->SetRotation(XMFLOAT3(0, 90, 0));
	
#pragma endregion 最初のシーンの初期化

	while (true) {

	#pragma region 基盤システムの更新

		// Windowsのメッセージ処理
		if (winApp->ProcessMessage()) {
			// ゲームループを抜ける
			break;
		}

		input->Update();

	#pragma endregion 基盤システムの更新

	#pragma region 最初のシーンの更新

		//sprite->Update();
		// 3Dオブジェクト更新
		object3d->Update();

	#pragma endregion 最初のシーンの更新

		// 描画前処理
		dXCommon->PreDraw();

	#pragma region 最初のシーンの描画

	#pragma region 3Dオブジェクト描画

		// 3Dオブジェクト描画前処理
		Object3d::PreDraw(dXCommon->GetCommandList());

		// 3Dオブジェクトの描画
		object3d->Draw();

		// 3Dオブジェクト描画後処理
		Object3d::PostDraw();

	#pragma endregion 3Dオブジェクト描画

		//Sprite::SpritePipelineSet spritePipelineSet;
		//sprite->Draw(spritePipelineSet.pipelineSet);
		sprite->SpriteCommonBeginDraw(dXCommon->GetCommandList(), spriteCommon_);
		title.SpriteDraw(dXCommon->GetCommandList(), spriteCommon_, dXCommon->GetDevice(), title.vbView);
		
	#pragma endregion 最初のシーンの描画

		// 描画後処理
		dXCommon->PostDraw();
	}
#pragma region 最初のシーンの終了

	// スプライト解放
	delete sprite;
	sprite = nullptr;

	// 3Dオブジェクト解放
	delete object3d;
	// 3Dモデル解放
	delete model;

#pragma endregion 最初のシーンの終了

#pragma region 基盤システムの終了

	// 入力開放
	delete input;
	input = nullptr;

	// WindowsAPIの終了処理
	winApp->Finalize();

	// WindowsAPI解放
	delete winApp;
	winApp = nullptr;

	// DirectX解放
	dXCommon->fpsFixedFinalize();
	delete dXCommon;
	dXCommon = nullptr;


#pragma endregion 基盤システムの終了

	return 0;
}