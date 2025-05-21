#include "file.hpp"

void add_to_multitask(MultiTask* mt, Task* repl_tn);
void fill_multitask(MultiTask* mt, list<Task>& ts);
void link_executors_to_tasks(list<Executor>& es, list<Task>& ts);
void form_bond(ExecutorN* e_ptr, TaskN* t_ptr);