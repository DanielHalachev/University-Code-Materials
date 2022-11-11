function main(n) {
    new Suica();
    oxyz();
    demo();

    var a;
    // създаване на 4 точки във върховетe на квадрат със страна n единици
    a = point([0, 0, 0]);
    a.color = [Math.random(), Math.random(), Math.random()];
    a = point([n, 0, 0]);
    a.color = [Math.random(), Math.random(), Math.random()];
    a = point([0, n, 0]);
    a.color = [Math.random(), Math.random(), Math.random()];
    a = point([n, n, 0]);
    a.color = [Math.random(), Math.random(), Math.random()];

    a = point([0, 0, n]);
    a.color = [Math.random(), Math.random(), Math.random()];
    a = point([n, 0, n]);
    a.color = [Math.random(), Math.random(), Math.random()];
    a = point([0, n, n]);
    a.color = [Math.random(), Math.random(), Math.random()];
    a = point([n, n, n]);
    a.color = [Math.random(), Math.random(), Math.random()];
}