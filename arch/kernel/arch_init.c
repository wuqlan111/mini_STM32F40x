
#include  <stdint.h>
#include  <memory.h>

#include  "arch_regs.h"


extern  void  reset_init_exceptions(void);
extern  void  arch_systick_init(void);

extern  int  main(void);


void   arch_init(void)
{

    reset_init_exceptions();
    // arch_systick_init();

    main();

}







