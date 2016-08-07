a = 0.6; // washer thickness
b = 3.2; // washer rim width
c = 6.4; // washer ID

$fs=0.02;
translate ([0,0,a/2]) {
    difference() {
        cylinder(a, r=(b+c)/2, center=true);
        cylinder(a, r=c/2, center=true);
    }
}
