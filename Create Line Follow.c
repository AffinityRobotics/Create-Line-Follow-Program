//#include <kipr/botball.h>

void GetChargingStatus();
void GetCreateSensorReadings();
void CreateSimpleMove();
void CreateLineFollowLeftFront();

int main() 
{
    create_connect();
    msleep(1500);
//	GetChargingStatus();
//    msleep(1500);
	GetCreateSensorReadings();
    msleep(1500);
    CreateLineFollowLeftFront();
    create_stop();
	create_disconnect();
	return 0;
}

void GetChargingStatus()
{
	printf("Battery Charge = %d\n", get_create_battery_charge());
    printf("Battery Charging State = %d\n", get_create_battery_charging_state());
    printf("Battery Charge Capacity = %d\n", get_create_battery_capacity());
    printf("Battery Current = %d\n", get_create_battery_current());
    
}

void GetCreateSensorReadings()
{
	printf("digital reading for front left sensor = %d\n", get_create_lfcliff());
    printf("digital reading for front right sensor = %d\n", get_create_rfcliff());
	printf("analog reading for front left sensor = %d\n", get_create_lfcliff_amt());
	printf("analog reading for front right sensor = %d\n", get_create_rfcliff_amt());

}
//  for testing purpposes
void CreateSimpleMove()
{
    	while (digital(0)==0)
	{
    	create_drive_straight(100);
   		msleep(2000);
	}
}

void CreateLineFollowLeftFront()
{
	int black_threshold_low = 1240;
	int black_threshold_high = 1500;
    
	while (digital(0)==0)
	{
		// check front left and right sensor readings against the black threshold amount
		if(get_create_lfcliff_amt() < black_threshold_low)
		{
			printf("Curving right, Left Cliff: %d  Right cliff %d\n", get_create_lfcliff_amt(), get_create_rfcliff_amt());
			create_drive_direct(50, 0);
		}
		else if(get_create_lfcliff_amt() > black_threshold_high)
		{
			printf("Curving left, Left Cliff: %d  Right cliff %d\n", get_create_lfcliff_amt(), get_create_rfcliff_amt());
			create_drive_direct(0, 50);
		}
        else
        {
            printf("Straight, Left Cliff: %d  Right cliff %d\n", get_create_lfcliff_amt(), get_create_rfcliff_amt());
			create_drive_direct(50, 50);
        }
	}
    create_stop();
	create_disconnect();
}
