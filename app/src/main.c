#include <zephyr/kernel.h>

int main(void)
{
	while (1) {
		printk("Hello World! %s\n", CONFIG_BOARD_TARGET);
		k_sleep(K_SECONDS(1));
	}
	
	return 0;
}
