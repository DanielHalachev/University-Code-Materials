function main(x, y, z, a) {
    new Suica();
    oxyz();
    demo();

    var s = square([x, y, z], a / Math.sqrt(2));
    s.mode = Suica.LINE;
    s.focus = [1, 0, 0];

    var s = square([x, y, z], a);
    s.mode = Suica.LINE;
    s.focus = [1, 0, 0];
    s.spin = (radians(45));

}