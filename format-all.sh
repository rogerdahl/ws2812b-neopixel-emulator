#!/bin/sh

find ./src \( -name '*.cpp' -or -name '*.c' -or -name '*.h' \) -exec clang-format --style=file -i {} +;

