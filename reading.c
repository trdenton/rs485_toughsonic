#include <stdio.h>
#include <errno.h>
#include <modbus.h>


modbus_t *mb;
uint16_t result;


void print_usage(void)
{
  printf("Usage:\ntake_reading <usb device>\n");
}

int main( int argc, char* argv[])
{
	//mb = modbus_new_tcp("127.0.0.1", 13202);
  
  if (argc <2)
  {
    fprintf(stderr,"ERROR - no USB device specified\n");
    print_usage();
    return -1;
  }
  else if (argc >2)
  {
    fprintf(stderr,"ERROR - too many arguments\n");
    print_usage();
    return -2;

  }

	mb = modbus_new_rtu(argv[1],9600,'N',8,1);
	if (mb==NULL)
	{
		fprintf(stderr,"could not open device %s\n",argv[1]);
		return -3;
	}
	modbus_set_slave(mb,1);
	modbus_connect(mb);
	
	/* Read 5 registers from the address 1 */
	int rc;
	int count=0;
	do
	{
		rc = modbus_read_registers(mb, 0x208, 1, &result);
		count++;
	
	} while (rc ==-1 && count < 10);

	if(rc==-1)
	{
		fprintf(stderr,"could not read device\n");
		return -4;
	}


	double reading_inches = result *  (.00384);

	printf("%f\"\n",reading_inches);
	
	
	modbus_close(mb);
	modbus_free(mb);
	return 0;
}
