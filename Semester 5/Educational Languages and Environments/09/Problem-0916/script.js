function main(n, r, x, y, z) {
    new Suica();
    oxyz();
    demo();
    for (var i = 0; i < n; i++) {
        var alpha = radians(random(0, 360));
        var beta = alpha + radians(90);
        x1 = x + r * Math.cos(alpha);
        y1 = y + r * Math.sin(alpha);
        z1 = z;

        x2 = x + r * Math.cos(beta);
        y2 = y + r * Math.sin(beta);
        z2 = z;

        segment([x1, y1, z1], [x2, y2, z2]);
    }
}