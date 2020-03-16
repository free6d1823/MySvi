#include <stdint.h>
#include <target/power.h>
#include <target/pmic.h>

#ifdef CONFIG_TESTOS_ATE
int power_init(void)
{
    return 0;
}
#else
void pmic_init(uint8_t bid, uint8_t masterId);
int pmbus_init(void);

int power_init(void)
{
    pmic_init(0, 0);
    pmbus_init();
    return 0;
}
#endif
