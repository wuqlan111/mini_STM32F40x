
#include  <stdint.h>
#include  <memory.h>
#include  <string.h>

#include  "3rd/gm_cli.h"
#include  "../include/console.h"


static  void cli_putchar(const char c)
{
    console_putchar((uint8_t)c);
}

void  system_cli_module_init(void)
{
    GM_CLI_Init();
    /* 注册输出驱动 */
    GM_CLI_RegOutCharCallBack(cli_putchar);
    /* 设置提示符 */
    GM_CLI_SetCommandPrompt("[STM32-CLI] > ");
    /* 启动CLI */
    GM_CLI_Start();
}








int32_t  cli_test_command_callback(int32_t argc, char * argv[])
{
    int32_t  ret  =   0;
    // uint32_t  






    return   0;

}





















GM_CLI_CMD_EXPORT(command_name, "command_usage_string", command_callback);


