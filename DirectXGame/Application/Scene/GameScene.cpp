#include "GameScene.h"

using namespace DirectX;
using namespace std;

GameScene::GameScene()
{
}

GameScene::~GameScene()
{
}

void GameScene::Initialize(SpriteCommon& spriteCommon)
{
	winApp = WinApp::GetInstance();
	input = Input::GetInstance();
	dXCommon = DirectXCommon::GetInstance();

	// カメラ
	camera = new Camera();
	camera->Initialize();

	// レベルデータの読み込み
	levelData = LevelLoader::LoadFile("test.json");

	// モデルデータを読み込む
	playerM = Model::LoadFromOBJ("fighter");
	enemyM = Model::LoadFromOBJ("enemy");

	models.insert(std::make_pair("fighter", playerM));
	models.insert(std::make_pair("enemy", enemyM));

	// レベルデータからオブジェクトを生成、配置
	for (auto& objectData : levelData->objects) {
		// ファイル名から登録済みモデルを検索
		Model* model = nullptr;
		decltype(models)::iterator it = models.find(objectData.fileName);
		if (it != models.end()) { model = it->second; }
		// モデルを指定して3Dオブジェクトを生成
		Object3d* newObject = Object3d::Create();
		newObject->SetModel(model);
		// 座標
		DirectX::XMFLOAT3 pos;
		DirectX::XMStoreFloat3(&pos, objectData.translation);
		newObject->SetPosition(pos);
		// 回転
		DirectX::XMFLOAT3 rot;
		DirectX::XMStoreFloat3(&rot, objectData.rotation);
		newObject->SetRotation(rot);
		// サイズ
		DirectX::XMFLOAT3 scale;
		DirectX::XMStoreFloat3(&scale, objectData.scaling);
		newObject->SetScale(scale);

		// 配列に登録
		objects.push_back(newObject);
	}

	position[0] = { 0.0f,0.0f,-3.0f };
	Object3d::SetEye(position[0]);
	
}

void GameScene::Update()
{
	// ImGui受付開始
	imGuiManager->Begin();

	// 入力の更新
	input->Update();

	// カメラの更新
	camera->Update();

	// 3Dオブジェクト更新
	for (auto& object : objects) {
		object->Update();
	}

	if (input->PushKey(DIK_O)) {
		position[0].x += 0.1f;
	}
	if (input->PushKey(DIK_I)) {
		position[0].x -= 0.1f;
	}
	if (input->PushKey(DIK_K)) {
		position[0].y += 0.1f;
	}
	Object3d::SetEye(position[0]);

	/*if (input->PushKey(DIK_RIGHT)) {
	//	eye[0].x += 0.5;
	//}
	if (input->PushKey(DIK_LEFT)) {
		eye[0].x -= 0.5;
	}
	if (input->PushKey(DIK_UP)) {
		eye[0].y += 0.5;
	}
	if (input->PushKey(DIK_DOWN)) {
		eye[0].y -= 0.5;
	}
	camera->SetEye(eye[0]);*/

	// オブジェクトの更新
	//ObjectUpdate();
	
	// ImGui受付終了
	imGuiManager->End();
}

void GameScene::Draw(SpriteCommon& spriteCommon)
{
#pragma region 3Dオブジェクトの描画

	// 3Dオブジェクト描画前処理
	Object3d::PreDraw(dXCommon->GetCommandList());

	// 3Dオブジェクトの描画
	for (auto& object : objects) {
		object->Draw();
	}

	// FBX3Dオブジェクトの描画
	//fbxObject->Draw(dXCommon->GetCommandList());

	// 3Dオブジェクト描画後処理
	Object3d::PostDraw();
#pragma endregion 

#pragma region パーティクルの描画

	// コマンドリストの取得
	//ID3D12GraphicsCommandList* cmdList = dXCommon->GetCommandList();

	// 3Dオブジェクト描画前処理
	ParticleManager::PreDraw(dXCommon->GetCommandList());

	// 3Dオブクジェクトの描画

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>

	// 3Dオブジェクト描画後処理
	ParticleManager::PostDraw();

#pragma endregion

#pragma region スプライト描画

	//Sprite::PreDraw(dXCommon->GetCommandList(), spriteCommon_);

	//

	//Sprite::PostDraw();

#pragma endregion
}

void GameScene::Finalize()
{
	// オブジェクトの解放
	ObjectFinalize();

	// スプライトの解放
	SpriteFinalize();
}

void GameScene::ObjectInitialize() 
{
	// OBJからモデルデータを読み込む
	//player = Model::LoadFromOBJ("fighter", "effect1.png");
	////Model[0]->LoadTexture("effect1.png");
	//enemy = Model::LoadFromOBJ("ironSphere", "ironShpere/ironSphere.png");
	////Model[2] = Model::LoadFromOBJ("skydome", "skydome/skydome.jpg");
	//// 3Dオブジェクト生成
	//playerO = Object3d::Create();
	//enemyO = Object3d::Create();
	//// オブジェクトにモデルをひも付ける
	//playerO->SetModel(player);
	//enemyO->SetModel(enemy);
	////object3d[2]->SetModel(Model[2]);
	//// 3Dオブジェクトの位置を指定
	//position[0] = { 0,-5,-35 };
	//rotation[0] = { 0,0,0 };
	//playerO->SetPosition(position[0]);
	//playerO->SetScale({ 5, 5, 5 });
	//playerO->SetRotation(rotation[0]);
	////object3d[0]->SetEye(eye[0]);

	//position[1] = { 0,0,50 };
	//enemyO->SetPosition(position[1]);
	//enemyO->SetScale({ 5,5,5 });
	//enemyO->SetRotation({ 0, 90, 0 });

	/*object3d[2]->SetPosition({ 0,-40,0 });
	object3d[2]->SetScale({ 100, 100, 100 });
	object3d[2]->SetRotation({0,100,20});*/
}

