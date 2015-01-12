#include "GTRenderer.h"

LightSource::LightSource()
: m_vTotalPower(Vector3(0.0f)) {

}

LightSource::LightSource(Vector3 vTotalPower)
: m_vTotalPower(vTotalPower) {

}

void LightSource::setTotalPower(Vector3 vTotalPower) {
	m_vTotalPower = vTotalPower;
}
