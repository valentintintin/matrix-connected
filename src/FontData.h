#ifndef MATRIX_CONNECTED_FONTDATA_H
#define MATRIX_CONNECTED_FONTDATA_H

MD_MAX72XX::fontType_t font[] PROGMEM =
        {
                0, 	// 0   - 'Empty Cell'
                5, 62, 91, 79, 91, 62, 	// 1   - 'Sad Smiley'
                5, 62, 107, 79, 107, 62, 	// 2   - 'Happy Smiley'
                5, 28, 62, 124, 62, 28, 	// 3   - 'Heart'
                5, 24, 60, 126, 60, 24, 	// 4   - 'Diamond'
                5, 28, 87, 125, 87, 28, 	// 5   - 'Clubs'
                5, 28, 94, 127, 94, 28, 	// 6   - 'Spades'
                4, 0, 24, 60, 24, 	// 7   - 'Bullet Point'
                5, 255, 231, 195, 231, 255, 	// 8   - 'Rev Bullet Point'
                4, 0, 24, 36, 24, 	// 9   - 'Hollow Bullet Point'
                5, 255, 231, 219, 231, 255, 	// 10   - 'Rev Hollow BP'
                5, 48, 72, 58, 6, 14, 	// 11   - 'Male'
                5, 38, 41, 121, 41, 38, 	// 12   - 'Female'
                5, 64, 127, 5, 5, 7, 	// 13   - 'Music Note 1'
                5, 64, 127, 5, 37, 63, 	// 14   - 'Music Note 2'
                5, 90, 60, 231, 60, 90, 	// 15   - 'Snowflake'
                5, 127, 62, 28, 28, 8, 	// 16   - 'Right Pointer'
                5, 8, 28, 28, 62, 127, 	// 17   - 'Left Pointer'
                5, 20, 34, 127, 34, 20, 	// 18   - 'UpDown Arrows'
                5, 255, 255, 255, 255, 255, 	// 19   - 'Full Block'
                5, 240, 240, 240, 240, 240, 	// 20   - 'Half Block Bottom'
                3, 255, 255, 255, 	// 21   - 'Half Block LHS'
                5, 0, 0, 0, 255, 255, 	// 22   - 'Half Block RHS'
                5, 15, 15, 15, 15, 15, 	// 23   - 'Half Block Top'
                5, 8, 4, 126, 4, 8, 	// 24   - 'Up Arrow'
                5, 16, 32, 126, 32, 16, 	// 25   - 'Down Arrow'
                5, 8, 8, 42, 28, 8, 	// 26   - 'Right Arrow'
                5, 8, 28, 42, 8, 8, 	// 27   - 'Left Arrow'
                5, 170, 0, 85, 0, 170, 	// 28   - '30% shading'
                5, 170, 85, 170, 85, 170, 	// 29   - '50% shading'
                5, 48, 56, 62, 56, 48, 	// 30   - 'Up Pointer'
                5, 6, 14, 62, 14, 6, 	// 31   - 'Down Pointer'
                2, 0, 0, 	// 32    - 'Space'
                1, 95, 	// 33   - '!'
                3, 7, 0, 7, 	// 34   - '""'
                5, 20, 127, 20, 127, 20, 	// 35   - '#'
                5, 68, 74, 255, 74, 50, 	// 36   - '$'
                5, 99, 19, 8, 100, 99, 	// 37   - '%'
                5, 54, 73, 73, 54, 72, 	// 38   - '&'
                1, 7, 	// 39   - '''
                3, 62, 65, 65, 	// 40   - '('
                3, 65, 65, 62, 	// 41   - ')'
                5, 8, 42, 28, 42, 8, 	// 42   - '*'
                5, 8, 8, 62, 8, 8, 	// 43   - '+'
                3, 96, 224, 0, 	// 44  '
                4, 8, 8, 8, 8, 	// 45   - '-'
                2, 96, 96, 	// 46   - '.'
                5, 96, 16, 8, 4, 3, 	// 47   - '/'
                5, 62, 81, 73, 69, 62, 	// 48   - '0'
                3, 66, 127, 64, 	// 49   - '1'
                5, 66, 97, 81, 73, 70, 	// 50   - '2'
                5, 65, 65, 69, 75, 49, 	// 51   - '3'
                5, 24, 20, 18, 127, 16, 	// 52   - '4'
                5, 39, 69, 69, 69, 57, 	// 53   - '5'
                5, 60, 74, 73, 73, 48, 	// 54   - '6'
                5, 1, 1, 121, 5, 3, 	// 55   - european style '7'
                5, 54, 73, 73, 73, 54, 	// 56   - '8'
                5, 6, 73, 73, 41, 30, 	// 57   - '9'
#ifdef VALENTIN_SMALL
                2, 36, 0, 	// 58   - ':'
#else
                1, 36, 	// 58   - ':'
#endif
                1, 116, 	// 59   - ';'
                3, 8, 20, 34, 	// 60   - '<'
                4, 20, 20, 20, 20, 	// 61   - '='
                3, 34, 20, 8, 	// 62   - '>'
                5, 1, 89, 9, 9, 6, 	// 63   - '?'
                5, 62, 65, 93, 89, 78, 	// 64   - '@'
                5, 126, 9, 9, 9, 126, 	// 65   - 'A'
                5, 127, 73, 73, 73, 54, 	// 66   - 'B'
                5, 62, 65, 65, 65, 65, 	// 67   - 'C'
                5, 127, 65, 65, 65, 62, 	// 68   - 'D'
                5, 127, 73, 73, 73, 65, 	// 69   - 'E'
                5, 127, 9, 9, 9, 1, 	// 70   - 'F'
                5, 62, 65, 65, 73, 121, 	// 71   - 'G'
                5, 127, 8, 8, 8, 127, 	// 72   - 'H'
                3, 65, 127, 65, 	// 73   - 'I'
                5, 48, 65, 65, 65, 63, 	// 74   - 'J'
                5, 127, 8, 20, 34, 65, 	// 75   - 'K'
                5, 127, 64, 64, 64, 64, 	// 76   - 'L'
                5, 127, 2, 12, 2, 127, 	// 77   - 'M'
                5, 127, 4, 8, 16, 127, 	// 78   - 'N'
                5, 62, 65, 65, 65, 62, 	// 79   - 'O'
                5, 127, 9, 9, 9, 6, 	// 80   - 'P'
                5, 62, 65, 65, 97, 126, 	// 81   - 'Q'
                5, 127, 9, 25, 41, 70, 	// 82   - 'R'
                5, 70, 73, 73, 73, 49, 	// 83   - 'S'
                5, 1, 1, 127, 1, 1, 	// 84   - 'T'
                5, 63, 64, 64, 64, 63, 	// 85   - 'U'
                5, 31, 32, 64, 32, 31, 	// 86   - 'V'
                5, 63, 64, 56, 64, 63, 	// 87   - 'W'
                5, 99, 20, 8, 20, 99, 	// 88   - 'X'
                5, 3, 4, 120, 4, 3, 	// 89   - 'Y'
                5, 97, 81, 73, 69, 67, 	// 90   - 'Z'
                3, 127, 65, 65, 	// 91   - '['
                5, 3, 4, 8, 16, 96, 	// 92   - '\'
                3, 65, 65, 127, 	// 93   - ']'
                5, 4, 2, 1, 2, 4, 	// 94   - '^'
                4, 128, 128, 128, 128, 	// 95   - '_'
                3, 1, 2, 4, 	// 96   - '`'
                4, 56, 68, 68, 124, 	// 97   - 'a'
                4, 127, 68, 68, 56, 	// 98   - 'b'
                4, 56, 68, 68, 68, 	// 99   - 'c'
                4, 56, 68, 68, 127, 	// 100   - 'd'
                4, 56, 84, 84, 88, 	// 101   - 'e'
                4, 4, 126, 5, 1, 	// 102   - 'f'
                4, 24, 164, 164, 124, 	// 103   - 'g'
                4, 127, 4, 4, 120, 	// 104   - 'h'
                1, 125, 	// 105   - 'i'
                3, 132, 133, 124, 	// 106   - 'j'
                4, 127, 16, 40, 68, 	// 107   - 'k'
                1, 127, 	// 108   - 'l'
                5, 124, 4, 120, 4, 120, 	// 109   - 'm'
                4, 124, 4, 4, 120, 	// 110   - 'n'
                4, 56, 68, 68, 56, 	// 111   - 'o'
                4, 252, 36, 36, 24, 	// 112   - 'p'
                4, 24, 36, 36, 252, 	// 113   - 'q'
                4, 124, 4, 4, 8, 	// 114   - 'r'
                4, 88, 84, 84, 52, 	// 115   - 's'
                3, 4, 127, 4, 	// 116   - 't'
                4, 60, 64, 64, 124, 	// 117   - 'u'
                4, 28, 32, 64, 124, 	// 118   - 'v'
                5, 60, 64, 48, 64, 60, 	// 119   - 'w'
                4, 108, 16, 16, 108, 	// 120   - 'x'
                4, 28, 160, 160, 124, 	// 121   - 'y'
                4, 100, 84, 84, 76, 	// 122   - 'z'
                4, 8, 54, 65, 65, 	// 123   - '{'
                1, 127, 	// 124   - '|'
                4, 65, 65, 54, 8, 	// 125   - '}'
                4, 2, 1, 2, 1, 	// 126   - '~'
                5, 127, 65, 65, 65, 127, 	// 127   - 'Hollow Block'
                5, 62, 85, 85, 85, 65, 	// 128   - 'Euro symbol'
                5, 56, 68, 68, 56, 68, 	// 129   - 'Alpha'
                5, 124, 42, 42, 62, 20, 	// 130   - 'Beta'
                5, 126, 2, 2, 6, 6, 	// 131   - 'Gamma'
                5, 2, 126, 2, 126, 2, 	// 132   - 'Pi'
                5, 99, 85, 73, 65, 99, 	// 133   - 'Sigma'
                5, 56, 68, 68, 60, 4, 	// 134   - 'Theta'
                5, 64, 126, 32, 30, 32, 	// 135   - 'mu'
                5, 6, 2, 126, 2, 2, 	// 136   - 'Tau'
                8, 99, 19, 8, 100, 99, 0, 96, 96, 	// 137   - 'Percent 00'
                5, 42, 42, 42, 42, 42, 	// 138   - '3 Bar Equals'
                3, 81, 74, 68, 	// 139   - '>='
                3, 68, 74, 81, 	// 140   - '<='
                5, 0, 0, 255, 1, 3, 	// 141   - 'Top of Integral'
                3, 224, 128, 255, 	// 142   - 'Bot of Integral'
                5, 54, 18, 54, 36, 54, 	// 143   - 'Wavy ='
                3, 2, 5, 2, 	// 144   - 'Degree'
                2, 24, 24, 	// 145   - 'Math Product'
                2, 16, 16, 	// 146   - 'Short Dash'
                5, 48, 64, 255, 1, 1, 	// 147   - 'Square Root'
                4, 31, 1, 1, 30, 	// 148   - 'Superscript n'
                0, 	// 149
                0, 	// 150
                0, 	// 151
                0, 	// 152
                9, 1, 1, 127, 1, 127, 2, 12, 2, 127, 	// 153   - 'Trademark'
                0, 	// 154
                0, 	// 155
                0, 	// 156
                0, 	// 157
                0, 	// 158
                0, 	// 159
                1, 0, 	// 160   - ' Non-breaking space'
                1, 125, 	// 161   - '¡ Inverted Exclamation Mark'
                4, 24, 36, 126, 36, 	// 162   - '¢ Cent sign'
                4, 68, 126, 69, 65, 	// 163   - '£ Pound sign'
                5, 34, 28, 20, 28, 34, 	// 164   - '¤ Currency sign'
                5, 1, 42, 124, 42, 1, 	// 165   - '¥ Yen sign'
                1, 119, 	// 166   - '¦ Broken bar'
                4, 78, 85, 85, 57, 	// 167   - '§ Section sign'
                3, 2, 0, 2, 	// 168   - '¨ Diaeresis (Umlaut)'
                7, 126, 129, 189, 165, 165, 129, 126, 	// 169   - '© Copyright sign'
                3, 38, 41, 47, 	// 170   - 'ª Feminine Ordinal Indicator'
                5, 8, 20, 42, 20, 34, 	// 171   - '« Left-pointing double angle quotation mark'
                4, 8, 8, 8, 24, 	// 172   - '¬ Not sign'
                3, 8, 8, 8, 	// 173   - ' Soft hyphen'
                7, 126, 129, 189, 149, 169, 129, 126, 	// 174   - '® Registered sign'
                5, 1, 1, 1, 1, 1, 	// 175   - '¯ macron'
                3, 2, 5, 2, 	// 176   - '° Degree symbol'
                3, 36, 46, 36, 	// 177   - '± Plus-minus sign'
                3, 25, 21, 18, 	// 178   - '² Superscript two'
                3, 21, 21, 10, 	// 179   - '³ Superscript three'
                2, 2, 1, 	// 180   - '´ Acute accent'
                4, 248, 32, 64, 120, 	// 181   - 'µ Micro sign'
                5, 6, 9, 127, 1, 127, 	// 182   - 'Pilcrow sign'
                2, 24, 24, 	// 183   - '· Middle dot'
                4, 0, 128, 160, 192, 	// 184   - '¸ Cedilla'
                3, 18, 31, 16, 	// 185   - '¹ Superscript one'
                3, 38, 41, 38, 	// 186   - 'º Masculine ordinal indicator'
                5, 34, 20, 42, 20, 8, 	// 187   - '» Right-pointing double angle quotation mark'
                8, 64, 47, 16, 8, 4, 30, 17, 124, 	// 188   - '¼ Vulgar fraction one quarter'
                8, 64, 47, 16, 8, 4, 98, 85, 76, 	// 189   - '½ Vulgar fraction one half'
                9, 21, 85, 63, 16, 8, 4, 30, 17, 124, 	// 190   - '¾ Vulgar fraction three quarters'
                5, 48, 72, 72, 77, 64, 	// 191   - '¿ Inverted Question Mark'
                5, 120, 21, 22, 20, 120, 	// 192   - 'À Latin Capital Letter A with grave'
                5, 120, 20, 22, 21, 120, 	// 193   - 'Á Latin Capital letter A with acute'
                5, 122, 21, 20, 21, 122, 	// 194   - 'Â Latin Capital letter A with circumflex'
                5, 120, 22, 21, 22, 121, 	// 195   - 'Ã Latin Capital letter A with tilde'
                5, 120, 21, 20, 21, 120, 	// 196   - 'Ä Latin Capital letter A with diaeresis'
                5, 120, 20, 21, 20, 120, 	// 197   - 'Å Latin Capital letter A with ring above'
                7, 126, 9, 9, 127, 73, 73, 65, 	// 198   - 'Æ Latin Capital letter Æ'
                5, 158, 161, 97, 33, 33, 	// 199   - 'Ç Latin Capital letter C with cedilla'
                5, 124, 84, 85, 70, 68, 	// 200   - 'È Latin Capital letter E with grave'
                5, 124, 84, 86, 69, 68, 	// 201   - 'É Latin Capital letter E with acute'
                5, 126, 85, 84, 69, 70, 	// 202   - 'Ê Latin Capital letter E with circumflex'
                5, 124, 85, 84, 69, 68, 	// 203   - 'Ë Latin Capital letter E with diaeresis'
                3, 69, 126, 68, 	// 204   - 'Ì Latin Capital letter I with grave'
                3, 68, 126, 69, 	// 205   - 'Í Latin Capital letter I with acute'
                3, 70, 125, 70, 	// 206   - 'Î Latin Capital letter I with circumflex'
                3, 69, 124, 69, 	// 207   - 'Ï Latin Capital letter I with diaeresis'
                5, 8, 127, 73, 65, 62, 	// 208   - 'Ð Latin Capital letter Eth'
                5, 124, 10, 17, 34, 125, 	// 209   - 'Ñ Latin Capital letter N with tilde'
                5, 56, 68, 69, 70, 56, 	// 210   - 'Ò Latin Capital letter O with grave'
                5, 56, 68, 70, 69, 56, 	// 211   - 'Ó Latin Capital letter O with acute'
                5, 58, 69, 68, 69, 58, 	// 212   - 'Ô Latin Capital letter O with circumflex'
                5, 56, 70, 69, 70, 57, 	// 213   - 'Õ Latin Capital letter O with tilde'
                5, 56, 69, 68, 69, 56, 	// 214   - 'Ö Latin Capital letter O with diaeresis'
                5, 34, 20, 8, 20, 34, 	// 215   - '× Multiplication sign'
                5, 124, 98, 90, 70, 62, 	// 216   - 'Ø Latin Capital letter O with stroke'
                5, 60, 64, 65, 66, 60, 	// 217   - 'Ù Latin Capital letter U with grave'
                5, 60, 64, 66, 65, 60, 	// 218   - 'Ú Latin Capital letter U with acute'
                5, 60, 66, 65, 66, 60, 	// 219   - 'Û Latin Capital Letter U with circumflex'
                5, 60, 65, 64, 65, 60, 	// 220   - 'Ü Latin Capital Letter U with diaeresis'
                5, 2, 4, 122, 5, 2, 	// 221   - 'Ý Latin Capital Letter Y with acute'
                4, 63, 18, 18, 12, 	// 222   - 'Þ Latin Capital Letter Thorn'
                5, 126, 73, 73, 78, 48, 	// 223   - 'ß Latin Small Letter sharp S'
                4, 56, 69, 70, 124, 	// 224   - 'à Latin Small Letter A with grave'
                4, 56, 68, 70, 125, 	// 225   - 'á Latin Small Letter A with acute'
                4, 56, 70, 69, 126, 	// 226   - 'â Latin Small Letter A with circumflex'
                4, 58, 69, 70, 125, 	// 227   - 'ã Latin Small Letter A with tilde'
                4, 56, 69, 68, 125, 	// 228   - 'ä Latin Small Letter A with diaeresis'
                4, 48, 74, 77, 122, 	// 229   - 'å Latin Small Letter A with ring above'
                7, 32, 84, 84, 56, 84, 84, 88, 	// 230   - 'æ Latin Small Letter Æ'
                4, 156, 162, 98, 34, 	// 231   - 'ç Latin Small Letter C with cedilla'
                4, 56, 85, 86, 88, 	// 232   - 'è Latin Small Letter E with grave'
                4, 56, 84, 86, 89, 	// 233   - 'é Latin Small Letter E with acute'
                4, 56, 86, 85, 90, 	// 234   - 'ê Latin Small Letter E with circumflex'
                4, 56, 85, 84, 89, 	// 235   - 'ë Latin Small Letter E with diaeresis'
                2, 1, 122, 	// 236   - 'ì Latin Small Letter I with grave'
                2, 122, 1, 	// 237   - 'í Latin Small Letter I with acute'
                3, 2, 121, 2, 	// 238   - 'î Latin Small Letter I with circumflex'
                3, 2, 120, 2, 	// 239   - 'ï Latin Small Letter I with diaeresis'
                4, 48, 75, 75, 60, 	// 240   - 'ð Latin Small Letter Eth'
                4, 122, 9, 10, 113, 	// 241   - 'ñ Latin Small Letter N with tilde'
                4, 48, 73, 74, 48, 	// 242   - 'ò Latin Small Letter O with grave'
                4, 48, 72, 74, 49, 	// 243   - 'ó Latin Small Letter O with acute'
                4, 48, 74, 73, 50, 	// 244   - 'ô Latin Small Letter O with circumflex'
                4, 50, 73, 74, 49, 	// 245   - 'õ Latin Small Letter O with tilde'
                4, 57, 68, 68, 57, 	// 246   - 'ö Latin Small Letter O with diaeresis'
                5, 8, 8, 42, 8, 8, 	// 247   - '÷ Division sign'
                4, 56, 84, 76, 56, 	// 248   - 'ø Latin Small Letter O with stroke'
                4, 56, 65, 66, 120, 	// 249   - 'ù Latin Small Letter U with grave'
                4, 56, 64, 66, 121, 	// 250   - 'ú Latin Small Letter U with acute'
                4, 56, 66, 65, 122, 	// 251   - 'û Latin Small Letter U with circumflex'
                4, 58, 64, 64, 122, 	// 252   - 'ü Latin Small Letter U with diaeresis'
                4, 24, 160, 162, 121, 	// 253   - 'ý Latin Small Letter Y with acute'
                4, 252, 40, 40, 16, 	// 254   - 'þ Latin Small Letter Thorn'
                4, 157, 160, 160, 125,		// 255 - 'y diaresis'
        };

