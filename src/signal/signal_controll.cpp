#include "./signal_controll.h"

struct sigaction signal_controll_action;

void signal_controll::handle_pipe(int sig)
{
}
void signal_controll::signal_controll()
{
    //屏蔽socket write时失败导致进程退出
    signal_controll_action.sa_handler = signal_controll::handle_pipe;
    sigemptyset(&signal_controll_action.sa_mask);
    signal_controll_action.sa_flags = 0;
    sigaction(SIGPIPE, &signal_controll_action, 0);
}