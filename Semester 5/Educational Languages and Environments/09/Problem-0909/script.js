function main(n, r, x, y, z) {
    new Suica();
    oxyz();
    demo();
    for (var i = 0; i < n; i++) {
        var alpha = radians(random(0, 360));
        var beta = radians(random(0, 360));
        var X = x + r * Math.cos(alpha) * Math.cos(beta);
        var Y = y + r * Math.sin(alpha) * Math.cos(beta);
        var Z = z + r * Math.sin(beta);
        p = point([X, Y, Z]);
        p.pointSize = 5;
        p.color = [Math.random(), Math.random(), Math.random()];

    }
}