# Created by the script cgal_create_cmake_script
# This is the CMake script for compiling a CGAL application.


cmake_minimum_required(VERSION 3.1...3.15)
project( Box_intersection_d_Tests )

find_package( CGAL QUIET )

find_package( TBB )

if ( CGAL_FOUND )

  create_single_source_cgal_program( "automated_test.cpp" )
  create_single_source_cgal_program( "benchmark_box_intersection.cpp" )
  create_single_source_cgal_program( "random_set_test.cpp" )
  create_single_source_cgal_program( "test_box_grid.cpp" )

  if( TBB_FOUND )
    CGAL_target_use_TBB( test_box_grid )
  else()
    message( STATUS "NOTICE: Intel TBB was not found. Sequential code will be used." )
  endif()
else()
    message(STATUS "This program requires the CGAL library, and will not be compiled.")
endif()

