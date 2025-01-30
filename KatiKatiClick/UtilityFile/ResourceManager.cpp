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

const std::vector<int>& ResourceManager::GetSoftImages(const char* file_name, int all_num, int num_x, int num_y, int size_x, int size_y)
{
	// コンテナ内に指定ファイルが無ければ、生成する
	if (images_container.count(file_name) == NULL)
	{
		if (all_num == 1)
		{
			CreateSoftImagesResource(file_name);
		}
		else
		{
			CreateSoftImagesResource(file_name, all_num, num_x, num_y, size_x, size_y);
		}
	}

	return images_container[file_name];
}

const int ResourceManager::GetSounds(std::string file_name)
{
	// コンテナ内に指定ファイルが無ければ、生成する
	if (sounds_container.count(file_name) == NULL)
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

	// 全ての音源を削除
	for (std::pair<std::string, int> value : sounds_container)
	{
		InitSoundMem(value.second);
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

void ResourceManager::CreateSoftImagesResource(std::string file_name)
{
	int img[6] = {};
	// 指定されたファイルを読み込み元となるソフトイメージを取得
	int soft_img = LoadSoftImage(file_name.c_str());

	// エラーチェック
	if (soft_img == -1)
	{
		throw(file_name + "がありません\n");
	}

	//画像データとして作成する
	img[0] = CreateGraphFromSoftImage(soft_img);

	//ソフトイメージの改造:青
	SetPaletteSoftImage(soft_img, 2, 77, 141, 166,255);
	SetPaletteSoftImage(soft_img, 3, 97, 192, 206,255);

	//改造したデータを画像データとして作成する
	img[1]=CreateGraphFromSoftImage(soft_img);

	//ソフトイメージの改造:紫
	SetPaletteSoftImage(soft_img, 2, 127, 77, 166, 255);
	SetPaletteSoftImage(soft_img, 3, 179, 97, 206, 255);

	//改造したデータを画像データとして作成する
	img[2] = CreateGraphFromSoftImage(soft_img);

	//ソフトイメージの改造:緑
	SetPaletteSoftImage(soft_img, 2, 77, 166, 108, 255);
	SetPaletteSoftImage(soft_img, 3, 97, 206, 134, 255);

	//改造したデータを画像データとして作成する
	img[3] = CreateGraphFromSoftImage(soft_img);

	//ソフトイメージの改造:赤
	DxLib::SetPaletteSoftImage(soft_img, 2, 206, 97, 97, 255);
	DxLib::SetPaletteSoftImage(soft_img, 3, 166, 77, 77, 255);
	//改造したデータを画像データとして作成する
	img[4] = CreateGraphFromSoftImage(soft_img);

	//ソフトイメージの改造:黄色
	SetPaletteSoftImage(soft_img, 2, 232, 173, 24, 255);
	SetPaletteSoftImage(soft_img, 3, 253, 209, 89, 255);

	//改造したデータを画像データとして作成する
	img[5] = CreateGraphFromSoftImage(soft_img);

	for (int i = 1; i <= 5; i++) {
		// コンテナに読み込んだ画像を追加する
		images_container[file_name].push_back(img[i]);
	}

	DeleteSoftImage(soft_img);

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

void ResourceManager::CreateSoftImagesResource(std::string file_name, int all_num, int num_x, int num_y, int size_x, int size_y)
{
	// 指定されたファイルを読み込む
	int* img =  new int[all_num];
	int soft_img = LoadSoftImage(file_name.c_str());


	// エラーチェック
	if (soft_img == -1)
	{
		throw(file_name + "がありません\n");
	}

	//変更前の画像を保存
	//DxLib::CreateDivGraphFromSoftImage(soft_img, all_num, num_x, num_y, size_x, size_y, img);

	//ソフトイメージの改造:青
	DxLib::SetPaletteSoftImage(soft_img, 2, 77, 141, 166, 255);
	DxLib::SetPaletteSoftImage(soft_img, 3, 97, 192, 206, 255);

	//分割読込
	DxLib::CreateDivGraphFromSoftImage(soft_img, all_num, num_x, num_y, size_x, size_y, img);
	// コンテナに読み込んだ画像を追加する
	for (int i = 0; i < all_num; i++)
	{
		images_container[file_name].push_back(img[i]);
	}

	//ソフトイメージの改造:紫
	DxLib::SetPaletteSoftImage(soft_img, 2, 127, 77, 166, 255);
	DxLib::SetPaletteSoftImage(soft_img, 3, 179, 97, 206, 255);
	//分割読込
	DxLib::CreateDivGraphFromSoftImage(soft_img, all_num, num_x, num_y, size_x, size_y, img);
	// コンテナに読み込んだ画像を追加する
	for (int i = 0; i < all_num; i++)
	{
		images_container[file_name].push_back(img[i]);
	}

	//ソフトイメージの改造:緑
	DxLib::SetPaletteSoftImage(soft_img, 2, 77, 166, 108, 255);
	DxLib::SetPaletteSoftImage(soft_img, 3, 97, 206, 134, 255);
	//分割読込
	DxLib::CreateDivGraphFromSoftImage(soft_img, all_num, num_x, num_y, size_x, size_y, img);
	// コンテナに読み込んだ画像を追加する
	for (int i = 0; i < all_num; i++)
	{
		images_container[file_name].push_back(img[i]);
	}

	//ソフトイメージの改造:赤
	DxLib::SetPaletteSoftImage(soft_img, 2, 206,97, 97, 255);
	DxLib::SetPaletteSoftImage(soft_img, 3, 166, 77, 77, 255);
	//分割読込
	DxLib::CreateDivGraphFromSoftImage(soft_img, all_num, num_x, num_y, size_x, size_y, img);
	// コンテナに読み込んだ画像を追加する
	for (int i = 0; i < all_num; i++)
	{
		images_container[file_name].push_back(img[i]);
	}

	//ソフトイメージの改造:黄色
	SetPaletteSoftImage(soft_img, 2, 232, 173, 24, 255);
	SetPaletteSoftImage(soft_img, 3, 253, 209, 89, 255);
	//分割読込
	DxLib::CreateDivGraphFromSoftImage(soft_img, all_num, num_x, num_y, size_x, size_y, img);
	// コンテナに読み込んだ画像を追加する
	for (int i = 0; i < all_num; i++)
	{
		images_container[file_name].push_back(img[i]);
	}
	
	// 動的メモリの解放
	if (img != nullptr) {
		delete[] img;
	}
	DeleteSoftImage(soft_img);
}

void ResourceManager::CreateSoundsResource(std::string file_name)
{
	// 指定されたファイルを読み込む
	int handle = LoadSoundMem(file_name.c_str());

	// エラーチェック
	if (handle == -1)
	{
		throw(file_name + "がありません\n");
	}

	// コンテナに読み込んだ音源を追加する
	sounds_container[file_name] = handle;
}