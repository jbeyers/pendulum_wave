a = 2.4; // Thickness of the holder
d = 24.8; // Diameter of the ball
b = d/2; // width of the holder
c = d/20; // reduce diameter of clip by this much to ensure tight grip.
e = d/4; // Cutout size

$fs=0.02;
difference() {
    intersection() {
        sphere(r=d/2+a);
        cube([d+2*a, d+2*a, b], center=true);
    }
    sphere(r=d/2);
    translate([0,d+2*a-e,0]) cube([d+2*a, d+2*a, b], center=true);

}

translate([0, -(d/2+a), 0])
difference() {
    cylinder(b, r=a, center=true);
    cylinder(b, r=a/2, center=true);
}

