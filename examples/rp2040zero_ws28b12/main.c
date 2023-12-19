#include <FreeRTOS.h>
#include <task.h>
#include <stdbool.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "ws2812.pio.h"

static const TickType_t MS_DELAY = 10 / portTICK_PERIOD_MS;
static const uint8_t INTENSITY_MAX = 255;
static const uint8_t INTENSITY_MIN = 0;
static const uint8_t RGB_LED_PIN = 16;

static TaskHandle_t task_handle = NULL;

/**
 * Sets the pixel color
 * 
 * @param pixel_grb 32-bit value
 */
static inline void put_pixel(uint32_t pixel_grb)
{
    pio_sm_put_blocking(pio0, 0, pixel_grb << 8u);
}

/**
 * Converts the three 8-bit RGB values to a single 32-bit value
 * 
 * @param r red value
 * @param g green value
 * @param b blue value
 * @return 32-bit value
*/
static inline uint32_t urgb_u32(uint8_t r, uint8_t g, uint8_t b)
{
    return ((uint32_t)(r) << 8) |
           ((uint32_t)(g) << 16) |
           (uint32_t)(b);
}

enum intensity_direction{
    UP,
    DOWN
};

enum color{
    RED,
    GREEN,
    BLUE
};

static bool update_intensity(int *intensity, enum intensity_direction *direction)
{
    bool change_color = false;
    if (*direction == UP)
    {
        ++(*intensity);
        if (*intensity > INTENSITY_MAX - 1)
        {
            *direction = DOWN;
            *intensity = INTENSITY_MAX;
        }
    }
    else
    {
        --(*intensity);
        if (*intensity < INTENSITY_MIN + 1)
        {
            *direction = UP;
            *intensity = INTENSITY_MIN;
            change_color = true;
        }
    }
    return change_color;
}

static int intensity_ = INTENSITY_MIN;
static enum intensity_direction direction_ = UP;
static int color_ = RED;
void led_task_pico(void *unused_arg)
{
    PIO pio = pio0;
    int sm = 0;
    uint offset = pio_add_program(pio, &ws2812_program);

    ws2812_program_init(pio, sm, offset, RGB_LED_PIN, 800000, false);

    while (true)
    {
        if (update_intensity(&intensity_, &direction_))
        {
            ++color_;
        }

        if (color_ > BLUE)
        {
            color_ = RED;
        }

        if (color_ == RED)
        {
            put_pixel(urgb_u32(intensity_, 0, 0));
        }
        else if (color_ == GREEN)
        {
            put_pixel(urgb_u32(0, intensity_, 0));
        }
        else
        {
            put_pixel(urgb_u32(0, 0, intensity_));
        }
        vTaskDelay(MS_DELAY);
    }
}

int main()
{
    BaseType_t pico_status = xTaskCreate(led_task_pico,
                                         "PICO_LED_TASK",
                                         128,
                                         NULL,
                                         1,
                                         &task_handle);

    if (pico_status == pdPASS)
    {
        vTaskStartScheduler();
    }

    while (true)
    {
    };
}
