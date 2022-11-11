function main(n, x, y, z, a) {
    new Suica();
    oxyz();
    demo();

    for (var i = 0; i < n; i++) {
        var s = square([x, y, z], a);
        s.focus = [1, 0, 0];
        s.mode = Suica.LINE;
        s.spin = radians(i * 45);
        a = a / Math.sqrt(2);
    }

}