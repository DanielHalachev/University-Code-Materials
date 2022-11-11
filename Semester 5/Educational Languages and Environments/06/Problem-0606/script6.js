function main() {
    var listItems = (document.getElementsByTagName("li" && "b"));
    var tables = document.getElementsByClassName("t");
    for (var i = 0; i < tables.length; i++) {
        tables[i].style.display = "none";
        listItems[i].elem = tables[i];
        listItems[i].addEventListener("click", function (event) {
            var style = event.target.elem.style;
            if (style.display == "none") {
                style.display = "block";
            } else {
                style.display = "none";
            }
        })
    }
}