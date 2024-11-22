Project:      .\hidden-catch
Build Number: 57
Date:         Fri Nov 22 14:04:28 2024
Compiler:     ICCAVR
Version:      8.30.00
Device:       ATMega128

NOTE: AVR Code addresses are word addresses
All other addresses (including ones in FLASH) are byte addresses
  ROM 3% full. 2680 out of 131072 bytes used (does not include absolute areas).
  RAM 76 bytes used (does not include stack usage).

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                             lit   00D4     48 =     72. bytes (rel,con,rom,lit)

       Addr  Global Symbol
      -----  --------------------------------
       00D4  __lit_start
       011C  __lit_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                           idata   011C     4C =     76. bytes (rel,con,rom,lit)

       Addr  Global Symbol
      -----  --------------------------------
       011C  __idata_start
       0168  __idata_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                            text   0168    9E4 =   2532. bytes (rel,con,rom,code)

       Addr  Global Symbol
      -----  --------------------------------
       00B4  __text_start
       00B4  __start
       00D6  _exit
       00D7  _CGRAM_set_menu
       01C6  _LCD_menu
       01D4  _CGRAM_set_quiz2
       0245  _LCD_delay
       024D  _PortInit
       0253  _LCD_Data
       0274  _LCD_Comm
       0295  _LCD_Shift
       02A6  _LCD_CHAR
       02AE  _LCD_STR
       02BE  _LCD_pos
       02CE  _LCD_Clear
       02D2  _LCD_Init
       02EA  _Cursor_Home
       02EE  _Interrupt_init
       02FB  _LCD_game_start
       0349  _Quiz_1
       03E8  _Quiz_2
       03EA  _main
       0431  _delay_ms
       0448  _delay_us
       045F  _LED_correct
       0477  _usart0_transmit
       0481  _usart0_receive
       048B  _Init_USART0
       0498  _Init_Timer2
       04A2  _timer2_comp_isr
       04CF  _get_random
       04EA  <LIBRARY>
       04EA  div32u
       04EC  mod32u
       04F0  div32s
       04F2  mod32s
       051E  long_div_prolog
       0531  long_div_epilog
       0541  tst_R16_R19
       0546  tst_R24_R27
       054B  neg_R24_R27
       0554  empy16s
       0564  pop_xgsetF0FC
       056F  push_xgsetF0FC
       0571  push_xgset30FC
       0573  push_xgset00FC
       0575  push_xgset003C
       057A  push_xgsetF000
       057F  pop_xgsetF000
       0584  neg32
       058D  asgncblkx
       05A6  __text_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                            data   0100     4C =     76. bytes (rel,con,ram)

       Addr  Global Symbol
      -----  --------------------------------
       0100  __data_start
       0100  _score
       0102  _start_flag
       0104  _q1_flag
       0106  _q2_flag
       0146  _txdata
       0147  _rxdata
       0148  _random_seed
       014C  __data_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                          vector   0024     50 =     80. bytes (abs,ovr,rom,code)

Files Linked      [ module(s) ]

C:\iccv8avr\lib\crtatmega.o	[ crtatmega.s ]
.\.objs\cgram.o	[ cgram.c ]
.\.objs\lcd.o	[ lcd.c ]
.\.objs\main.o	[ main.c ]
.\.objs\my128.o	[ my128.c ]
.\.objs\utils.o	[ utils.c ]
<library>	[ div32.s, emul16s.s, gpop5.s, gpush.s, gpushy.s, lneg.s, pmstructx.s ]

User Global Definitions

ram_end = 0x10ff
hwstk_size = 0x14

Area Definitions

-bfunc_lit:0xd4.0x1000
-bdata:0x100.0x10ff

Additional Flags
  -e:0x20000
