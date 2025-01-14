#ifndef SEGMENT_H
#define SEGMENT_H

#define SEGMENT_GPIO_TOP 16
#define SEGMENT_GPIO_TOP_LEFT 22
#define SEGMENT_GPIO_TOP_RIGHT 17
#define SEGMENT_GPIO_MID 23
#define SEGMENT_GPIO_BOT 19
#define SEGMENT_GPIO_BOT_LEFT 21
#define SEGMENT_GPIO_BOT_RIGHT 18
#define SEGMENT_GPIO_POINT 27

#define LATCH_ONE 32
#define LATCH_SECOND 33
#define LATCH_THIRD 12
#define LATCH_FOURTH 13
#define LATCH_FIFTH 14
#define LATCH_SIXTH 15

#define CATHODE 25  // PWD

void segment_init();
void segment_display_all(int latch_gpio);

#endif  // SEGMENT_H