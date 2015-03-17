#include "GTRenderer.h"

DirectionLight::DirectionLight(Vector3 vDirection, Vector3 vTotalPower) 
: LightSource(vTotalPower), m_vDirection(vDirection) {

}

Vector3 DirectionLight::getLightDirection(Vector3* pPosition) {
	return Vector3NormalizeEx(m_vDirection);
}
