#include <hwlib.hpp> 
#include <math.h>
#include <array>


// Get radials form degrees 
constexpr double radians_from_degrees( int degrees ){
   return 2 * 3.14 * ( degrees / 360.0 );
}

// Get the sines of the point 
constexpr int scaled_sine_from_degrees( int degrees){
   return  64 + (32 * sin( radians_from_degrees( degrees )));
}

//Get the cosinus of the point 
constexpr int scaled_cos_from_degrees(int degrees){
	return  31.5 + (32 * cos( radians_from_degrees(degrees)));
}

/*
This function addes points to the array
makes two arrays one array filled with sinus points
and one array filled with cosinus points
*/
template<int N, typename t>
class set_point {
private:
	std::array<t,N> values = {};
public:
	template<typename f>
	constexpr set_point(f function){
		for(int i = 0; i < N; i++){
			values[i] = function(10 * i);
		}
	}
	constexpr t get_point(int n) const{
		return values[n / 10];
	}
	
};

/*
This function reads out the buttons
after reading it checks if the hrs parameter is not bigger or equals 12 
if this is true it is set to 0 else it is incremented
after it checks if the mins parameter is not bigger or equals 60
if this is true it is set to 0 else it is incremented
*/
void readButtons(hwlib::target::pin_in & btH, hwlib::target::pin_in & btM,int & hrs, int & mins){
	if(btH.read()){ hrs >= 12 ? hrs = 0 : hrs++;}
	else if (btM.read()){mins >= 60 ? mins = 0 : mins++;}
}

int main( void ){	
   // wait for the PC console to start
   hwlib::wait_ms( 2000 ); 
	auto hourAdd 	= hwlib::target::pin_in(hwlib::target::pins::d50);
	auto minAdd 	= hwlib::target::pin_in(hwlib::target::pins::d51);
	auto scl 		= hwlib::target::pin_oc( hwlib::target::pins::d52 );
    auto sda 		= hwlib::target::pin_oc( hwlib::target::pins::d53 );
    auto i2c_bus 	= hwlib::i2c_bus_bit_banged_scl_sda( scl, sda );
    uint8_t OledAddres = 0x3c;
    // uint8_t OledAddres = 0x78;
    auto oled    = hwlib::glcd_oled(i2c_bus, OledAddres);
	int hour = 0;
	int minute = 0;

	constexpr auto sinPoints = set_point<360, int>(scaled_sine_from_degrees);
	constexpr auto cosPoints = set_point<360, int>(scaled_cos_from_degrees);
	for(;;){
			readButtons(hourAdd,minAdd,hour,minute);
			oled.clear();
			auto time = hwlib::now_us();
			int time_sec = time / 1000000;
			for( int angle_degrees = 0; angle_degrees < 360; angle_degrees += 30 ){
				oled.write(hwlib::xy(sinPoints.get_point(angle_degrees),cosPoints.get_point(angle_degrees)),hwlib::white);
			}
			int secHand = time_sec % 60;
			int time_min =(time_sec / 60) %60;
			int time_hr = (time_sec / 3600) %12;
			
			hwlib::cout<<time_hr<<':'<<time_min<<':'<<time_sec<<hwlib::endl;
			hwlib::line(hwlib::xy(64,31.5), hwlib::xy(sinPoints.get_point(360-(secHand * 6)),cosPoints.get_point(360-(secHand *6)))).draw(oled);
			hwlib::line(hwlib::xy(64,31.5), hwlib::xy(sinPoints.get_point(360-((minute+time_min) * 6)),cosPoints.get_point(360-((minute+time_min) * 6)))).draw(oled);
			hwlib::line(hwlib::xy(63,31.5), hwlib::xy(sinPoints.get_point(360-((hour+time_hr) * 30)),cosPoints.get_point(360-(((hour+time_hr) * 30))))).draw(oled);
			oled.flush();
		}
	}