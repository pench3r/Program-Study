#include <linux/kernel.h>
#include <linux/syscalls.h>
#include <linux/module.h>
#include <linux/delay.h>
#include <linux/kallsyms.h>

MODULE_LICENSE("GPL");

/* SMP handling */
#define SMP_UPDATE(x) \
	do { \
		unsigned long __cr0; \
		preempt_disable(); \
		__cr0 = read_cr0() & (~X86_CR0_WP); \
		write_cr0(__cr0); \
		x; \
		__cr0 = read_cr0() | X86_CR0_WP; \
		write_cr0(__cr0); \
		preempt_enable(); \
	} while (0)


static void set_addr_rw(unsigned long _addr)
{
	unsigned int level;
	pte_t *pte = lookup_address(_addr, &level);

	if (pte->pte &~ _PAGE_RW)
		pte->pte |= _PAGE_RW;
}

static void set_addr_ro(unsigned long _addr)
{
	unsigned int level;
	pte_t *pte = lookup_address(_addr, &level);

	pte->pte = pte->pte &~_PAGE_RW;
}



unsigned long *real_sys_call_table;
typeof(sys_open) *real_open;
asmlinkage long fake_open(const char __user *filename, int flag, umode_t mode) {
	if (flag & O_CREAT) {
		printk(KERN_INFO "Open file %s.\n", filename);
	}
	return real_open(filename, flag, mode);
}


static unsigned long **find_sys_call_table(void) {
    unsigned long ptr;
    unsigned long *p;
    for (ptr = (unsigned long)sys_close;
         ptr < (unsigned long)&loops_per_jiffy;
         ptr += sizeof(void *)) {
        p = (unsigned long *)ptr;
        if (p[__NR_close] == (unsigned long)sys_close)
            return (unsigned long **)p;
    }
    return NULL;
}

static int __init sys_call_hook_init(void) {
	printk(KERN_INFO "Begin to hijack system call...\n");
	// real_sys_call_table = find_sys_call_table();	
	real_sys_call_table = (void *)kallsyms_lookup_name("sys_call_table");
	printk(KERN_INFO "The system call table address is %p.\n", real_sys_call_table); 
	real_open = (typeof(sys_open) *)real_sys_call_table[__NR_open];
	
	set_addr_rw((unsigned long)real_sys_call_table);
	SMP_UPDATE({real_sys_call_table[__NR_open] = (void *)&fake_open;});


	return 0;
}

static void __exit sys_call_hook_exit(void) {
	SMP_UPDATE({real_sys_call_table[__NR_open] = (void *)real_open;});
	set_addr_ro((unsigned long)real_sys_call_table);
	printk(KERN_INFO "Remove hook...\n");
}

module_init(sys_call_hook_init);
module_exit(sys_call_hook_exit);
