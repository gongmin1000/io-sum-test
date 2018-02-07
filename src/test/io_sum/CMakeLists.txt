# ceph_test_cls_version
add_executable(ceph_test_io_sum
  test_io_sum.cc
  )
set_target_properties(ceph_test_io_sum PROPERTIES COMPILE_FLAGS
  ${UNITTEST_CXX_FLAGS})
target_link_libraries(ceph_test_io_sum
  os
  ceph-common
  librados
  cls_version_client
  global
  ${UNITTEST_LIBS}
  ${CRYPTO_LIBS}
  ${EXTRALIBS}
  ${BLKID_LIBRARIES}
  ${CMAKE_DL_LIBS}
  radostest
  )

