$fn=60;

module top() {
    import("Bosch_battery_108_top.stl");
}

module mid() {
    import("Bosch_battery_108_body.stl");
}

module bot() {
    import("Bosch_battery_108_cap.stl");
}

module core(h) {
    rotate([0,0,30])cylinder(r=32, h=h,$fn=3);
}


module top_a() {
    intersection() {
        top();
        cylinder(r=25,h=10.0625);
    }
}

module top_b() {
    intersection() {
        top();
        translate([0,0,10.0625]) cylinder(r=25,h=15);
    }
}

module top2() {
    hull() intersection() {
        top_a();
        core(11);
    }
    top_a();
    hull() intersection() {
        top_b();
        core(30);
        translate([-10.5,-22.9,10]) cube([21,20,15]);
    }
    top_b();
}

module mid2(){
    hull() intersection() {
        mid();
        core(100);
    }
    mid();
}

module bot2(){
    hull() intersection() {
        bot();
        cylinder(r=30,h=18.0625);
    }
    hull() intersection() {
        bot();
        translate([0,0,18.0625]) cylinder(r=30,h=17.5);
    }
    hull() difference() {
        bot();
        translate([0,0,0]) cylinder(r=30,h=17.6 + 18.0625);
        translate([0,0,17.5 + 21.5]) cylinder(r=30,h=10);
    }
    hull() difference() {
        bot();
        translate([0,0,0]) cylinder(r=30,h=17.5 + 21.5);
    }
}

module bat() {
    translate([0,0,3]) {
        translate([0,0,61]) top2();
        mid2();
    }
    bot2();
}

module bigger_bat() {
    minkowski(){
        bat();
        sphere(r=0.5, $fn=30);
    }
}

module holder() {
    difference() {
        translate([0,2,0]) cylinder(r=25, h=47.5);
        translate([0,0,83]) rotate([180,0,0]) bigger_bat();
    }
}

module contacts() {
    translate([4.5,6,0]) cube([2,8,10]);
    translate([-6.5,6,0]) cube([2,8,10]);
}

holder();
