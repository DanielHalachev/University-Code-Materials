function vLen(a) {
    return Math.sqrt(a[0] * a[0] + a[1] * a[1] + a[2] * a[2]);
}

function main(xp, yp, zp, xq, yq, zq) {
    var p = [xp, yp, zp];
    var q = [xq, yq, zq];
    var sum = vLen(p) + vLen(q);
    var difer = vLen(p) - vLen(q);

    console.log('сумата от дължините на векторите p и q е:' + vLen(p) + '+' + vLen(q) + '=' + sum);
    console.log('разликата от дължините на векторите p и q е:' + vLen(p) + '-' + vLen(q) + '=' + difer);

}