# Display

Use the OLED display on the Seeed Studio Expansion Base for XIAO.

### Library

[**u8g2**](https://github.com/olikraus/U8g2_Arduino) - search and install with the library manager in Arduino IDE

### Code for English text

```ino
#include <Arduino.h>
#include <U8x8lib.h>
#include <Wire.h>

U8X8_SSD1306_128X64_NONAME_HW_I2C u8x8(/* clock=*/ SCL, /* data=*/ SDA, /* reset=*/ U8X8_PIN_NONE);   // OLEDs without Reset of the Display

void setup(void) {
  u8x8.begin();
  u8x8.setFlipMode(1);   // set number from 1 to 3, the screen word will rotary 180
}

void loop(void) {
  u8x8.setFont(u8x8_font_chroma48medium8_r);
  u8x8.setCursor(0, 0);
  u8x8.print("Hello World!");
}
```

### Code for Chinese text

```ino
#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* clock=*/ SCL, /* data=*/ SDA, /* reset=*/ U8X8_PIN_NONE);

void setup(void) {
  u8g2.begin();
  u8g2.enableUTF8Print();
}

void loop(void) {
  u8g2.setFont(u8g2_font_unifont_t_chinese1);
  u8g2.setFontDirection(0);
  u8g2.clearBuffer();
  u8g2.setCursor(0, 15);
  u8g2.print("Hello World!");
  u8g2.setCursor(0, 40);
  u8g2.print("你好世界");
  u8g2.sendBuffer();

  delay(1000);
}
```

The default is not included all the Chinese characters. Follow the steps below to add.

1. Download the [code](https://github.com/olikraus/u8g2) and copy folder `tools` to your `u8g2` library folder (`C:\Users\user\Documents\Arduino\libraries\U8g2`).
2. Add **Unicode** of character to file `U8g2\tools\font\build\chinese1.map`. (For example, to `繁` (Unicode: `\u7e41`), add `$7e41` to the file.)
3. Change directory to `U8g2\tools\font\bdfconv` and run command `bdfconv.exe -v ../bdf/unifont.bdf -b 0 -f 1 -M ../build/chinese1.map -d ../bdf/7x13.bdf -n u8g2_font_unifont -o u8g2_font_unifont.c`.
4. Replace the value of `u8g2_font_unifont_t_chinese1` in `U8g2\src\clib\u8g2_fonts.c` with the array in `U8g2\tools\font\bdfconv\u8g2_font_unifont.c`.
5. Done. Change the example code and upload to your device.
