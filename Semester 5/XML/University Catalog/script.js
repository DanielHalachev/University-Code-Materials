function main() {
    // hide non-home page elements
    document.getElementById('regions').style.display = 'none';
    document.getElementById('table').style.display = 'none';

    // collapsable regions
    var coll = document.getElementsByClassName("collapsable");

    for (var i = 0; i < coll.length; i++) {
        coll[i].addEventListener("click", function () {
            this.classList.toggle("active");
            var content = this.nextElementSibling;
            if (content.style.maxHeight) {
                content.style.maxHeight = null;
            } else {
                content.style.maxHeight = content.scrollHeight + "px";
            }
        });
    }
    // collapsable faculties
    var collf = document.getElementsByClassName("collapsableFaculties");
    for (var j = 0; j < collf.length; j++) {
        collf[j].addEventListener("click", function () {
            this.classList.toggle("on");
            var content = this.nextElementSibling;
            if (content.style.maxHeight) {
                content.style.maxHeight = null;
                this.innerHTML = "Покажи факултетите";
            } else {
                content.style.maxHeight = content.scrollHeight + "px";
                this.innerHTML = "Скрий факултетите";
            }
        });
    }
}
function showOverview() {
    document.getElementById('overview').style.display = 'inline';
    document.getElementById('regions').style.display = 'none';
    document.getElementById('table').style.display = 'none';
};
function showRegions() {
    document.getElementById('overview').style.display = 'none';
    document.getElementById('regions').style.display = 'inline';
    document.getElementById('table').style.display = 'none';
};
function showDetails() {
    document.getElementById('overview').style.display = 'none';
    document.getElementById('regions').style.display = 'none';
    document.getElementById('table').style.display = 'inline';
};

function sortTable(n) {
    var shouldSwitch, switchcount = 0;
    var table = document.getElementById("myTable");
    var switching = true;
    var dir = "asc";
    while (switching) {
        switching = false;
        var rows = table.rows;
        for (var i = 1; i < (rows.length - 1); i++) {
            shouldSwitch = false;
            var x = rows[i].getElementsByTagName("TD")[n];
            var y = rows[i + 1].getElementsByTagName("TD")[n];

            if (dir == "asc") {
                if (x.innerHTML.toLowerCase() > y.innerHTML.toLowerCase()) {
                    shouldSwitch = true;
                    break;
                }
            } else if (dir == "desc") {
                if (x.innerHTML.toLowerCase() < y.innerHTML.toLowerCase()) {
                    shouldSwitch = true;
                    break;
                }
            }

        }
        if (shouldSwitch) {
            rows[i].parentNode.insertBefore(rows[i + 1], rows[i]);
            switching = true;
            switchcount++;
        } else {
            if (switchcount == 0 && dir == "asc") {
                dir = "desc";
                switching = true;
            }
        }
    }
}

function showFaculties() {
    this.style.display = "inline";
}

function searchTable() {
    var input = document.getElementById("searchBox");
    var filter = input.value.toUpperCase();
    var table = document.getElementById("myTable");
    var tr = table.getElementsByTagName("tr");

    for (var i = 0; i < tr.length; i++) {
        var td = tr[i].getElementsByTagName("td")[0];
        if (td) {
            var txtValue = td.textContent || td.innerText;
            if (txtValue.toUpperCase().indexOf(filter) > -1) {
                tr[i].style.display = "";
            } else {
                tr[i].style.display = "none";
            }
        }
    }
}