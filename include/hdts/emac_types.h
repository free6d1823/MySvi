#ifndef EMAC_TYPES
#define EMAC_TYPES

/* Loopback modes */
typedef enum EMAC_LB_MODE_ENUM {
  EMAC_LB_NONE = 0,                 /* No loopback */
  EMAC_LB_MAC,                      /* MAC internal loopback */
  EMAC_LB_PHY_DIG,                  /* PHY digital loopback */
  EMAC_LB_PHY_SERDES,               /* PHY SERDES loopback */
  EMAC_LB_EPHY_MAC_IF,              /* EPHY MAC interface loopback */
  EMAC_LB_EPHY_EXT_STUB,            /* EPHY external Stub loopback */
  EMAC_LB_EPHY_LINE,                /* EPHY line loopback */
} EMAC_LB_MODE;

#endif
