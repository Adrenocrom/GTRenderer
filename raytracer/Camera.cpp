#include "GTRenderer.h"

Image::Image(int iWidth, int iHeight) {
	m_ppvImage = NULL;
	m_ppvImage = new Vector3*[iWidth];
	
	for(int x = 0; x < iWidth; ++x) {
		m_ppvImage[x] = new Vector3[iHeight];
	}
}

Image::~Image() {
	if(m_ppvImage) {
		for(int x = 0; x < m_iWidth; ++x) {
			delete[] m_ppvImage[x];
			m_ppvImage[x] = NULL;
		}
		delete[] m_ppvImage;
		m_ppvImage = NULL;
	}
}

void Image::saveImageToFile(const std::string& str_filename) {

}
