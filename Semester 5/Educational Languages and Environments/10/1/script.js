function main(n, x, y, z, a) {
    new Suica();
    oxyz();
    demo();
    for (var i = 0; i < n; i++) {
        a -= 1;
        var s = square([x, y, z], a);
        s.mode = Suica.LINE;
        s.focus = [1, 0, 0];
    }

}