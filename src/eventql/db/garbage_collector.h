/**
 * Copyright (c) 2016 DeepCortex GmbH <legal@eventql.io>
 * Authors:
 *   - Paul Asmuth <paul@eventql.io>
 *
 * This program is free software: you can redistribute it and/or modify it under
 * the terms of the GNU Affero General Public License ("the license") as
 * published by the Free Software Foundation, either version 3 of the License,
 * or any later version.
 *
 * In accordance with Section 7(e) of the license, the licensing of the Program
 * under the license does not imply a trademark license. Therefore any rights,
 * title and interest in our trademarks remain entirely with us.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE. See the license for more details.
 *
 * You can be released from the requirements of the license by purchasing a
 * commercial license. Buying such a license is mandatory as soon as you develop
 * commercial activities involving this program without disclosing the source
 * code of your own applications
 */
#pragma once
#include <eventql/util/stdtypes.h>
#include <eventql/util/autoref.h>
#include <eventql/db/file_tracker.h>
#include "eventql/eventql.h"
#include <thread>
#include <condition_variable>

namespace eventql {

enum class GarbageCollectorMode {
  DISABLED, MANUAL
};

String garbageCollectorModeToString(GarbageCollectorMode mode);
GarbageCollectorMode garbageCollectorModeFromString(String str);

class GarbageCollector {
public:

  static const uint64_t kDefaultGCInterval = 30 * kMicrosPerSecond;
  static const uint64_t kDefaultCachedirMaxSize = 1024llu * 1024llu * 1024llu * 64llu; // 64 GB

  GarbageCollector(
      GarbageCollectorMode mode,
      FileTracker* file_tracker,
      const String& data_dir,
      const String& trash_dir,
      const String& cache_dir,
      uint64_t cache_dir_maxsize = kDefaultCachedirMaxSize,
      size_t gc_interval = kDefaultGCInterval);

  ~GarbageCollector();

  void runGC();

  void startGCThread();
  void stopGCThread();

protected:

  void emptyTrash();
  void flushCache();

  GarbageCollectorMode mode_;
  FileTracker* file_tracker_;
  String data_dir_;
  String trash_dir_;
  String cache_dir_;
  uint64_t cache_dir_maxsize_;
  uint64_t gc_interval_;

  std::thread thread_;
  bool thread_running_;
  std::mutex mutex_;
  std::condition_variable cv_;
};

} // namespace eventql

