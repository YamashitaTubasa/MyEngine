#include "MyGame.h"

void MyGame::Initialize()
{	
	// 基底クラスの初期化処理
	TYFramework::Initialize();

	// ゲームシーンの初期化
	gameScene = new GameScene();
	gameScene->Initialize(spriteCommon);
}

void MyGame::Finalize()
{
	// ゲームシーンの解放
	gameScene->Finalize();
	delete gameScene;

	// 基底クラスの終了処理
	TYFramework::Finalize();
}

void MyGame::Update()
{
	// 基底クラスの更新処理
	TYFramework::Update();

	// ゲームシーンの更新
	gameScene->Update();
}

void MyGame::Draw()
{
	ID3D12GraphicsCommandList* cmdList = dXCommon->GetCommandList();

#pragma region ゲームシーン描画

	//=== ゲームシーン描画 ===//
	gameScene->Draw(spriteCommon);

#pragma endregion
}
