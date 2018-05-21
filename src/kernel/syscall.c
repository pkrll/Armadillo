
extern int __pause();
extern int __terminate();

void make_io_request() {
	__pause();
}

void exit() {
	__terminate();
}
