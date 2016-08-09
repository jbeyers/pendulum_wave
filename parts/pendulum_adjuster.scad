a = 6; // Gap between bars
b = 20; // width of the bars
c = 29; // Width of whole thing
d = 24; // Width of slot
e = 3; // Outside wall thickness
t = 0.25; // tolerance

rotate([180,0,0]) {
    difference() {
        cube([e+t+b+t+a+t+b+t+e, c, b+t+e]);
        translate([e, 0, 0]) cube([b+t+t, c, b+t]);
        translate([e+t+b+t+a, 0, 0]) cube([b+t+t, c, b+t]);
        translate([b, 0, 0]) cube([b+t+t, c, b+t-a]);
        translate([e+t+b+t, (c-d)/2, 0]) cube([a, d, b+t]);
        translate([e+t+b+t, (c-d)/2, 0]) cube([a/2, d, b+t+e]);
    }
}
