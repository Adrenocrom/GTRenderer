#ifndef RENDERER_H
#define RENDERER_H

#pragma once

class Renderer {
	public:
		Renderer();
		virtual ~Renderer() {};

		virtual void render(Scene* pScene, Camera* pCamera) const = 0;
};

#endif
