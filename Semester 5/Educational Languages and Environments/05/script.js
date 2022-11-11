// 1
//console.log("Exercise JavaScript Suica");

// 2
console.log(6, 2, 6.2);
console.log(6 * 2);
console.log(6, -2);
console.log(6 / 2);
console.log(6 - 2);
console.log(6 * 2 - 6 / 2);
console.log(-2);
console.log("6--2");
console.log((6 * 2 - 6) / 2);

//3
console.log(Math.sqrt(4)); //just sqrt doesn't work
console.log(Math.PI); //just PI doesn't work
console.log(Math.sin(Math.PI / 2));
console.log(Math.round(26.8)); //закръгля до най-близкото
console.log(Math.floor(26, 8)); //, = . за числа; floor - връща първия integer по-малък от аргумента
console.log(Math.abs(-2));
console.log(Math.abs(17 - 35));

//4
console.log("\„Не е важно да знаеш всичко, важното е да знаеш къде да го намериш.\“\nАлберт Айнщайн");
console.log(2000 + 15 + "SUICA");
console.log("SUICA" + 2000 + 15);
a = 7;
b = 14;
a + b;
console.log(a + b);
console.log(String(a) + String(b));
console.log('' + a + b);

//5
var str = "\„Не е важно да знаеш всичко, важното е да знаеш къде да го намериш.\“";
console.log(str);
console.log(str.length);
console.log(str[1], str[2]);
console.log(str.slice(5, 10));
console.log(str + "\n\„Албърт Айнщайн\"");

//6
console.log(Boolean(5 < 12));
console.log(17 - 5 < 12); // also possible
console.log(true && false);
console.log(true || false);
console.log(!true);
console.log(!false);

//7
var a = 3;
var b = 4 * a;
var c = a + b;
console.log(a, b, c);
console.log("a=" + a, "b=" + b, "c=" + c);
console.log("a=" + a, "b=" + b, "c=a+b=" + c);

//8
var arra = [8, 15, 23, 5, 11];
var arrb = ["червено", "зелено", "синьо", "жълто"];
var arrc = [1, 1, 1];
console.log(arra, arrb, arrc);
console.log(arra.length, arrb.length, arrc.length);
console.log(arra[3]);
console.log(arra[2] - arra[4]);

//8
arra.push(7, 9, 18, 8);
console.log(arra, arra.length);
console.log(arra.length - arrb.length);
console.log(arra.slice(2, 4));
console.log(arra);
arra.splice(3);
console.log(arra);
arra.push(arrc);//concat works, too
console.log(arra);

//9
arrb.push("бяло", "черно");
var arr = [arrb[arrb.indexOf("бяло")], arrb[arrb.indexOf("зелено")], arrb[arrb.indexOf("червено")]];
console.log(arr);
arrb.sort();
arrb.reverse();

//10
m = { x: 10, y: 15, z: 2 };
console.log(m);
console.log(m.x + m.y);
m.max = Math.max(m.x, m.y);
m.name = "A" + m.max;
console.log("m.z=" + m.z);
console.log("m[name]=" + m.name);

//11
a = -2;
b = 8;
c = 16;

if (a < b) {
    if (b < c) {
        console.log(c);
    } else {
        console.log(b);
    }
} else {
    if (a < c) {
        console.log(c);
    }
    else {
        console.log(b);
    }
}

//12
for (var i = 1; i < 10; i++) {
    console.log(i + "*" + i + "=" + i * i);
}

//13
function square(n) {
    return n * n;
}
for (var i = 1; i < 10; i++) {
    console.log(i + "*" + i + "=" + square(i));
}
//does't work
for(var i=1; i<10; i++){
    console.log(i+"*"+i+"=",function(i){return i*i;});
}

//14
sqrt = function(n){
    return Math.sqrt(n);
}
//sqrt = Math.sqrt;
//console.log(sqrt(25));

//15
function multiply(n, m){
    return n+"*"+m+"="+n*m;
}
for(var i =1; i<=10; i++){
    for(var j = 1; j<=10; j++){
        console.log(multiply(i,j));
    }
}