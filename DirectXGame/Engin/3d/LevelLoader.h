#pragma once

#include <json.hpp>
#include <string>
#include <fstream>
#include "Vector3.h"

// レベルデータ
struct LevelData {
	// オブジェクトデータ
	struct ObjectData {
		// ファイル名
		std::string fileName;
		// 移動
		Vector3 translation;
		// 回転角
		Vector3 rotation;
		// スケール
		Vector3 scaling;
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
