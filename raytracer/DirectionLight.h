#ifndef DIRECTIONLIGHT_H
#define DIRECTIONLIGHT_H

#pragma once

class DirectionLight : public LightSource {
	public:
		Vector3	m_vDirection;

		DirectionLight(Vector3 vDirection, Vector3 vTotalPower = Vector3(1.0, 1.0, 1.0));
		virtual ~DirectionLight() {};
		
};

#endif
