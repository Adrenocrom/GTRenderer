#ifndef LIGHTSOURCE_H
#define LIGHTSOURCE_H

#pragma once

class LightSource {
	public:
		LightSource();
		LightSource(Vector3 vTotalPower);
		virtual ~LightSource();

		void setTotalPower(Vector3 vTotalPower);
	protected:
		Vector3 m_vTotalPower;
};

#endif
