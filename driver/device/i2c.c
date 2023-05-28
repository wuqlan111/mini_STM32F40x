
#include  <stdbool.h>

#include   "../include/i2c.h"


//I2C_CR1 flags
#define I2C_CR1_RESET     (1<<15)          // i2c under reset state
#define I2C_CR1_ALERT     (1<<13)          // 
#define I2C_CR1_PEC     (1<<12)     // packet error checking
#define I2C_CR1_POS     (1<<11)
#define I2C_CR1_ACK     (1<<10)     // ACK returned after a byte received 
#define I2C_CR1_STOP     (1<<9)     // stop generation
#define I2C_CR1_START     (1<<8)        // start generation
#define I2C_CR1_NOSTRETCH     (1<<7)        // clock stretching disable 
#define I2C_CR1_ENGC     (1<<6)         // enable general call
#define I2C_CR1_ENPEC     (1<<5)        // enable PEC calculation
#define I2C_CR1_ENARP     (1<<4)        // enable ARP
#define I2C_CR1_SMBTYPE     (1<<3)      // SMBus host
#define I2C_CR1_SMBMODE     0x2         // SMBus mode
#define I2C_CR1_PE     0x1          // enable peripheral

#define I2C_CR2_LAST     (1<<12)        // next DMA EOT is the last transfer
#define I2C_CR2_DMAEN     (1<<11)       // DMA request enable
#define I2C_CR2_INTBUFEN     (1<<10)        // buffer interrupt enable
#define I2C_CR2_INTEVTEN    (1<<9)      // event interrupt enable
#define I2C_CR2_ITERREN     (1<<8)      // error interrupt enable
#define I2C_CR2_FREQ     0x3f       // peripheral clock frequency
#define I2C_MIN_FREQ    0x2
#define I2C_MAX_FREQ    50
#define I2C_MIN_PTIME   20  // min clock time(ns)

#define I2C_OAR1_10BITADDR  (1<<15)     //10-bit slave address, 7-bit address not ACK
#define I2C_OAR1_ADDR  (0x3ff)          // interface address

#define I2C_OAR2_ADDR   0xfe        // interface address
#define I2C_OAR2_ENDUAL  0x1        // OAR1 and OAR2 all recognized in 7-bit addressing mode


#define I2C_DR_DATA   0xff          // 8-bit data register


#define I2C_SR1_SMBALERT    (1<<15)         // SMBus alert
#define I2C_SR1_TIMEOUT     (1<<14)         // timeout or tlow error
#define I2C_SR1_PECERR      (1<<12)         // PEC error, receiver returns NACK after PEC reception 
#define I2C_SR1_OVERRUN     (1<<11)         // overrun or underrun
#define I2C_SR1_ACKFAIL     (1<<10)         // ACK failure
#define I2C_SR1_ARLO        (1<<9)          // detecte  arbitration lost 
#define I2C_SR1_BERR        (1<<8)          // misplaced start or stop condition
#define I2C_SR1_TDREMPTY    (1<<7)          // data register empty
#define I2C_SR1_RDRNEMPTY     (1<<6)        // data register not empty
#define I2C_SR1_STOPF     (1<4)             // detecte stop condition 
#define I2C_SR1_10BITADD     0x8            // master has sent first address byte
#define I2C_SR1_BTF        0x4              // data byte transfer succeeded
#define I2C_SR1_ADDRMATCH        0x2        // received address matched or end of address transmission
#define I2C_SR1_SBIT        0x1         // start condition generated


#define I2C_SR2_PEC7_0    (0xff<<8)         // packet error checking register
#define I2C_SR2_DUALF     (1<<7)            // received address matched with OAR2
#define I2C_SR2_SMBHOST      (1<<6)         // receive SMBus host address
#define I2C_SR2_SMBDEFAULT    (1<<5)        // receive SMBus device default address
#define I2C_SR2_GENCALL    (1<<4)           // receive general call address 
#define I2C_SR2_DTRA       0x4          // data bytes transmitted
#define I2C_SR2_BUSY    0x2             // communication ongoing on the bus
#define I2C_SR2_MSL     0x1             // master Mode



