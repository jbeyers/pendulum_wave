a = 25.8; // Overall length
b = 0.4; // flange thickness
c = 10.0; // flange diameter
d = 6.8; // ID of bobbin
e = 0.42; // Wall thickness

$fs=0.02;
translate ([0,0,a/2]) {
    // Center pillar
    difference() {
        union() {
            difference() {
                cylinder(a, r=c/2, center=true);
                cylinder(a-b*2, r=c/2, center=true);
                }
            cylinder(a, r=d/2 + e, center=true);
        }
        cylinder(a, r=d/2, center=true);
    }
}
