#ifndef POINTLIGHT_H
#define POINTLIGHT_H

#pragma once

class PointLight :  public LightSource {
	public:
		Vector3	m_vPosition;	

		PointLight(Vector3 vPosition, Vector3 vTotalPower = Vector3(1.0, 1.0, 1.0));
		Vector3 getLightDirection(Vector3* pPosition);
};

#endif
