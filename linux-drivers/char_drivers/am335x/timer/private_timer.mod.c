#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);

struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
 .name = KBUILD_MODNAME,
 .init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
 .exit = cleanup_module,
#endif
 .arch = MODULE_ARCH_INIT,
};

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0x6fb8d7bc, "module_layout" },
	{ 0x16808ecc, "cdev_del" },
	{ 0xc7ef0ce2, "class_destroy" },
	{ 0xcfad398d, "device_destroy" },
	{ 0x7485e15e, "unregister_chrdev_region" },
	{ 0x45a55ec8, "__iounmap" },
	{ 0x29537c9e, "alloc_chrdev_region" },
	{ 0xda72f6c6, "cdev_add" },
	{ 0xb1f57786, "cdev_init" },
	{ 0xdc1e1b7d, "device_create" },
	{ 0x4c1d0cd4, "__class_create" },
	{ 0xd8e484f0, "register_chrdev_region" },
	{ 0x40a6f522, "__arm_ioremap" },
	{ 0x67c2fa54, "__copy_to_user" },
	{ 0x27e1a049, "printk" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "EFAE50EBB0B5CE71189ABEA");
