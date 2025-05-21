#include "linking.hpp"

void add_to_multitask(MultiTask* mt, Task* t_ptr) {
  if (t_ptr->completion_date.is_empty()) {
    mt->tasks.push_back(t_ptr);
  } else {
    mt->completed_tasks.push_back(t_ptr);
  }
}
void fill_multitask(MultiTask* mt, list<Task>& ts) {
  TaskN* p = ts.first;
  while (p) {
    add_to_multitask(mt, p->value);
    p = p->next;
  }
}

void form_bond(ExecutorN* e_ptr, TaskN* t_ptr) {
  add_to_multitask(&e_ptr->value->task_pool, t_ptr->value);
  t_ptr->value->executors.push_back(e_ptr->replicate());
}

void link_executors_to_tasks(list<Executor>& es, list<Task>& ts) {
  TaskN* cur_task = ts.first;
  file::protocol() << "Начало образования связей\n";
  while (cur_task) {
    unsigned i = 0;
    file::protocol() << "Для задачи {";
    cur_task->value->name.print(file::protocol());
    file::protocol() << "}:\n";
    cur_task->value->_executors_positions.print(file::protocol());
    file::protocol() << '\n';

    list<_Id>::Node* cur_id = cur_task->value->_executors_positions.first;
    ExecutorN* cur_exec = es.first;
    while (cur_id) {
      if (i == cur_id->value->id) {
        form_bond(cur_exec, cur_task);
        cur_id = cur_id->next;
      }
      i++;
      cur_exec = cur_exec->next;
    }
    cur_exec = cur_task->value->executors.first;
    while (cur_exec) {
      file::protocol() << "\tСвязь с {";
      cur_exec->value->name.print(file::protocol());
      file::protocol() << "}\n";
      cur_exec = cur_exec->next;
    }

    file::protocol() << std::endl;
    cur_task = cur_task->next;
  }
}
