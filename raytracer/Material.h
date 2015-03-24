#ifndef MATERIAL_H
#define MATERIAL_H

#pragma once

class Material {
	public:
		Material();
		Material(Vector3 vColor, double dLambda);		

		Vector3	m_vColor;
		double	m_dLambda;
};

#endif
