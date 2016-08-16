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

bar = [b+t+t, c, b+t];
l = e+t+b+t+f/2-(a/2+t+b+t+e);

$fs=0.02;

module adjuster () {
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
}


module pivot () {
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
}


module anchor () {
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
}

module slider() {
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
}
