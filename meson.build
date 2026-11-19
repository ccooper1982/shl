project(
  'shl',
  ['c', 'cpp'],
  version: '0.1.0',
  default_options: [
    'cpp_std=c++23',
    'warning_level=3'
  ],
)

add_project_arguments(
  '-Werror=return-local-addr',
  language: 'cpp',
)

tree_sitter = dependency('tree-sitter')
fmt = dependency('fmt')
gtest = dependency('gtest')
gtest_main = dependency('gtest_main')

shl_sources = files(
  'src/exec/core.cpp',
  'src/exec/proc.cpp',
  'src/exec/executor.cpp',
  'src/exec/file.cpp',
  'src/main.cpp',
  'src/parser.cpp',
  'src/semantics.cpp',
  'src/symbol_table.cpp',
  'grammar/src/parser.c',
)

include_dirs = include_directories('grammar/src','include')

shl_exec = executable('shl', shl_sources,
  include_directories: include_dirs,
  dependencies: [tree_sitter, fmt],
  install: false
)

shl_tests = executable(
  'shl_tests',
  files('tests/ast.cpp',
        'tests/parser.cpp',
        'tests/semantics.cpp',
        'tests/symbol_table.cpp',
        'tests/execute_stack.cpp',
        'tests/execute_exit_status.cpp',
        'src/parser.cpp',
        'src/semantics.cpp',
        'src/symbol_table.cpp',
        'src/exec/core.cpp',
        'src/exec/proc.cpp',
        'src/exec/executor.cpp',
        'src/exec/file.cpp',
        'grammar/src/parser.c'
  ),
  include_directories: include_dirs,
  dependencies: [tree_sitter, fmt, gtest, gtest_main],
  cpp_args: ['-DCPY_UNIT_TESTS'],
)

test('shl tests', shl_tests, workdir: meson.project_source_root())

test_tmp = meson.project_build_root() / 'shl_test_tmp'
test('shl_self_test',
    shl_exec,
    args: [meson.project_source_root() / 'tests' / 'scripts' / 'self_test.shl'],
    env: ['SHL_TEST_TMP=' + test_tmp],
    workdir: meson.project_source_root())
