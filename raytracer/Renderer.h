#ifndef RENDERER_H
#define RENDERER_H

#pragma once

class Renderer {
	public:
		Renderer();
		virtual ~Renderer() {};

		virtual void render(Camera* pCamera) = 0;
};

#endif
