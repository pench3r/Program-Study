#include <linux/kernel.h>
#include <linux/syscalls.h>
#include <linux/module.h>

MODULE_LICENSE("GPL");

unsigned long **real_sys_call_table;
asmlinkage long (*real_open)(const char __user *, int, umode_t);
asmlinkage long fake_open(const char __user *filename, int flag, umode_t mode) {
	if ( (flag & O_CREAT) && strcmp(filename, "/dev/null") != 0) {
		printk(KERN_INFO "Open file %s.\n", filename);
	}
	return real_open(filename, flag, mode);
}

static void disable_write_protect(void) {
	unsigned long cr0 = read_cr0();
	clear_bit(16, &cr0);
	write_cr0(cr0);
}

static void enable_write_protect(void) {
	unsigned long cr0 = read_cr0();
	set_bit(16, &cr0);
	write_cr0(cr0);
}

static unsigned long **find_sys_call_table(void) {
	unsigned long **entry = (unsigned long **)PAGE_OFFSET;
	for (; (unsigned long)entry < ULONG_MAX; entry += 1) {
		if (entry[__NR_close] == (unsigned long *)sys_close)
			return entry;
	}
	return NULL;
}

static int __init sys_call_hook_init(void) {
	printk(KERN_INFO "Begin to hijack system call...\n");
	real_sys_call_table = find_sys_call_table();	
	printk(KERN_INFO "The system call table address is %p.\n", real_sys_call_table); 

	disable_write_protect();
	real_open = (void *)real_sys_call_table[__NR_open];
	real_sys_call_table[__NR_open] = (unsigned long *)fake_open;
	enable_write_protect();

	return 0;
}

static void __exit sys_call_hook_exit(void) {
	disable_write_protect();
	real_sys_call_table[__NR_open] = (unsigned long *)real_open;
	enable_write_protect();
	printk(KERN_INFO "Remove hook...\n");
}

module_init(sys_call_hook_init);
module_exit(sys_call_hook_exit);