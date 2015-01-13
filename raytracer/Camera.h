#ifndef IMAGE_H
#define IMAGE_H

#pragma once

class Image {
	public:
		int m_iWidth;
		int m_iHeight;
		Vector3** m_ppvImage;

		Image(int iWidth, int iHeight);
		~Image();

		void saveImageToFile(const std::string& str_filename);

};

#endif
