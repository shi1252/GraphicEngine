#include "Transform.h"
#include "Vector.h"
#include "Matrix4x4.h"
#include <functional>

Transform::Transform()
{
	position = Vector3::zero;
	rotation = Vector3::zero;
	position.SetHook(std::bind(&Transform::ValueChanged, this));
	rotation.SetHook(std::bind(&Transform::ValueChanged, this));
	scale.SetHook(std::bind(&Transform::ValueChanged, this));
	scale = Vector3::one;
}

Transform::Transform(const Transform & t)
{
	position = t.position;
	rotation = t.rotation;
	scale = t.scale;
	matrix = t.matrix;
	invMatrix = t.invMatrix;
}

Transform::~Transform()
{
}

void Transform::Translate(Vector3 pos)
{
	position = pos;
}

void Transform::Translate(Vector3 dir, float distance)
{
	position += dir * distance;
}

void Transform::Rotate(Vector3 rot)
{
	rotation = Vector3::RotateClamp(rotation + rot);
}

Matrix4x4 Transform::GetMatrix()
{
	return matrix;
}

Matrix4x4 Transform::GetInverseMatrix()
{
	return invMatrix;
}

void Transform::ValueChanged()
{
	matrix = Matrix4x4::TRSMatrix(position, rotation, scale);
	invMatrix = Matrix4x4::InverseTRSMatrix(position, rotation, scale);
}