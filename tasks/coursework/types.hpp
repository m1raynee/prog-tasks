#pragma once
#include "const.hpp"
#include "abstracts.hpp"

using std::istream, std::ofstream;

#define NODE_CONSTRAINT_FOR(NAME, SEP, END) \
void print(ostream& out);                   \
void destroy();                             \
inline static char sep[] = SEP;             \
inline static char end[] = END;             \
static ofstream* protocol;

struct StrChunk;
using str = list<StrChunk, unsigned>;

struct date {
    // memory efficiency!!
    // ```
    //     2           1           0
    // 0000 0000 | 0000 0000 | 0000 0000
    //  | day||month||        year     |
    // ```
    unsigned char bytes[3];
    date(
        unsigned year,
        short unsigned month,
        short unsigned day
    );
    unsigned year();
    short unsigned month();
    short unsigned day();
    bool is_empty();
};

struct StrChunk {
    char s[STR_CHUNK_LENGTH]{};

    NODE_CONSTRAINT_FOR(StrChunk, " -> ", "nullptr")
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
    date completion_date{0, 0, 0};

    list<Executor> executors{true};
    list<_Id> _executors_positions{};

    NODE_CONSTRAINT_FOR(Task, "\n", "\n")
    friend istream& operator>>(istream& is, Task& obj);
};

struct MultiTask {
    list<Task> tasks{true};
    list<Task> completed_tasks{true};
    void destroy();
    static ofstream* protocol;
};

struct Executor {
    unsigned service_number;
    str name{};
    str address{};

    MultiTask task_pool;

    NODE_CONSTRAINT_FOR(Executor, "\n", "\n")
    friend istream& operator>>(istream& is, Executor& obj);
};

#include "types.ipp"