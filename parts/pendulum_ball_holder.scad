a = 1.2; // Thickness of the holder
d = 24.8; // Diameter of the ball
b = 6; // width of the holder
c = 6; // diameter of the magnet
e = d/4; // Cutout size
f = 2.4; // Hole size for the string

$fs=0.02;
difference() {
    hull() {
        intersection() {
            sphere(r=d/2+a);
            cube([d+2*a, d+2*a, b], center=true);
        }
        translate([0, -(d/2+f), 0]) cylinder(b, r=f, center=true);
    }
    sphere(r=d/2);
    translate([0, -(d/2+f), 0]) cylinder(b, r=f/2, center=true);
    translate([0,d+2*a-e,0]) cube([0.4, d+2*a, b], center=true);
    translate([0,d/2,0]) rotate ([90,45,0]) cube([c,c,d], center=true);
}
