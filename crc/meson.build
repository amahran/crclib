sources = [
  'crc.c'
]

include_directories = [
  '.'
]

# exe = executable('crc', 
#   sources : sources,
#   include_directories : include_directories,
#   install : false)

crc_lib = static_library('crclib',
  sources : sources,
  include_directories : include_directories,
  # compiler flags
  # c_args : [''],
  # linker flags
  # link_args : [''],
  install : false
)

crc_dep = declare_dependency(
  include_directories : include_directories('.'), 
  link_with : crc_lib
)

