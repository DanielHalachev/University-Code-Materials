function select() {
    // show it's an input element in order to make .value an avalable option
    /**
     * @type HTMLInputElement
     */
    var input = document.getElementById("list")
    document.getElementById("content").innerHTML = "Избраният ден от седмицата е: " + input.value;
}