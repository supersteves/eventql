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
#include <eventql/eventql.h>
#include <eventql/util/return_code.h>

namespace eventql {
class ProcessConfig;
class Session;

class Database {
public:

  static Database* newDatabase(ProcessConfig* process_config);
  virtual ~Database() = default;

  virtual ReturnCode start() = 0;
  virtual void shutdown() = 0;

  /**
   * Start a thread from which database operations can be executed
   */
  virtual void startThread(std::function<void(Session* session)> entrypoint) = 0;

  /**
   * Get session for the current thread
   */
  virtual Session* getSession() = 0;

};

} // namespace eventql
