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



difference() {
    // Main shape
    union() {
        cube([3*e,c,b]);
        translate([2*e,0,0]) cube([b,c,2*e]);
        // Slot to fit adjustment strip
    }
    // slot for slider
    translate([0,2*e,0]) cube([e-t,c-4*e,b]);
    translate([e-t,e-t,0]) cube([t+e+t,c-2*e,b]);

    translate([3*e,(c-j)/2-t,e]) cube([b,j+2*t,2*e]);
    translate([2*e+10,c/2,e]) cylinder(b,r=i/2,center=true);
    translate([2*e+10+5,(c-k)/2,0]) cube([b,k,b]);
}
