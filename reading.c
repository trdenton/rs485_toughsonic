#include <stdio.h>
#include <errno.h>
#include <modbus.h>


modbus_t *mb;
uint16_t result;

int main()
{
	//mb = modbus_new_tcp("127.0.0.1", 13202);
	mb = modbus_new_rtu("/dev/ttyUSB1",9600,'N',8,1);
	if (mb==NULL)
	{
		fprintf(stderr,"could not open device\n");
		return -1;
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
		return -1;
	}


	double reading_inches = result *  (.00384);

	printf("%f\"\n",reading_inches);
	
	
	modbus_close(mb);
	modbus_free(mb);
	return 0;
}
