[![Coverage Status](https://coveralls.io/repos/github/nevstruevdmitriy/lab05/badge.svg)](https://coveralls.io/github/nevstruevdmitriy/lab05)

[![Build Status](https://travis-ci.com/nevstruevdmitriy/lab05.svg?branch=master)](https://travis-ci.com/nevstruevdmitriy/lab05)

## Laboratory work V

Данная лабораторная работа посвещена изучению фреймворков для тестирования на примере **GTest**

```sh
$ open https://github.com/google/googletest
```

## Tasks

- [x] 1. Создать публичный репозиторий с названием **lab05** на сервисе **GitHub**
- [x] 2. Выполнить инструкцию учебного материала
- [x] 3. Ознакомиться со ссылками учебного материала
- [x] 4. Составить отчет и отправить ссылку личным сообщением в **Slack**

## Tutorial

Переменные
```sh
$ export GITHUB_USERNAME=<имя_пользователя>
$ alias gsed=sed # for *-nix system
```

дириктория
```sh
$ cd ${GITHUB_USERNAME}/workspace
$ pushd .
$ source scripts/activate
```

новый реп
```sh
$ git clone https://github.com/${GITHUB_USERNAME}/lab04 projects/lab05
$ cd projects/lab05
$ git remote remove origin
$ git remote add origin https://github.com/${GITHUB_USERNAME}/lab05
```

доавляем подпроэкт - gtest
```sh
$ mkdir third-party
$ git submodule add https://github.com/google/googletest third-party/gtest
cloning ...
done
$ cd third-party/gtest && git checkout release-1.8.1 && cd ../..
Note: checking out 'release-1.8.1'
$ git add third-party/gtest
$ git commit -m"added gtest framework"
```

доавляем новую опцию собирать ли тесты
```sh
$ gsed -i '/option(BUILD_EXAMPLES "Build examples" OFF)/a\
option(BUILD_TESTS "Build tests" OFF)
' CMakeLists.txt
$ cat >> CMakeLists.txt <<EOF

if(BUILD_TESTS)
  enable_testing()
  add_subdirectory(third-party/gtest)
  file(GLOB \${PROJECT_NAME}_TEST_SOURCES tests/*.cpp)
  add_executable(check \${\${PROJECT_NAME}_TEST_SOURCES})
  target_link_libraries(check \${PROJECT_NAME} gtest_main)
  add_test(NAME check COMMAND check)
endif()
EOF
```

добавляем тест
```sh
$ mkdir tests
$ cat > tests/test1.cpp <<EOF
#include <print.hpp>

#include <gtest/gtest.h>

TEST(Print, InFileStream)
{
  std::string filepath = "file.txt";
  std::string text = "hello";
  std::ofstream out{filepath};

  print(text, out);
  out.close();

  std::string result;
  std::ifstream in{filepath};
  in >> result;

  EXPECT_EQ(result, text);
}
EOF
```

собираем и компилируем
```sh
$ cmake -H. -B_build -DBUILD_TESTS=ON
$ cmake --build _build
... собирается...
[100%] Built target equation
$ cmake --build _build --target test
Running tests...
Test project /home/dimka/Desktop/птз8с/ak/hw/nevstruev.dmitriy/workspace/projects/lab05/_build
    Start 1: check
1/1 Test #1: check ............................   Passed    0.00 sec

100% tests passed, 0 tests failed out of 1

Total Test time (real) =   0.00 sec


```

запускаем, проверяем
```sh
$ _build/check
[==========] Running 1 test from 1 test case.
[----------] Global test environment set-up.
[----------] 1 test from Print
[ RUN      ] Print.InFileStream
[       OK ] Print.InFileStream (0 ms)
[----------] 1 test from Print (0 ms total)

[----------] Global test environment tear-down
[==========] 1 test from 1 test case ran. (0 ms total)
[  PASSED  ] 1 test.
$ cmake --build _build --target test -- ARGS=--verbose
```

незначительные изменения в конфигах
```sh
$ gsed -i 's/lab04/lab05/g' README.md
$ gsed -i 's/\(DCMAKE_INSTALL_PREFIX=_install\)/\1 -DBUILD_TESTS=ON/' .travis.yml
$ gsed -i '/cmake --build _build --target install/a\
- cmake --build _build --target test -- ARGS=--verbose
' .travis.yml
```

проверяем на валидность
```sh
$ travis lint
Hooray, .travis.yml looks valid :)
```

Пушим всё в мастер
```sh
$ git add .travis.yml
$ git add tests
$ git add -p
$ git commit -m"added tests"
$ git push origin master
```

логинимся в травис и подключаем реп
```sh
$ travis login --auto
$ travis enable
```

делаем скриншот 
```sh
$ mkdir artifacts
$ sleep 20s && gnome-screenshot --file artifacts/screenshot.png
# for macOS: $ screencapture -T 20 artifacts/screenshot.png
# open https://github.com/${GITHUB_USERNAME}/lab05
```

## Report

```sh
$ popd
$ export LAB_NUMBER=05
$ git clone https://github.com/tp-labs/lab${LAB_NUMBER} tasks/lab${LAB_NUMBER}
$ mkdir reports/lab${LAB_NUMBER}
$ cp tasks/lab${LAB_NUMBER}/README.md reports/lab${LAB_NUMBER}/REPORT.md
$ cd reports/lab${LAB_NUMBER}
$ edit REPORT.md
$ gist REPORT.md
```

## Homework

### Задание
1. Создайте `CMakeList.txt` для библиотеки *banking*.
2. Создайте модульные тесты на классы `Transaction` и `Account`.
    * Используйте mock-объекты.
    * Покрытие кода должно составлять 100%.
3. Настройте сборочную процедуру на **TravisCI**.
4. Настройте [Coveralls.io](https://coveralls.io/).

## Links

- [C++ CI: Travis, CMake, GTest, Coveralls & Appveyor](http://david-grs.github.io/cpp-clang-travis-cmake-gtest-coveralls-appveyor/)
- [Boost.Tests](http://www.boost.org/doc/libs/1_63_0/libs/test/doc/html/)
- [Catch](https://github.com/catchorg/Catch2)

```
Copyright (c) 2015-2020 The ISC Authors
```

