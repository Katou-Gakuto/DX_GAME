#pragma once
struct CollisionData;

class CollisionManager
{
public:
	CollisionManager() {}
	~CollisionManager() = default;

	/*当たり判定反映処理*/
	void CollisionProcess();
};