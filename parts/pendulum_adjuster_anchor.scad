a = 6; // Gap between bars
b = 20; // width of the bars
c = 29; // Width of whole thing
d = 24; // Width of slot
e = 3; // Outside wall thickness, and 45 degree area width
f = 200; // length of bar this must be in center of
g = 4; // Slot width for cable tie
h = 20; // Slide length
i = 4.5; // Screw hole diameter
j = 6.8; // Nut width
k = 0.5; // Slot for line
t = 0.25; // tolerance


$fs=0.02;
difference() {
    // Main shape
    hull() {
        cube([e,c,e]);
        translate([b+10,c/2,0]) cylinder(e, r=c/2);
    }
    translate([0,(c-g)/2,e-g/2]) cube([b+e,g,g]);
    translate([b+e,(c-g)/2,0]) cube([g/2,g,e]);

    translate([b+10,c/2,e]) cylinder(b,r=i/2,center=true);
    cube([b+e,e,e]);
    translate([0,c-e,0]) cube([b+e,e,e]);
}
