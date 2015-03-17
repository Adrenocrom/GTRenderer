#ifndef OCTRACER_H
#define OCTRACER_H

#pragma once

bool g_compare_positions (const IntersectionInfo& first, const IntersectionInfo& second);

class OCTracer : public Renderer {
	public:
		OCTracer();
		virtual ~OCTracer() {};

		void render(Scene* pScene, Camera* pCamera);

		Vector3 calcColorOfRay(Scene* 	pScene, 
									  Ray* 		pRay, 
									  Vector3 	vLightColor,
									  int			iObjectId,
									  int 		iDepth, 
									  int 		iMaxDepth = 2);
};

#endif
