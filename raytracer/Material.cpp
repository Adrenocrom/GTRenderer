#include "GTRenderer.h"

Material::Material() {
	m_vColor 	= Vector3(10.0);
	m_dLambda 	= 0.5;
}

Material::Material(Vector3 vColor, double dLambda) :
	m_vColor(vColor), m_dLambda(dLambda) {

}
