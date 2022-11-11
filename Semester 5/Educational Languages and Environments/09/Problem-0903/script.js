function vLen(a) {
    return Math.sqrt(a[0] * a[0] + a[1] * a[1] + a[2] * a[2]);
}

function calc() {
    var xp = document.getElementById("xp").value;
    var yp = document.getElementById("yp").value;
    var zp = document.getElementById("zp").value;
    var xq = document.getElementById("xq").value;
    var yq = document.getElementById("yq").value;
    var zq = document.getElementById("zq").value;

    var p = [xp, yp, zp];
    var q = [xq, yq, zq];

    var sum = vLen(p) + vLen(q);
    document.getElementById("resultsum").innerHTML = 'Сумата от дължините на векторите p и q е: ' + vLen(p) + ' + ' + vLen(q) + ' = ' + sum;

    var difer = vLen(p) - vLen(q);
    document.getElementById("resultdiffer").innerHTML = 'Разликата от дължините на векторите p и q е: ' + vLen(p) + ' - ' + vLen(q) + ' = ' + difer;
}