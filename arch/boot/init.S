	
	.syntax	unified
	.arch	armv7-m

	.section  .exception.table, "a",%progbits
	.align  2	
	.global  expr_vector_table
expr_vector_table:
	.word MAIN_STACK_TOP
	.word reset_handler
	.word NMI_handler
	.word hard_fault_handler
	.word memory_fault_handler
	.word bus_fault_handler
	.word usage_fault_handler
	.word 0
	.word 0
	.word 0
	.word 0
	.word svcall_handler
	.word debug_handler
	.word 0
	.word pendsv_handler
	.word systick_handler
extern_vector:	.space  0x1000
	.size	expr_vector_table, . - expr_vector_table


	.macro  SAVE_CONTEXT
			push   {r4-r11, lr}
			mrs	   r0, control
			push   {r0}
			mrs   r0,   primask
			push   {r0}
			mrs   r0,   basepri
			push   {r0}
			mrs   r0,   faultmask
			push   {r0}
			mov    r0,    sp
			push   {r0}
			sub   r1,  sp, #0x20
			mov   sp,   r1
	.endm

	.macro  RESUME_CONTEXT
			add  r0,  sp, #0x20
			mov  sp,    r0
			pop  {r0}
			mov  sp,   r0
			pop  {r0}
			msr  faultmask,  r0
			pop  {r0}
			msr  basepri, r0
			pop  {r0}
			msr  primask, r0
			pop  {r0}
			msr  control, r0
			pop  {r4-r11, lr}
	.endm

	.macro  RETURN_FROM_EXCEPTION
		bx  lr
	.endm


	.macro	def_irq_handler	handler_name
			.align	1
			.thumb_func
			.type	\handler_name, %function
			.size	\handler_name, . - \handler_name
			\handler_name:
	.endm


	.extern  arch_init
	.extern  do_NMI
	.extern  do_hard_fault
	.extern	 do_mem_fault
	.extern  do_bus_fault
	.extern  do_usage_fault
	.extern  do_svcall
	.extern  do_debug
	.extern  do_pendsv
	.extern  do_systick

	.text
	.thumb
	.thumb_func
	.align   2
	.global  reset_handler
	.type	reset_handler, %function
reset_handler:
		@ set process stack
		ldr    r0,   =PROCESS_STACK_TOP
		msr    psp,  r0
		b   arch_init

    def_irq_handler  NMI_handler
		SAVE_CONTEXT
		bl  do_NMI
		RESUME_CONTEXT
		RETURN_FROM_EXCEPTION


    def_irq_handler  hard_fault_handler
		SAVE_CONTEXT
		bl  do_hard_fault
		RESUME_CONTEXT
		RETURN_FROM_EXCEPTION

    def_irq_handler  memory_fault_handler
		SAVE_CONTEXT
		bl  do_mem_fault
		RESUME_CONTEXT
		RETURN_FROM_EXCEPTION



    def_irq_handler  bus_fault_handler
		SAVE_CONTEXT
		bl  do_bus_fault
		RESUME_CONTEXT
		RETURN_FROM_EXCEPTION


    def_irq_handler  usage_fault_handler
		SAVE_CONTEXT
		bl  do_usage_fault
		RESUME_CONTEXT
		RETURN_FROM_EXCEPTION

    def_irq_handler  svcall_handler
		SAVE_CONTEXT
		bl  do_svcall
		RESUME_CONTEXT
		RETURN_FROM_EXCEPTION

    def_irq_handler  debug_handler
		SAVE_CONTEXT
		bl  .
		RESUME_CONTEXT
		RETURN_FROM_EXCEPTION

    def_irq_handler  pendsv_handler
		SAVE_CONTEXT
		bl  .
		RESUME_CONTEXT
		RETURN_FROM_EXCEPTION

    def_irq_handler  systick_handler
		SAVE_CONTEXT
		bl  do_systick
		RESUME_CONTEXT
		RETURN_FROM_EXCEPTION


	
	.end



