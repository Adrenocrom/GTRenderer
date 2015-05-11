#include "zikade.h"

#define winbuild

bool compareHits(const hitInfo& a, const hitInfo& b) {
	if(a.tn > b.tn)
			return false;
	return true;
}

bool compareHitsRad(const hitInfo& a, const hitInfo& b) {
	if(a.tn < b.tn)
			return false;
	return true;
}

real global_counter;

void zikade::init() {
	lights  = NULL;
	pLights = NULL; 
	dLights = NULL; 
	spheres = NULL;
	rays	  = NULL;
	kd		  = NULL;

	lambda = 1.0;
	aspect = (real)SI_WIDTH / (real)SI_HEIGHT;

	numSamples = 10;
	numRays 	  = SI_WIDTH*SI_HEIGHT;
	rays 		= new ray[numRays];
	sensor 	= new real3[numRays];

	cam_look = false;
	cam_lookAt = real3(0.0, 0.0, 0.0);
	cam_pos 	 = real3(2.0, 0.0, -100.0);
	cam_pitch = 0.0;
	cam_yaw   = 0.0; 
	cam_focal = 20.0;
	kd_maxd	 = 10;
	center_of_mass = real3(0.0, 0.0, 0.0);
	cam_com 	 = false;

	std_r = -1.0;
	std_k = -1.0;
	std_c = real3(-1.0, -1.0, -1.0);
	std_apr = 1;
	std_bg = real3(0.0, 0.0, 0.0);
}

void zikade::exit() {
	SAFE_DELETE_ARRAY(lights);
	SAFE_DELETE_ARRAY(pLights);
	SAFE_DELETE_ARRAY(dLights);
	SAFE_DELETE_ARRAY(spheres);
	SAFE_DELETE_ARRAY(rays);
	SAFE_DELETE_ARRAY(sensor);
	SAFE_DELETE(kd);
}

void zikade::loadScene(const char* filename) {
	ifstream file(filename);
	if (!file.is_open())	{
		cerr << "Error: Could not find file "<<filename<<endl;
		return;
	}
	
	string str_line;
	while(getline(file, str_line, '\n')) {
		stringstream line(str_line);
		readLine(line);
	}
	file.close();

	numPLights = tempPLights.size();
	numDLights = tempDLights.size();
	numLights  = numPLights + numDLights;
	numSpheres = tempSpheres.size();

	lights  = new lightSource*[numLights];
	pLights = new pointLight[numPLights];
	dLights = new directionLight[numDLights];
	spheres = new sphere[numSpheres];

	for(uint i = 0; i < numPLights; ++i) {
		pLights[i] = tempPLights[i];
		lights[i] = &pLights[i];
	}
	for(uint i = 0; i < numDLights; ++i) {
		dLights[i] = tempDLights[i];
		lights[numPLights + i] = &dLights[i];
	}
	for(uint i = 0; i < numSpheres; ++i)
		spheres[i] = tempSpheres[i];
	tempPLights.clear();
	tempDLights.clear();
	tempSpheres.clear();

	kd = new kdTree(numSpheres, spheres, kd_maxd);
	center_of_mass /= numSpheres;
	
	if(cam_look) {
		if(cam_com) cam_lookAt = center_of_mass;
		move(cam_pos, cam_lookAt, cam_focal);
	}
	else 	move(cam_pos, cam_pitch, cam_yaw, cam_focal);

	cerr<<"cam_pos: "<<cam_pos.x<<" "<<cam_pos.y<<" "<<cam_pos.z<<" \ncam_lookat: "<<cam_lookAt.x<<" "<<cam_lookAt.y<<" "<<cam_lookAt.z<<endl;
	cout<<"precalcs done"<<endl;
}

