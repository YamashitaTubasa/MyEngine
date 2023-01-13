#include "Input/Input.h"
#include "Platform/WinApp.h"
#include "Platform/DirectXCommon.h"
#include "2d/Sprite.h"
#include "3d/Model.h"
#include "3d/Object3d.h"
#include "Scene/GameScene.h"

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

	// ゲームシーンの初期化
	GameScene* gameScene = new GameScene();

#pragma endregion 基盤システムの初期化

#pragma region 最初のシーンの初期化

	gameScene->Initialize(dXCommon, winApp);
	
#pragma endregion 最初のシーンの初期化

	while (true) {

	#pragma region 基盤システムの更新

		// Windowsのメッセージ処理
		if (winApp->ProcessMessage()) {
			// ゲームループを抜ける
			break;
		}

	#pragma endregion 基盤システムの更新

	#pragma region 最初のシーンの更新

		// ゲームシーンの更新
		gameScene->Update();
		
	#pragma endregion 最初のシーンの更新

	#pragma region 最初のシーンの描画

		// ゲームシーンの描画
		gameScene->Draw(dXCommon);

	#pragma endregion 最初のシーンの描画

	}
#pragma region 最初のシーンの終了

	// ゲームシーンの解放
	gameScene->Finalize();
	
#pragma endregion 最初のシーンの終了

#pragma region 基盤システムの終了

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