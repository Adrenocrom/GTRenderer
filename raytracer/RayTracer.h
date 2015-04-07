#ifndef RAYTRACER_H
#define RAYTRACER_H

#pragma once

class RayTracer : public Renderer {
	public:
		RayTracer();
		virtual ~RayTracer() {};

		void render(Camera* pCamera);

	

};

#endif
