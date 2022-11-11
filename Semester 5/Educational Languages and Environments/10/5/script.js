function main(x, y, z, a, b) {
    new Suica();
    oxyz();
    demo();

    var r = rectangle([x, y, z], [a, b]);
    r.mode = Suica.LINE;
}