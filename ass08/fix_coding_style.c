// SPDX-License-Identifier: GPL-2.0
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/miscdevice.h>
#include <linux/fs.h>
#include <linux/slab.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Netshikulwe Donald <netshiku@gmail.com>");
MODULE_DESCRIPTION("Fix Coding Style");

static ssize_t myfd_read(const struct file *fp, char __user *user,
		size_t size, loff_t *offs);
static ssize_t myfd_write(const struct file *fp, const char __user *user,
		size_t size, loff_t *offs);
static const struct file_operations myfd_fops = {
	.owner = THIS_MODULE,
	.read = &myfd_read,
	.write = &myfd_write
};
static const struct miscdevice myfd_device = {
	.minor = MISC_DYNAMIC_MINOR,
	.name = "reverse",
	.fops = &myfd_fops
};

char str[PAGE_SIZE];
char *tmp;

static int __init myfd_init(void)
{
	int retval;

	retval = misc_register(&(*(&(myfd_device))));
	return 1;
}
static void __exit myfd_cleanup(void)
{
	misc_deregister(&myfd_device);
}

ssize_t myfd_read(const struct file *fp, char __user *user,
		size_t size, loff_t *offs)
{
	size_t t, i;
	char *tmp2;

	/*
	 * Malloc like a boss
	 */

	tmp2 = kmalloc(sizeof(char) * PAGE_SIZE * 2, GFP_KERNEL);
	tmp = tmp2;
	for (t = strlen(str) - 1, i = 0; t >= 0; t--, i++)
		tmp[i] = str[t];
	tmp[i] = 0x0;
	return simple_read_from_buffer(user, size, offs, tmp, i);
}
ssize_t myfd_write(const struct file *fp, const char __user *user,
		size_t size, loff_t *offs)
{
	ssize_t res;

	res = 0;

	res = simple_write_to_buffer(str, size, offs, user, size) + 1;
	// 0x0 = ’\0’
	str[size + 1] = 0x0;
	return res;
}
module_init(myfd_init);
module_exit(myfd_cleanup);
