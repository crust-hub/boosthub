#ifndef __SIGNAL_CONTROLL_H__
#define __SIGNAL_CONTROLL_H__
#include <signal.h>
namespace signal_controll
{
    void handle_pipe(int sig);
    void signal_controll();
} // namespace signal_controll

#endif