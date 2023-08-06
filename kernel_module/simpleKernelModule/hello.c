

#include <linux/init.h>

#include <linux/module.h>

#include <linux/kernel.h>

MODULE_LICENSE("GPL");

MODULE_AUTHOR("or");

MODULE_DESCRIPTION("A simple example Linux module.");

MODULE_VERSION("0.02");
static char *message = "Default message";  // Default message
module_param(message, charp, S_IRUGO);
MODULE_PARM_DESC(message, "User-provided message");


static int __init hello_init(void)
{
    printk(KERN_INFO "Hello %s\n",message);
    return 0;    // Non-zero return means that the module couldn't be loaded.
}

static void __exit hello_cleanup(void)
{
    printk(KERN_INFO "Goodbye, World!\n");
}

module_init(hello_init);
module_exit(hello_cleanup);
