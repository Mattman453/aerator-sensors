#include "SPI.hpp"

void setChannel(unsigned char *data, long channel) {
    data[0] = (0x01 << 7) | (0x01 << 6);
    data[1] = 0;
    data[2] = 0;
    data[0] = data[0] + (channel << 3);
}

long getSPIOutput(unsigned char *data) {
    long output = ((data[0] & 3) << 8) + data[1];
    return output;
}