#ifndef LIGHTSOURCE_H
#define LIGHTSOURCE_H

#pragma once

class LightSource {
	public:
		LightSource();
		LightSource(Vector3 vTotalPower);

		void setTotalPower(Vector3 vTotalPower);
	//protected:
		Vector3 m_vTotalPower;

		virtual Vector3 getLightDirection(Vector3* pPosition) = 0;
};

#endif
