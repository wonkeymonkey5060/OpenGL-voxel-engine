#ifndef OBJLOADER_H
#define OBJLOADER_H

#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <glm/glm.hpp>

inline std::vector<float> loadObj(const std::string& filename) {
    std::vector<glm::vec3>  tempPos;
    std::vector<glm::vec2>  tempUV;
    std::vector<glm::vec3>  tempNorm;

    // these will store the face‑indexed ordering
    std::vector<unsigned>   posIdx, uvIdx, normIdx;

    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Failed to open " << filename << std::endl;
        return {};
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream ss(line);
        std::string tag;
        ss >> tag;

        if (tag == "v") {
            glm::vec3 p; ss >> p.x >> p.y >> p.z;
            tempPos.push_back(p);
        }
        else if (tag == "vt") {
            glm::vec2 uv; ss >> uv.x >> uv.y;
            tempUV.push_back(uv);
        }
        else if (tag == "vn") {
            glm::vec3 n; ss >> n.x >> n.y >> n.z;
            tempNorm.push_back(n);
        }
        else if (tag == "f") {
            // each face is 3 groups of v/vt/vn
            for (int i = 0; i < 3; ++i) {
                unsigned vi, uvi, ni;
                char slash;
                ss >> vi >> slash >> uvi >> slash >> ni;
                posIdx .push_back(vi  - 1);
                uvIdx  .push_back(uvi - 1);
                normIdx.push_back(ni  - 1);
            }
        }
    }

    // now build the interleaved buffer
    std::vector<float> interleaved;
    interleaved.reserve(posIdx.size() * 8);
    for (size_t i = 0; i < posIdx.size(); ++i) {
        auto &P = tempPos [ posIdx[i] ];
        auto &T = tempUV  [ uvIdx [i] ];
        auto &N = tempNorm[ normIdx[i] ];

        interleaved.push_back(P.x);
        interleaved.push_back(P.y);
        interleaved.push_back(P.z);
        interleaved.push_back(T.x);
        interleaved.push_back(T.y);
        interleaved.push_back(N.x);
        interleaved.push_back(N.y);
        interleaved.push_back(N.z);
    }

    return interleaved;
}

#endif // OBJLOADER_H
