project('crclib', 'c', 'cpp',
  version : '0.1.0',
  default_options : [
    'c_std=c17',
    'cpp_std=c++20',
    'warning_level=everything',
    'b_sanitize=address,undefined'])

common_flags = [
  '-Wconversion'] # warns against implicit conversions affecting the value

debug_flags = common_flags
release_flags = common_flags

if get_option('buildtype') == 'debug'
  add_project_arguments(debug_flags, language: 'c')
elif get_option('buildtype') == 'release'
  add_project_arguments(release_flags, language: 'c')
endif

# this will search those subdirs for meson.build
subdir('crc')
subdir('tests')

exe = executable('main',
  sources : 'main.c',
  dependencies : [crc_dep],
  install : false
)
