#include "2d/Sprite.h"

void Sprite::Initialize(SpriteCommon* spriteCommon){
	this->spriteCommon = spriteCommon;
}

void Sprite::Update(){

	PipelineSet object3dPipelineSet = Object3dCreateGraphicsPipeline(dev.Get());
	//HRESULT result;
	//ID3D12Device* device = nullptr;

	//// 頂点データ
	//XMFLOAT3 vertices[] = {
	//	{-0.5f, -0.5f, 0.0f}, // 左下
	//	{-0.5f, +0.5f, 0.0f}, // 左上
	//	{+0.5f, -0.5f, 0.0f}, // 右下
	//};

	//// 頂点データ全体サイズ = 頂点データ一つ分のサイズ * 頂点データの要素数
	//UINT sizeVB = static_cast<UINT>(sizeof(XMFLOAT3) * _countof(vertices));

	//// 頂点バッファの設定
	//D3D12_HEAP_PROPERTIES heapProp{}; // ヒープ設定
	//heapProp.Type = D3D12_HEAP_TYPE_UPLOAD; // GPUへの転送用
	//// リリース設定
	//D3D12_RESOURCE_DESC resDesc{};
	//resDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	//resDesc.Width = sizeVB; // 頂点全体サイズ
	//resDesc.Height = 1;
	//resDesc.DepthOrArraySize = 1;
	//resDesc.MipLevels = 1;
	//resDesc.SampleDesc.Count = 1;
	//resDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
	//
	//// 頂点バッファの生成
	//ID3D12Resource* vertBuff = nullptr;
	//result = device->CreateCommittedResource(
	//	&heapProp, // ヒープ設定
	//	D3D12_HEAP_FLAG_NONE,
	//	&resDesc, // リソース設定
	//	D3D12_RESOURCE_STATE_GENERIC_READ,
	//	nullptr,
	//	IID_PPV_ARGS(&vertBuff));
	//assert(SUCCEEDED(result));

	//// GPU上のバッファに対応した仮想メモリ(メインメモリ上)を取得する
	//XMFLOAT3* vertMap = nullptr;
	//result = vertBuff->Map(0, nullptr, (void**)&vertMap);
	//assert(SUCCEEDED(result));
	//// 全頂点に対して
	//for (int i = 0; i < _countof(vertices); i++) {
	//	vertMap[i] = vertices[i]; // 座標をコピー
	//}
	//// 繋がりを解除
	//vertBuff->Unmap(0, nullptr);

	//// 頂点バッファビューの作成
	//D3D12_VERTEX_BUFFER_VIEW vbView{};
	//// GPU仮想アドレス
	//vbView.BufferLocation = vertBuff->GetGPUVirtualAddress();
	//// 頂点バッファのサイズ
	//vbView.SizeInBytes = sizeVB;
	//// 頂点一つ分のデータサイズ
	//vbView.StrideInBytes = sizeof(XMFLOAT3);

	//ID3DBlob* vsBlob = nullptr; // 頂点シェーダオブジェクト
	//ID3DBlob* psBlob = nullptr; // ピクセルシェーダオブジェクト
	//ID3DBlob* errorBlob = nullptr; // エラーオブジェクト

	//// 頂点シェーダの読み込みとコンパイル
	//result = D3DCompileFromFile(
	//	L"SpriteVS.hlsl", // シェーダファイル
	//	nullptr,
	//	D3D_COMPILE_STANDARD_FILE_INCLUDE, // インクルード可能にする
	//	"main", "vs_5_0", // エントリーポイント名、シェーダーモデル指定
	//	D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION, // デバック用設定
	//	0,
	//	&vsBlob, &errorBlob);

	//// エラーなら
	//if (FAILED(result)) {
	//	// errorBlobからエラー内容をstring型にコピー
	//	std::string error;
	//	error.resize(errorBlob->GetBufferSize());

	//	std::copy_n((char*)errorBlob->GetBufferPointer(),
	//		errorBlob->GetBufferSize(),
	//		error.begin());
	//	error += "\n";
	//	// エラー内容を出力ウィンドウに表示
	//	OutputDebugStringA(error.c_str());
	//	assert(0);
	//}

	//// ピクセルシェーダの読み込みとコンパイル
	//result = D3DCompileFromFile(
	//	L"SpritePS.hlsl", // シェーダファイル名
	//	nullptr,
	//	D3D_COMPILE_STANDARD_FILE_INCLUDE, // インクルード可能にする
	//	"main", "ps_5_0", // エントリーポイント名、シェーダーも出る用指定
	//	0,
	//	&psBlob, &errorBlob);
}

void Sprite::Draw(SpritePipelineSet* spipelineSet) {

	// パイプラインステートとルートシグネチャの設定
	cmdList->SetPipelineState(spipelineSet->pipelineSet.pipelinestate.Get());
	cmdList->SetGraphicsRootSignature(pipelineSet.rootsignature.Get());
}

