// Copyright (c) Facebook, Inc. and its affiliates.
// This source code is licensed under the MIT license found in the
// LICENSE file in the root directory of this source tree.

#include "PTexMeshShader.h"

#include <fcntl.h>
#include <sys/mman.h>
#include <iostream>

#include <Corrade/Containers/Reference.h>
#include <Magnum/GL/BufferTextureFormat.h>
#include <Magnum/GL/Context.h>
#include <Magnum/GL/Shader.h>
#include <Magnum/GL/Version.h>
#include <Magnum/ImageView.h>
#include <Magnum/PixelFormat.h>

#include "esp/assets/PTexMeshData.h"
#include "esp/core/esp.h"
#include "esp/io/io.h"

using namespace Magnum;

namespace esp {
namespace gfx {

PTexMeshShader::PTexMeshShader(Magnum::GL::Version version,
                               const std::string& vertexShaderFilename,
                               const std::string& geometryShaderFilename,
                               const std::string& fragmentShaderFilename)
    : BaseShader(version,
                 vertexShaderFilename,
                 geometryShaderFilename,
                 fragmentShaderFilename) {
  loadShaders();
}

void PTexMeshShader::loadShaders() {
  ASSERT(vertexShaderFilename_ != "" && fragmentShaderFilename_ != "");

  MAGNUM_ASSERT_GL_VERSION_SUPPORTED(glVersion_);

  GL::Shader vert{glVersion_, GL::Shader::Type::Vertex};
  GL::Shader geom{glVersion_, GL::Shader::Type::Geometry};
  GL::Shader frag{glVersion_, GL::Shader::Type::Fragment};

  const std::string shaderDir = STR(SHADER_DIR);
  const std::string vertexShaderFile =
      std::string(shaderDir) + "/" + vertexShaderFilename_;
  const std::string geometryShaderFile =
      std::string(shaderDir) + "/" + geometryShaderFilename_;
  const std::string fragmentShaderFile =
      std::string(shaderDir) + "/" + fragmentShaderFilename_;

  vert.addFile(vertexShaderFile);
  geom.addFile(geometryShaderFile);
  frag.addFile(fragmentShaderFile);

  CORRADE_INTERNAL_ASSERT_OUTPUT(GL::Shader::compile({vert, geom, frag}));

  attachShaders({vert, geom, frag});

  CORRADE_INTERNAL_ASSERT_OUTPUT(link());
}

}  // namespace gfx
}  // namespace esp
