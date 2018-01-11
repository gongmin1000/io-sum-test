// -*- mode:C++; tab-width:8; c-basic-offset:2; indent-tabs-mode:t -*-
// vim: ts=8 sw=2 smarttab
/*
 * Ceph - scalable distributed file system
 *
 * Copyright (C) 2013 Inktank
 *
 * This is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License version 2.1, as published by the Free Software
 * Foundation.  See file COPYING.
 *
 */

#include <iostream>
#include <errno.h>

#include "include/rados/librados.hpp"
#include "include/encoding.h"
#include "test/librados/test.h"
#include "gtest/gtest.h"

using namespace librados;

TEST(DrHello, Test01) {
  Rados cluster;
  std::string pool_name = get_temp_pool_name();
  ASSERT_EQ("", create_one_pool_pp(pool_name, cluster));
  IoCtx ioctx;
  cluster.ioctx_create(pool_name.c_str(), ioctx);

  const std::string obj_name = "obj-test";
  bufferlist in,out;
  in.append(obj_name);
  ioctx.create(obj_name,false);
  ioctx.write_full(obj_name,in);

  while(1){
  	std::cout << "hello" << ioctx.get_instance_id() << std::endl;
	ioctx.read(obj_name,out,obj_name.length(),0);
	std::cout << "obj_name=" << out.to_str() << std::endl;
	sleep(1);
  }

  ASSERT_EQ(0, destroy_one_pool_pp(pool_name, cluster));
}


/*TEST(DrHello, Test02) {
  Rados cluster;
  std::string pool_name = get_temp_pool_name();
  ASSERT_EQ("", create_one_pool_pp(pool_name, cluster));
  IoCtx ioctx;
  cluster.ioctx_create(pool_name.c_str(), ioctx);

  bufferlist in, out;
  ASSERT_EQ(-ENOENT, ioctx.exec("myobject", "hello", "say_hello", in, out));
  ASSERT_EQ(0, ioctx.write_full("myobject", in));
  ASSERT_EQ(0, ioctx.exec("myobject", "hello", "say_hello", in, out));
  ASSERT_EQ(std::string("Hello, world!"), std::string(out.c_str(), out.length()));

  out.clear();
  in.append("Tester");
  ASSERT_EQ(0, ioctx.exec("myobject", "hello", "say_hello", in, out));
  ASSERT_EQ(std::string("Hello, Tester!"), std::string(out.c_str(), out.length()));

  out.clear();
  in.clear();
  char buf[4096];
  memset(buf, 1, sizeof(buf));
  in.append(buf, sizeof(buf));
  ASSERT_EQ(-EINVAL, ioctx.exec("myobject", "hello", "say_hello", in, out));

  ASSERT_EQ(0, destroy_one_pool_pp(pool_name, cluster));
}
*/
