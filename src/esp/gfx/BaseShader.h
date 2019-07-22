// Copyright (c) Facebook, Inc. and its affiliates.
// This source code is licensed under the MIT license found in the
// LICENSE file in the root directory of this source tree.

#pragma once

#include <Magnum/GL/AbstractShaderProgram.h>
#include <Magnum/GL/Version.h>
#include <string>

namespace esp {
namespace gfx {

class BaseShader : public Magnum::GL::AbstractShaderProgram {
 public:
  BaseShader(Magnum::GL::Version version = Magnum::GL::Version::GL410,
             const std::string& vertexShaderFilename = "",
             const std::string& geometryShaderFilename = "",
             const std::string& fragmentShaderFilename = "");
  virtual ~BaseShader(){};
  void setGLVersion(Magnum::GL::Version version);
  void setVertexShaderFilename(std::string& filename);
  void setGeometryShaderFilename(std::string& filename);
  void setFragmentShaderFilename(std::string& filename);
  virtual void loadShaders() = 0;

 protected:
  Magnum::GL::Version glVersion_ = Magnum::GL::Version::GL410;
  std::string vertexShaderFilename_ = "";
  std::string geometryShaderFilename_ = "";
  std::string fragmentShaderFilename_ = "";
};

}  // namespace gfx
}  // namespace esp
