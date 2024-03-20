#include "crc_test.h"

int errors = 0;
int passed = 0;
int percents;

int main(void) {
    crc_test(CRC3_GSM, 8);
    crc_test(CRC3_ROHC, 8);
    crc_test(CRC4_G_704, 8);
    crc_test(CRC4_INTERLAKEN, 8);
    crc_test(CRC5_EPC_C1G2, 8);
    crc_test(CRC5_G_704, 8);
    crc_test(CRC5_USB, 8);
    crc_test(CRC6_CDMA2000_A, 8);
    crc_test(CRC6_CDMA2000_B, 8);
    crc_test(CRC6_DARC, 8);
    crc_test(CRC6_G_704, 8);
    crc_test(CRC6_GSM, 8);
    crc_test(CRC7_MMC, 8);
    crc_test(CRC7_ROHC, 8);
    crc_test(CRC7_UMTS, 8);
    crc_test(CRC8_AUTOSAR, 8);
    crc_test(CRC8_BLUETOOTH, 8);
    crc_test(CRC8_CDMA2000, 8);
    crc_test(CRC8_DARC, 8);
    crc_test(CRC8_DVB_S2, 8);
    crc_test(CRC8_GSM_A, 8);
    crc_test(CRC8_GSM_B, 8);
    crc_test(CRC8_HITAG, 8);
    crc_test(CRC8_I_432_1, 8);
    crc_test(CRC8_I_CODE, 8);
    crc_test(CRC8_LTE, 8);
    crc_test(CRC8_MAXIM_DOW, 8);
    crc_test(CRC8_MIFARE_MAD, 8);
    crc_test(CRC8_NRSC_5, 8);
    crc_test(CRC8_OPENSAFETY, 8);
    crc_test(CRC8_ROHC, 8);
    crc_test(CRC8_SAE_J1850, 8);
    crc_test(CRC8_SMBUS, 8);
    crc_test(CRC8_TECH_3250, 8);
    crc_test(CRC8_WCDMA, 8);
    crc_test(CRC10_ATM, 16);
    crc_test(CRC10_CDMA2000, 16);
    crc_test(CRC10_GSM, 16);
    crc_test(CRC11_FLEXRAY, 16);
    crc_test(CRC11_UMTS, 16);
    crc_test(CRC12_CDMA2000, 16);
    crc_test(CRC12_DECT, 16);
    crc_test(CRC12_GSM, 16);
    crc_test(CRC12_UMTS, 16);
    crc_test(CRC13_BBC, 16);
    crc_test(CRC14_DARC, 16);
    crc_test(CRC14_GSM, 16);
    crc_test(CRC15_CAN, 16);
    crc_test(CRC15_MPT1327, 16);
    crc_test(CRC16_ARC, 16);
    crc_test(CRC16_CDMA2000, 16);
    crc_test(CRC16_CMS, 16);
    crc_test(CRC16_DDS_110, 16);
    crc_test(CRC16_DECT_R, 16);
    crc_test(CRC16_DECT_X, 16);
    crc_test(CRC16_DNP, 16);
    crc_test(CRC16_EN_13757, 16);
    crc_test(CRC16_GENIBUS, 16);
    crc_test(CRC16_GSM, 16);
    crc_test(CRC16_IBM_3740, 16);
    crc_test(CRC16_IBM_SDLC, 16);
    crc_test(CRC16_ISO_IEC_14443_3_A, 16);
    crc_test(CRC16_KERMIT, 16);
    crc_test(CRC16_LJ1200, 16);
    crc_test(CRC16_M17, 16);
    crc_test(CRC16_MAXIM_DOW, 16);
    crc_test(CRC16_MCRF4XX, 16);
    crc_test(CRC16_MODBUS, 16);
    crc_test(CRC16_NRSC_5, 16);
    crc_test(CRC16_OPENSAFETY_A, 16);
    crc_test(CRC16_OPENSAFETY_B, 16);
    crc_test(CRC16_PROFIBUS, 16);
    crc_test(CRC16_RIELLO, 16);
    crc_test(CRC16_SPI_FUJITSU, 16);
    crc_test(CRC16_T10_DIF, 16);
    crc_test(CRC16_TELEDISK, 16);
    crc_test(CRC16_TMS37157, 16);
    crc_test(CRC16_UMTS, 16);
    crc_test(CRC16_USB, 16);
    crc_test(CRC16_XMODEM, 16);
    crc_test(CRC17_CAN_FD, 32);
    crc_test(CRC21_CAN_FD, 32);
    crc_test(CRC24_BLE, 32);
    crc_test(CRC24_FLEXRAY_A, 32);
    crc_test(CRC24_FLEXRAY_B, 32);
    crc_test(CRC24_INTERLAKEN, 32);
    crc_test(CRC24_LTE_A, 32);
    crc_test(CRC24_LTE_B, 32);
    crc_test(CRC24_OPENPGP, 32);
    crc_test(CRC24_OS_9, 32);
    crc_test(CRC30_CDMA, 32);
    crc_test(CRC31_PHILIPS, 32);
    crc_test(CRC32_AIXM, 32);
    crc_test(CRC32_AUTOSAR, 32);
    crc_test(CRC32_BASE91_D, 32);
    crc_test(CRC32_BZIP2, 32);
    crc_test(CRC32_CD_ROM_EDC, 32);
    crc_test(CRC32_CKSUM, 32);
    crc_test(CRC32_ISCSI, 32);
    crc_test(CRC32_ISO_HDLC, 32);
    crc_test(CRC32_JAMCRC, 32);
    crc_test(CRC32_MEF, 32);
    crc_test(CRC32_MPEG_2, 32);
    crc_test(CRC32_XFER, 32);
    crc_test(CRC40_GSM, 64);
    crc_test(CRC64_ECMA_182, 64);
    crc_test(CRC64_GO_ISO, 64);
    crc_test(CRC64_MS, 64);
    crc_test(CRC64_REDIS, 64);
    crc_test(CRC64_WE, 64);
    crc_test(CRC64_XZ, 64);

#ifdef __SIZEOF_INT128__
    crc_test(CRC82_DARC, 128);
#endif

    percents = 100 * passed / (passed + errors);
    printf("[%d%%] tests passed, %d errors\n", percents, errors);

    return 0;
}
