#include "zikade.h"

bool compareHits(const hitInfo& a, const hitInfo& b) {
	if(a.tf < b.tf)
			return false;
	return true;
}

void zikade::init() {
	pLights = NULL; 
	dLights = NULL; 
	spheres = NULL;
	rays	  = NULL;

	lambda = 1.0;
	aspect = (real)SI_WIDTH / (real)SI_HEIGHT;

	numRays = SI_WIDTH*SI_HEIGHT;
	rays 		= new ray[numRays];
	sensor 	= new real3[numRays];

	move(real3(0.0, 0.0, -40.0), 0.0, 0.0, 5.0);
}

void zikade::exit() {
	SAFE_DELETE_ARRAY(pLights);
	SAFE_DELETE_ARRAY(dLights);
	SAFE_DELETE_ARRAY(spheres);
	SAFE_DELETE_ARRAY(rays);
	SAFE_DELETE_ARRAY(sensor);
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
		line >> s.c.x; line >> s.c.y; line >> s.p.z;
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
	} 
}

void zikade::loadSiff(const char* filename) {
	ifstream file(filename);
	if (!file.is_open())	{
			cerr<<"Error: Could not find siff file "<<filename<<endl;
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
			line >> s.c.x; line >> s.c.y; line >> s.c.z;
			s.k = 0.05;
			s.k = (-1.0 / (lambda * 2.0 * s.r)) * log(1 - s.k);
			s.p *= 0.01;

			tempSpheres.push_back(s);
			num++;
		}
	}

	cout<<"Loaded "<<num<<" spheres from siff file"<<endl;
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
		for(uint x = 0; x < SI_HEIGHT; ++x) {
			index = y * SI_WIDTH + x;
			r = &rays[index];
			r->d.x  = aspect * ( (((real)x/(real)SI_WIDTH) * 2.0) - 1.0 );
			r->d.y  = 1.0 - (((real)y/(real)SI_HEIGHT) * 2.0);
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
			index = y * SI_HEIGHT + x;
			image[x][y] = sensor[index];
		}
	}
}

void zikade::render(rgbWxH& image) {
	//#pragma omp parallel for schedule(dynamic, 1)
	for(uint i = 0; i < numRays; ++i) {
		sensor[i] = trace(rays[i], real3(10.0, 10.0, 10.0));	
	}
	convert(image);
}

real3 zikade::trace(const ray& r, real3 _flux) {
	list<hitInfo> hits;
	hitInfo		  hit;
	for(uint i = 0; i < numSpheres; ++i) {
		if(intersect(r, spheres[i], hit)) {
			hit.id = i;
			hits.push_back(hit);
		}
	}
	hits.sort(compareHits);

	real3 flux;
	auto end = hits.end();
	for(auto it = hits.begin(); it != end; ++it) {
		hitInfo& h = *it;
		sphere*  s = &spheres[h.id];
		
		real tau = exp(- (s->k * (h.tf - h.tn)) ); 
		real opa = 1.0 - tau;
		

		flux = opa * s->c + tau * _flux;
	}

	return flux;
}
