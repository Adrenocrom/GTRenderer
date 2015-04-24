#ifndef ZIKADE_H
#define ZIKADE_H

#pragma once

#include <stdio.h>
#include <cmath>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <list>

using namespace std;

#define MIN(a, b) ((a) < (b) ? (a) : (b)) // Minimum
#define MAX(a, b) ((a) > (b) ? (a) : (b)) // Maximum
#define PI	(3.1415926535897932384626433832795f) // Pi
#define DEG_TO_RAD(x) ((x) * 0.0174532925199432957692369076848) // Grad -> Bogenmaß
#define RAD_TO_DEG(x) ((x) * 57.295779513082320876798154814105)

#define SAFE_DELETE(x)       {if((x)) {delete (x); (x) = NULL;}}										// Sicheres Löschen
#define SAFE_DELETE_ARRAY(x) {if((x)) {delete[] (x); (x) = NULL;}}	

#include "si.h"
#include "light.h"
#include "lightTracer.h"

#endif
