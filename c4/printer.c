#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void init() {
    // TODO:
}

void printer(char *str) {
	while (*str != '\0') {
		putchar(*str);
		fflush(stdout);
		str ++;
		sleep(1);
	}
}

// 以下区域代码不允许修改，只允许修改 printer 方法。
void *thread_fun_1(void *arg) {
	char *str = "hello"	;
	printer(str);
}


void *thread_fun_2(void *arg) {
	char *str = "world";
	printer(str);
}

int main () {
    init();
	pthread_t tid1, tid2;

	pthread_create(&tid1, NULL, thread_fun_1, NULL);

	pthread_join(tid1, NULL);
	pthread_create(&tid2, NULL, thread_fun_2, NULL);
	pthread_join(tid2, NULL);

	return 0;
}

