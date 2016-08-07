a = 20; // Alu cross section
b = 1.2; // Alu thickness
c = 40; // length of plug
d = 0.1; // Clearance tolerance

difference() {
    rotate([45,45,0]) cube([a, a, a], center=false);
    translate([0,0,-4*a]) cube([a*8, a*8, a*8], center=true);
}