void GameScene::ObjectUpdate()
{
	

	/*if (input->PushKey(DIK_RIGHT)){
		eye[0].x += 0.5;
	}
	if (input->PushKey(DIK_LEFT)) {
		eye[0].x -= 0.5;
	}*/

	if (input->PushKey(DIK_W)) {
		position[0].y += 0.4f;
	}
	if (input->PushKey(DIK_A)) {
		position[0].x -= 0.4f;
	}
	if (input->PushKey(DIK_S)) {
		position[0].y -= 0.4f;
	}
	if (input->PushKey(DIK_D)) {
		position[0].x += 0.4f;
	}

	position[1].z -= 1;
	if (position[1].z < -100) {
		position[1].z = 50;
	}

}

void GameScene::ObjectFinalize()
{

}

void GameScene::SpriteInitialize(SpriteCommon& spriteCommon)
{
	
}

void GameScene::SpriteUpdate()
{
}

void GameScene::SpriteFinalize()
{
	// スプライト解放
	delete sprite;
	sprite = nullptr;
}

void GameScene::ParticleInitialize()
{
	//for (int i = 0; i < 100; i++) {
	//	// X,Y,Zすべて[-5.0f,+5.0f]でランダムに分布
	//	const float md_pos = 10.0f;
	//	XMFLOAT3 pos{};
	//	float posx = -5;
	//	pos.x = (float)rand() / RAND_MAX * md_pos - md_pos / 2.0f + posx;
	//	pos.y = (float)rand() / RAND_MAX * md_pos - md_pos / 2.0f;
	//	pos.z = (float)rand() / RAND_MAX * md_pos - md_pos / 2.0f;
	//	// X,Y,Z全て[-0.05f,+0.05f]でランダム分布
	//	const float md_vel = 0.1f;
	//	XMFLOAT3 vel{};
	//	vel.x = (float)rand() / RAND_MAX * md_vel - md_vel / 2.0f;
	//	vel.y = (float)rand() / RAND_MAX * md_vel - md_vel / 2.0f;
	//	vel.z = (float)rand() / RAND_MAX * md_vel - md_vel / 2.0f;
	//	// 重力に見立ててYのみ[-0.001f,0]でランダム分布
	//	XMFLOAT3 acc{};
	//	const float md_acc = 0.001f;
	//	acc.y = (float)rand() / RAND_MAX * md_acc;

	//	// 追加
	//	particleMan->Add(20, pos, vel, acc, 1.0f, 0.0);
	//}
}

void GameScene::ParticleUpdate()
{
	//// カメラ移動
	//if (input->PushKey(DIK_W) || input->PushKey(DIK_S) || input->PushKey(DIK_D) || input->PushKey(DIK_A))
	//{
	//	if (input->PushKey(DIK_W)) { ParticleManager::CameraMoveEyeVector({ 0.0f,+1.0f,0.0f }); }
	//	else if (input->PushKey(DIK_S)) { ParticleManager::CameraMoveEyeVector({ 0.0f,-1.0f,0.0f }); }
	//	if (input->PushKey(DIK_D)) { ParticleManager::CameraMoveEyeVector({ +1.0f,0.0f,0.0f }); }
	//	else if (input->PushKey(DIK_A)) { ParticleManager::CameraMoveEyeVector({ -1.0f,0.0f,0.0f }); }
	//}

	//particleMan->Update();
}

void GameScene::GameReset()
{
	
}

int GameScene::CheckCollision(XMFLOAT3 position, XMFLOAT3 scale) {
	////オブジェクトの座標
	//float objLeftX = position.x - scale.x;
	//float objRightX = position.x + scale.x;
	//float objTopY = position.y + scale.y;
	//float objBottomY = position.y - scale.y;
	//float objFrontZ = position.z - scale.z;
	//float objBZ = position.z + scale.z;
	////プレイヤーの座標
	//float playerLeftX = object3d[0]->GetPosition().x - object3d[0]->GetScale().x;
	//float playerRightX = object3d[0]->GetPosition().x + object3d[0]->GetScale().x;
	//float playerTopY = object3d[0]->GetPosition().y + object3d[0]->GetScale().y;
	//float playerBottomY = object3d[0]->GetPosition().y - object3d[0]->GetScale().y;
	//float playerFrontZ = object3d[0]->GetPosition().z - object3d[0]->GetScale().z;
	//float playerBZ = object3d[0]->GetPosition().z + object3d[0]->GetScale().z;

	//if (objLeftX < playerRightX && playerLeftX < objRightX) {
	//	if (objBottomY < playerTopY && playerBottomY < objTopY) {
	//		if (objFrontZ < playerBZ && playerFrontZ < objBZ) {
	//			return true;
	//		}
	//	}
	//}
	return true;
}
