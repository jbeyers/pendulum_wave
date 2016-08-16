a = 6; // Gap between bars
b = 20; // width of the bars
c = 29; // Width of whole thing
d = 24; // Width of slot
e = 3; // Outside wall thickness, and 45 degree area width
f = 200; // length of bar this must be in center of
g = 4; // Slot width for cable tie
t = 0.25; // tolerance

bar = [b+t+t, c, b+t];
l = e+t+b+t+f/2-(a/2+t+b+t+e);

difference() {
    // Main shape
    union() {
        cube([e,c,b/2+e]);
        translate([0,e,0]) cube([l, c-2*e, e]);
        // Slot to fit adjustment strip
        translate([l,c/2,0]) {
            translate([0,-1.5*e,0]) cube([e+t,3*e,e]);
            translate([e+t,-2.5*e,0]) cube([e,5*e,e]);
        }
    }
    // slot for cable tie
    translate([0,(c-g)/2,0]) cube([g/2, g, b+t+e]);
    // Slot for screw adjuster
    translate([e+t+b,c/2,0]) {
        translate([0,-c/4-t,0]) cube([t+e+t,t+c/2+t,e]);
        translate([t+e+t,-g/2,0]) cube([g,g,e]);
    }






}
