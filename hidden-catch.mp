Project:      .\hidden-catch
Build Number: 46
Date:         Thu Nov 21 20:05:22 2024
Compiler:     ICCAVR
Version:      8.30.00
Device:       ATMega128

NOTE: AVR Code addresses are word addresses
All other addresses (including ones in FLASH) are byte addresses
  ROM 2% full. 2612 out of 131072 bytes used (does not include absolute areas).
  RAM 72 bytes used (does not include stack usage).

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                             lit   00D4     48 =     72. bytes (rel,con,rom,lit)

       Addr  Global Symbol
      -----  --------------------------------
       00D4  __lit_start
       011C  __lit_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                           idata   011C     48 =     72. bytes (rel,con,rom,lit)

       Addr  Global Symbol
      -----  --------------------------------
       011C  __idata_start
       0164  __idata_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                            text   0164    9A4 =   2468. bytes (rel,con,rom,code)

       Addr  Global Symbol
      -----  --------------------------------
       00B2  __start
       00B2  __text_start
       00D4  _exit
       00D5  _CGRAM_set_menu
       01C4  _LCD_menu
       01D2  _CGRAM_set_quiz2
       0243  _LCD_delay
       024B  _PortInit
       0251  _LCD_Data
       0272  _LCD_Comm
       0293  _LCD_Shift
       02A4  _LCD_CHAR
       02AC  _LCD_STR
       02BC  _LCD_pos
       02CC  _LCD_Clear
       02D0  _LCD_Init
       02E8  _Cursor_Home
       02EC  _LED_correct
       0304  _Interrupt_init
       0311  _LCD_game_start
       035F  _seed_random
       0369  _Quiz_1
       040B  _main
       0441  _delay_ms
       0458  _delay_us
       046F  <LIBRARY>
       046F  mod16s
       0473  div16s
       048D  mod16u
       048F  div16u
       0490  xdiv16u
       04A9  empy16s
       04B9  empy32s
       04B9  empy32u
       04ED  pop_xgsetF0FC
       04F8  push_xgsetF0FC
       04FA  push_xgset30FC
       04FC  push_xgset00FC
       04FE  push_xgset003C
       0503  push_xgsetF000
       0508  pop_xgsetF000
       050D  long_prolog
       051B  long_epilog
       0526  tstzero1
       052C  tstzero2
       0532  asgncblkx
       054B  _srand
       0557  _rand
       0584  __text_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                            data   0100     48 =     72. bytes (rel,con,ram)

       Addr  Global Symbol
      -----  --------------------------------
       0100  __data_start
       0100  _score
       0102  _start_flag
       0104  _q1_flag
       0148  __data_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                          vector   0000      4 =      4. bytes (abs,ovr,rom,code)

Files Linked      [ module(s) ]

C:\iccv8avr\lib\crtatmega.o	[ crtatmega.s ]
.\.objs\cgram.o	[ cgram.c ]
.\.objs\lcd.o	[ lcd.c ]
.\.objs\main.o	[ main.c ]
.\.objs\my128.o	[ my128.c ]
<library>	[ div16s.s, div16u.s, emul16s.s, emul32.s, gpop5.s, gpush.s, gpushy.s, longutil.s, pmstructx.s, rand.s ]


User Global Definitions

ram_end = 0x10ff
hwstk_size = 0x14

Area Definitions

-bfunc_lit:0xd4.0x1000
-bdata:0x100.0x10ff

Additional Flags
  -e:0x20000
