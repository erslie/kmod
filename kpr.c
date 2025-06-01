#include "klib.h"

MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("ersli");
MODULE_DESCRIPTION("A simple kprobe test module");

static struct kprobe my_kprobe = {
    .symbol_name = "sys_openat",
};

static int handler_pre(struct kprobe *p, struct pt_regs *regs) {

    pr_info("kprobes_test: Pre-handler for %s triggered. (PID: %d, Comm: %s)\n",
            p->symbol_name, current->pid, current->comm);

    return 0;
}

static void handler_post(struct kprobe *p, 
                        struct pt_regs *regs, 
                        unsigned long flags) 
{

    pr_info("kprobe_test: Post-handler for %s triggered. (PID: %d, Comm: %s, Return value: %ld)\n",
            p->symbol_name, current->pid, current->comm, regs_return_value(regs));

}

static int __init kprobe_init(void)
{
    int ret;

    pr_info("kprobe_test: Initializing KProbe module...\n");

    my_kprobe.pre_handler = handler_pre;
    my_kprobe.post_handler = handler_post;

    ret = register_kprobe(&my_kprobe);
    if (ret < 0) {
        pr_err("kprobe_test: register_kprobe failed with error %d\n", ret);
        return ret;
    }

    pr_info("kprobe_test: KProbe on %s registered successfully.\n", my_kprobe.symbol_name);
    return 0;
}

static void __exit kprobe_exit(void)
{
    unregister_kprobe(&my_kprobe);
    pr_info("kprobe_test: KProbe on %s unregistered.\n", my_kprobe.symbol_name);
    pr_info("kprobe_test: KProbe module unloaded.\n");
}

module_init(kprobe_init);
module_exit(kprobe_exit);