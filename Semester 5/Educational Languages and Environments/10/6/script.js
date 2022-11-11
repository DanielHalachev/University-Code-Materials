function main(x, y, z, a) {
    new Suica();
    oxyz();
    demo();

    var s = rectangle([x, y, z], [a, 2 * a]);
    s.mode = Suica.LINE;

    var s = rectangle([x - a / 2, y + 3 * a / 2, z], [a, 2 * a]);
    s.mode = Suica.LINE;
    s.spin = radians(90);

    var s = rectangle([x + a, y + 2 * a / 2, z], [a, 2 * a]);
    s.mode = Suica.LINE;
    s.spin = radians(180);

    var s = rectangle([x + 3 * a / 2, y + a / 2, z], [a, 2 * a]);
    s.mode = Suica.LINE;
}