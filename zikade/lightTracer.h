#ifndef LIGHTTRACER_H
#define LIGHTTRACER_H

#pragma once

bool compareHits(const hitInfo& a, const hitInfo& b);
bool compareHitsRad(const hitInfo& a, const hitInfo& b);

class zikade {
	private:
		uint numRays;
		uint numPLights;
		uint numDLights;
		uint numLights;
		uint numSpheres;

		lightSource**	 lights;
		pointLight* 	 pLights;
		directionLight* dLights;
		sphere*			 spheres;
		ray*				 rays;
		real3*			 sensor;
		
		real				 lambda;
		real				 aspect;
		bool				 cam_com;
		real3				 center_of_mass;
		real3				 cam_pos;
		bool				 cam_look;
		real3				 cam_lookAt;
		real				 cam_pitch;
		real				 cam_yaw;
		real				 cam_focal;
		real				 std_r;
		real3				 std_c;
		real				 std_k;
		uint				 kd_maxd;
		uint				 numSamples;
		kdTree*			 kd;

		void readLine(stringstream& line);
		void loadSiff(const char* filename);
		void convert(rgbWxH& image);
		vector<pointLight> 		tempPLights;
		vector<directionLight>	tempDLights;
		vector<sphere>				tempSpheres;

		inline real	trans(const sphere* s, const real& tn, const real& tf) {return exp( -(s->k * (tf-tn)) );}
		real3	trace(const ray& r, real3 Ib, uint d = 0; int id = -1);
		real3 radiance(const ray& r, uint d, ushort* xi = NULL);
	
	public:	
		zikade() {init();}
		~zikade() {exit();}

		void init();
		void render(rgbWxH& image);
		void move(real3 p, real pitch, real yaw, real f);
		void move(real3 p, real3 l, real f);
		void exit();

		void loadScene(const char* filename);
};

#endif
