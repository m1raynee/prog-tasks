#pragma once
#include <fstream>
#include <iomanip>
#include "const.hpp"
#include "abstracts.hpp"

using std::istream, std::ofstream;

#define NODE_CONSTRAINT_FOR(NAME, SEP, END) \
void print(ostream& out);                   \
void destroy();                             \
inline static char sep[] = SEP;             \
inline static char end[] = END;

struct StrChunk;
using str = list<StrChunk, unsigned>;

struct date {
    // memory efficiency!!
    // ```
    // - - 2 - - - - - 1 - - - - - 0 - -
    // 0000 0000 | 0000 0000 | 0000 0000
    // -|-day||month||- - - - year - - |
    // ```
    unsigned char bytes[3];
    date(
        unsigned year,
        short unsigned month,
        short unsigned day
    );
    unsigned year() const;
    short unsigned month() const;
    short unsigned day() const;
    bool is_empty() const;
    void print(ostream& os) const;
};
bool operator==(const date& a, const date& b);
bool operator< (const date& a, const date& b);
bool operator!=(const date& a, const date& b);
bool operator> (const date& a, const date& b);
bool operator<=(const date& a, const date& b);
bool operator>=(const date& a, const date& b);

struct StrChunk {
    char s[STR_CHUNK_LENGTH]{};

    NODE_CONSTRAINT_FOR(StrChunk, " -> ", " -> nullptr")
        void print(ostream& out, unsigned count);
    bool operator==(const StrChunk& other);
};

struct _Id {
    unsigned id;
    NODE_CONSTRAINT_FOR(_Id, ", ", "");
};

struct Executor;
struct Task {
    str name{};
    unsigned rate;  // hours
    unsigned fee;  // * 1k rubles

    // only completed_tasks
    unsigned scope;
    date completion_date{ 0, 0, 0 };

    list<Executor> executors{ true };
    list<_Id> _executors_positions{};

    NODE_CONSTRAINT_FOR(Task, "\n", "\n")
        friend istream& operator>>(istream& is, Task& obj);
};

struct MultiTask {
    list<Task> tasks{ true };
    list<Task> completed_tasks{ true };
    void destroy();
};

struct Executor {
    unsigned long service_number;
    str name{};
    str address{};

    MultiTask task_pool;

    NODE_CONSTRAINT_FOR(Executor, "\n", "\n")
        friend istream& operator>>(istream& is, Executor& obj);
    bool operator==(Executor& b);
};

struct file {
    static std::ofstream& protocol();
    static std::ofstream& out();
};

using ExecutorN = list<Executor>::Node;
using TaskN = list<Task>::Node;

#include "types.ipp"