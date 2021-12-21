#include "LinuxMagic.h"
#include <signal.h>
#include <cstdlib>
#include <cstring>
#include <ncurses.h>
#include <unistd.h>
#ifdef __SANITIZE_ADDRESS__
#include <sanitizer/asan_interface.h>
#endif

namespace {
void segv_handler(int, siginfo_t*, void*) {
	endwin();
	abort();
}

void set_segv_handler() {
	struct sigaction action;
  memset(&action, 0, sizeof(struct sigaction));
  action.sa_flags = SA_SIGINFO;
  action.sa_sigaction = segv_handler;
  sigaction(SIGSEGV, &action, NULL);
}
};

void magic_init() {
#ifdef __SANITIZE_ADDRESS__
  __asan_set_error_report_callback([](const char* msg){endwin(); puts(msg);});
#endif
  set_segv_handler();
  atexit([](){endwin();});
}