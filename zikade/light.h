#ifndef LIGHT_H
#define LIGHT_H

#pragma once

struct lightSource {
	real3 power;
	virtual real3 direction(const real3& _p) = 0;
};

struct pointLight : lightSource {
	real3 p;
	real3 direction(const real3& _p) {
		return normalize(_p - p);
	}
};

struct directionLight : lightSource {
	real3 d;
	real3 direction(const real3& _p) {
		return d;
	}
};

#endif
