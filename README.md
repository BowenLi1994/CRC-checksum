# CRC-checksum
## Purpose
1. Implement a routine to compute CRC checksum
2. Practice processing frames

## Description
In this project, you will be given a dump file containing an unknown number of frames. The framing is done using a byte-oriented framing scheme with FLAG bytes and byte stuffing. Each frame starts and ends with a FLAG byte. To perform byte stuffing, an ESC byte is defined. When an ESC or FLAG byte occurs in the user data or checksum, an ESC is inserted before the special character for the escape. Each flame contains at least one byte of user data and 2 bytes of checksum. FLAG is the ASCII character 'a' and ESC is the ASCII character 'b' in our system. The format of the frame is as follows with user_data and CRC_checksum being byte-stuffed
                                                       **FLAG--user_data--CRC_checksum--FLAG**
The dump file contains a sequence of such frames, which may or may or be valid. Your job is to identify valid frames, remove invalid frames, and re-assemble the original data in the valid frames. The CRC checksum is computed with the following generator polynomial
                                                       **x^16+x^14+x^13+x^8+x^4+x+1**
You should implement your routine to allow flexible generator polynomial. The channel supports two bit stream. So the CRC checksum is not computed in the conventional way in that the bit order are different. In particular, for each byte that has 8 bits from the most to the least significant bit: b7, b6, b5, b4, b3, b2, b1, b0, our channel sees the bits in the following order when computing the checksum: b7, b3, b6, b2, b5, b1, b4, b0. This order affects how the CRC checksum is calculated.                                                       
