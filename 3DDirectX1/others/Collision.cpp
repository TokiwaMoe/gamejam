#include"Collision.h"
using namespace DirectX;

bool Collision::CheackSphere2Plane(const Sphere& sphere, const Plane& plane, DirectX::XMVECTOR* inter)
{
	XMVECTOR distV = XMVector3Dot(sphere.center, plane.normal);
	float dist = distV.m128_f32[0] - plane.distance;
	if (fabsf(dist) > sphere.radius) return false;
	if (inter) {
		*inter = -dist * plane.normal + sphere.center;
	}
	return true;
}


	void Collision::ClosestPtPoint2Triangle(const DirectX::XMVECTOR & point, const Triangle & triangle, DirectX::XMVECTOR * closest)
	{
		// point��p0�̊O���̒��_�̈�̒��ɂ��邩�ǂ����`�F�b�N
		XMVECTOR p0_p1 = triangle.p1 - triangle.p0;
		XMVECTOR p0_p2 = triangle.p2 - triangle.p0;
		XMVECTOR p0_pt = point - triangle.p0;

		XMVECTOR d1 = XMVector3Dot(p0_p1, p0_pt);
		XMVECTOR d2 = XMVector3Dot(p0_p2, p0_pt);

		if (d1.m128_f32[0] <= 0.0f && d2.m128_f32[0] <= 0.0f)
		{
			// p0���ŋߖT
			*closest = triangle.p0;
			return;
		}

		// point��p1�̊O���̒��_�̈�̒��ɂ��邩�ǂ����`�F�b�N
		XMVECTOR p1_pt = point - triangle.p1;

		XMVECTOR d3 = XMVector3Dot(p0_p1, p1_pt);
		XMVECTOR d4 = XMVector3Dot(p0_p2, p1_pt);

		if (d3.m128_f32[0] >= 0.0f && d4.m128_f32[0] <= d3.m128_f32[0])
		{
			// p1���ŋߖT
			*closest = triangle.p1;
			return;
		}

		// point��p0_p1�̕ӗ̈�̒��ɂ��邩�ǂ����`�F�b�N���A�����point��p0_p1��ɑ΂���ˉe��Ԃ�
		float vc = d1.m128_f32[0] * d4.m128_f32[0] - d3.m128_f32[0] * d2.m128_f32[0];
		if (vc <= 0.0f && d1.m128_f32[0] >= 0.0f && d3.m128_f32[0] <= 0.0f)
		{
			float v = d1.m128_f32[0] / (d1.m128_f32[0] - d3.m128_f32[0]);
			*closest = triangle.p0 + v * p0_p1;
			return;
		}

		// point��p2�̊O���̒��_�̈�̒��ɂ��邩�ǂ����`�F�b�N
		XMVECTOR p2_pt = point - triangle.p2;

		XMVECTOR d5 = XMVector3Dot(p0_p1, p2_pt);
		XMVECTOR d6 = XMVector3Dot(p0_p2, p2_pt);
		if (d6.m128_f32[0] >= 0.0f && d5.m128_f32[0] <= d6.m128_f32[0])
		{
			*closest = triangle.p2;
			return;
		}

		// point��p0_p2�̕ӗ̈�̒��ɂ��邩�ǂ����`�F�b�N���A�����point��p0_p2��ɑ΂���ˉe��Ԃ�
		float vb = d5.m128_f32[0] * d2.m128_f32[0] - d1.m128_f32[0] * d6.m128_f32[0];
		if (vb <= 0.0f && d2.m128_f32[0] >= 0.0f && d6.m128_f32[0] <= 0.0f)
		{
			float w = d2.m128_f32[0] / (d2.m128_f32[0] - d6.m128_f32[0]);
			*closest = triangle.p0 + w * p0_p2;
			return;
		}

		// point��p1_p2�̕ӗ̈�̒��ɂ��邩�ǂ����`�F�b�N���A�����point��p1_p2��ɑ΂���ˉe��Ԃ�
		float va = d3.m128_f32[0] * d6.m128_f32[0] - d5.m128_f32[0] * d4.m128_f32[0];
		if (va <= 0.0f && (d4.m128_f32[0] - d3.m128_f32[0]) >= 0.0f && (d5.m128_f32[0] - d6.m128_f32[0]) >= 0.0f)
		{
			float w = (d4.m128_f32[0] - d3.m128_f32[0]) / ((d4.m128_f32[0] - d3.m128_f32[0]) + (d5.m128_f32[0] - d6.m128_f32[0]));
			*closest = triangle.p1 + w * (triangle.p2 - triangle.p1);
			return;
		}

		float denom = 1.0f / (va + vb + vc);
		float v = vb * denom;
		float w = vc * denom;
		*closest = triangle.p0 + p0_p1 * v + p0_p2 * w;
	}

	bool Collision::CheckSphere2Triangle(const Sphere& sphere, const Triangle& triangle, DirectX::XMVECTOR* inter)
	{
		XMVECTOR p;
		ClosestPtPoint2Triangle(sphere.center, triangle, &p);
		XMVECTOR v = p - sphere.center;
		v = XMVector3Dot(v, v);
		if (v.m128_f32[0]> sphere.radius* sphere.radius) return false;
		if (inter) {
			*inter = p;
		}
		return true;
	}

	bool Collision::CheckRay2Plane(const Ray& ray, const Plane& plane, float* distance, DirectX::XMVECTOR* inter)
	{
		const float epsilon = 1.0e-5f;	// �덷�z���p�̔����Ȓl

		float d1 = XMVector3Dot(plane.normal, ray.dir).m128_f32[0];
		// ���ʂɂ͓�����Ȃ�
		if (d1 > -epsilon) {
			return false;
		}

		float d2 = XMVector3Dot(plane.normal, ray.start).m128_f32[0];
		float t = (plane.distance - d2) / d1;

		if (t < 0) return false;

		// ��������������
		if (distance) {
			*distance = t;
		}

		// ��_���v�Z
		if (inter) {
			*inter = ray.start + t * ray.dir;
		}

		return true;

	}

	bool Collision::CheckRay2Triangle(const Ray& ray, const Triangle& triangle, float* distance, DirectX::XMVECTOR* inter)
	{
		//�O�p�`������Ă��镽�ʂ��Z�o
		Plane plane;
		XMVECTOR interPlane;
		plane.normal = triangle.normal;
		plane.distance = XMVector3Dot(triangle.normal, triangle.p0).m128_f32[0];
		//���C�ƕ��ʂ��������ĂȂ���Γ������Ă��Ȃ�
		if (!CheckRay2Plane(ray, plane, distance, &interPlane)) { return false; }
		//���C�ƕ��ʂ��������Ă����̂ŋ����ƌ�_���������܂ꂽ
		//���C�ƕ��ʂ̌�_���O�p�`�̓����ɂ��邩����
		const float epsilon = 1.0e-5f;//�덷�z���p�̔����Ȓl
		XMVECTOR m;
		//��p0_p1�ɂ���
		XMVECTOR pt_p0 = triangle.p0 - interPlane;
		XMVECTOR p0_p1 = triangle.p1 - triangle.p0;
		m = XMVector3Cross(pt_p0, p0_p1);
		//�ӂ̊O���ł���Γ������Ă��Ȃ��̂Ŕ����ł��؂�
		if (XMVector3Dot(m, triangle.normal).m128_f32[0] < -epsilon) { return false; }
		//��p1_p2�ɂ���
		XMVECTOR pt_p1 = triangle.p1 - interPlane;
		XMVECTOR p1_p2 = triangle.p2 - triangle.p1;
		m = XMVector3Cross(pt_p1, p1_p2);
		//�ӂ̊O���ł���Γ������Ă��Ȃ��̂Ŕ����ł��؂�
		if (XMVector3Dot(m, triangle.normal).m128_f32[1] < -epsilon) { return false; }
		//��p2_p0�ɂ���
		XMVECTOR pt_p2 = triangle.p2 - interPlane;
		XMVECTOR p2_p0 = triangle.p0 - triangle.p2;
		m = XMVector3Cross(pt_p0, p0_p1);
		//�ӂ̊O���ł���Γ������Ă��Ȃ��̂Ŕ����ł��؂�
		if (XMVector3Dot(m, triangle.normal).m128_f32[2] < -epsilon) { return false; }

		if (inter) {
			*inter = interPlane;
		}
		return true;
	}

	bool Collision::CheckRay2Sphere(const Ray& ray, const Sphere& sphere, float* distance, DirectX::XMVECTOR* inter)
	{
		XMVECTOR m = ray.start - sphere.center;
		float b = XMVector3Dot(m, ray.dir).m128_f32[0];
		float c = XMVector3Dot(m, m).m128_f32[0] - sphere.radius * sphere.radius;
		// ray�̎n�_��sphere�̊O���ɂ���(c > 0)�Aray��sphere���痣��Ă���������
		// �����Ă���ꍇ(b > 0)�A������Ȃ�
		if (c > 0.0f && b > 0.0f) {
			return false;
		}

		float discr = b * b - c;
		// ���̔��ʎ��̓��C�������O��Ă��邱�ƂɈ�v
		if (discr < 0.0f) {
			return false;
		}

		// ���C�͋��ƌ������Ă���B
		// ��������ŏ��̒lt���v�Z
		float t = -b - sqrtf(discr);
		// t�����ł���ꍇ�A���C�͋��̓�������J�n���Ă���̂�t���[���ɃN�����v
		if (t < 0) t = 0.0f;

		if (distance) {
			*distance = t;
		}

		if (inter) {
			*inter = ray.start + t * ray.dir;
		}

		return true;
	}

	//���Ƌ��̓����蔻��
	bool Collision::CheckSphere2Sphere(const Sphere& sphereA, const Sphere& sphereB)
	{
		//�Q�̋��̒��S���W�����ԃx�N�g�������߂�
		XMVECTOR vec = sphereA.center - sphereB.center;

		//�x�N�g���̒����̂Q��i�Q�_�Ԃ̋����̂Q��j�����߂�
		float sqLength = vec.m128_f32[0] * vec.m128_f32[0] + vec.m128_f32[1] * vec.m128_f32[1] + vec.m128_f32[2] * vec.m128_f32[2];

		//2�̋��̔��a�̍��v�����߂�
		float r = sphereA.radius + sphereB.radius;

		//�Q�_�Ԃ̋����̂Q�恃���a�̍��v�̂Q��Ȃ�Q�̋��͌������Ă���
		return  sqLength < r* r;
	}

	bool Collision::CheckSphere2Sphere2(const Sphere& sphereA, const Sphere& sphereB, DirectX::XMVECTOR* inter)
	{
		// ���S�_�̋����̂Q�� <= ���a�̘a�̂Q��@�Ȃ����
		float dist = XMVector3LengthSq(sphereA.center - sphereB.center).m128_f32[0];

		float radius2 = sphereA.radius + sphereB.radius;
		radius2 *= radius2;

		if (dist <= radius2) {
			if (inter) {
				// A�̔��a��0�̎����W��B�̒��S�@B�̔��a��0�̎����W��A�̒��S�@�ƂȂ�悤�⊮
				float t = sphereB.radius / (sphereA.radius + sphereB.radius);
				*inter = XMVectorLerp(sphereA.center, sphereB.center, t);
			}
			return true;
		}

		return false;
	}

	bool Collision::CheckSphere2Box(const Sphere& sphere, const Box& box)
	{
		float sqDistance = 0.0f;
		float pos;

		pos = sphere.center.m128_f32[0];
		if (pos < box.minPosition.m128_f32[0])
		{
			sqDistance += (box.minPosition.m128_f32[0] - pos) * (box.minPosition.m128_f32[0] - pos);
		}
		else if (pos > box.maxPosition.m128_f32[0])
		{
			sqDistance += (box.maxPosition.m128_f32[0] - pos) * (box.maxPosition.m128_f32[0] - pos);
		}

		//y�������̋����̂Q������Z
		pos = sphere.center.m128_f32[1];
		if (pos < box.minPosition.m128_f32[1])
		{
			sqDistance += (box.minPosition.m128_f32[1] - pos) * (box.minPosition.m128_f32[1] - pos);
		}
		else if (pos > box.maxPosition.m128_f32[1])
		{
			sqDistance += (box.maxPosition.m128_f32[1] - pos) * (box.maxPosition.m128_f32[1] - pos);
		}
		pos = sphere.center.m128_f32[2];
		//z�������̋����̂Q������Z
		if (pos < box.minPosition.m128_f32[2])
		{
			sqDistance += (box.minPosition.m128_f32[2] - pos) * (box.minPosition.m128_f32[2] - pos);
		}
		else if (pos > box.maxPosition.m128_f32[2])
		{
			sqDistance += (box.maxPosition.m128_f32[2] - pos) * (box.maxPosition.m128_f32[2] - pos);
		}

		return sqDistance < sphere.radius* sphere.radius;
	}

	bool Collision::CheckSphere2OBB(Sphere& sphere, OBB& obb)
	{
		XMVECTOR Vec{ 0, 0, 0,0 };   // �ŏI�I�ɒ��������߂�x�N�g��

 // �e���ɂ��Ă͂ݏo�������̃x�N�g�����Z�o
		for (int i = 0; i < 3; i++)
		{
			float L = obb.GetLen_W(i);
			if (L <= 0) continue;  // L=0�͌v�Z�ł��Ȃ�
			float s = ((sphere.center.m128_f32[0] - obb.GetPos_W().m128_f32[0]) * obb.GetDirect(i).m128_f32[0]) + ((sphere.center.m128_f32[1] - obb.GetPos_W().m128_f32[1]) * obb.GetDirect(i).m128_f32[1]) + ((sphere.center.m128_f32[2] - obb.GetPos_W().m128_f32[2]) * obb.GetDirect(i).m128_f32[2]) / L;

			// s�̒l����A�͂ݏo��������������΂��̃x�N�g�������Z
			s = fabs(s);
			if (s > 1)
				Vec += (1 - s) * L * obb.GetDirect(i);   // �͂ݏo���������̃x�N�g���Z�o
		}

		float length = (Vec.m128_f32[0] * Vec.m128_f32[0]) + (Vec.m128_f32[1] * Vec.m128_f32[1]) + (Vec.m128_f32[2] * Vec.m128_f32[2]);   // �������o��
		return length < sphere.radius* sphere.radius;
	}

	bool Collision::CheckOBB2OBB(OBB& obbA, OBB& obbB)
	{
		// �e�����x�N�g���̊m��
		// �iN***:�W���������x�N�g���j
		XMVECTOR NAe1 = obbA.GetDirect(0), Ae1 = NAe1 * obbA.GetLen_W(0);
		XMVECTOR NAe2 = obbA.GetDirect(1), Ae2 = NAe2 * obbA.GetLen_W(1);
		XMVECTOR NAe3 = obbA.GetDirect(2), Ae3 = NAe3 * obbA.GetLen_W(2);
		XMVECTOR NBe1 = obbB.GetDirect(0), Be1 = NBe1 * obbB.GetLen_W(0);
		XMVECTOR NBe2 = obbB.GetDirect(1), Be2 = NBe2 * obbB.GetLen_W(1);
		XMVECTOR NBe3 = obbB.GetDirect(2), Be3 = NBe3 * obbB.GetLen_W(2);
		XMVECTOR Interval = obbA.GetPos_W() - obbB.GetPos_W();

		// ������ : Ae1
		float rA = sqrt((Ae1.m128_f32[0] * Ae1.m128_f32[0]) + (Ae1.m128_f32[1] * Ae1.m128_f32[1]) + (Ae1.m128_f32[2] * Ae1.m128_f32[2]));
		float rB = LenSegOnSeparateAxis(&NAe1, &Be1, &Be2, &Be3);
		float L = fabs((Interval.m128_f32[0] * NAe1.m128_f32[0]) + (Interval.m128_f32[1] * NAe1.m128_f32[1]) + (Interval.m128_f32[2] * NAe1.m128_f32[2]));
		if (L > rA + rB)
			return false; // �Փ˂��Ă��Ȃ�

		// ������ : Ae2
		rA = sqrt((Ae2.m128_f32[0] * Ae2.m128_f32[0]) + (Ae2.m128_f32[1] * Ae2.m128_f32[1]) + (Ae2.m128_f32[2] * Ae2.m128_f32[2]));
		rB = LenSegOnSeparateAxis(&NAe2, &Be1, &Be2, &Be3);
		L = fabs((Interval.m128_f32[0] * NAe2.m128_f32[0]) + (Interval.m128_f32[1] * NAe2.m128_f32[1]) + (Interval.m128_f32[2] * NAe2.m128_f32[2]));
		if (L > rA + rB)
			return false; // �Փ˂��Ă��Ȃ�

		// ������ : Ae3
		rA = sqrt((Ae3.m128_f32[0] * Ae3.m128_f32[0]) + (Ae3.m128_f32[1] * Ae3.m128_f32[1]) + (Ae3.m128_f32[2] * Ae3.m128_f32[2]));
		rB = LenSegOnSeparateAxis(&NAe3, &Be1, &Be2, &Be3);
		L = fabs((Interval.m128_f32[0] * NAe3.m128_f32[0]) + (Interval.m128_f32[1] * NAe3.m128_f32[1]) + (Interval.m128_f32[2] * NAe3.m128_f32[2]));
		if (L > rA + rB)
			return false; // �Փ˂��Ă��Ȃ�

		// ������ : Be1
		rA = sqrt((Be1.m128_f32[0] * Be1.m128_f32[0]) + (Be1.m128_f32[1] * Be1.m128_f32[1]) + (Be1.m128_f32[2] * Be1.m128_f32[2]));
		rB = LenSegOnSeparateAxis(&Be1, &Ae1, &Ae2, &Ae3);
		L = fabs((Interval.m128_f32[0] * Be1.m128_f32[0]) + (Interval.m128_f32[1] * Be1.m128_f32[1]) + (Interval.m128_f32[2] * Be1.m128_f32[2]));
		if (L > rA + rB)
			return false; // �Փ˂��Ă��Ȃ�

		// ������ : Be2
		rA = sqrt((Be2.m128_f32[0] * Be2.m128_f32[0]) + (Be2.m128_f32[1] * Be2.m128_f32[1]) + (Be2.m128_f32[2] * Be2.m128_f32[2]));
		rB = LenSegOnSeparateAxis(&Be2, &Ae1, &Ae2, &Ae3);
		L = fabs((Interval.m128_f32[0] * Be2.m128_f32[0]) + (Interval.m128_f32[1] * Be2.m128_f32[1]) + (Interval.m128_f32[2] * Be2.m128_f32[2]));
		if (L > rA + rB)
			return false; // �Փ˂��Ă��Ȃ�

		// ������ : Be3
		rA = sqrt((Be3.m128_f32[0] * Be3.m128_f32[0]) + (Be3.m128_f32[1] * Be3.m128_f32[1]) + (Be3.m128_f32[2] * Be3.m128_f32[2]));
		rB = LenSegOnSeparateAxis(&Be3, &Ae1, &Ae2, &Ae3);
		L = fabs((Interval.m128_f32[0] * Be3.m128_f32[0]) + (Interval.m128_f32[1] * Be3.m128_f32[1]) + (Interval.m128_f32[2] * Be3.m128_f32[2]));
		if (L > rA + rB)
			return false; // �Փ˂��Ă��Ȃ�

		// ������ : C11
		XMVECTOR Cross;
		Cross=XMVector3Cross( NAe1, NBe1);
		rA = LenSegOnSeparateAxis(&Cross, &Ae2, &Ae3);
		rB = LenSegOnSeparateAxis(&Cross, &Be2, &Be3);
		L = fabs((Interval.m128_f32[0] * Cross.m128_f32[0]) + (Interval.m128_f32[1] * Cross.m128_f32[1]) + (Interval.m128_f32[2] * Cross.m128_f32[2]));
		if (L > rA + rB)
			return false;

		// ������ : C12
		Cross = XMVector3Cross(NAe1, NBe2);
		rA = LenSegOnSeparateAxis(&Cross, &Ae2, &Ae3);
		rB = LenSegOnSeparateAxis(&Cross, &Be1, &Be3);
		L = fabs((Interval.m128_f32[0] * Cross.m128_f32[0]) + (Interval.m128_f32[1] * Cross.m128_f32[1]) + (Interval.m128_f32[2] * Cross.m128_f32[2]));
		if (L > rA + rB)
			return false;

		// ������ : C13
		Cross = XMVector3Cross(NAe1, NBe3);
		rA = LenSegOnSeparateAxis(&Cross, &Ae2, &Ae3);
		rB = LenSegOnSeparateAxis(&Cross, &Be1, &Be2);
		L = fabs((Interval.m128_f32[0] * Cross.m128_f32[0]) + (Interval.m128_f32[1] * Cross.m128_f32[1]) + (Interval.m128_f32[2] * Cross.m128_f32[2]));
		if (L > rA + rB)
			return false;

		// ������ : C21
		Cross = XMVector3Cross(NAe2, NBe1);
		rA = LenSegOnSeparateAxis(&Cross, &Ae1, &Ae3);
		rB = LenSegOnSeparateAxis(&Cross, &Be2, &Be3);
		L = fabs((Interval.m128_f32[0] * Cross.m128_f32[0]) + (Interval.m128_f32[1] * Cross.m128_f32[1]) + (Interval.m128_f32[2] * Cross.m128_f32[2]));
		if (L > rA + rB)
			return false;

		// ������ : C22
		Cross = XMVector3Cross(NAe2, NBe2);
		rA = LenSegOnSeparateAxis(&Cross, &Ae1, &Ae3);
		rB = LenSegOnSeparateAxis(&Cross, &Be1, &Be3);
		L = fabs((Interval.m128_f32[0] * Cross.m128_f32[0]) + (Interval.m128_f32[1] * Cross.m128_f32[1]) + (Interval.m128_f32[2] * Cross.m128_f32[2]));
		if (L > rA + rB)
			return false;

		// ������ : C23
		Cross = XMVector3Cross(NAe2, NBe3);
		rA = LenSegOnSeparateAxis(&Cross, &Ae1, &Ae3);
		rB = LenSegOnSeparateAxis(&Cross, &Be1, &Be2);
		L = fabs((Interval.m128_f32[0] * Cross.m128_f32[0]) + (Interval.m128_f32[1] * Cross.m128_f32[1]) + (Interval.m128_f32[2] * Cross.m128_f32[2]));
		if (L > rA + rB)
			return false;

		// ������ : C31
		Cross = XMVector3Cross(NAe3, NBe1);
		rA = LenSegOnSeparateAxis(&Cross, &Ae1, &Ae2);
		rB = LenSegOnSeparateAxis(&Cross, &Be2, &Be3);
		L = fabs((Interval.m128_f32[0] * Cross.m128_f32[0]) + (Interval.m128_f32[1] * Cross.m128_f32[1]) + (Interval.m128_f32[2] * Cross.m128_f32[2]));
		if (L > rA + rB)
			return false;

		// ������ : C32
		Cross = XMVector3Cross(NAe3, NBe2);
		rA = LenSegOnSeparateAxis(&Cross, &Ae1, &Ae2);
		rB = LenSegOnSeparateAxis(&Cross, &Be1, &Be3);
		L = fabs((Interval.m128_f32[0] * Cross.m128_f32[0]) + (Interval.m128_f32[1] * Cross.m128_f32[1]) + (Interval.m128_f32[2] * Cross.m128_f32[2]));
		if (L > rA + rB)
			return false;

		// ������ : C33
		Cross = XMVector3Cross(NAe3, NBe3);
		rA = LenSegOnSeparateAxis(&Cross, &Ae1, &Ae2);
		rB = LenSegOnSeparateAxis(&Cross, &Be1, &Be2);
		L = fabs((Interval.m128_f32[0] * Cross.m128_f32[0]) + (Interval.m128_f32[1] * Cross.m128_f32[1]) + (Interval.m128_f32[2] * Cross.m128_f32[2]));
		if (L > rA + rB)
			return false;

		// �������ʂ����݂��Ȃ��̂Łu�Փ˂��Ă���v
		return true;
	}

	float Collision::LenSegOnSeparateAxis(DirectX::XMVECTOR* Sep, DirectX::XMVECTOR* e1, DirectX::XMVECTOR* e2, DirectX::XMVECTOR* e3)
	{
		// 3�̓��ς̐�Βl�̘a�œ��e���������v�Z
		// ������Sep�͕W��������Ă��邱��
	
		double fr1 = fabs((Sep->m128_f32[0] * e1->m128_f32[0]) + (Sep->m128_f32[1] * e1->m128_f32[1]) + (Sep->m128_f32[2] * e1->m128_f32[2]));
		
		double fr2 = fabs((Sep->m128_f32[0] * e2->m128_f32[0]) + (Sep->m128_f32[1] * e2->m128_f32[1]) + (Sep->m128_f32[2] * e2->m128_f32[2]));
		
		double fr3 = e3 ? (fabs((Sep->m128_f32[0] * e3->m128_f32[0]) + (Sep->m128_f32[1] * e3->m128_f32[1]) + (Sep->m128_f32[2] * e3->m128_f32[2]))) : 0;
		return fr1 + fr2 + fr3;
	}

	bool Collision::CheckCircle2Circle(const Circle& circleA, const Circle& circleB)
	{
		float ax = (circleB.center.x - circleA.center.x) * (circleB.center.x - circleA.center.x);
		float ay = (circleB.center.y - circleA.center.y) * (circleB.center.y - circleA.center.y);
		float ar = (circleA.radius + circleB.radius) * (circleA.radius + circleB.radius);
		if (ax + ay <= ar)
		{
			return true;
		}
		else
		{
			return false;
		}
	}





	
