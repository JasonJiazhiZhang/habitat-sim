// Copyright (c) Facebook, Inc. and its affiliates.
// This source code is licensed under the MIT license found in the
// LICENSE file in the root directory of this source tree.

#include "BaseShader.h"

// #include <Corrade/Containers/Reference.h>
// #include <Magnum/GL/Context.h>
#include <Magnum/GL/Shader.h>
#include <Magnum/GL/Texture.h>
#include <Magnum/GL/Version.h>

namespace esp {
namespace gfx {

BaseShader::BaseShader(Magnum::GL::Version version,
                       const std::string& vertexShaderFilename,
                       const std::string& geometryShaderFilename,
                       const std::string& fragmentShaderFilename)
    : glVersion_(version),
      vertexShaderFilename_(vertexShaderFilename),
      geometryShaderFilename_(geometryShaderFilename),
      fragmentShaderFilename_(fragmentShaderFilename) {}

void BaseShader::setGLVersion(Magnum::GL::Version version) {
  glVersion_ = version;
}

void BaseShader::setVertexShaderFilename(std::string& filename) {
  vertexShaderFilename_ = filename;
}

void BaseShader::setGeometryShaderFilename(std::string& filename) {
  geometryShaderFilename_ = filename;
}

void BaseShader::setFragmentShaderFilename(std::string& filename) {
  fragmentShaderFilename_ = filename;
}

}  // namespace gfx
}  // namespace esp
