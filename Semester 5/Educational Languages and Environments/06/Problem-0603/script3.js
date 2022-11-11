function calculate() {
    var name = document.getElementById("name").value;
    var family = document.getElementById("family").value;
    if (name == "" || family == "") {
        document.getElementById("result").innerHTML = "Неточни имена";
    }
    else if (document.getElementById("year").value == NaN) {
        document.getElementById("result").innerHTML = "Празна година";
    }
    else {
        var year = (parseInt(document.getElementById("year").value));
        var date = new Date();
        if (year < 1900 || year > date.getFullYear) {
            document.getElementById("result").innerHTML = "Въвели сте грешна година!"
        }
        else {
            document.getElementById("result").innerHTML = "Настоящата възраст на" + name + " " + family + " е: " + (date.getFullYear() - year) + " години";
        }
    }

}