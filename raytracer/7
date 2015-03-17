#include "GTRenderer.h"

PointLight::PointLight(Vector3 vPosition, Vector3 vTotalPower)
: LightSource(vTotalPower), m_vPosition(vPosition) {

}

Vector3 PointLight::getLightDirection(Vector3* pPosition) {
	if(pPosition)	
		return Vector3Normalize(*pPosition - m_vPosition);
	
	printf("\n\033[31mError no correct Pointer to Position\033[0m\n");
	return Vector3(0.0, 0.0, -1.0);
}
