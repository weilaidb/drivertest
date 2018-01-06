#include <linux/module.h> //MODULE_LICENSE
#include <linux/kernel.h> //printk 
#include <linux/init.h> //module_init
#include <linux/slab.h> //kmalloc kfree

char *gp = NULL;
static int malloc_init(void)
{
	char *p = kmalloc(1024, GFP_KERNEL);
	gp = p;
	printk("malloc addr :%p\n", gp);
	printk("%s :%s\n", __FILE__, __FUNCTION__);
	return 0;

}


static void malloc_exit(void)
{
	kfree(gp);
	printk("%s: %s\n", __FILE__, __FUNCTION__);
}

module_init(malloc_init);//
module_exit(malloc_exit);
MODULE_LICENSE("GPL");
