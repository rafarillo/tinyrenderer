#ifndef __MODEL_H__
#define __MODEL_H__

#include <vector>
#include "geometry.hpp"

class Model {
private:
	std::vector<Vec3f> verts_;
	std::vector<Vec3f> uvVerts_;
	std::vector<std::vector<int>> faces_;
	std::vector<std::vector<int>> texCoord;
public:
	Model(const char *filename);
	~Model();
	int nverts();
	int nfaces();
	Vec3f vert(int i);
	std::vector<int> face(int idx);
	std::vector<int> TexCoord(int idx);
	Vec3f uvVerts(int i);
};

#endif //__MODEL_H__