/**
 * This file is part of the "libcsql" project
 *   Copyright (c) 2015 Paul Asmuth, zScale Technology GmbH
 *
 * libcsql is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License v3.0. You should have received a
 * copy of the GNU General Public License along with this program. If not, see
 * <http://www.gnu.org/licenses/>.
 */
#pragma once
#include <eventql/util/stdtypes.h>
#include <eventql/util/autoref.h>
#include <eventql/sql/tasks/TaskDAG.h>
#include <eventql/sql/result_cursor.h>

using namespace stx;

namespace csql {
class QueryPlan;

struct SchedulerCallbacks {
  HashMap<TaskID, Vector<RowSinkFn>> on_row;
  HashMap<TaskID, Vector<Function<void (TaskID)>>> on_complete;
  Vector<Function<void ()>> on_query_finished;
};

class Scheduler : public RefCounted {
public:
  virtual ~Scheduler() {};
  virtual ScopedPtr<ResultCursor> execute(QueryPlan* query_plan, size_t stmt_idx) = 0;
};

class DefaultScheduler : public Scheduler {
public:
  ScopedPtr<ResultCursor> execute(QueryPlan* query_plan, size_t stmt_idx) override;
};

} // namespace csql
