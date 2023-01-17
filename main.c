#include <Arduino.h>

#include <U8g2lib.h>

void oled_roll_Task(void *pt)
{
    U8G2_SSD1306_128X64_NONAME_1_HW_I2C u8g2(U8G2_R0, /* reset=*/U8X8_PIN_NONE, /* clock=*/9, /* data=*/10); // ESP32 Thing, HW I2C with pin remapping
    u8g2.begin();
    for (;;)
    {
        u8g2.clearBuffer();
        u8g2.setFont(u8g2_font_ncenB08_tr);
        for (int x = 0; x < 256; x++)
        {                                             // x+=y ----->等价于x=x+y
            u8g2.clearBuffer();                       // 清除内部缓冲区
            u8g2.drawStr(x, 8, "Hello World!");       // 第一段输出位置
            u8g2.drawStr(x - 128, 8, "Hello World!"); // 第二段输出位置
            vTaskDelay(200);                          // 延时程序，可以降低位移速度
            u8g2.sendBuffer();                        // transfer internal memory to the displa
        }
    }
}

void setup()
{
    xTaskCreate(oled_roll_Task, "Roll OLED", 1024 * 3, NULL, 1, NULL);
    vTaskDelay(1000);
}

void loop()
{
    ;
}
