default_vert_glsl = custom_target(
  'default.vertex.h',
  command: [textify, 'default_vertex_shader_source', '@INPUT@', '@OUTPUT@'],
  input: 'default.vert',
  output: 'default.vert.h',
)

default_frag_glsl = custom_target(
  'default.frag.h',
  command: [textify, 'default_fragment_shader_source', '@INPUT@', '@OUTPUT@'],
  input: 'default.frag',
  output: 'default.frag.h',
)

texture_frag_glsl = custom_target(
  'texture.frag.h',
  command: [textify, 'texture_fragment_shader_source', '@INPUT@', '@OUTPUT@'],
  input: 'texture.frag',
  output: 'texture.frag.h',
)
