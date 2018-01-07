#include <linux/module.h> //MODULE_LICENSE
#include <linux/kernel.h> //printk 
#include <linux/init.h> //module_init

#include <linux/io.h> // include asm/io.h , 包含了 ioremap  iounmap的声明
#include <linux/gpio.h> //gpio_request
#include <mach/gpio.h> //

struct led_info {
	unsigned gpio; //管脚号，来自mach/gpio.h
	const char *name;
	u8 stat;//灯的状态，0为亮，1为灭
};



static u32 *led_regs;

#define GPM4CON (*(volatile u32 *)led_regs)
#define GPM4DAT (*(volatile u32 *)(led_regs + 1))

static int test_init(void)
{
	printk("%s: %s\n", __FUNCTION__, __FILE__);
	
	//申请gpio的使用权
	size_t i = 0;
	for(i = 0; i < ARRAY_SIZE(EXYNOS4X12_GPM4); i++) {
		gpio_request(led[i].gpio, led[i].name);
		//将对应管脚设置为输出
		gpio_direction_output(led[i].gpio, led[i].stat);
	}
	
}

static  void test_exit(void)
{
	printk("%s :%s\n", __FILE__, __FUNCTION__);
	//申请gpio的使用权
	size_t i = 0;
	for(i = 0; i < ARRAY_SIZE(led); i++) {
		//灭灯
		gpio_set_value(led[i].gpio, 1);
		gpio_free(led[i].gpio);
	}	
}







static int led_init(void)
{
	//GPM4_0-3 设为输出
	GPM4CON &= ~0xffff;

	return 0;
}

static void led_on(u8 stat)
{
	CPM4DAT = (GPM4DAT & ~0xf ) | stat & 0xf;
}



static int gpio_init(void)
{
	printk("%s :%s\n", __FILE__, __FUNCTION__);

//ioremap 获取虚拟地址
//根据原理图可知 ，4个LED灯对应的GPIO的GPM4_0-3
	led_regs = ioremap(0x110002e0, 8);
	printk("led_regs addr :%p\n", led_regs);

	return 0;

}


static void gpio_exit(void)
{

	printk("%s: %s\n", __FILE__, __FUNCTION__);
//释放虚拟地址
	iounmap(led_regs);
}

module_init(gpio_init);//
module_exit(gpio_exit);
MODULE_LICENSE("GPL");
