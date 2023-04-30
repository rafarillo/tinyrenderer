#ifndef __MODEL__
#define __MODEL__

#include "geometry.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

class Model
{
    private:
        std::vector<Vec3f> _vertices;
        std::vector<std::vector<int>> _faces;
    public:
        Model(const char* filename);
        ~Model();
        int nVerts();
        int nFaces();
        Vec3f vert(int i);
        std::vector<int> face(int idx);
};


#endif