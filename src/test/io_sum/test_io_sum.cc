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
#include "acconfig.h"


#include <iostream>
#include <errno.h>


#include "global/global_init.h"
#include "global/global_context.h"
#include "common/ceph_argparse.h"
#include "include/assert.h"
#include "common/debug.h"
#include "common/errno.h"





#include "include/rados/librados.hpp"
#include "include/encoding.h"

#include "mon/MonitorDBStore.h"

#include "test/librados/test.h"
#include "gtest/gtest.h"


#include "include/assert.h"

#define dout_context g_ceph_context
#define dout_subsys ceph_subsys_
#undef dout_prefix
#define dout_prefix *_dout << "io-sum-msg "

using namespace librados;

TEST(IOSum, Test01) {
  return; 
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
  	std::cout << "hello global = " << ioctx.get_instance_id() << std::endl;
	ioctx.read(obj_name,out,obj_name.length(),0);
	std::cout << "obj_name=" << out.to_str() << std::endl;
	sleep(1);
  }

  ASSERT_EQ(0, destroy_one_pool_pp(pool_name, cluster));
}


TEST(IOSum, Test02) {
  MonitorDBStore store(std::string("/home/dongrui/work/ceph-dev/io-sum-test/build"));
  //在目录下kv_backend内存储kv后端类型，这里使用rocksdb
  dout(0) ;
  store.create_and_open(*_dout);
  
  MonitorDBStore::TransactionRef t(new MonitorDBStore::Transaction());
  t->put("test02","x",1);
  store.apply_transaction(t);
  *_dout << "x = "  << store.get("test02","x");
  store.close();
  *_dout << dendl;
}


int main(int argc, char *argv[])
{
  vector<const char*> args;
  argv_to_vec(argc, (const char **)argv, args);

  auto cct = global_init(nullptr, args,
                         CEPH_ENTITY_TYPE_CLIENT, CODE_ENVIRONMENT_UTILITY,
                         0);
  common_init_finish(g_ceph_context);
  g_ceph_context->_conf->apply_changes(NULL);
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}



