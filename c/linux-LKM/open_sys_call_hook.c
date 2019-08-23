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
typeof(sys_read) *real_read;

asmlinkage long (*real_execve)(const char __user *filename,
    const char __user *const __user *argv,
    const char __user *const __user *envp);

asmlinkage long fake_execve(const char __user *filename,
    const char __user *const __user *argv,
    const char __user *const __user *envp){
    unsigned char kbuf[255];
    unsigned long filename_len = strnlen_user(filename, 255);
    copy_from_user(kbuf, filename, filename_len);
    printk(KERN_INFO "execve command: %s.\n", kbuf);
    return real_execve(filename, argv, envp);
}

asmlinkage long my_read(int fd, char __user *buf, size_t count)
{
	unsigned char kbuf[32];

	printk(KERN_INFO "read fd: %d.\n", fd);

	/* Call the original syscall */
	return real_read(fd, buf, count);
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
	// real_read = (typeof(sys_read) *)real_sys_call_table[__NR_read];
	real_execve = (void *)real_sys_call_table[__NR_execve];
	
	set_addr_rw((unsigned long)real_sys_call_table);
	// SMP_UPDATE({real_sys_call_table[__NR_read] = (void *)&my_read;});
	SMP_UPDATE({real_sys_call_table[__NR_execve] = (void *)&fake_execve;});

	return 0;
}

static void __exit sys_call_hook_exit(void) {
	// SMP_UPDATE({real_sys_call_table[__NR_read] = (void *)real_read;});
	SMP_UPDATE({real_sys_call_table[__NR_execve] = (void *)real_execve;});
	set_addr_ro((unsigned long)real_sys_call_table);
	printk(KERN_INFO "Remove hook...\n");
}

module_init(sys_call_hook_init);
module_exit(sys_call_hook_exit);
