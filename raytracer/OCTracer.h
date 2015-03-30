#ifndef OCTRACER_H
#define OCTRACER_H

#pragma once

bool g_compare_positions (const IntersectionInfo& first, const IntersectionInfo& second);

void renderPixel(int tId, int iChunkSize, double dMax, Scene* pScene, Camera* pCamera);

extern double g_dCounter;

class OCTracer : public Renderer {
	public:
		OCTracer();
		virtual ~OCTracer() {};

		void render(Scene* pScene, Camera* pCamera);

		static Vector3 calcColorOfRay(Scene* 	pScene, 
				 					 		 	Ray* 		pRay, 
									  			Vector3 	vLightColor,
									  			int			iObjectId,
									  			int 		iDepth, 
									  			int 		iMaxDepth);
};

#endif
