Project:      .\hidden-catch
Build Number: 38
Date:         Wed Nov 20 20:40:59 2024
Compiler:     ICCAVR
Version:      8.30.00
Device:       ATMega128

NOTE: AVR Code addresses are word addresses
All other addresses (including ones in FLASH) are byte addresses
  ROM 2% full. 2245 out of 131072 bytes used (does not include absolute areas).
  RAM 65 bytes used (does not include stack usage).

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                             lit   00D4     30 =     48. bytes (rel,con,rom,lit)

       Addr  Global Symbol
      -----  --------------------------------
       00D4  __lit_start
       0104  __lit_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                           idata   0104     41 =     65. bytes (rel,con,rom,lit)

       Addr  Global Symbol
      -----  --------------------------------
       0104  __idata_start
       0145  __idata_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                            text   0146    854 =   2132. bytes (rel,con,rom,code)

       Addr  Global Symbol
      -----  --------------------------------
       00A3  __start
       00A3  __text_start
       00C5  _exit
       00C6  _CGRAM_set_menu
       01B5  _LCD_menu
       01C3  _LCD_delay
       01CB  _PortInit
       01D1  _LCD_Data
       01F2  _LCD_Comm
       0213  _LCD_Shift
       0224  _LCD_CHAR
       022C  _LCD_STR
       023C  _LCD_pos
       024C  _LCD_Clear
       0250  _LCD_Init
       0268  _Cursor_Home
       026C  _Interrupt_init
       0279  _LCD_game_start
       02C7  _Quiz_1
       0356  _main
       038A  _delay_ms
       03A1  _delay_us
       03B8  <LIBRARY>
       03B8  mod16s
       03BC  div16s
       03D6  mod16u
       03D8  div16u
       03D9  xdiv16u
       03F2  empy16s
       0402  empy32u
       0402  empy32s
       0436  pop_xgsetF0FC
       0441  push_xgsetF0FC
       0443  push_xgset30FC
       0445  push_xgset00FC
       0447  push_xgset003C
       044C  push_xgsetF000
       0451  pop_xgsetF000
       0456  long_prolog
       0464  long_epilog
       046F  tstzero1
       0475  tstzero2
       047B  asgncblkx
       0494  _srand
       04A0  _rand
       04CD  __text_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                            data   0100     41 =     65. bytes (rel,con,ram)

       Addr  Global Symbol
      -----  --------------------------------
       0100  __data_start
       0100  _score
       0102  _start_flag
       0104  _q1_flag
       0141  __data_end

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
