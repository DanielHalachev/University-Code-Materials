function main(n, r, xc, yc, zc) {
    new Suica();
    oxyz();
    demo();
    for (var i = 0; i < n; i++) {
        alpha = 360 * i / n;
        var x = xc + r * Math.cos(radians(alpha));
        var y = yc + r * Math.sin(radians(alpha));
        var z = zc;
        var a = point([x, y, z]);
        a.color = [Math.random(), Math.random(), Math.random()];
        a.pointSize = 5;
    }
}