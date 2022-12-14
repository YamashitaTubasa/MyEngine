#include "Input/Input.h"
#include "Platform/WinApp.h"
#include "Platform/DirectXCommon.h"
#include "2d/SpriteCommon.h"
#include "2d/Sprite.h"

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
	SpriteCommon* spriteCommon = nullptr;
	spriteCommon = new SpriteCommon();
	spriteCommon->Initialize();

#pragma endregion 基盤システムの初期化

#pragma region 最初のシーンの初期化

	// スプライト
	Sprite* sprite = new Sprite();
	sprite->Initialize(spriteCommon);
	
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

		sprite->Update();

	#pragma endregion 最初のシーンの更新

		// 描画前処理
		dXCommon->PreDraw();

	#pragma region 最初のシーンの描画

		Sprite::SpritePipelineSet spritePipelineSet;
		sprite->Draw(spritePipelineSet.pipelineSet);
		
	#pragma endregion 最初のシーンの描画

		// 描画後処理
		dXCommon->PostDraw();
	}
#pragma region 最初のシーンの終了

	// スプライト解放
	delete sprite;
	sprite = nullptr;

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

	// スプライトの解放
	delete spriteCommon;
	spriteCommon = nullptr;

#pragma endregion 基盤システムの終了

	return 0;
}