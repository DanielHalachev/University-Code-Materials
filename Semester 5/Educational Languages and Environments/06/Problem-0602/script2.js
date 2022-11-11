function main() {
    var arr = document.getElementsByTagName("li" && "ul"); // means li of ul; not the same as ul && li
    for (var i = 0; i < arr.length; i++) {
        arr[i].style.backgroundColor='yellow';
        arr[i].style.fontStyle="italic";
    }
}

