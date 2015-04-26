#include "zikade.h"

bool compareHits(const hitInfo& a, const hitInfo& b) {
	if(a.tn > b.tf)
			return false;
	return true;
}

real global_counter;

void zikade::init() {
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

	_look = false;
	_lookAt = real3(0.0, 0.0, 0.0);
	_pos 	 = real3(2.0, 0.0, -100.0);
	_pitch = 0.0;
	_yaw   = 0.0; 
	_focal = 20.0;
	_maxd	 = 10;
}

void zikade::exit() {
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
	while(std::getline(file, str_line, '\n')) {
		stringstream line(str_line);
		readLine(line);
	}
	file.close();

	numPLights = tempPLights.size();
	numDLights = tempDLights.size();
	numSpheres = tempSpheres.size();

	pLights = new pointLight[numPLights];
	dLights = new directionLight[numDLights];
	spheres = new sphere[numSpheres];

	for(uint i = 0; i < numPLights; ++i)
		pLights[i] = tempPLights[i];
	for(uint i = 0; i < numDLights; ++i)
		dLights[i] = tempDLights[i];
	for(uint i = 0; i < numSpheres; ++i)
		spheres[i] = tempSpheres[i];
	tempPLights.clear();
	tempDLights.clear();
	tempSpheres.clear();

	kd = new kdTree(numSpheres, spheres, _maxd);
	if(_look) move(_pos, _lookAt, _focal);
	else 	move(_pos, _pitch, _yaw, _focal);

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
		tempDLights.push_back(l);
	} else if(entry == "loadSiff") {
		string s;
		line >> s;
		loadSiff(s.c_str());
	} else if(entry == "camera") {
		line >> _pos.x; line >> _pos.y; line >> _pos.z;
		line >> _pitch; line >> _yaw;   line >> _focal;
		_pitch = DEG_TO_RAD(_pitch);
		_yaw	 = DEG_TO_RAD(_yaw);
	} else if(entry == "lookat") {
		_look = true;
		line >> _pos.x; 	 line >> _pos.y; 	  line >> _pos.z;
		line >> _lookAt.x; line >> _lookAt.y; line >> _lookAt.z;
		line >> _focal;
	} else if(entry == "kdtree") {
		line >> _maxd;
	} else if(entry == "samples") {
		line >> numSamples;
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
			line >> s.p.x; line >> s.p.y; line >> s.p.z;
			line >> s.r;
			s.sr = s.r*s.r;
			line >> s.c.x; line >> s.c.y; line >> s.c.z;
			s.k = 0.8;
			s.k = (-1.0 / (lambda * 2.0 * s.r)) * log(1 - s.k);
			//s.p *= 0.01;

			tempSpheres.push_back(s);
			num++;
		}
	}

	cout<<"Loaded "<<num<<" spheres from file"<<endl;
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
	//#pragma omp parallel num_threads(10)
	//{
		#pragma omp parallel for schedule(static, 1)
		for(uint i = 0; i < numRays; ++i) {
			sensor[i] = trace(rays[i], real3(10.0, 10.0, 10.0));
			cnt++;
			printf("\rRender: [\033[31m%.2f %%\033[0m]", ((float)cnt / (float)numRays) * 100.0f);
		}
	//}
	printf("\n");
	convert(image);
}

real3 zikade::trace(const ray& r, real3 _flux) {
	list<hitInfo> hits;
	kd->hit(r, hits);
	hits.sort(compareHits);
	real t, delta;

	real3 flux = real3(40.0, 40.0, 40.0);
	auto end = hits.end();
	for(auto it = hits.begin(); it != end; ++it) {
		hitInfo& h = *it;
		sphere*  s = &spheres[h.id];
		
		real tau = exp(- (s->k * (h.tf - h.tn)) ); 
		real opa = 1.0 - tau;

		flux = opa * s->c + tau * _flux;

		delta = (h.tf - h.tn) / (real)numSamples;
		for(t = h.tn; t < h.tf; t += delta) {
			real3 o = r.o + t * r.d;

			for(uint l = 0; l < 0; ++l) {
			}
		}
	}

	return flux;
}