void zikade::readLine(stringstream& line) {
	string entry;
	getline(line, entry, ' ');

	if(entry.empty())
		return;
	if('#' == entry[0])
		return;
	if(entry == "lambda") {
		line >> lambda;
		return;
	}else if(entry == "sphere") {
		sphere s;
		line >> s.p.x; line >> s.p.y; line >> s.p.z;
		line >> s.r;
		s.sr = s.r*s.r;
		line >> s.c.x; line >> s.c.y; line >> s.c.z;
		line >> s.k;				
		s.k = (-1.0 / (lambda * 2.0 * s.r)) * log(1 - s.k);
		center_of_mass += s.p;
		tempSpheres.push_back(s);
		return;
	} else if(entry == "pointlight") {
		pointLight l;
		line >> l.p.x; line >> l.p.y; line >> l.p.z;
		line >> l.power.x; line >> l.power.y; line >> l.power.z;
		tempPLights.push_back(l);
		return;
	} else if(entry == "directional") {
		directionLight l;
		line >> l.d.x; line >> l.d.y; line >> l.d.z;
		line >> l.power.x; line >> l.power.y; line >> l.power.z;
		l.d = normalize(l.d);
		tempDLights.push_back(l);
	} else if(entry == "loadSiff") {
		string s;
		line >> s;
		loadSiff(s.c_str());
	} else if(entry == "camera") {
		line >> cam_pos.x; line >> cam_pos.y; line >> cam_pos.z;
		line >> cam_pitch; line >> cam_yaw;   line >> cam_focal;
		cam_pitch = DEG_TO_RAD(cam_pitch);
		cam_yaw	 = DEG_TO_RAD(cam_yaw);
	} else if(entry == "lookat") {
		cam_look = true;
		line >> cam_pos.x; 	 line >> cam_pos.y; 	  line >> cam_pos.z;
		line >> cam_lookAt.x; line >> cam_lookAt.y; line >> cam_lookAt.z;
		line >> cam_focal;
	} else if(entry == "lookatcom") {
		cam_look = true;
		cam_com	= true;
		line >> cam_pos.x; 	 line >> cam_pos.y; 	  line >> cam_pos.z;
		line >> cam_focal;
	} else if(entry == "kdtree") {
		line >> kd_maxd;
	} else if(entry == "samples") {
		line >> numSamples;
	} else if(entry == "setRadius") {
		line >> std_r;
	} else if(entry == "setColor") {
		line >> std_c.x;	line >> std_c.y; 	line >> std_c.z;
	} else if(entry == "setk") {
		line >> std_k;
	} else if(entry == "setApproxLevel") {
		line >> std_apr;
	} else if(entry == "setbg") {
		line >> std_bg.x; line >> std_bg.y; line >> std_bg.z;
	}
}

void zikade::loadSiff(const char* filename) {
	ifstream file(filename);
	if (!file.is_open())	{
			cerr<<"Error: Could not find file "<<filename<<endl;
			return;
	}

	uint num = 0;
	string str_line;
	while(std::getline(file, str_line, '\n')) {
		stringstream line(str_line);
		string entry;
		getline(line, entry, ' ');
										
		if(entry == "SIFFa1.0") {}
		else {
			sphere s;
			s.p.x = (real)stod(entry); 
			line >> s.p.y; line >> s.p.z;
			line >> s.r;
			if(std_r > 0.0) s.r = std_r;
			s.sr = s.r*s.r;
			line >> s.c.x; line >> s.c.y; line >> s.c.z;
			if(std_c.x >= 0.0) s.c = std_c;
			s.k = 0.3;
			if(std_k >= 0.0) s.k = std_k;
			s.k = (-1.0 / (lambda * 2.0 * s.r)) * log(1 - s.k);
			center_of_mass += s.p;

			tempSpheres.push_back(s);
			num++;
		}
	}

	cerr<<"Loaded "<<num<<" spheres from "<<filename<<endl;
	file.close();
}

void zikade::move(real3 p, real pitch, real yaw, real f) {
	real3x3 mRot;
	const real cosp = cos(pitch);
	const real sinp = sin(pitch);
	const real cosy = cos(yaw);
	const real siny = sin(yaw);
	mRot[0] = cosp;  mRot[1] = -(siny * sinp); mRot[2] = cosy * sinp;
	mRot[3] = 0.0;	  mRot[4] = cosy; 			 mRot[5] = -siny;
	mRot[6] = -cosp; mRot[7] = -(siny * cosp); mRot[8] = cosy * cosp;

	uint index;
	ray*  r;
	for(uint y = 0; y < SI_HEIGHT; ++y) {
		for(uint x = 0; x < SI_WIDTH; ++x) {
			index = y * SI_WIDTH + x;
			r = &rays[index];
			r->d.x  = (((real)x/(real)(SI_WIDTH))  * 2.0 - 1.0) * aspect;
			r->d.y  = 1.0 - ((real)y/(real)(SI_HEIGHT)) * 2.0;
			r->d.z  = f;
			r->d.rotate(mRot);
			r->d = normalize(r->d);
			r->o = p;
		}
	}
}

