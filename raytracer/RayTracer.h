#ifndef RAYTRACER_H
#define RAYTRACER_H

#pragma once

class RayTracer : public Renderer {
	public:
		RayTracer();
		virtual ~RayTracer() {};

		virtual void render(Scene* pScene) const override;
};

#endif
