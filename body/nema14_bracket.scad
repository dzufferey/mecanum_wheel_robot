$fn=60;
wall=3;


tolerance = 0.2;
width = 35.2;
screw = 26;

r = (width - screw) / 2 + tolerance;
m3 = 1.5 + tolerance;

module shell() {
    difference() {
        hull(){
            difference() {
                translate([-wall,-wall,-wall]) cube([width+2*wall,width+wall,width+wall]);
                translate([-wall,0,0]) cube(width+2*wall);
            }
        }
        translate([-tolerance,-tolerance,-tolerance]) cube(width + 2*tolerance);
    }
    difference() {
        translate([-wall-10,-wall,-wall]) cube([width+2*wall+20,wall,width+wall]);
        for (x = [-6-wall, width + wall + 6]) {
            for (z = [4-wall,width-4]) {
                translate ([x,-wall, z]) rotate([-90,0,0]) translate ([0,0,-0.5]) cylinder(r=m3,h=wall+1);
             }
        }
    }
}

module complete() {
    difference() {
        translate([-r,-r, 0]) shell();
        translate([0,0,-wall]) {
            for (x = [0,screw]) {
                for (y = [0,screw]) {
                    translate ([x,y,0]) cylinder (r=m3,h=wall);
                }
            }
            translate ([screw/2,screw/2,0]) cylinder (r=12,h=wall);
        }
    }
}

complete();