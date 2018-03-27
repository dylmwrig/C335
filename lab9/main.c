/* main.c --- 
 * 
 * Filename: main.c
 * Description: 
 * Author: 
 * Maintainer: 
 * Created: Thu Jan 10 11:23:43 2013
 * Last-Updated: 
 *           By: 
 *     Update #: 0
 * Keywords: 
 * Compatibility: 
 * 
 */

/* Commentary: 
 * 
 * 
 * 
 */

/* Change log:
 * 
 * 
 */

/*
 * Author: Dylan Wright
 * Partner: EJ Seong (we worked on initializations together)
 */

/* Code: */

#include <stm32f30x.h>  // Pull in include files for F30x standard drivers 
#include <f3d_led.h>
#include <f3d_uart.h>
#include <f3d_gyro.h>
#include <f3d_lcd_sd.h>
#include <f3d_i2c.h>
#include <f3d_accel.h>
#include <f3d_mag.h>
#include <f3d_nunchuk.h>
#include <f3d_rtc.h>
#include <ff.h>
#include <diskio.h>
#include <stdio.h>
#include <string.h> //strlen

//these structs are copied from the document about bmp inclusion
struct bmpfile_magic {
  unsigned char magic[2];
};

struct bmpfile_header {
  uint32_t filesz;
  uint16_t creator1;
  uint16_t creator2;
  uint32_t bmp_offset;
};

typedef struct {
  uint32_t header_sz;
  int32_t   width;
  int32_t   height;
  uint16_t nplanes;
  uint16_t bitspp;
  uint32_t compress_type;
  uint32_t bmp_bytesz;
  int32_t   hres;
  int32_t   vres;
  uint32_t ncolors;
  uint32_t nimpcolors;
} BITMAPINFOHEADER;

struct bmppixel { // little endian byte order
 uint8_t b;
 uint8_t g;
 uint8_t r;
};

/*
 * converting color
 * as noted on page 185 in the manual about bmp images, the color will be 24 bit.
 * However, to display on the lcd, you will have to convert it to 16 bit. This is lossy conversion.
 * Basically, you will remove 8 bits as evenly as possible across the 3 bytes so one does not lose more data than the others
 * You do this by removing 3 bits from the first, 3 from the second, and 2 from the third.
 * you then pass these bits into the 16 bytes and boom its converted.
 *
 */

void die (FRESULT rc) {
  printf("Failed with rc=%u.\n", rc);
  while (1);
}

FATFS Fatfs;		/* File system object */
FIL Fil;		/* File object */
BYTE Buff[128];		/* File read buffer */
BITMAPINFOHEADER info;
nunchuk_t n;

