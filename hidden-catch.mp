Project:      .\hidden-catch
Build Number: 0
Date:         Wed Nov 20 14:27:00 2024
Compiler:     ICCAVR
Version:      8.30.00
Device:       ATMega128

NOTE: AVR Code addresses are word addresses
All other addresses (including ones in FLASH) are byte addresses
  ROM 1% full. 1180 out of 131072 bytes used (does not include absolute areas).
  RAM 0 bytes used (does not include stack usage).

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                             lit   00D4     30 =     48. bytes (rel,con,rom,lit)

       Addr  Global Symbol
      -----  --------------------------------
       00D4  __lit_start
       0104  __lit_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                            text   0104    46C =   1132. bytes (rel,con,rom,code)

       Addr  Global Symbol
      -----  --------------------------------
       0082  __start
       0082  __text_start
       00A4  _exit
       00A5  _LCD_delay
       00AD  _PortInit
       00B3  _LCD_Data
       00D4  _LCD_Comm
       00F5  _LCD_Shift
       0106  _LCD_CHAR
       010E  _LCD_STR
       011E  _LCD_pos
       012E  _LCD_Clear
       0132  _LCD_Init
       014A  _Cursor_Home
       014E  _CGRAM_set_menu
       023D  _LCD_menu
       024B  _main
       0257  _delay_ms
       026E  _delay_us
       0285  <LIBRARY>
       0285  empy16s
       0295  push_xgsetF000
       029A  pop_xgsetF000
       029F  asgncblkx
       02B8  __text_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                          vector   0000      4 =      4. bytes (abs,ovr,rom,code)

Files Linked      [ module(s) ]

C:\iccv8avr\lib\crtatmega.o	[ crtatmega.s ]
.\.objs\lcd.o	[ lcd.c ]
.\.objs\main.o	[ main.c ]
.\.objs\my128.o	[ my128.c ]
<library>	[ emul16s.s, gpushy.s, pmstructx.s ]

User Global Definitions

ram_end = 0x10ff
hwstk_size = 0x14

Area Definitions

-bfunc_lit:0xd4.0x1000
-bdata:0x100.0x10ff

Additional Flags
  -e:0x20000
