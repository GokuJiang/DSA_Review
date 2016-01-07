cmake_minimum_required(VERSION 3.3)
project(xinnuoTest)
INCLUDE_DIRECTORIES()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES Vector.h  main.cpp  ListNode.h List.h Stack.h Queue.h BinaryTree.h release.h Entry.h BST.h AVL.h Splay.h BTNode.h BTree.h)
#set(SOURCE_FILES main.cpp Vector.cpp Vector.h)
add_executable(xinnuoTest ${SOURCE_FILES})