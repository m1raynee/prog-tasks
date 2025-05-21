// 7.31. ѕроводитс€ учет выполнени€ работ разного вида несколькими
// исполнител€ми. “ребуетс€ хранить информацию об исполнител€х (‘»ќ, адрес,
// табельный номер), о работах (наименование, исполнители, норма на
// исполнител€/-ей, тариф) и о выполненных работах (исполнители, наименование,
// объем, дата завершени€). Ќадо обеспечить возможность получени€:
//     - общего списка работ и их исполнителей,
//     - списка выполненных работ на конкретную дату/период (группировка по
//     исполнител€м и/или видам работ),
//     - работ, выполненных одним исполнителем,
//     - есть ли работы, выполненные одной и той же группой исполнителей.
// ƒл€ выполненных работ должна подсчитыватьс€ стоимость работ.
#include "file.hpp"

#define LOOP_ARGS_DEFINITION                            \
  std::istream &is, std::ostream &os, list<Task>&tasks, \
      list<Executor>&executors, MultiTask &tasks_pool

#define LOOP_ARGS is, os, tasks, executors, tasks_pool

void loop_main(LOOP_ARGS_DEFINITION);
void info_tasks_list(std::ostream& os, list<Task>& tasks);
void loop_date_select(LOOP_ARGS_DEFINITION);

void info_tasks_date_by_executors(std::ostream& os,
                                  list<Executor>& executors,
                                  date beg,
                                  date end);
void info_tasks_date_by_task(std::ostream& os,
                             list<Task>& completed_tasks,
                             date beg,
                             date end);
ExecutorN* loop_executor_select(LOOP_ARGS_DEFINITION);
void info_tasks_of_executor(std::ostream& os, Executor* executor);
void loop_executors_group_select(LOOP_ARGS_DEFINITION);
void info_group_tasks(std::ostream& os,
                      list<Executor> executors,
                      unsigned e,
                      list<Task> tasks,
                      unsigned t);