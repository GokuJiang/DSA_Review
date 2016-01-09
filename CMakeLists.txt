cmake_minimum_required(VERSION 3.3)
project(xinnuoTest)
INCLUDE_DIRECTORIES()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

<<<<<<< HEAD
set(SOURCE_FILES Vector.h  main.cpp  ListNode.h List.h Stack.h Queue.h BinaryTree.h release.h Graph.h)
=======
set(SOURCE_FILES Vector.h  main.cpp  ListNode.h List.h Stack.h Queue.h BinaryTree.h release.h Entry.h BST.h AVL.h Splay.h BTNode.h BTree.h)
>>>>>>> 7738fe60bec796af23cba02af78f918d67ba7a0f
#set(SOURCE_FILES main.cpp Vector.cpp Vector.h)
add_executable(xinnuoTest ${SOURCE_FILES})