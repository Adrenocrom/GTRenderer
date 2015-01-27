#include "GTRenderer.h"

PointLight::PointLight(Vector3 vPosition, Vector3 vTotalPower)
: LightSource(vTotalPower), m_vPosition(vPosition) {

}
