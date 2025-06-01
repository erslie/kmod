#include "klib.h"

MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("ersli");
MODULE_DESCRIPTION("A simple hello world kernel module with an exported function");

void my_hello_function(int count)
{
    printk(KERN_INFO "hello: Hello, kernel world! count:%d\n", count);
}

EXPORT_SYMBOL(my_hello_function);

static int hello_init(void) {

    printk(KERN_INFO "hello: Module loaded. my_hello_function is available.\n");
    my_hello_function(1);
    return 0;
}

static void hello_exit(void) {
    printk(KERN_INFO "hello: Module unloaded.\n");
}

module_init(hello_init);
module_exit(hello_exit);