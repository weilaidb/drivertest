#include <linux/module.h> //MODULE_LICENSE
#include <linux/kernel.h> //printk 
#include <linux/init.h> //module_init


static int test_init(void)
{
	printk("%s :%s\n", __FILE__, __FUNCTION__);
	return 0;

}


static void test_exit(void)
{

	printk("%s: %s\n", __FILE__, __FUNCTION__);
}

module_init(test_init);//
module_exit(test_exit);
MODULE_LICENSE("GPL");