#define I2C_CCR_FMODE  (1<<15)          // Fm mode I2C
#define I2C_CCR_DUTY  (1<<14)           // Fm mode tlow/thigh = 16/9 
#define I2C_CCR_CLOCK   0xfff           // clock control register in Fm/Sm mode



#define I2C_TRISE_MAX    0x3f      // maximum rise time in Fm/Sm mode


#define  I2C_FLTR_ANOFF  0x10       // disable analog noise filter
#define  I2C_FLTR_DNF   0xf         // digital noise filter

#define   I2C_REG_ADDR_STEP                (0x400u)
#define   I2C_REGS_BASE_ADDR               (0x40005400u)

#define  I2C_CR1_REG_ADDR(i2c)             (I2C_REGS_BASE_ADDR + (i2c) * I2C_REG_ADDR_STEP )
#define  I2C_CR2_REG_ADDR(i2c)             (I2C_REGS_BASE_ADDR + (i2c) * I2C_REG_ADDR_STEP + 0x4)
#define  I2C_OAR1_REG_ADDR(i2c)            (I2C_REGS_BASE_ADDR + (i2c) * I2C_REG_ADDR_STEP + 0x8)
#define  I2C_OAR2_REG_ADDR(i2c)            (I2C_REGS_BASE_ADDR + (i2c) * I2C_REG_ADDR_STEP + 0xC)
#define  I2C_DR_REG_ADDR(i2c)              (I2C_REGS_BASE_ADDR + (i2c) * I2C_REG_ADDR_STEP + 0x10)
#define  I2C_SR1_REG_ADDR(i2c)             (I2C_REGS_BASE_ADDR + (i2c) * I2C_REG_ADDR_STEP + 0x14)
#define  I2C_SR2_REG_ADDR(i2c)             (I2C_REGS_BASE_ADDR + (i2c) * I2C_REG_ADDR_STEP + 0x18)
#define  I2C_CCR_REG_ADDR(i2c)             (I2C_REGS_BASE_ADDR + (i2c) * I2C_REG_ADDR_STEP + 0x1C)
#define  I2C_TRISE_REG_ADDR(i2c)           (I2C_REGS_BASE_ADDR + (i2c) * I2C_REG_ADDR_STEP + 0x20)
#define  I2C_FLTR_REG_ADDR(i2c)            (I2C_REGS_BASE_ADDR + (i2c) * I2C_REG_ADDR_STEP + 0x24)




static i2c_reg_t * i2c_devs[I2C_DEV_NUMBER];

int32_t slave_send_data(uint32_t  i2c_slave, uint8_t data){

    if (i2c_slave >= I2C_DEV_NUMBER)
        return -1;

    i2c_reg_t * i2c_dev =  i2c_devs[i2c_slave];
    i2c_dev->i2c_dr = data;

    



}



