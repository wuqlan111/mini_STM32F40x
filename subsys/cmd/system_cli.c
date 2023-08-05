
#include  "3rd/gm_cli.h"














void  system_cli_module_init(void)
{
    GM_CLI_Init();
    /* 注册输出驱动 */
    // GM_CLI_RegOutCharCallBack();
    /* 设置提示符 */
    GM_CLI_SetCommandPrompt("[STM32-CLI] > ");
    /* 启动CLI */
    GM_CLI_Start();
}





