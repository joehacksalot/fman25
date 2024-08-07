#ifndef USER_SETTINGS_H_
#define USER_SETTINGS_H_

#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"

#include "BatterySensor.h"
#include "GameTypes.h"

#define MAX_SSID_LENGTH (32)
#define MAX_PASSWORD_LENGTH (64)

typedef struct WifiSettings_t
{
    uint8_t ssid[MAX_SSID_LENGTH];
    uint8_t password[MAX_PASSWORD_LENGTH];
} WifiSettings;

typedef struct UserSettingsFile_t
{
    uint32_t selectedIndex;
    uint8_t soundEnabled;
    uint8_t vibrationEnabled;
    uint8_t pairId[PAIR_ID_SIZE];
    WifiSettings wifiSettings;
    uint8_t reserved;
} UserSettingsFile;

typedef struct UserSettings_t
{
    UserSettingsFile settings;
    bool updateNeeded;
    uint8_t badgeId[BADGE_ID_SIZE];
    uint8_t badgeIdB64[BADGE_ID_B64_SIZE];
    uint8_t key[KEY_SIZE];
    uint8_t keyB64[KEY_B64_SIZE];
    SemaphoreHandle_t mutex;
    BatterySensor *pBatterySensor;
} UserSettings;

esp_err_t UserSettings_Init(UserSettings *this, BatterySensor * pBatterySensor);

esp_err_t UserSettings_UpdateFromJson(UserSettings *this, uint8_t * settingsJson);

esp_err_t UserSettings_SetPairId(UserSettings *this, uint8_t * pairId);

esp_err_t UserSettings_SetSelectedIndex(UserSettings *this, uint32_t selectedIndex);

#endif // USER_SETTINGS_H_