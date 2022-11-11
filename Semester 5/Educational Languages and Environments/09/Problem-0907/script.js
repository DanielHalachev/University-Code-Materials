function main(n) {
    new Suica();
    oxyz();
    demo();
    n = n / 2;
    var a;
    // създаване на 4 точки във върховетe на квадрат със страна n единици
    a = point([n, n, n]);
    a.color = [Math.random(), Math.random(), Math.random()];
    a = point([-n, n, n]);
    a.color = [Math.random(), Math.random(), Math.random()];
    a = point([-n, -n, n]);
    a.color = [Math.random(), Math.random(), Math.random()];
    a = point([n, -n, n]);
    a.color = [Math.random(), Math.random(), Math.random()];

    a = point([n, n, -n]);
    a.color = [Math.random(), Math.random(), Math.random()];
    a = point([-n, n, -n]);
    a.color = [Math.random(), Math.random(), Math.random()];
    a = point([-n, -n, -n]);
    a.color = [Math.random(), Math.random(), Math.random()];
    a = point([n, -n, -n]);
    a.color = [Math.random(), Math.random(), Math.random()];
}