#include "Utils.h"

void millisToString(uint64_t milliseconds, String *timeString) {
    uint64_t seconds = milliseconds / 1000;
    milliseconds %= 1000;

    auto minutes = (uint64_t) (seconds / 60);
    seconds %= 60;

    auto hours = (uint64_t) (minutes / 60);
    minutes %= 60;

    auto days = (uint64_t) (hours / 24);
    hours %= 24;

    timeString->remove(0, timeString->length());

    if (days > 0) {
        *timeString += (uint8_t) days;
        *timeString += "J ";
    }
    if (days > 0 || hours > 0) {
        *timeString += (uint8_t) hours;
        *timeString += ":";
    }
    if (minutes < 10) {
        *timeString += "0";
    }
    *timeString += (uint8_t) minutes;
    *timeString += ":";
    if (seconds < 10) {
        *timeString += "0";
    }
    *timeString += (uint8_t) seconds;
    if (days == 0) {
        *timeString += ",";
        *timeString += (uint16_t) milliseconds;
    }
}

void utf8ToCp437(String &s) {
    unsigned int iRt = 0;

    s.replace("–", "-");
    s.replace("’", "'");
    s.replace("`", "'");
    s.replace("œ", "oe");

    for (unsigned int i = 0; i < s.length(); i++) {
        if ((unsigned char) s[i] >= 128) {
            switch ((unsigned char) s[i]) {
                case 0x11:
                    switch ((unsigned char) s[i + 1]) {
                        case 0x81:
                            switch ((unsigned char) s[i + 2]) {
                                case 0xBF:
                                    s[iRt] = 0xFC;
                                    i += 2;
                                    break;

                                default:
                                    s[iRt] = ' ';
                                    i += 2;
                                    break;
                            };
                            break;

                        case 0x82:
                            switch ((unsigned char) s[i + 2]) {
                                case 0xA7:
                                    s[iRt] = 0x9E;
                                    i += 2;
                                    break;

                                default:
                                    s[iRt] = ' ';
                                    i += 2;
                                    break;
                            };
                            break;

                        case 0x88:
                            switch ((unsigned char) s[i + 2]) {
                                case 0x99:
                                    s[iRt] = 0xF9;
                                    i += 2;
                                    break;

                                case 0x9E:
                                    s[iRt] = 0xEC;
                                    i += 2;
                                    break;

                                case 0xA9:
                                    s[iRt] = 0xEF;
                                    i += 2;
                                    break;

                                case 0x9A:
                                    s[iRt] = 0xFB;
                                    i += 2;
                                    break;

                                default:
                                    s[iRt] = ' ';
                                    i += 2;
                                    break;
                            };
                            break;

                        case 0x89:
                            switch ((unsigned char) s[i + 2]) {
                                case 0x88:
                                    s[iRt] = 0xF7;
                                    i += 2;
                                    break;

                                case 0xA1:
                                    s[iRt] = 0xF0;
                                    i += 2;
                                    break;

                                case 0xA5:
                                    s[iRt] = 0xF2;
                                    i += 2;
                                    break;

                                case 0xA4:
                                    s[iRt] = 0xF3;
                                    i += 2;
                                    break;

                                default:
                                    s[iRt] = ' ';
                                    i += 2;
                                    break;
                            };
                            break;

                        case 0x94:
                            switch ((unsigned char) s[i + 2]) {
                                case 0x80:
                                    s[iRt] = 0xC4;
                                    i += 2;
                                    break;

                                case 0x82:
                                    s[iRt] = 0xB3;
                                    i += 2;
                                    break;

                                case 0x90:
                                    s[iRt] = 0xBF;
                                    i += 2;
                                    break;

                                case 0x94:
                                    s[iRt] = 0xC0;
                                    i += 2;
                                    break;

                                case 0x98:
                                    s[iRt] = 0xD9;
                                    i += 2;
                                    break;

                                case 0xA4:
                                    s[iRt] = 0xB4;
                                    i += 2;
                                    break;

                                case 0xB4:
                                    s[iRt] = 0xC1;
                                    i += 2;
                                    break;

                                case 0xAC:
                                    s[iRt] = 0xC2;
                                    i += 2;
                                    break;

                                case 0x9C:
                                    s[iRt] = 0xC3;
                                    i += 2;
                                    break;

                                case 0xBC:
                                    s[iRt] = 0xC5;
                                    i += 2;
                                    break;

                                case 0x8C:
                                    s[iRt] = 0xDA;
                                    i += 2;
                                    break;

                                default:
                                    s[iRt] = ' ';
                                    i += 2;
                                    break;
                            };
                            break;

                        case 0x95:
                            switch ((unsigned char) s[i + 2]) {
                                case 0x90:
                                    s[iRt] = 0xCD;
                                    i += 2;
                                    break;

                                case 0x91:
                                    s[iRt] = 0xBA;
                                    i += 2;
                                    break;

                                case 0x92:
                                    s[iRt] = 0xD5;
                                    i += 2;
                                    break;

                                case 0x93:
                                    s[iRt] = 0xD6;
                                    i += 2;
                                    break;

                                case 0x94:
                                    s[iRt] = 0xC9;
                                    i += 2;
                                    break;

                                case 0x95:
                                    s[iRt] = 0xB8;
                                    i += 2;
                                    break;

                                case 0x96:
                                    s[iRt] = 0xB7;
                                    i += 2;
                                    break;

                                case 0x97:
                                    s[iRt] = 0xBB;
                                    i += 2;
                                    break;

                                case 0x98:
                                    s[iRt] = 0xD4;
                                    i += 2;
                                    break;

                                case 0x99:
                                    s[iRt] = 0xD3;
                                    i += 2;
                                    break;

                                case 0xA1:
                                    s[iRt] = 0xB5;
                                    i += 2;
                                    break;

                                case 0xA2:
                                    s[iRt] = 0xB6;
                                    i += 2;
                                    break;

                                case 0xA3:
                                    s[iRt] = 0xB9;
                                    i += 2;
                                    break;

                                case 0x9D:
                                    s[iRt] = 0xBC;
                                    i += 2;
                                    break;

                                case 0x9C:
                                    s[iRt] = 0xBD;
                                    i += 2;
                                    break;

                                case 0x9B:
                                    s[iRt] = 0xBE;
                                    i += 2;
                                    break;

                                case 0x9E:
                                    s[iRt] = 0xC6;
                                    i += 2;
                                    break;

                                case 0x9F:
                                    s[iRt] = 0xC7;
                                    i += 2;
                                    break;

                                case 0x9A:
                                    s[iRt] = 0xC8;
                                    i += 2;
                                    break;

                                case 0xA9:
                                    s[iRt] = 0xCA;
                                    i += 2;
                                    break;

                                case 0xA6:
                                    s[iRt] = 0xCB;
                                    i += 2;
                                    break;

                                case 0xA0:
                                    s[iRt] = 0xCC;
                                    i += 2;
                                    break;

                                case 0xAC:
                                    s[iRt] = 0xCE;
                                    i += 2;
                                    break;

                                case 0xA7:
                                    s[iRt] = 0xCF;
                                    i += 2;
                                    break;

                                case 0xA8:
                                    s[iRt] = 0xD0;
                                    i += 2;
                                    break;

                                case 0xA4:
                                    s[iRt] = 0xD1;
                                    i += 2;
                                    break;

                                case 0xA5:
                                    s[iRt] = 0xD2;
                                    i += 2;
                                    break;

                                case 0xAB:
                                    s[iRt] = 0xD7;
                                    i += 2;
                                    break;

                                case 0xAA:
                                    s[iRt] = 0xD8;
                                    i += 2;
                                    break;

                                default:
                                    s[iRt] = ' ';
                                    i += 2;
                                    break;
                            };
                            break;

                        case 0x96:
                            switch ((unsigned char) s[i + 2]) {
                                case 0x80:
                                    s[iRt] = 0xDF;
                                    i += 2;
                                    break;

                                case 0x84:
                                    s[iRt] = 0xDC;
                                    i += 2;
                                    break;

                                case 0x88:
                                    s[iRt] = 0xDB;
                                    i += 2;
                                    break;

                                case 0x90:
                                    s[iRt] = 0xDE;
                                    i += 2;
                                    break;

                                case 0x91:
                                    s[iRt] = 0xB0;
                                    i += 2;
                                    break;

                                case 0x92:
                                    s[iRt] = 0xB1;
                                    i += 2;
                                    break;

                                case 0x93:
                                    s[iRt] = 0xB2;
                                    i += 2;
                                    break;

                                case 0x8C:
                                    s[iRt] = 0xDD;
                                    i += 2;
                                    break;

                                case 0xA0:
                                    s[iRt] = 0xFE;
                                    i += 2;
                                    break;

                                default:
                                    s[iRt] = ' ';
                                    i += 2;
                                    break;
                            };
                            break;

                        case 0x8C:
                            switch ((unsigned char) s[i + 2]) {
                                case 0x90:
                                    s[iRt] = 0xA9;
                                    i += 2;
                                    break;

                                case 0xA0:
                                    s[iRt] = 0xF4;
                                    i += 2;
                                    break;

                                case 0xA1:
                                    s[iRt] = 0xF5;
                                    i += 2;
                                    break;

                                default:
                                    s[iRt] = ' ';
                                    i += 2;
                                    break;
                            };
                            break;

                        default:
                            s[iRt] = ' ';
                            i++;
                            break;
                    }
                    break;

                case 0xC6:
                    switch ((unsigned char) s[i + 1]) {
                        case 0x92:
                            s[iRt] = 0x9F;
                            i++;
                            break;

                        default:
                            s[iRt] = ' ';
                            i++;
                            break;
                    }
                    break;

                case 0xCE:
                    switch ((unsigned char) s[i + 1]) {
                        case 0x93:
                            s[iRt] = 0xE2;
                            i++;
                            break;

                        case 0x98:
                            s[iRt] = 0xE9;
                            i++;
                            break;

                        case 0xB1:
                            s[iRt] = 0xE0;
                            i++;
                            break;

                        case 0xA3:
                            s[iRt] = 0xE4;
                            i++;
                            break;

                        case 0xBC:
                            s[iRt] = 0xE6;
                            i++;
                            break;

                        case 0xA6:
                            s[iRt] = 0xE8;
                            i++;
                            break;

                        case 0xA9:
                            s[iRt] = 0xEA;
                            i++;
                            break;

                        case 0xB4:
                            s[iRt] = 0xEB;
                            i++;
                            break;

                        case 0xB5:
                            s[iRt] = 0xEE;
                            i++;
                            break;

                        default:
                            s[iRt] = ' ';
                            i++;
                            break;
                    }
                    break;

                case 0xCF:
                    switch ((unsigned char) s[i + 1]) {
                        case 0x80:
                            s[iRt] = 0xE3;
                            i++;
                            break;

                        case 0x83:
                            s[iRt] = 0xE5;
                            i++;
                            break;

                        case 0x84:
                            s[iRt] = 0xE7;
                            i++;
                            break;

                        case 0x86:
                            s[iRt] = 0xED;
                            i++;
                            break;

                        default:
                            s[iRt] = ' ';
                            i++;
                            break;
                    }
                    break;

                case 0xC2:
                    switch ((unsigned char) s[i + 1]) {
                        case 0xA1:
                            s[iRt] = 0xAD;
                            i++;
                            break;

                        case 0xBF:
                            s[iRt] = 0xA8;
                            i++;
                            break;

                        case 0xB7:
                            s[iRt] = 0xFA;
                            i++;
                            break;

                        case 0xAB:
                            s[iRt] = 0xAE;
                            i++;
                            break;

                        case 0xBB:
                            s[iRt] = 0xAF;
                            i++;
                            break;

                        case 0xA2:
                            s[iRt] = 0x9B;
                            i++;
                            break;

                        case 0xA3:
                            s[iRt] = 0x9C;
                            i++;
                            break;

                        case 0xA5:
                            s[iRt] = 0x9D;
                            i++;
                            break;

                        case 0xB1:
                            s[iRt] = 0xF1;
                            i++;
                            break;

                        case 0xAC:
                            s[iRt] = 0xAA;
                            i++;
                            break;

                        case 0xB0:
                            s[iRt] = 0xF8;
                            i++;
                            break;

                        case 0xA0:
                            s[iRt] = 0xFF;
                            i++;
                            break;

                        case 0xBC:
                            s[iRt] = 0xAC;
                            i++;
                            break;

                        case 0xBD:
                            s[iRt] = 0xAB;
                            i++;
                            break;

                        case 0xB2:
                            s[iRt] = 0xFD;
                            i++;
                            break;

                        case 0xAA:
                            s[iRt] = 0xA6;
                            i++;
                            break;

                        case 0xBA:
                            s[iRt] = 0xA7;
                            i++;
                            break;

                        default:
                            s[iRt] = ' ';
                            i++;
                            break;
                    }
                    break;

                case 0xC3:
                    switch ((unsigned char) s[i + 1]) {
                        case 0x80:
                            s[iRt] = 0x85;
                            i++;
                            break;

                        case 0x82:
                            s[iRt] = 0x83;
                            i++;
                            break;

                        case 0x84:
                            s[iRt] = 0x8E;
                            i++;
                            break;

                        case 0x85:
                            s[iRt] = 0x8F;
                            i++;
                            break;

                        case 0x86:
                            s[iRt] = 0x92;
                            i++;
                            break;

                        case 0x87:
                            s[iRt] = 0x80;
                            i++;
                            break;

                        case 0x88:
                            s[iRt] = 0x8A;
                            i++;
                            break;

                        case 0x89:
                            s[iRt] = 0x90;
                            i++;
                            break;

                        case 0x8A:
                            s[iRt] = 0x88;
                            i++;
                            break;

                        case 0x8B:
                            s[iRt] = 0x89;
                            i++;
                            break;

                        case 0x8E:
                            s[iRt] = 0x8C;
                            i++;
                            break;

                        case 0x8F:
                            s[iRt] = 0x8B;
                            i++;
                            break;

                        case 0x91:
                            s[iRt] = 0xA5;
                            i++;
                            break;

                        case 0x94:
                            s[iRt] = 0x95;
                            i++;
                            break;

                        case 0x96:
                            s[iRt] = 0x99;
                            i++;
                            break;

                        case 0xB7:
                            s[iRt] = 0xF6;
                            i++;
                            break;

                        case 0xA1:
                            s[iRt] = 0xA0;
                            i++;
                            break;

                        case 0xA0:
                            s[iRt] = 0x85;
                            i++;
                            break;

                        case 0xA2:
                            s[iRt] = 0x83;
                            i++;
                            break;

                        case 0xA7:
                            s[iRt] = 0x87;
                            i++;
                            break;

                        case 0xA9:
                            s[iRt] = 0x82;
                            i++;
                            break;

                        case 0xA8:
                            s[iRt] = 0x8A;
                            i++;
                            break;

                        case 0xAA:
                            s[iRt] = 0x88;
                            i++;
                            break;

                        case 0xAB:
                            s[iRt] = 0x89;
                            i++;
                            break;

                        case 0xAD:
                            s[iRt] = 0xA1;
                            i++;
                            break;

                        case 0xAC:
                            s[iRt] = 0x8D;
                            i++;
                            break;

                        case 0xAE:
                            s[iRt] = 0x8C;
                            i++;
                            break;

                        case 0xAF:
                            s[iRt] = 0x8B;
                            i++;
                            break;

                        case 0xB1:
                            s[iRt] = 0xA4;
                            i++;
                            break;

                        case 0xB3:
                            s[iRt] = 0xA2;
                            i++;
                            break;

                        case 0xB2:
                            s[iRt] = 0x95;
                            i++;
                            break;

                        case 0xB4:
                            s[iRt] = 0x93;
                            i++;
                            break;

                        case 0x9F:
                            s[iRt] = 0xE1;
                            i++;
                            break;

                        case 0xBA:
                            s[iRt] = 0xA3;
                            i++;
                            break;

                        case 0xB9:
                            s[iRt] = 0x97;
                            i++;
                            break;

                        case 0xBB:
                            s[iRt] = 0x96;
                            i++;
                            break;

                        case 0xBF:
                            s[iRt] = 0x98;
                            i++;
                            break;

                        case 0xBC:
                            s[iRt] = 0x81;
                            i++;
                            break;

                        case 0x9C:
                            s[iRt] = 0x9A;
                            i++;
                            break;

                        case 0xA6:
                            s[iRt] = 0x91;
                            i++;
                            break;

                        case 0xA4:
                            s[iRt] = 0x84;
                            i++;
                            break;

                        case 0xB6:
                            s[iRt] = 0x94;
                            i++;
                            break;

                        case 0xA5:
                            s[iRt] = 0x86;
                            i++;
                            break;

                        default:
                            s[iRt] = ' ';
                            i++;
                            break;
                    }
                    break;
            }
        } else {
            s[iRt] = s[i];
        }
        iRt++;
    }

    if (iRt < s.length()) {
        s.remove(iRt, s.length() - iRt);
    }
}