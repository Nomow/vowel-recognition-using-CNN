
set(PROJ_LIB_SRC
  Streaming.cpp
  Landmarks.cpp
  Img.cpp
  ConvolNetwork.cpp
)
set(MAIN_SRC
  main.cpp
)
add_library(newLib ${PROJ_LIB_SRC})

find_package(OpenCV REQUIRED)
if( OpenCV_FOUND)
message(STATUS "OpenCV library status:")
message(STATUS "    version: ${OpenCV_VERSION}")
message(STATUS "    libraries: ${OpenCV_LIBS}")
message(STATUS "    include path: ${OpenCV_INCLUDE_DIRS}")
endif(OpenCV_FOUND)


find_package(STASM)
if(STASM_FOUND)
message(STATUS " Found Stasm")
include_directories(${STASM_INCLUDE_DIRS})
LINK_DIRECTORIES(${STASM_LINK_DIRS} )
endif(STASM_FOUND)


find_package(Caffe)
if(Caffe_FOUND)
message(STATUS " Caffe found")
include_directories(${Caffe_INCLUDE_DIRS})
add_definitions(${Caffe_DEFINITIONS})
endif(Caffe_FOUND)

find_package(CUDA)
if(CUDA_FOUND)
message(STATUS " CUDA found")
include_directories(${CUDA_INCLUDE_DIRS})
endif(CUDA_FOUND)
add_executable(main ${MAIN_SRC})

target_link_libraries(main newLib ${OpenCV_LIBS} ${STASM_LIBRARIES} ${Caffe_LIBRARIES} ${CUDA_LIBRARIES})
