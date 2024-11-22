Project:      .\hidden-catch
Build Number: 62
Date:         Fri Nov 22 15:13:04 2024
Compiler:     ICCAVR
Version:      8.30.00
Device:       ATMega128

NOTE: AVR Code addresses are word addresses
All other addresses (including ones in FLASH) are byte addresses
  ROM 3% full. 2750 out of 131072 bytes used (does not include absolute areas).
  RAM 80 bytes used (does not include stack usage).

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                             lit   00D4     48 =     72. bytes (rel,con,rom,lit)

       Addr  Global Symbol
      -----  --------------------------------
       00D4  __lit_start
       011C  __lit_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                           idata   011C     50 =     80. bytes (rel,con,rom,lit)

       Addr  Global Symbol
      -----  --------------------------------
       011C  __idata_start
       016C  __idata_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                            text   016C    A26 =   2598. bytes (rel,con,rom,code)

       Addr  Global Symbol
      -----  --------------------------------
       00B6  __text_start
       00B6  __start
       00D8  _exit
       00D9  _CGRAM_set_menu
       01C8  _LCD_menu
       01D6  _CGRAM_set_quiz2
       0247  _LCD_delay
       024F  _PortInit
       0255  _LCD_Data
       0276  _LCD_Comm
       0297  _LCD_Shift
       02A8  _LCD_CHAR
       02B0  _LCD_STR
       02C0  _LCD_pos
       02D0  _LCD_Clear
       02D4  _LCD_Init
       02EC  _Cursor_Home
       02F0  _Interrupt_init
       02FD  _LCD_game_start
       034B  _Quiz_1
       03EA  _Quiz_2
       03EC  _main
       0433  _delay_ms
       044A  _delay_us
       0461  _LED_correct
       0479  _usart0_transmit
       0483  _usart0_receive
       048D  _Init_USART0
       049A  _Init_Timer2
       04A4  _timer2_comp_isr
       04F2  _get_random
       050D  <LIBRARY>
       050D  div32u
       050F  mod32u
       0513  div32s
       0515  mod32s
       0541  long_div_prolog
       0554  long_div_epilog
       0564  tst_R16_R19
       0569  tst_R24_R27
       056E  neg_R24_R27
       0577  empy16s
       0587  pop_xgsetF0FC
       0592  push_xgsetF0FC
       0594  push_xgset30FC
       0596  push_xgset00FC
       0598  push_xgset003C
       059D  push_xgsetF000
       05A2  pop_xgsetF000
       05A7  neg32
       05B0  asgncblkx
       05C9  __text_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                            data   0100     50 =     80. bytes (rel,con,ram)

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
       014C  _n
       0150  __data_end

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
