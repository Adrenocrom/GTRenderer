#include "zikade.h"

rgbWxH image;

void renderScene(string in,  string out); 
void renderSceneEx(string in, string out);

int main(int argc, char* argv[]) {
	string in	= "scene.txt";
	string out	= "out.pbm";
	string param= "";

	if(argc > 1) in  		= argv[1];
	if(argc > 2) out 		= argv[2];
	if(argc > 3) param 	= argv[3];

	if(param == "-e") renderSceneEx(in, out);
	else	renderScene(in, out);

	return 0;
}

void renderScene(string in, string out) {
	zikade zi;
	zi.loadScene(in.c_str());
	time_t begin, end;
	time(&begin);
	zi.render(image);
	time(&end);
	fprintf(stderr, "time in seconds: %.2f\n", difftime(end, begin));

	saveRgbWxHToPbm(image, out.c_str());
}

void renderSceneEx(string in, string out) {
	clock_t cbegin, cend;
	time_t  tbegin, tend;
	zikade zi;
	cbegin = clock();
	zi.loadScene(in.c_str());
	cend	 = clock();
	fprintf(stderr, "loaded in %.2f\n", ((float)(cend - cbegin)) / CLOCKS_PER_SEC);

	uint samples;
	for(uint s = 0; s <= 50; s += 5) {
		if(s == 0) samples = 1;
		else	   samples = s;	
		
		if(s == 50) {
			for(uint a = 0; a <= 4; a += 1) {
				cerr<<"samples = "<<samples<<", alevel = "<<a<<endl;
				printf("samples = %d, alevel = %d\n", samples, a);
				time(&tbegin);
				zi.setNumSamples(s);
				zi.setApproximationLevel(a);
				zi.render(image);
				time(&tend);
				cerr<<"time in seconds: "<<difftime(tend, tbegin)<<endl;
				printf("time in seconds: %.2f\n", difftime(tend, tbegin));
				string name(out+to_string(SI_WIDTH)+"x"+to_string(SI_HEIGHT)+"_samples_"+to_string(samples)+"_approx_"+to_string(a)+".pbm");
				//out += <<SI_WIDTH<<"x"<<SI_HEIGHT<<"_samples_"<<s<<"_approx_"<<a<<".pbm";
				saveRgbWxHToPbm(image, name.c_str());
			}
		}
		else {
			uint a = 3;
			cerr<<"samples = "<<samples<<", alevel = "<<a<<endl;
			printf("samples = %d, alevel = %d\n", samples, a);
			time(&tbegin);
			zi.setNumSamples(s);
			zi.setApproximationLevel(a);
			zi.render(image);
			time(&tend);
			cerr<<"time in seconds: "<<difftime(tend, tbegin)<<endl;
			printf("time in seconds: %.2f\n", difftime(tend, tbegin));
			string name(out+to_string(SI_WIDTH)+"x"+to_string(SI_HEIGHT)+"_samples_"+to_string(samples)+"_approx_"+to_string(a)+".pbm");
			//out += <<SI_WIDTH<<"x"<<SI_HEIGHT<<"_samples_"<<s<<"_approx_"<<a<<".pbm";
			saveRgbWxHToPbm(image, name.c_str());
		}
	}
}
