// document.addEventListener("DOMContentLoaded", function() {
// Get all the headers inside the main tag
// var mainHeaders = document.querySelectorAll('main h2, main h3, main h4, main h5, main h6');
//
// var nav = document.querySelector('nav');
//
// var navList = document.createElement('ul');
//
// // Loop through each header and create a list item with a link to the header
// mainHeaders.forEach((header) => {
//   // Create a list item and a link
//   var listItem = document.createElement('li');
//   var link = document.createElement('a');
//
//   // Add the header text as the link text
//   link.textContent = header.textContent;
//
//   // Set the href attribute to the ID of the header element
//   link.href = `#${header.id}`;
//
//   // Add the link to the list item and the list item to the navigation list
//   listItem.appendChild(link);
//   navList.appendChild(listItem);
// });
//
// nav.appendChild(navList);
// });

function tableOfContents(container, output) {
var toc = "";
var level = 0;
var container = document.querySelector(container) || document.querySelector('#contents');
var output = output || '#toc';

container.innerHTML =
    container.innerHTML.replace(
        /<h([\d])>([^<]+)<\/h([\d])>/gi,
        function (str, openLevel, titleText, closeLevel) {
            if (openLevel != closeLevel) {
                return str;
            }

            if (openLevel > level) {
                toc += (new Array(openLevel - level + 1)).join('<ul>');
            } else if (openLevel < level) {
                toc += (new Array(level - openLevel + 1)).join('</li></ul>');
            } else {
                toc += (new Array(level+ 1)).join('</li>');
            }

            level = parseInt(openLevel);

            var anchor = titleText.replace(/ /g, "_");
            toc += '<li><a href="#' + anchor + '">' + titleText
                + '</a>';

            return '<h' + openLevel + ' id="' + anchor + '">' + titleText + '</h' + closeLevel + '>';
        }
    );

if (level) {
    toc += (new Array(level + 1)).join('</ul>');
}
document.querySelector(output).innerHTML += toc;
};
function toggleNav() {
  var nav = document.querySelector("aside");
  var main = document.querySelector("main");
  nav.classList.toggle('active');
  main.classList.toggle('active');
}