int32_t set_master_frequency(uint32_t  i2c_master, uint32_t clk_freq, bool duty, bool fm_mode)
{

    if (i2c_master >= I2C_DEV_NUMBER || clk_freq > I2C_MAX_FREQ || clk_freq < I2C_MIN_FREQ)
        return -1;

    i2c_reg_t * master =  i2c_devs[i2c_master];

    //check i2c master  busy
    if (master->i2c_sr2 & I2C_SR2_BUSY)
        return -1;
    
    master->i2c_cr1 &= ~(I2C_CR1_PE);      //disable i2c master
    master->i2c_cr2 &= ~(I2C_CR2_FREQ);
    master->i2c_cr2 |= clk_freq;

    master->i2c_ccr &= ~I2C_CCR_CLOCK;
    uint32_t clk_time = I2C_MAX_FREQ * I2C_MIN_PTIME / clk_freq;
    uint32_t scl_time =  fm_mode?I2C_FMODE_TIME:I2C_SMODE_TIME;


    if (fm_mode)
       master->i2c_ccr |= I2C_CCR_FMODE;
    else
        master->i2c_ccr &= ~(I2C_CCR_FMODE);
    
    if (duty)
        master->i2c_ccr |= I2C_CCR_DUTY;
    else
        master->i2c_ccr &=  ~I2C_CCR_DUTY;

    uint32_t rate =  fm_mode?(duty?25:3):2;
    master->i2c_ccr |= (scl_time / rate);

    master->i2c_trise &= ~I2C_TRISE_MAX;
    master->i2c_trise |= ((1000 / clk_time) + 1);
    
    master->i2c_cr1 |= I2C_CR1_PE; 
    return 0;

}






int32_t  master_start_condition(uint32_t  i2c_master,  uint16_t slave_addr, bool addr_10bit, bool read)
{

    uint8_t data;
     if ( i2c_master >= I2C_DEV_NUMBER || !addr_10bit && (slave_addr > 0x7f) || addr_10bit && (slave_addr > 0x3ff))
        return -1;

    i2c_reg_t * master = i2c_devs[i2c_master];
    data = addr_10bit?( 0xf0 | ((slave_addr & 0x300) >>7 )):(slave_addr << 1) | read;
    master->i2c_dr =  data;
    master->i2c_cr1 |= I2C_CR1_START;

    while (!(master->i2c_sr1 & I2C_SR1_TDREMPTY))
        ;
    
    if (!addr_10bit)
        return 0;

    data =  (slave_addr & 0x7f) << 1 | read;

    while (!(master->i2c_sr1 & I2C_SR1_TDREMPTY))
        ;

    return 0;
    
}



int32_t i2c_get_data(uint32_t  i2c_dev){


    if ( i2c_dev >= I2C_DEV_NUMBER )
        return -1;

    i2c_reg_t * dev =  i2c_devs[i2c_dev];

    while (!(dev->i2c_sr1 & I2C_SR1_RDRNEMPTY))
        ;
    
    return dev->i2c_dr;

}





int32_t i2c_send_data(uint32_t  i2c_dev,  uint8_t data){

    if ( i2c_dev >= I2C_DEV_NUMBER )
        return -1;

    i2c_reg_t * dev =  i2c_devs[i2c_dev];

    while (!(dev->i2c_sr1 & I2C_SR1_TDREMPTY))
        ;
    
    dev->i2c_dr =  data;
    return   0;

}



int32_t i2c_stop_transfer(uint32_t  i2c_dev){

    if ( i2c_dev >= I2C_DEV_NUMBER )
        return -1;

    i2c_reg_t * dev =  i2c_devs[i2c_dev];

    dev->i2c_cr1 |= I2C_CR1_STOP;

    return  0;

}



int32_t  set_i2c_addr(uint32_t  i2c_master, bool addr10bit,  uint16_t addr){


    if ( i2c_master >= I2C_DEV_NUMBER  || addr10bit && (addr > 0x3ff) || !addr10bit && (addr > 0x7f))
        return -1;

    i2c_reg_t * master =  i2c_devs[i2c_master];

    if (master->i2c_cr1 & I2C_SR2_BUSY)
        return -1;

    master->i2c_cr1 &= ~ I2C_CR1_PE;

    master->i2c_oar1 &= ~ I2C_OAR1_ADDR;

    if (addr10bit){
        master->i2c_oar1 |= I2C_OAR1_10BITADDR;
        master->i2c_oar1 |= addr;
    }else{

       master->i2c_oar1 &= ~I2C_OAR1_10BITADDR;
       master->i2c_oar1 |= (addr << 1);
    }
        
    master->i2c_cr1 |= I2C_CR1_PE;
    return  0;

}





















