a = 6; // Gap between bars
b = 20; // width of the bars
c = 29; // Width of whole thing
e = 3; // Outside wall thickness, and 45 degree area width
f = 160; // length of bar this must be in center of
g = 4; // Slot width for cable tie
h = 20; // Slide length
i = 4.5; // Screw hole diameter
j = 6.8; // Nut width
k = 0.5; // Slot for line
d = c-e-e; // Width of slot
m = 300; // Long distance for cutouts
n = 1; // Extra bit so cutouts go through without rendering
o = 1.6; // Thickness of cylinder springs for slider

t = 0.25; // tolerance

bar = [b+t+t, c, b+t];
l = e+t+b+t+f/2-(a/2+t+b+t+e);

$fs=0.02;

//pivot();
//translate([0, 35, 0]) adjuster();
//translate([0, 70, 0]) anchor();
translate([0, 105, 0]) slider();
//translate([0, 0, 0]) bar_support();


module pivot () {
    difference() {
        // Main block
        cube([e+t+b+t+a+t+b+t+e, c, b/2+e]);
        // Slots for bars to fit in
        translate([e, 0, e]) cube(bar);
        translate([e+t+b+t+a, 0, e]) cube(bar);
        // Cutout for free-hanging line
        translate([e+t+b+t, (c-d)/2, e]) cube([a, d, b]);
        // slot for line to go through
        translate([e+t+b+t, (c-d)/2, 0]) cube([a/2, d, b]);
        translate([e+t+b+t+a/2, (c-d)/2, e]) rotate([0,135,0]) cube([b, e, b+t+e]);
        translate([e+t+b+t+a/2, (c-d)/2+d-e, e]) rotate([0,135,0]) cube([b, e, b+t+e]);
        // Cable tie slot
        translate([0,(c-g)/2,-n]) cube([g/2, g, m]);
        // Slot to fit adjustment strip
        translate([e+t+b+t+a+t+b+t+e,c/2,0]) {
            translate([-e,-1.5*e-t,-n]) cube([e,t+3*e+t,m]);
            translate([-e-t-e-t,-2.5*e-t,-n]) cube([t+e+t,t+5*e+t,m]);
        }
    }
}


module adjuster () {
    difference() {
        // Main shape
        union() {
            cube([e,c,b/2+e]);
            translate([0,e,0]) cube([l, c-2*e, e]);
            // Slot to fit adjustment strip
            translate([l,c/2,0]) {
                translate([0,-1.5*e+t,0]) cube([t+e+t,3*e-2*t,e]);
                translate([t+e+t,-2.5*e+t,0]) cube([e-2*t,5*e-2*t,e]);
            }
        }
        translate([l,c/2-g/2,0]) cube([e, g, m]);
        // slot for cable tie
        translate([0,(c-g)/2,0]) cube([g/2, g, b+t+e]);
        // Slot for screw adjuster
        translate([e+t+b,c/2,0]) {
            translate([0,-c/4-t,0]) cube([t+e+t,t+c/2+t,e]);
            translate([t+e+t,-g/2,0]) cube([g,g,e]);
        }
    }
}


module anchor () {
    difference() {
        // Main shape
        hull() {
            translate([0,e+t,0]) cube([e,c-2*e-2*t,e]);
            translate([b+10,c/2,0]) cylinder(e, r=c/2-e-t);
        }
        // Slot and hole for cable tie
        translate([0,(c-g)/2,e-g/2]) cube([b+e,g,g]);
        translate([b+e,(c-g)/2,0]) cube([g/2,g,e]);

        translate([b+10,c/2,e]) cylinder(b,r=i/2,center=true);
        cube([b+e,c/4+t,e]);
        translate([0,3*c/4-t,0]) cube([b+e,c/4+t,e]);
    }
}

module slider() {
    difference() {
        // Main shape
        union() {
            translate([e,0,0]) cube([2*e,c,b]);
            translate([e,c/5,0]) cylinder(b,r=c/5,center=false);
            translate([e,4*c/5,0]) cylinder(b,r=c/5,center=false);
            translate([2*e,0,0]) cube([b,c,2*e]);
            // Slot to fit adjustment strip
        }
        // Hollow out the cylinders
        translate([e,c/5,0]) cylinder(b,r=c/5-o,center=false);
        translate([e,4*c/5,0]) cylinder(b,r=c/5-o,center=false);
        // slot for slider
        translate([e+0.4,e-2*t,0]) cube([t+e+t-0.4,c-2*e+4*t,b]);

        // Bolt and nut capture
        translate([3*e,(c-j)/2-t,e]) cube([b,j+2*t,2*e]);
        translate([e+10,c/2,e]) cylinder(b,r=i/2,center=true);
        // Line guides
        translate([e+10,0,e]) cylinder(b,r=i/2,center=true);
        translate([e+10,c,e]) cylinder(b,r=i/2,center=true);
        // Line capture slot
        translate([2*e+10+5,(c-k-t)/2,0]) cube([b,k+2*t,b]);
    }
}


module bar_support () {
    support_l = 2*b+4*t+a+2*e;
    difference() {
        // Main block
        cube([e+2*t+b+c,support_l, b/2+e]);
        // Bar cutouts
        translate([e,0,e]) cube([b+2*t,m,b]);
        translate([e,e,e]) cube([m,b+2*t,b]);
        translate([e,e+b+2*t+a,e]) cube([m,b+2*t,b]);
        translate([2*e+2*t+b,e+b+2*t+a/2,0]) {
            translate([0,-b/2-t,0]) cube([m,b+2*t,b]);
            translate([-g/2,-g/2,0]) cube([g,g,b]);
        }
        // Cable tie slots
        translate([-g/2,support_l/2-g/2,0]) cube([g,g,b]);
        translate([e+2*t+b+c/2-g/2,-g/2,0]) cube([g,g,b]);
        translate([e+2*t+b+c/2-g/2,support_l-g/2,0]) cube([g,g,b]);
    }
}


