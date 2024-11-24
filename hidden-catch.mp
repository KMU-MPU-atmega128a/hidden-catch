Project:      .\hidden-catch
Build Number: 2
Date:         Sun Nov 24 14:06:33 2024
Compiler:     ICCAVR
Version:      8.30.00
Device:       ATMega128

NOTE: AVR Code addresses are word addresses
All other addresses (including ones in FLASH) are byte addresses
  ROM 3% full. 2755 out of 131072 bytes used (does not include absolute areas).
  RAM 63 bytes used (does not include stack usage).

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                             lit   00D4     48 =     72. bytes (rel,con,rom,lit)

       Addr  Global Symbol
      -----  --------------------------------
       00D4  __lit_start
       011C  __lit_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                           idata   011C     3F =     63. bytes (rel,con,rom,lit)

       Addr  Global Symbol
      -----  --------------------------------
       011C  __idata_start
       015B  __idata_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                            text   015C    A3C =   2620. bytes (rel,con,rom,code)

       Addr  Global Symbol
      -----  --------------------------------
       00AE  __text_start
       00AE  __start
       00D0  _exit
       00D1  _Interrupt_init
       00DE  _LCD_game_start
       012C  _Quiz_1
       01C9  _Quiz_2
       01CB  _main
       0214  _CGRAM_set_menu
       0303  _LCD_menu
       0311  _CGRAM_set_quiz2
       0382  _LCD_delay
       038A  _PortInit
       0390  _LCD_Data
       03B1  _LCD_Comm
       03D2  _LCD_Shift
       03E3  _LCD_CHAR
       03EB  _LCD_STR
       03FB  _LCD_pos
       040B  _LCD_Clear
       040F  _LCD_Init
       0427  _Cursor_Home
       042B  _LED_correct
       0443  _delay_ms
       045A  _delay_us
       0471  _Init_Timer2
       0479  _timer2_comp_isr
       04A6  _second_counter
       04D9  _get_random
       04EF  _usart0_transmit
       04F9  _usart0_receive
       0503  _Init_USART0
       0510  <LIBRARY>
       0510  div32u
       0512  mod32u
       0516  div32s
       0518  mod32s
       0544  long_div_prolog
       0557  long_div_epilog
       0567  tst_R16_R19
       056C  tst_R24_R27
       0571  neg_R24_R27
       057A  empy16s
       058A  pop_xgsetF0FC
       0595  push_xgsetF0FC
       0597  push_xgset30FC
       0599  push_xgset00FC
       059B  push_xgset003C
       05A0  push_xgsetF000
       05A5  pop_xgsetF000
       05AA  neg32
       05B3  asgncblkx
       05CC  __text_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                            data   0100     3F =     63. bytes (rel,con,ram)

       Addr  Global Symbol
      -----  --------------------------------
       0100  _score
       0100  __data_start
       0102  _start_flag
       0104  _q1_flag
       0106  _q2_flag
       0135  _tmp
       0139  _n
       013D  _txdata
       013E  _rxdata
       013F  __data_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                          vector   0024     50 =     80. bytes (abs,ovr,rom,code)

Files Linked      [ module(s) ]

C:\iccv8avr\lib\crtatmega.o	[ crtatmega.s ]
.\.objs\main.o	[ main.c ]
.\.objs\utils\cgram.o	[ cgram.c ]
.\.objs\utils\lcd.o	[ lcd.c ]
.\.objs\utils\led.o	[ led.c ]
.\.objs\utils\my128.o	[ my128.c ]
.\.objs\utils\timer.o	[ timer.c ]
.\.objs\utils\usart.o	[ usart.c ]
<library>	[ div32.s, emul16s.s, gpop5.s, gpush.s, gpushy.s, lneg.s, pmstructx.s ]

User Global Definitions

ram_end = 0x10ff
hwstk_size = 0x14

Area Definitions

-bfunc_lit:0xd4.0x1000
-bdata:0x100.0x10ff

Additional Flags
  -e:0x20000
