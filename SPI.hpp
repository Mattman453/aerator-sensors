#ifndef SPI_LIB_HPP
#define SPI_LIB_HPP

static const long pressure = 1;
static const long moisture= 0;
static const long force = 2;
static const double LSBSIZE = 5.0/1024;

void setChannel(unsigned char *data, long channel);
long getSPIOutput(unsigned char *data);

#endif
