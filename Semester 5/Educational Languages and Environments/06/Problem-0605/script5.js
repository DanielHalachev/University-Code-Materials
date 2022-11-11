function main() {
    var arr = document.getElementsByTagName("i" && "b");
    var list = [];
    for (var i = 0; i < arr.length; i++) {
        list.push("<i>" + arr[i].innerHTML + "</i>");
    }
    document.getElementById("bruh").innerHTML = list.join(" || ");
}