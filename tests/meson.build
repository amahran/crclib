# gtest_proj = subproject('gtest')
# gtest_dep = gtest_proj.get_variable('gtest_dep')
# gtest_main_dep = gtest_proj.get_variable('gtest_main_dep')
# Fetch GoogleTest from Meson WrapDB
# gtest_dep = dependency('gtest', fallback: ['gtest', 'gtest_dep'])
gtest_dep = dependency('gtest', required: false)
if not gtest_dep.found()
    gtest_dep = dependency('gtest', fallback: ['gtest', 'gtest_dep'])
endif

cpp_args = ['-std=c++20']

sources = [
  'test_crc.cpp'
]

includes = [
  '.'
]

# create an executable target called 'test_exe'
test_exe = executable('test_crc',
  sources : sources,
  include_directories : includes,
  cpp_args : cpp_args,
  # this will work only if crc has the 'declare_dependency' method defined
  dependencies : [gtest_dep, crc_dep]
)

# Add the test to the Meson test suite
test('Test CRC functionality', test_exe, args : ['--gtest_color=yes'])

