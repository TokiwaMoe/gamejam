#pragma once

#include "CollisionPrimitive.h"
#include "RaycastHit.h"

#include <d3d12.h>
#include <forward_list>

class BaseCollider;

class CollisionManager
{
public:// �ÓI�����o�֐�
	static CollisionManager* GetInstance();

public:// �����o�֐�

	inline void AddCollider(BaseCollider* collider) {
		colliders.push_front(collider);
	}

	inline void RemoveCollider(BaseCollider* collider) {
		colliders.remove(collider);
	}

	
	void CheckAllCollisions();
	//�I�u�W�F�N�g�w��ł��鋅�Ƌ��̓����蔻��
	void ColSphere(BaseCollider*colA,BaseCollider* colB);
	bool Raycast(const Ray& ray, RaycastHit* hitInfo = nullptr, float maxDistance = D3D12_FLOAT32_MAX);
	bool Raycast(const Ray& ray, unsigned short attribute, RaycastHit* hitInfo = nullptr, float maxDistance = D3D12_FLOAT32_MAX);

	int GetColCount() { return colCount; }
	bool GetColflag() { return colflag; }
private:
	CollisionManager() = default;
	CollisionManager(const CollisionManager&) = delete;
	~CollisionManager() = default;
	CollisionManager& operator=(const CollisionManager&) = delete;

	// �R���C�_�[�̃��X�g
	std::forward_list<BaseCollider*> colliders;
	int colCount = 0;
	bool colflag = false;
};

