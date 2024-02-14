#include "Components/SquareCollider.h"

bool SquareCollider::IsColliding(const SquareCollider& _colliderA, const SquareCollider& _colliderB, bool colliderIsEnabled)
{
	if (colliderIsEnabled) {
		const Maths::Vector2f positionA = _colliderA.GetOwner()->GetPosition();
		const Maths::Vector2f positionB = _colliderB.GetOwner()->GetPosition();
		return (positionA.X < positionB.X + _colliderB.GetWidth() && positionA.X + _colliderA.GetWidth() > positionB.X && positionA.Y < positionB.Y + _colliderB.GetHeight() && positionA.Y + _colliderA.GetHeight() > positionB.Y);
	}
	return false;
}

void SquareCollider::Update()
{
	enabled = Component::GetOwner()->isEnabled();
}
