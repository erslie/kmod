#include <linux/module.h>
#include <linux/kernel.h>

MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("ersli");
MODULE_DESCRIPTION("A simple hello world kernel module");

static int hello_init(void) {
    printk(KERN_INFO "Hello, Kernel World!\n");
    return 0;
}

static void hello_exit(void) {
    printk(KERN_INFO "Goodbye...\n");
}

module_init(hello_init);
module_exit(hello_exit);