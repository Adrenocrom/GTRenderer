#include "GTRenderer.h"

DirectionLight::DirectionLight(Vector3 vDirection, Vector3 vTotalPower) 
: LightSource(vTotalPower), m_vDirection(vDirection) {

}
