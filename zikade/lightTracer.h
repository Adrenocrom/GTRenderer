#ifndef LIGHTTRACER_H
#define LIGHTTRACER_H

#pragma once

bool compareHits(const hitInfo& a, const hitInfo& b);

class zikade {
	private:
		uint numRays;
		uint numPLights;
		uint numDLights;
		uint numSpheres;

		pointLight* 	 pLights;
		directionLight* dLights;
		sphere*			 spheres;
		ray*				 rays;
		real3*			 sensor;

		real				 lambda;
		real				 aspect;

		void readLine(stringstream& line);
		void loadSiff(const char* filename);
		void convert(rgbWxH& image);
		vector<pointLight> 		tempPLights;
		vector<directionLight>	tempDLights;
		vector<sphere>				tempSpheres;

		real3	trace(const ray& r, real3 _flux);
	public:
		zikade() {init();}
		~zikade() {exit();}

		void init();
		void render(rgbWxH& image);
		void move(real3 p, real pitch, real yaw, real f);
		void exit();

		void loadScene(const char* filename);
};

#endif
