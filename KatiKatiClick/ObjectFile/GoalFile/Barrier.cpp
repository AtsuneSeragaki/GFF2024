#include "Barrier.h"
#include "DxLib.h"
#include "../../UtilityFile/Define.h"
#include "../../UtilityFile/ResourceManager.h"

Barrier::Barrier()
{
	location.x = (float)SCREEN_WIDTH / 2.0f;
	width = (float)SCREEN_WIDTH;
	height = (float)ONE_LANE_HEIGHT / 4.0f;
	shape = Shape::square;
	object_type = ObjectType::barrier;
	hp = 2;
	can_hit = true;

	// ResourceManagerのインスタンスを取得
	ResourceManager* rm = ResourceManager::GetInstance();
	std::vector<int> tmp_img;

	//敵画像の読み込み
	tmp_img = rm->GetImages("Resource/Images/Barrier/Barrier.png");
	img.push_back(tmp_img[0]);

}

Barrier::~Barrier()
{
}

void Barrier::Initialize()
{
}

void Barrier::Update()
{
	if (hp <= 0)
	{
		can_delete = true;
	}
}

void Barrier::Draw() const
{

	DrawRotaGraph(location.x, location.y, 1, 0, img[0], TRUE);
	
	//DrawBox((int)location.x - (int)width / 2, (int)location.y - (int)height / 2, (int)location.x + (int)width / 2, (int)location.y + (int)height / 2, 0xffff00, TRUE);
	//DrawBox((int)location.x - (int)width / 2, (int)location.y - (int)height / 2, (int)location.x + (int)width / 2, (int)location.y + (int)height / 2, 0xAD6820, FALSE);
}

void Barrier::HitReaction(ObjectBase* character)
{
	if (character->GetObjectType() == ObjectType::enemy)
	{
		if (hp > 0)
		{
			hp -= 1;
		}
	}
}
