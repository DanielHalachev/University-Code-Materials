function main(n, r) {
    new Suica();
    oxyz();
    demo();
    var C1 = point([random(-20, 20), random(-20, 20), random(-20, 20)]);
    var h = random(-20, 20);

    for (var i = 0; i < n; i++) {
        var alpha = radians(i * 360 / n);
        var x1 = C1.center[0] + r * Math.cos(alpha);
        var y1 = C1.center[1] + r * Math.sin(alpha);
        var z1 = C1.center[2];

        var x2 = C1.center[0] + r * Math.cos(alpha);
        var y2 = C1.center[1] + r * Math.sin(alpha);
        var z2 = C1.center[2] + h;

        segment([x1, y1, z1], [x2, y2, z2]);
    }
}