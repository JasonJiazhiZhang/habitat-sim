// Copyright (c) Facebook, Inc. and its affiliates.
// This source code is licensed under the MIT license found in the
// LICENSE file in the root directory of this source tree.

#include "GenericShader.h"

#include <Corrade/Containers/Reference.h>
#include <Magnum/GL/Context.h>
#include <Magnum/GL/Shader.h>
#include <Magnum/GL/Texture.h>
#include <Magnum/GL/Version.h>

namespace esp {
namespace gfx {

namespace {
enum { TextureLayer = 0 };
}

GenericShader::GenericShader(const Flags flags,
                             Magnum::GL::Version version,
                             const std::string& vertexShaderFilename,
                             const std::string& fragmentShaderFilename) : BaseShader(version, vertexShaderFilename, fragmentShaderFilename), flags_(flags) {
  loadShaders();
}

GenericShader& GenericShader::bindTexture(Magnum::GL::Texture2D& texture) {
  ASSERT((flags_ & Flag::Textured) || (flags_ & Flag::PrimitiveIDTextured));

  texture.bind(TextureLayer);

  if (flags_ & Flag::PrimitiveIDTextured)
    setUniform(uniformLocation("texSize"), texture.imageSize(0).x());

  return *this;
}

void GenericShader::loadShaders() {
  ASSERT(vertexShaderFilename_ != "" && fragmentShaderFilename_ != "");

  MAGNUM_ASSERT_GL_VERSION_SUPPORTED(glVersion_);

  Magnum::GL::Shader vert{glVersion_,
                          Magnum::GL::Shader::Type::Vertex};
  Magnum::GL::Shader frag{glVersion_,
                          Magnum::GL::Shader::Type::Fragment};

  const std::string shaderDir = STR(SHADER_DIR);
  const std::string vertexShaderFile = std::string(shaderDir) + "/" + vertexShaderFilename_;
  const std::string fragmentShaderFile = std::string(shaderDir) + "/" + fragmentShaderFilename_;

  vert.addSource(flags_ & Flag::Textured ? "#define TEXTURED\n" : "")
      .addSource(flags_ & Flag::VertexColored ? "#define VERTEX_COLORED\n" : "")
      .addSource(flags_ & Flag::PerVertexIds ? "#define PER_VERTEX_IDS\n" : "")
      .addFile(vertexShaderFile);
  
  frag.addSource(flags_ & Flag::Textured ? "#define TEXTURED\n" : "")
      .addSource(flags_ & Flag::VertexColored ? "#define VERTEX_COLORED\n" : "")
      .addSource(flags_ & Flag::PerVertexIds ? "#define PER_VERTEX_IDS\n" : "")
      .addSource(flags_ & Flag::PrimitiveIDTextured ? "#define ID_TEXTURED\n"
                                                   : "")
      .addFile(fragmentShaderFile);

  CORRADE_INTERNAL_ASSERT_OUTPUT(Magnum::GL::Shader::compile({vert, frag}));

  attachShaders({vert, frag});

  CORRADE_INTERNAL_ASSERT_OUTPUT(link());

  if (flags_ & Flag::Textured) {
    setUniform(uniformLocation("textureData"), TextureLayer);
  }

  if (flags_ & Flag::PrimitiveIDTextured) {
    setUniform(uniformLocation("primTexture"), TextureLayer);
  }
}

}  // namespace gfx
}  // namespace esp
