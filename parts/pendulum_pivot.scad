a = 6; // Gap between bars
b = 20; // width of the bars
c = 29; // Width of whole thing
d = 24; // Width of slot
e = 3; // Outside wall thickness, and 45 degree area width
f = 200; // length of bar this must be in center of
g = 4; // Slot width for cable tie
t = 0.25; // tolerance

bar = [b+t+t, c, b+t];

rotate([180,0,0]) {
    difference() {
        // Main block
        cube([e+t+b+t+a+t+b+t+e, c, b+t+e]);
        // Trim the whole block to half height
        translate([0,0,-b/2]) cube([e+t+b+t+a+t+b+t+e, c, b+t+e]);
        // Slots for bars to fit in
        translate([e, 0, 0]) cube(bar);
        translate([e+t+b+t+a, 0, 0]) cube(bar);
        translate([e+t+b+t, (c-d)/2, 0]) cube([a, d, b+t]);
        // slot for line to go through
        translate([e+t+b+t, (c-d)/2, 0]) cube([a/2, d, b+t+e]);
        translate([e+t+b+t+a/2, (c-d)/2, b+t]) rotate([0,-45,0]) cube([b, e, b+t+e]);
        translate([e+t+b+t+a/2, (c-d)/2+d-e, b+t]) rotate([0,-45,0]) cube([b, e, b+t+e]);
        translate([0,(c-g)/2,0]) cube([g/2, g, b+t+e]);
        // Slot to fit adjustment strip
        translate([e+t+b+t+a+t+b+t+e,c/2,0]) {
            translate([-e-t-e-t,-2.5*e-t,0]) cube([t+e+t,t+5*e+t,b+t+e]);
            translate([-e,-1.5*e-t,0]) cube([e,t+3*e+t,b+t+e]);
        }
    }
}
