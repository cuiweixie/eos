#ifndef _HD_H_
#define _HD_H_
#define port_read(port,buf,n) \
  asm("cld;rep;insw"::"d"(port),"D"(buf),"c"(n))
#define port_write(port,buf,n) \
  asm("cld;rep;insw"::"d"(port),"S"(buf),"c"(n))
#define read_sector(buf) port_read(0x1f0,buf,256)
#define write_sector(buf) port_write(0x1f0,buf,256)
#define HD_BUSY 0x80
#define HD_READY 0x40
#define HD_WRERR 0x20
#define HD_SEEK  0x10
#define HD_DRQ  0x08
#define HD_ECC  0x04
#define HD_ERR  0x01
#define REG_STATUS 0x1f7
#define send_hd_cmd(features,device,count,lba,cmd) ({\
	 out_byte(0x3f6,0);\
	 out_byte(0x1f1,features);\
	 out_byte(0x1f2,count);\
	 out_byte(0x1f3,lba&0xff);\
	 out_byte(0x1f4,(lba>>8)&0xff);\
	 out_byte(0x1f5,(lba>>16)&0xff);\
	 out_byte(0x1f6,device);\
	 out_byte(0x1f7,cmd);\
	 })

extern int hd_out(u32 features,u32 device,u32 count,u32 lba,u32 cmd);
extern void init_hd();
#define read_hd(lba,count) hd_out(0,0xe0,count,lba,0x20)
#define write_hd(lba,count) hd_out(0,0xe0,count,lba,0x30)
#endif