int main(void) { 
  char footer[20];
  int count=0;
  int i, j;

  FRESULT rc;			/* Result code */
  DIR dir;			/* Directory object */
  FILINFO fno;			/* File information object */
  UINT bw, br;
  unsigned int retval;

  //bmppixel p = {1,2,3};
  //printf("%u", p.b);

  setvbuf(stdin, NULL, _IONBF, 0);
  setvbuf(stdout, NULL, _IONBF, 0);
  setvbuf(stderr, NULL, _IONBF, 0);

  f3d_uart_init();
  delay(30);
  f3d_lcd_init();
  delay(30);
  f3d_delay_init();
  delay(30);
  f3d_rtc_init();
  delay(30);
  f3d_i2c1_init(); 
  delay(30);
  f3d_nunchuk_init();
  delay(30);

/*
  f_mount(0, &Fatfs);		// Register volume work area (never fails) 

  printf("\nOpen an existing file (message.txt).\n");
    rc = f_open(&Fil, "MESSAGE.TXT", FA_READ);
  if (rc) die(rc);

  printf("\nType the file content.\n");
  for (;;) {
    rc = f_read(&Fil, Buff, sizeof Buff, &br);	// Read a chunk of file 
    if (rc || !br) break;			// Error or end of file 
    for (i = 0; i < br; i++)		        // Type the data 
      putchar(Buff[i]);
  }
  if (rc) die(rc);
  
  printf("\nClose the file.\n");
  rc = f_close(&Fil);
  if (rc) die(rc);
  
  printf("\nCreate a new file (hello.txt).\n");
  rc = f_open(&Fil, "HELLO.TXT", FA_WRITE | FA_CREATE_ALWAYS);
  if (rc) die(rc);
  
  printf("\nWrite a text data. (Hello world!)\n");
  rc = f_write(&Fil, "Hello world!\r\n", 14, &bw);
  if (rc) die(rc);
  printf("%u bytes written.\n", bw);
  
  printf("\nClose the file.\n");
  rc = f_close(&Fil);
  if (rc) die(rc);
  
  printf("\nOpen root directory.\n");
  rc = f_opendir(&dir, "");
  if (rc) die(rc);
  printf("\nDirectory listing...\n");
  for (;;) {
    rc = f_readdir(&dir, &fno);		// Read a directory item 
    if (rc || !fno.fname[0]) break;	// Error or end of dir 
    if (fno.fattrib & AM_DIR)
      printf("   <dir>  %s\n", fno.fname);
    else
      printf("%8lu  %s\n", fno.fsize, fno.fname);
 
  }
  if (rc) die(rc);
  
  printf("\nTest completed.\n");

  rc = disk_ioctl(0,GET_SECTOR_COUNT,&retval);
  printf("%d %d\n",rc,retval);
*/
 /* 
 * Read in and use images from the sd card
 * convert is a linux program which can be used on the image
 * both for rotating and resizing the image
 * example of using convert to resize a jpeg to the 128x160 geometry of the lcd:
 * convert -resize 128x160! input.jpg output.jpg
 */  


/*
  rc = f_open(&Fil, "OLDMAN.BMP", FA_READ);
  delay(50); //delaying just in case

  for(;;) {
    // Read a chunk of file
    rc = f_read(&Fil, Buff,sizeof Buff, &br);
    if (rc || !br) break; // Error or end of file 

    for(i = 0; i < br; i++)// Type the data 
      printf("%d\n", (Buff[i]));
  }

  if (rc) die(rc);
  //to convert the color to make it presentable on our lcd screen, you must bitwise shift color values
  //3 for read, 3 for green, 2 for blue
  //I am not sure if it matters which color you choose to shift by 2 so I'm choosing it arbitrarily
 
  for(j = 160; j > 0; j--){
    
    rc = f_read(&Fil, info,sizeof info, &br);
    printf("width %d height %d\n", info.width, info.height);

    //rc = f_read(&Fil, Buff,sizeof Buff, &br);
    if (rc) die(rc);
    for (i = 0; i < 128; i++){
      uint16_t color = ((uint16_t)(Buff[i].r >> 3)) << 11 | ((uint16_t) (Buff[i].g >> 3)) << 6 | (Buff[i].b >> 3);
      f3d_lcd_drawPixel(i, j, color);
    } //end for
  } //end for 

  printf("Displayed image\n");

  rc = f_close(&Fil);
*/
  //files I'm going to read
  //OLDMAN.BMP
  //GOBLIN.BMP
  //KILLME.BMP

  int choice = 1;
  char fileName[10];

  while (1){ 
    f3d_nunchuk_read(&n);

    //255 = joystick pointed to right
    if (n.jx == 255){
      choice++;
   
      if (choice > 3){
        choice = 1;
      } //end if
    } //end if
 
    //pointed to the left
    else if (n.jx == 0){
      choice--;

      if (choice < 1){
        choice = 3;
      } //end if
    } //end else if

    if (choice == 1){
      strcpy(fileName, "OLDMAN.BMP");
    } //end if

    else if (choice == 2){
      strcpy(fileName, "GOBLIN.BMP");
    } //end else if

    else if (choice == 3){
      strcpy(fileName, "KILLME.BMP");
    } //end else if

    printf("Opening %s\n", fileName);
  } //end while
} //end main

#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t* file, uint32_t line) {
/* Infinite loop */
/* Use GDB to find out why we're here */
  while (1);
}
#endif

/* main.c ends here */
