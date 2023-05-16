
#include  <stdbool.h>

#include   "../include/i2c.h"


typedef struct i2c_reg{

    uint32_t  i2c_cr1;
    uint32_t  i2c_cr2;
    uint32_t  i2c_oar1;
    uint32_t  i2c_oar2;
    uint32_t  i2c_dr;
    uint32_t  i2c_sr1;
    uint32_t  i2c_sr2;
    uint32_t  i2c_ccr;
    uint32_t  i2c_trise;
    uint32_t  i2c_fltr;

}i2c_reg_t;



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





















