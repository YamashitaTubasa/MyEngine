#pragma once

#include <json.hpp>
#include <string>
#include <fstream>
#include "Vector3.h"
#include <DirectXMath.h>

// レベルデータ
struct LevelData {
	// オブジェクトデータ
	struct ObjectData {
		// ファイル名
		std::string fileName;
		// 移動
		DirectX::XMVECTOR translation;
		// 回転角
		DirectX::XMVECTOR rotation;
		// スケール
		DirectX::XMVECTOR scaling;
	};
	std::vector<ObjectData> objects;
};

class LevelLoader
{
public:
	/// <summary>
	/// レベルデータファイル読み込み
	/// </summary>
	/// <returns></returns>
	static LevelData* LoadFile(std::string fileName);
};
