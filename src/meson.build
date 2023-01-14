_source = [
  'jpeg-texture.cc',
  'sphere.cc',
  'main.cc',

  default_vert_glsl,
  default_frag_glsl,
  texture_frag_glsl,
]

_deps = [
  glm_dep,
  jpeg_dep,
  zukou_dep,
]

executable(
  'celestial-body-app',
  _source,
  install: true,
  dependencies: _deps,
)
