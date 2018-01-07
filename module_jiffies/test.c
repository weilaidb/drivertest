#include <linux/module.h> //MODULE_LICENSE
#include <linux/kernel.h> //printk 
#include <linux/init.h> //module_init
#include <linux/timer.h>

static void ldm_handler(unsigned long data);


static struct timer_list timer  = {	
	.function = ldm_handler,
	.data = 123456789,
};


static void ldm_handler(unsigned long data)
{
	printk("data = %lu\n", data);
	mod_timer(&timer, jiffies + HZ);
	timer.data = jiffies;
}




static int test_init(void)
{
	printk("%s :%s\n", __FILE__, __FUNCTION__);
	printk("jiffies: %lu\n", jiffies);
	
	//初始化timer对象
	init_timer(&timer);
	timer.data = jiffies;
	//开启timer, function方法将在当前时间点后的1秒钟触发 
	//jiffies是一个全局变量，它的值不停完了递增，随时可以访问，获取当前时间点
	//HZ表示一秒钟里jiffies递增的数量
	mod_timer(&timer, jiffies + HZ);
	
	return 0;

}


static void test_exit(void)
{

	printk("%s: %s\n", __FILE__, __FUNCTION__);
	del_timer(&timer);
}

module_init(test_init);//
module_exit(test_exit);
MODULE_LICENSE("GPL");
