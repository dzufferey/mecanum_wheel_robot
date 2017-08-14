$fn=60;

module pin(h = 10) {
    difference() {
        cylinder(r = 4, h = h);
        cylinder(r = 1.3, h = h);
    }
}

module base() {
    dx = 60.96;
    dy = 58.42;
    cube([75, 68, 1]);
    for (x = [0, dx])
        for (y = [0, dy])
            translate([7+x, 5 + y, 0]) pin();
}

base();