void zikade::move(real3 p, real3 l, real f) {
	real3x3 mRot;
	real3	  zaxis = normalize(l - p);
	real3	  xaxis = normalize(cross(real3(0.0, 1.0, 0.0), zaxis));
	real3	  yaxis = cross(zaxis, xaxis);

	mRot[0] = xaxis.x; mRot[1] = yaxis.x; mRot[2] = zaxis.x;
	mRot[3] = xaxis.y; mRot[4] = yaxis.y; mRot[5] = zaxis.y;
	mRot[6] = xaxis.z; mRot[7] = yaxis.z; mRot[8] = zaxis.z;

	uint index;
	ray*  r;
	for(uint y = 0; y < SI_HEIGHT; ++y) {
		for(uint x = 0; x < SI_WIDTH; ++x) {
			index = y * SI_WIDTH + x;
			r = &rays[index];
			r->d.x  = (((real)x/(real)(SI_WIDTH))  * 2.0 - 1.0) * aspect;
			r->d.y  = 1.0 - ((real)y/(real)(SI_HEIGHT)) * 2.0;
			r->d.z  = f;
			r->d.rotate(mRot);
			r->d = normalize(r->d);
			r->o = p;
		}
	}
}

void zikade::convert(rgbWxH& image) {
	uint index;
	for(uint y = 0; y < SI_HEIGHT; ++y) {
		for(uint x = 0; x < SI_WIDTH; ++x) {
			index = y * SI_WIDTH + x;
			image[x][y] = sensor[index];
		}
	}
}

void zikade::render(rgbWxH& image) {
	uint cnt = 0;
	
	#pragma omp parallel for schedule(static, 1)
	for(uint i = 0; i < numRays; ++i) {
		sensor[i] = trace(rays[i], std_bg);
		cnt++;
		
		#ifdef winbuild
			printf("\rRender: [%.2f %%]", ((float)cnt / (float)numRays) * 100.0f);
		#else
			printf("\rRender: [\033[31m%.2f %%\033[0m]", ((float)cnt / (float)numRays) * 100.0f);
		#endif
	}
	
	printf("\n");
	convert(image);
}

real3 zikade::radiance(const ray& r, uint depth, ushort* xi) {
/*	list<hitInfo> hits;
	kd->hit(r, hits);
	hits.sort(compareHitsRad);
	if(hits.empty()) return real3();

	hitInfo& hit = hits.front();
	const sphere& s = spheres[hit.id];
	real3 pos  = r.o + hit.tn * r.d;
	real3 n    = normalize(pos - s.p);
	real3 nl   = dot(n, r.d) < 0 ? n : n*-1.0;
	real3 c	  = s.c;
	real  p = c.x > c.y && c.x > c.z ? c.x : c.y > c.z ? c.y : c.z; // max refl
	default_random_engine generator;
	uniform_real_distribution<real> distribution(0.0, 1.0);

	if (++depth > 25) {
		if (distribution(generator) < p) c *= (1 / p); 
		else return s.c;
	}

	real r1	= 2*M_PI*distribution(generator);
	real r2	= distribution(generator);
	real r2s	= sqrt(r2);
	real3 w = nl; 
	real3 u = normalize(cross(fabs(w.x) > 0.1 ? real3(0.0, 1.0, 0.0 ) : real3(1.0, 0.0, 0.0), w));
	real3 v = cross(w, u);
	real3 d = normalize(u * cos(r1) * r2s + v * sin(r1) * r2s + w * sqrt(1.0 - r2));

	return s.c + c * radiance(ray(pos , d), depth , xi);*/
	return real3();
}

real3 zikade::trace(const ray& r, real3 Ib, uint d, int id) {
	list<hitInfo> hits;
	kd->hit(r, hits, id);
	hits.sort(compareHits);
	hitInfo hit;
	int cnt = 0; 
	int apx = hits.size() - std_apr;
	real t, dx, T;
	real3 Ie, C, o;

	auto end = hits.end();
	for(auto it = hits.begin(); it != end; ++it) {
		hitInfo& h = *it;
		sphere*  s = &spheres[h.id];
		
		T = trans(s, h.tn, h.tf);
		C = real3();

		Ib = Ib * T;
		Ie	= real3();
		if(d > 0) {
			if(numLights && cnt >= apx) {
				dx = (h.tf - h.tn) / (real)numSamples;
				for(t = h.tn; t < h.tf; t += dx) {
					o = r.o + t * r.d;

					C = real3(0.0, 0.0, 0.0);
					for(uint l = 0; l < numLights; ++l) {
						hit.tf = 0.0;
						ray s_r(o, -lights[l]->direction(o));
						s->intersect(s_r, hit);
						real3 po = s_r.o + hit.ft * s_r.d;
						real3 n  = normalize(po - s.p);
		
						T = trans(s, 0, hit.tf);
						C += T * trace(s_r, lights[l]->power, d-1, h.id) + (1 - T) * s->c;
					}
					C /= (real)numLights;
	
					T = trans(s, t, h.tf);
					Ie += T * C * dx;
				}
			}
			else {
				Ie  = (1-T) * s->c;
			}
			++cnt;
		} 

		Ib = Ib + Ie;
	}

	return Ib;
}
