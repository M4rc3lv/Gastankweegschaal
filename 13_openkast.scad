$fn=50;
difference() {
 cube([80,100,3]);
 translate([16,2.5,-1]) cube([10,2.5,5]);
 translate([16,66,-1]) cube([10,2.5,5]);
}

difference() {
 translate([80,0,0]) cube([2.5,100,63]);
 
 // gaten knoppen
 translate([0,10,12]) translate([79,12,15]) rotate([0,90,0])cylinder(d=24.5,h=10);
 translate([0,65,12]) translate([79,12,15]) rotate([0,90,0])cylinder(d=24.5,h=10);
 
 // Display
 translate([90,55,44]) rotate([0,0,90]) cube([31,15,15]);
}



translate([78,0,3]) cube([3,100,2]);
//cylinder(d=24,h=10);

// Arduino 
difference() {
 translate([40,35,4]) rotate([0,0,270])  Ardu();
 
}

module Ardu() {
arduino_width = 54;
arduino_length = 71;
arduino_usb_width = 13;
arduino_usb_height = 15;
arduino_usb_x = 9.5;
arduino_power_width = 9.5;
arduino_power_height = 15;
arduino_power_x = 3.5;

wall_thickness = 2;
wall_height = 4;
bottom_thickness = 1;
side_shoulder = 6;

difference()
{
	// Exterior box
	cube([arduino_width+(2*wall_thickness),arduino_length+(2*wall_thickness),wall_height+bottom_thickness], center=true);

	// Interior recess
	translate([0,0,bottom_thickness/2.0])
		cube([arduino_width,arduino_length,wall_height+4], center=true);

	// Bottom hole
	cube([arduino_width-(2*side_shoulder),arduino_length-(2*side_shoulder),wall_height+bottom_thickness], center=true);

	// USB hole
	translate([	-1*((arduino_width/2.0)-(arduino_usb_width/2.0)-arduino_usb_x),
			-1*(arduino_length/2.0)-(wall_thickness/2.0),
			-1*(wall_height/2.0 - arduino_usb_height/2.0)+bottom_thickness/2.0])
	{
		cube([arduino_usb_width,wall_thickness,arduino_usb_height], center=true);
	}

	// Power hole
	translate([	((arduino_width/2.0)-(arduino_power_width/2.0)-arduino_power_x),
			-1*(arduino_length/2.0)-(wall_thickness/2.0),
			-1*(wall_height/2.0 - arduino_power_height/2.0)+bottom_thickness/2.0])
	{
		cube([arduino_power_width,wall_thickness,arduino_power_height], center=true);
	}
	
}

}