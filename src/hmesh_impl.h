#ifndef __HMESH_IMPL_H_
#define __HMESH_IMPL_H_

#pragma once

#include <cinolib/meshes/polygonmesh.h>
#include <string>

namespace hmesh
{

    class EditableMesh : cinolib::Polygonmesh<>
    {
    public:
        class Iterator
        {
        private:
            EditableMesh *_mesh;
        };
        bool Load(const std::string &path);
        Iterator *NewIterator();
    };

}
#endif