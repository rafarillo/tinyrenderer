#include "model.hpp"

Model::Model(const char *filename): _vertices(), _faces()
{
    std::ifstream in;
    in.open(filename, std::ifstream::in);
    if(in.fail())
    {
        printf("Error when try to open the file\n");
        return;
    }

    std::string line;
    while(!in.eof())
    {
        std::getline(in, line);
        std::istringstream iss(line.c_str());

        char trash;
        if(!line.compare(0, 2, "v "))
        {
            iss >> trash;
            Vec3f v;
            for(int i = 0; i < 3; i++) iss >> v.raw[i];
            _vertices.push_back(v);
        }
        else if(!line.compare(0, 2, "f "))
        {
            std::vector<int> f;
            int iTrash, idx;
            iss >> trash;
            while(iss >> idx >> trash >> iTrash >> trash >> iTrash)
            {
                idx--;
                f.push_back(idx);
            }
            _faces.push_back(f);
        }

    }
    std::cerr << "# v# " << _vertices.size() << " #f " << _faces.size() << std::endl;
}

Model::~Model()
{
}

int Model::nVerts()
{
    return _vertices.size();
}

int Model::nFaces()
{
    return _faces.size();
}

Vec3f Model::vert(int i)
{
    return _vertices[i];
}

std::vector<int> Model::face(int idx)
{
    return _faces[idx];
}
