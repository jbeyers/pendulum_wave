a = 20; // Alu cross section
b = 1.2; // Alu thickness
c = 30; // length of plug
d = 0.2; // Clearance tolerance
e = a-b-b-d-d; // plug cross section
f = 2; // Round edge radius

$fs=0.02;
module rts(h, r) {
    cylinder(h-r, r=r);
    translate([0,0,h-r]) sphere(r=r);
}

module prong() {
    translate([b+d, b+d,a]) hull() {
        translate([f,f,0]) rts(c, f);
        translate([e-f,f,0]) rts(c, f);
        translate([f,e-f,0]) rts(c, f);
        translate([e-f,e-f,0]) rts(c, f);
    }
}

difference() {
    rotate(a=atan(sqrt(2)), v=[1,1,0]) union() {
        cube([a, a, a], center=false);
        prong();
        rotate([-90,0,0]) translate([0,-a,0]) prong();
        rotate([0,-90,0]) translate([0,0,-a]) prong();
    };
    translate([0,0,-4*a]) cube([a*8, a*8, a*8], center=true);
}