Sprite::PipelineSet Sprite::Object3dCreateGraphicsPipeline(ID3D12Device* dev)
{
	HRESULT result;
	ComPtr<ID3DBlob> vsBlob; // 頂点シェーダオブジェクト
	ComPtr<ID3DBlob> psBlob; // ピクセルシェーダオブジェクト
	ComPtr<ID3DBlob> errorBlob; // エラーオブジェクト

	// 頂点シェーダの読み込みとコンパイル
	result = D3DCompileFromFile(
		L"SpriteVS.hlsl", // シェーダファイル名
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE, // インクルード可能にする
		"main", "vs_5_0", // エントリーポイント名、シェーダーモデル指定
		D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION, // デバッグ用指定
		0,
		&vsBlob, &errorBlob);

	if (FAILED(result)) {
		// errorBlobからエラー内容をstring型にコピー
		std::string errstr;
		errstr.resize(errorBlob->GetBufferSize());

		std::copy_n((char*)errorBlob->GetBufferPointer(),
			errorBlob->GetBufferSize(),
			errstr.begin());
		errstr += "\n";
		// エラー内容を出力ウィンドウに表示
		OutputDebugStringA(errstr.c_str());
		exit(1);
	}

	// ピクセルシェーダの読み込みとコンパイル
	result = D3DCompileFromFile(
		L"SpritePS.hlsl", // シェーダファイル名
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE, // インクルード可能にする
		"main", "ps_5_0", // エントリーポイント名、シェーダーモデル指定
		D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION, // デバック用設定
		0,
		&psBlob, &errorBlob);

	if (FAILED(result)) {
		// errorBlobからエラー内容をstring型にコピー
		std::string errstr;
		errstr.resize(errorBlob->GetBufferSize());

		std::copy_n((char*)errorBlob->GetBufferPointer(),
			errorBlob->GetBufferSize(),
			errstr.begin());
		errstr += "\n";
		// エラー内容を出力ウィンドウに表示
		OutputDebugStringA(errstr.c_str());
		exit(1);
	}

	// 頂点レイアウト
	D3D12_INPUT_ELEMENT_DESC inputLayout[] = {
		{
			"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,
			D3D12_APPEND_ALIGNED_ELEMENT,
			D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0
		},
		{
			"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0,
			D3D12_APPEND_ALIGNED_ELEMENT,
			D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0
		},
	};

	// グラフィックスパイプライン設定
	D3D12_GRAPHICS_PIPELINE_STATE_DESC gpipeline{};

	gpipeline.VS.pShaderBytecode = vsBlob->GetBufferPointer();
	gpipeline.VS.BytecodeLength = vsBlob->GetBufferSize();
	gpipeline.PS.pShaderBytecode = psBlob->GetBufferPointer();
	gpipeline.PS.BytecodeLength = psBlob->GetBufferSize();

	// サンプルマスクとラスタライザステートの設定
	gpipeline.SampleMask = D3D12_DEFAULT_SAMPLE_MASK; // 標準設定

	gpipeline.RasterizerState.CullMode = D3D12_CULL_MODE_NONE; // カリングしない
	gpipeline.RasterizerState.FillMode = D3D12_FILL_MODE_SOLID; // ポリゴン内塗りつぶし
	gpipeline.RasterizerState.DepthClipEnable = true; // 深度クリッピングを有効

	// ブレンドステードの設定
	gpipeline.BlendState.RenderTarget[0].RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL; // RBGAすべてのチャンネルを描画

	// 頂点レイアウト設定
	gpipeline.InputLayout.pInputElementDescs = inputLayout;
	gpipeline.InputLayout.NumElements = _countof(inputLayout);

	// 図形の形状を三角形に設定
	gpipeline.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;

	gpipeline.NumRenderTargets = 1; // 描画対象は1つ
	gpipeline.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM; // 0～255指定のRGBA
	gpipeline.SampleDesc.Count = 1; // 1ピクセルにつき1回サンプリング

	// パイプラインとルートシグネチャのセット
	PipelineSet pipelineSet;

	D3D12_ROOT_SIGNATURE_DESC rootSignatureDesc{};
	rootSignatureDesc.Flags = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;

	ComPtr<ID3DBlob> rootSigBlob;
	// バージョン自動判定でのシリアライズ
	result = D3D12SerializeRootSignature(&rootSignatureDesc, D3D_ROOT_SIGNATURE_VERSION_1_0, &rootSigBlob, &errorBlob);
	// ルートシグネチャの生成
	result = dev->CreateRootSignature(0, rootSigBlob->GetBufferPointer(), rootSigBlob->GetBufferSize(),
		IID_PPV_ARGS(&pipelineSet.rootsignature));
	rootSigBlob->Release();

	// パイプラインにルートシグネッチャをセット
	gpipeline.pRootSignature = pipelineSet.rootsignature.Get();

	// パイプラインステートの生成
	result = dev->CreateGraphicsPipelineState(&gpipeline, IID_PPV_ARGS(&pipelineSet.pipelinestate));

	// パイプラインとルートシグネチャを返す
	return pipelineSet;
}