MD_MAX72XX::fontType_t hearts[] PROGMEM =
        {
                0, 	// 0
                5, 12, 18, 36, 18, 12, 	        // 0  Small
                5, 12, 30, 60, 30, 12, 	        // 1  SmallFilled
                7, 14, 31, 50, 100, 50, 31, 14, 	// 2  Large
                7, 14, 31, 62, 124, 62, 31, 14, 	// 3  LargeFilled
        };

MD_MAX72XX::fontType_t cars[] PROGMEM =
        {
                0, 	// 0
                12, 4, 248, 239, 121, 89, 89, 89, 93, 121, 239, 248, 4, 	// 1  car_lights_off
                12, 4, 248, 255, 121, 89, 89, 89, 93, 121, 255, 248, 4, 	// 2  car_lights_on
        };

MD_MAX72XX::fontType_t homeAssistant[] PROGMEM =
        {
                0, 	// 0
                0, 	// 0
                0, 	// 0
                0, 	// 0
                0, 	// 0
                0, 	// 0
                0, 	// 0
                0, 	// 0
                0, 	// 0
                0, 	// 0
                0, 	// 0
                0, 	// 0
                0, 	// 0
                0, 	// 0
                0, 	// 0
                0, 	// 0
                0, 	// 0
                0, 	// 0
                0, 	// 0
                0, 	// 0
                0, 	// 0
                0, 	// 0
                0, 	// 0
                0, 	// 0
                0, 	// 0
                0, 	// 0
                0, 	// 0
                0, 	// 0
                0, 	// 0
                0, 	// 0
                0, 	// 0
                0, 	// 0
                0, 	// 0
                8, 12, 18, 97, 161, 97, 18, 12, 0, 	// 33   bulb_off
                8, 12, 30, 127, 191, 127, 30, 12, 0, 	// 34   bulb_on
                8, 16, 214, 62, 214, 16, 3, 6, 5, 	// 35   movement
                8, 136, 80, 32, 80, 136, 3, 6, 5, 	// 36   no_mouvement
                8, 128, 128, 128, 255, 129, 177, 145, 255, 	// 37   door_closed
                8, 0, 0, 0, 255, 129, 177, 145, 255, 	// 38   door_open
                8, 255, 153, 153, 255, 255, 153, 153, 255, 	// 39   window_close
                8, 255, 153, 255, 129, 129, 255, 153, 255, 	// 40   window_open
                8, 60, 66, 129, 159, 145, 145, 66, 60, 	// 41   clock
                8, 192, 224, 236, 236, 236, 224, 192, 0, 	// 42   people
                8, 3, 3, 0, 60, 66, 129, 129, 129, 	// 43   temperature
                8, 128, 70, 38, 16, 8, 196, 194, 1, 	// 44   percent
                8, 145, 66, 24, 189, 189, 24, 66, 145, 	// 45   sun
                8, 248, 140, 130, 178, 130, 140, 248, 0, 	// 46   locker
                8, 4, 18, 9, 169, 9, 18, 4, 0, 	// 47   wifi
                8, 250, 85, 112, 90, 85, 112, 90, 245, 	// 48   radiator
                8, 0, 0, 252, 230, 230, 252, 0, 0, 	// 49   battery
                8, 56, 68, 128, 159, 128, 68, 56, 0, 	// 50   off
                8, 240, 142, 140, 238, 238, 140, 136, 240, 	// 51   house
                8, 248, 236, 234, 137, 152, 184, 248, 0, 	// 52   radio
                8, 48, 80, 208, 144, 159, 83, 63, 16, 	// 53   wc
                8, 60, 66, 145, 161, 145, 137, 66, 60, 	// 54   check
                8, 1, 31, 17, 241, 241, 17, 31, 1, 	// 55   cover_open
                8, 1, 31, 31, 255, 255, 31, 31, 1, 	// 56   cover_closed
                8, 0, 0, 60, 60, 60, 60, 0, 0, 	// 57   stop
                8, 0, 0, 62, 28, 8, 0, 0, 0, 	// 58   play
                8, 0, 136, 152, 191, 152, 136, 0, 0, 	// 59   download
                8, 0, 128, 76, 110, 59, 25, 0, 0, 	// 60   energy
                8, 62, 65, 81, 69, 81, 65, 62, 0, 	// 61   socket_plug
                8, 60, 126, 255, 195, 129, 129, 0, 0, 	// 62   moon
                8, 255, 177, 201, 201, 201, 179, 131, 254, 	// 63   laundry_machine
                8, 126, 209, 113, 81, 89, 117, 217, 126, 	// 64   bus
                8, 252, 132, 164, 212, 212, 167, 135, 255, 	// 65    camera
                8, 56, 36, 231, 167, 167, 239, 36, 56, 	// 66 printer
                8, 140, 255, 255, 132, 132, 44, 84, 0, 	// 67   water_pump
                8, 255, 36, 38, 44, 56, 56, 56, 248, 	// 68   bed
                8, 0, 120, 142, 137, 137, 142, 120, 0, 	// 69 shop_basket
                8, 0, 63, 161, 237, 237, 161, 63, 0, 	// 70   monitor
        };

#endif //MATRIX_CONNECTED_FONTDATA_H
