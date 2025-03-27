#ifndef SPI_LIB_HPP
#define SPI_LIB_HPP

static const long PRESSURE = 1;
static const long MOISTURE= 0;
static const long FORCE = 2;
static const double LSBSIZE = 5.0/1024;

void setChannel(unsigned char *data, long channel);
long getSPIOutput(unsigned char *data);

#endif
