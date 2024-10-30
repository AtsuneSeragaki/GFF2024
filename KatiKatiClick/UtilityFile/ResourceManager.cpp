#include "ResourceManager.h"
#include "DxLib.h"

// 静的メンバ変数定義
ResourceManager* ResourceManager::instance = nullptr;

ResourceManager* ResourceManager::GetInstance()
{
	// インスタンスが生成されていない場合、生成する
	if (instance == nullptr)
	{
		instance = new ResourceManager();
	}

	// インスタンスのポインタを返却する
	return instance;
}

void ResourceManager::DeleteInstance()
{
	// インスタンスが存在していれば、削除する
	if (instance != nullptr)
	{
		instance->UnloadResourcesAll();
		delete instance;
		instance = nullptr;
	}
}

const std::vector<int>& ResourceManager::GetImages(std::string file_name, int all_num, int num_x, int num_y, int size_x, int size_y)
{
	// コンテナ内に指定ファイルが無ければ、生成する
	if (images_container.count(file_name) == NULL)
	{
		if (all_num == 1)
		{
			CreateImagesResource(file_name);
		}
		else
		{
			CreateImagesResource(file_name, all_num, num_x, num_y, size_x, size_y);
		}
	}

	return images_container[file_name];
}

const std::vector<int>& ResourceManager::GetImages(const char* file_name, int all_num, int num_x, int num_y, int size_x, int size_y)
{
	return GetImages(std::string(file_name), all_num, num_x, num_y, size_x, size_y);
}

const std::vector<int>& ResourceManager::GetImages(MaterialParam element)
{
	return GetImages(element.file_path, element.all_num, element.num_x, element.num_y, element.size_x, element.size_y);
}

const int ResourceManager::GetSounds(std::string file_name)
{
	// コンテナ内に指定ファイルが無ければ、生成する
	if (images_container.count(file_name) == NULL)
	{
		CreateSoundsResource(file_name);
	}

	return sounds_container[file_name];
}

const int ResourceManager::GetSounds(const char* file_name)
{
	return GetSounds(std::string(file_name));
}

void ResourceManager::UnloadResourcesAll()
{
	// コンテナ内に画像が無ければ、処理を終了する
	if (images_container.size() == NULL)
	{
		return;
	}

	// コンテナ内に音源が無ければ、処理を終了する
	if (sounds_container.size() == NULL)
	{
		return;
	}

	// 全ての画像を削除
	for (std::pair<std::string, std::vector<int>> value : images_container)
	{
		DeleteSharingGraph(value.second[0]);
		value.second.clear();
	}

	// 全ての画像を削除
	for (std::pair<std::string, int> value : sounds_container)
	{
		DeleteSharingGraph(value.second);
		
	}

	// コンテナを解散
	images_container.clear();
	sounds_container.clear();

}

void ResourceManager::CreateImagesResource(std::string file_name)
{
	// 指定されたファイルを読み込む
	int handle = LoadGraph(file_name.c_str());

	// エラーチェック
	if (handle == -1)
	{
		throw(file_name + "がありません\n");
	}

	// コンテナに読み込んだ画像を追加する
	images_container[file_name].push_back(handle);
}

void ResourceManager::CreateImagesResource(std::string file_name, int all_num, int num_x, int num_y, int size_x, int size_y)
{
	// 指定されたファイルを読み込む
	int* handle = new int[all_num];

	int err = LoadDivGraph(file_name.c_str(), all_num, num_x, num_y, size_x, size_y, handle);

	// エラーチェック
	if (err == -1)
	{
		throw(file_name + "がありません\n");
	}

	// コンテナに読み込んだ画像を追加する
	for (int i = 0; i < all_num; i++)
	{
		images_container[file_name].push_back(handle[i]);
	}

	// 動的メモリの解放
	delete[] handle;
}

void ResourceManager::CreateSoundsResource(std::string file_name)
{

}