#pragma once
#include "Component.h"
#include <vector>

class Waypoint : public Component
{
public:
	Waypoint() = default;
	~Waypoint() override = default;

	void AddWaypoint(Maths::Vector2f _waypoint) { waypoints.push_back(_waypoint); }
	std::vector<Maths::Vector2f> GetWaypoints() { return waypoints; }

	float GetIndex() { return index; }
	void SetIndex(float _index) { index = _index; }
private:
	std::vector<Maths::Vector2f> waypoints;
	float index=0;
};