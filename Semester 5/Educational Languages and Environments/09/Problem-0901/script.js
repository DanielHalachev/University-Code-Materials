function vLen(a) {
    return Math.sqrt(a[0] * a[0] + a[1] * a[1] + a[2] * a[2]);
}

function main() {
    var p = [12, 8, -1];
    var q = [5, 3, 1];
    var sum = vLen(p) + vLen(q);
    var difer = vLen(p) - vLen(q);

    console.log('сумата от дължините на векторите p и q е:' + vLen(p) + '+' + vLen(q) + '=' + sum);
    console.log('разликата от дължините на векторите p и q е:' + vLen(p) + '-' + vLen(q) + '=' + difer);

}