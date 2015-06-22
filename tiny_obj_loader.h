//
// Copyright 2012-2015, Syoyo Fujita.
//
// Licensed under 2-clause BSD liecense.
//
#ifndef _TINY_OBJ_LOADER_H
#define _TINY_OBJ_LOADER_H

#include <string>
#include <vector>
#include <map>

namespace tinyobj {

#ifdef TINY_OBJ_USE_DOUBLE
  //#pragma message "using double"
  typedef double real_t;
#else
  //#pragma message "using float"
  typedef float real_t;
#endif

typedef struct {
  std::string name;

  real_t ambient[3];
  real_t diffuse[3];
  real_t specular[3];
  real_t transmittance[3];
  real_t emission[3];
  real_t shininess;
  real_t ior;      // index of refraction
  real_t dissolve; // 1 == opaque; 0 == fully transparent
  // illumination model (see http://www.fileformat.info/format/material/)
  int illum;

  std::string ambient_texname;
  std::string diffuse_texname;
  std::string specular_texname;
  std::string normal_texname;
  std::map<std::string, std::string> unknown_parameter;
} material_t;

typedef struct {
  std::vector<real_t> positions;
  std::vector<real_t> normals;
  std::vector<real_t> texcoords;
  std::vector<unsigned int> indices;
  std::vector<int> material_ids; // per-mesh material ID
} mesh_t;

typedef struct {
  std::string name;
  mesh_t mesh;
} shape_t;

class MaterialReader {
public:
  MaterialReader() {}
  virtual ~MaterialReader() {}

  virtual std::string operator()(const std::string &matId,
                                 std::vector<material_t> &materials,
                                 std::map<std::string, int> &matMap) = 0;
};

class MaterialFileReader : public MaterialReader {
public:
  MaterialFileReader(const std::string &mtl_basepath)
      : m_mtlBasePath(mtl_basepath) {}
  virtual ~MaterialFileReader() {}
  virtual std::string operator()(const std::string &matId,
                                 std::vector<material_t> &materials,
                                 std::map<std::string, int> &matMap);

private:
  std::string m_mtlBasePath;
};

/// Loads .obj from a file.
/// 'shapes' will be filled with parsed shape data
/// The function returns error string.
/// Returns empty string when loading .obj success.
/// 'mtl_basepath' is optional, and used for base path for .mtl file.
std::string LoadObj(std::vector<shape_t> &shapes,       // [output]
                    std::vector<material_t> &materials, // [output]
                    const char *filename, const char *mtl_basepath = NULL);

/// Loads object from a std::istream, uses GetMtlIStreamFn to retrieve
/// std::istream for materials.
/// Returns empty string when loading .obj success.
std::string LoadObj(std::vector<shape_t> &shapes,       // [output]
                    std::vector<material_t> &materials, // [output]
                    std::istream &inStream, MaterialReader &readMatFn);

/// Loads materials into std::map
/// Returns an empty string if successful
std::string LoadMtl(std::map<std::string, int> &material_map,
                    std::vector<material_t> &materials, std::istream &inStream);
}

#endif // _TINY_OBJ_LOADER_H
