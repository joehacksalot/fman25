#ifndef TOUCH_SENSOR_H_
#define TOUCH_SENSOR_H_

#include "esp_err.h"
#include "esp_event.h"
#include "NotificationDispatcher.h"

#define DELTA_VALUE_HISTORY_SIZE 1

typedef enum TouchSensorEvent_t
{
    TOUCH_SENSOR_EVENT_RELEASED = 0,
    TOUCH_SENSOR_EVENT_TOUCHED,
    TOUCH_SENSOR_EVENT_SHORT_PRESSED,
    TOUCH_SENSOR_EVENT_LONG_PRESSED,
    TOUCH_SENSOR_EVENT_VERY_LONG_PRESSED
} TouchSensorEvent;

typedef struct TouchSensorEventNotificationData_t
{
    TouchSensorEvent touchSensorEvent;
    int touchSensorIdx;
} TouchSensorEventNotificationData;

#if defined (TRON_BADGE) || defined (REACTOR_BADGE)
typedef enum TouchSensorNames_t
{
    TOUCH_SENSOR_12_OCLOCK = 0, // 0
    TOUCH_SENSOR_1_OCLOCK,  // 1
    TOUCH_SENSOR_2_OCLOCK,  // 2
    TOUCH_SENSOR_4_OCLOCK,  // 3
    TOUCH_SENSOR_5_OCLOCK,  // 4
    TOUCH_SENSOR_7_OCLOCK,  // 5
    TOUCH_SENSOR_8_OCLOCK,  // 6
    TOUCH_SENSOR_10_OCLOCK, // 7
    TOUCH_SENSOR_11_OCLOCK, // 8
    TOUCH_SENSOR_NUM_BUTTONS // 9
} TouchSensorNames;

// Reactor Pin Map Notes:
// touch pin 1 -> no response
// touch pin 7 -> 12,6 o' clock -> 0 idx
// touch pin 6 -> 1 o' clock    -> 1 idx
// touch pin 4 -> 2 o' clock    -> 2 idx
// touch pin 3 -> 4 o' clock    -> 3 idx
// touch pin 2 -> 5 o' clock    -> 4 idx
// touch pin 5 -> 7 o' clock    -> 5 idx
// touch pin 0 -> 8 o' clock    -> 6 idx
// touch pin 9 -> 10 o' clock   -> 7 idx
// touch pin 8 -> 11 o' clock   -> 8 idx

#elif defined (CREST_BADGE)
typedef enum TouchSensorCrestNames_t
{
    TOUCH_SENSOR_RIGHT_WING_FEATHER_1 = 0, // 0
    TOUCH_SENSOR_RIGHT_WING_FEATHER_2,     // 1
    TOUCH_SENSOR_RIGHT_WING_FEATHER_3,     // 2
    TOUCH_SENSOR_RIGHT_WING_FEATHER_4,     // 3
    TOUCH_SENSOR_TAIL_FEATHER,             // 4
    TOUCH_SENSOR_LEFT_WING_FEATHER_4,      // 5
    TOUCH_SENSOR_LEFT_WING_FEATHER_3,      // 6
    TOUCH_SENSOR_LEFT_WING_FEATHER_2,      // 7
    TOUCH_SENSOR_LEFT_WING_FEATHER_1,      // 8
    
    TOUCH_SENSOR_NUM_BUTTONS // 9
} TouchSensorNames;

// Crest Pin Map Notes:
// touch pin 0 -> 0 idx
// touch pin 1 -> no response
// touch pin 2 -> 1 idx
// touch pin 3 -> 2 idx
// touch pin 4 -> 3 idx
// touch pin 5 -> 4 idx
// touch pin 6 -> 5 idx
// touch pin 7 -> 6 idx
// touch pin 8 -> 7 idx
// touch pin 9 -> 8 idx

#elif defined(FMAN25_BADGE)
typedef enum TouchSensorFman25Names_t
{
    TOUCH_SENSOR_RIGHT_TOUCH_1 = 0, // 0
    TOUCH_SENSOR_RIGHT_TOUCH_2,     // 1
    TOUCH_SENSOR_RIGHT_TOUCH_3,     // 2
    TOUCH_SENSOR_RIGHT_TOUCH_4,     // 3
    TOUCH_SENSOR_CENTER_TOUCH,      // 4
    TOUCH_SENSOR_LEFT_TOUCH_4,      // 5
    TOUCH_SENSOR_LEFT_TOUCH_3,      // 6
    TOUCH_SENSOR_LEFT_TOUCH_2,      // 7
    TOUCH_SENSOR_LEFT_TOUCH_1,      // 8
    
    TOUCH_SENSOR_NUM_BUTTONS // 9
} TouchSensorNames;
#endif 

typedef struct TouchSensor_t
{
    NotificationDispatcher *pNotificationDispatcher;
    int prevDeltaValueCtr[TOUCH_SENSOR_NUM_BUTTONS];
    int prevDeltaValues[TOUCH_SENSOR_NUM_BUTTONS][DELTA_VALUE_HISTORY_SIZE];
    int prevTouchValue[TOUCH_SENSOR_NUM_BUTTONS];
    int touchSensorActive[TOUCH_SENSOR_NUM_BUTTONS];
    TickType_t touchSensorActiveTimeStamp[TOUCH_SENSOR_NUM_BUTTONS];
    esp_event_loop_handle_t touch_notify_loop_task;
    bool touchEnabled;
} TouchSensor;

esp_err_t TouchSensor_Init(TouchSensor *this, NotificationDispatcher *pNotificationDispatcher);
int TouchSensor_GetTouchSensorActive(TouchSensor *this, int pad_num);
esp_err_t TouchSensor_SetTouchEnabled(TouchSensor *this, bool enabled);

#endif // TOUCH_SENSOR_H_