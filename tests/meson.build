gtest_proj = subproject('gtest')
gtest_dep = gtest_proj.get_variable('gtest_dep')

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
  # this will work only if crc has the 'declare_dependency' method defined
  dependencies : [gtest_dep, crc_dep]
)

# Add the test to the Meson test suite
test('Test CRC functionality', test_exe, args : ['--gtest_color=yes'])

