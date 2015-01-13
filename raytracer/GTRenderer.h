#ifndef GTRENDERER_H
#define GTRENDERER_H

#pragma once

#include <stdio.h>
#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <QImage>

#define FM_MIN(a, b) ((a) < (b) ? (a) : (b)) // Minimum
#define FM_MAX(a, b) ((a) > (b) ? (a) : (b)) // Maximum
#define FM_PI	(3.1415926535897932384626433832795f) // Pi
#define FM_DEG_TO_RAD(x) ((x) * 0.0174532925199432957692369076848f) // Grad -> Bogenmaß
#define FM_RAD_TO_DEG(x) ((x) * 57.295779513082320876798154814105f)

#include "Vector3.h"
#include "Camera.h"
#include "Sphere.h"
#include "Ray.h"
#include "Scene.h"
#include "Renderer.h"
#include "RayTracer.h"
#include "LightSource.h"

#endif
