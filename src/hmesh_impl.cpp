#include "hmesh_impl.h"
#include <tiny_gltf.h>
#include <ofbx.h>
#include <boost/algorithm/string.hpp>

bool hmesh::EditableMesh::Load(const std::string &path) {
    const std::string lower_str = boost::algorithm::to_lower_copy(path);

    if (lower_str.find(".obj") >= 0 || lower_str.find(".off") >= 0 || lower_str.find(".stl") >= 0) {
        this->load(path.c_str());
    } else if (lower_str.find(".gltf") >= 0) {
        
    } else if (lower_str.find(".glb") >= 0) {
    
    } else if (lower_str.find(".fbx") >= 0) {

    }

    return false;
}

hmesh::EditableMesh::Iterator *hmesh::EditableMesh::NewIterator() {

    return new EditableMesh::Iterator ();
}