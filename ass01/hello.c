#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

MODULE_AUTHOR("Donald");
MODULE_DESCRIPTION("Hello World\n");
MODULE_LICENSE("GPL");

static int __init hello_init(void)
{
	printk(KERN_INFO "Hello World!!!\n");
	return 0;
}

static void __exit hello_exit(void)
{
	printk(KERN_INFO "Goodbye!!!\n");
}

module_init(hello_init);
module_exit(hello_exit);
