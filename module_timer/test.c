#include <linux/module.h> //MODULE_LICENSE
#include <linux/kernel.h> //printk 
#include <linux/init.h> //module_init
#include <linux/timer.h>
#include <linux/gpio.h>


static void ldm_handler(unsigned long data);


static struct timer_list timer  = {	
	.function = ldm_handler,
	.data = 123456789,
};

#define GPX3CON (*(volatile u32*)((u32)S5P_VA_GPIO02 + 0x0c60))
#define GPX3DAT (*(volatile u8*)((u32)S5P_VA_GPIO02 + 0x0c64))



static void ldm_handler(unsigned long data)
{
	static int prev_key_stat = 0;
	
	int key_stat = (GPX3DAT >> 2) & 0xf;
	
	if(prev_key_stat != key_stat)
	{
		printk("key stat = %x\n", key_stat);		
		prev_key_stat = key_stat;
	}
	
	printk("data = %lu\n", data);
	mod_timer(&timer, jiffies + HZ / 10);
	timer.data = jiffies;
}




static int test_init(void)
{
	printk("%s :%s\n", __FILE__, __FUNCTION__);
	printk("jiffies: %lu\n", jiffies);
	
	//从原理图上可知，4个按键对应GPX3_2-5
	GPX3CON &= ~(0xffff << 8); 
	
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
