sources = [
  'crc.c'
]

include_directories = [
  '.'
]

crc_lib = static_library('crclib',
  sources : sources,
  include_directories : include_directories,
  install : false
)

crc_dep = declare_dependency(
  include_directories : include_directories('.'), 
  link_with : crc_lib
)

