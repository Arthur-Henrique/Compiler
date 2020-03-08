cmake_minimum_required(VERSION 3.15)
project(compiler)

set(CMAKE_CXX_STANDARD 17)

include_directories(prs)
include_directories(prs/ast)
include_directories(src)

add_executable(compiler
        app/main.fr
        lrn/main.cpp
        prs/ast/assignment.hpp
        prs/ast/block.hpp
        prs/ast/delay.hpp
        prs/ast/log.hpp
        prs/ast/node.hpp
        prs/ast/primitive.hpp
        prs/ast/variable.hpp
        prs/ast.h
        prs/lexicon.lex
        prs/syntax.y
        src/main.cpp
        src/model.cpp
        src/model.hpp
        src/monitor.hpp
        src/logger.hpp
        src/util.hpp)
