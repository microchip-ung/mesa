// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


get_symbol_landing_page = function(sym, obj) {
    var html = "<h1>" + sym + "</h1>";

    const decl = Object.entries(obj["decl"]);
    if (decl.length > 0) {
        html += "<h2>Defined in " + decl.length + " files:</h2>";
        html += "<ul>";

        for (var i = 0; i < decl.length; ++i) {
            const file = decl[i][0];
            const e = decl[i][1];

            for (var ii = 0; ii < e.length; ++ii) {
                var ee = e[ii];
                html += "<li><a href=\"#" + ee["file"] + "@l" + ee["line"] + "\">" + file + ":" + ee["line"] + "</a></li>";
            }
        }

        html += "</ul>"
    }

    const articles = Object.entries(obj["articles"]);
    if (articles.length > 0) {
        html += "<h2>Referenced in " + articles.length + " articles:</h2>"
        html += "<ul>"

        for (var i = 0; i < articles.length; ++i) {
            const file = articles[i][0]
            const e = articles[i][1];

            for (var ii = 0; ii < e.length; ++ii) {
                var ee = e[ii];
                html += "<li><a href=\"#" + ee["file"] + "@l" + ee["line"] + "\">" + file + ":" + ee["line"] + "</a></li>";
            }
        }
        html += "</ul>"
    }

    const impl = Object.entries(obj["impl"]);
    if (obj["impl"].length > 0) {
        html += "<h2>Implemented in " + impl.size + " files:</h2>"
        html += "<ul>"
        for (var i = 0; i < impl.length; ++i) {
            const file = impl[i][0]
            const e = impl[i][1];

            for (var ii = 0; ii < e.length; ++ii) {
                var ee = e[ii];
                html += "<li><a href=\"#" + ee["file"] + "@l" + ee["line"] + "\">" + file + ":" + ee["line"] + "</a></li>";
            }
        }
        html += "</ul>"
    }

    const use = Object.entries(obj["use"]);
    if (use.length > 0) {
        html += "<h2>Referenced in " + use.length + " files:</h2>"
        html += "<ul>"
        for (var i = 0; i < use.length; ++i) {
            const file = use[i][0]
            const e = use[i][1];

            for (var ii = 0; ii < e.length; ++ii) {
                var ee = e[ii];
                html += "<li><a href=\"#" + ee["file"] + "@l" + ee["line"] + "\">" + file + ":" + ee["line"] + "</a></li>";
            }
        }
        html += "</ul>"
    }

    return html
}

hashChange = function(e) {
    var param;
    var anc;
    var id;
    var page;
    var offset;
    const hash = window.top.location.hash.substr(1)
    console.log('Hash: ' + hash);

    sym_regex = /^sym:(.*)/
    sym_match = hash.match(sym_regex)

    symd_regex = /^symd:(.*)/
    symd_match = hash.match(symd_regex)

    if (sym_match && sym_match.length > 1) {
        console.log('Symbol: ' + sym_match[1]);
        s = symbol[sym_match[1]]

        if (s) {
            console.log(s);
            page = get_symbol_landing_page(sym_match[1], s);
        }

    } else if (symd_match && symd_match.length > 1) {
        console.log('Symbol defined: ' + symd_match[1]);
        s = symbol[symd_match[1]]

        if (s) {
            const decl = Object.entries(s["decl"]);
            // Must only be declared in 1 file
            console.log("Defined in " + decl.length + " files");
            if (decl.length == 1) {
                const file = decl[0][0];
                const e = decl[0][1];

                // File must only have 1 definition
                console.log("Defined in " + e.length + " time in " + file);
                if (e.length == 1) {
                    page = pages[file];
                    anc = "a[name*='" + e[0]["line"] + "']";
                }
            }
        }

    } else if (hash.length == 0) {
        page = pages["mepa/docs/readme"];

    } else {
        const split = hash.split('@');
        const path = split[0];

        if (split.length > 1) {
            param = split[1];
            anc = "a[name*='" + param + "']";
        }

        console.log('path: ' + path);

        page = pages[path];
    }

    if (page) {
        $('#content').html(page);

        if (param) { // Check if param is an id
            console.log('param: ' + param);
            const elements = $("#" + param); // $() returns an array with zero length if id not found
            if (elements && elements.length > 0) { // If id is found then it is in first element
                id = elements[0]; // Use first element
            }
        }

        if (id) { // id overrides anchor
            console.log("id: ", id);
            id.scrollIntoView();
        } else if (anc) {
            console.log("anc: " + anc);
            const scrollto = $(anc);
            if (scrollto && window.innerDocClick) { // If scrollto is found then anc refers to a line number in current document
                scrollto.css("background-color", "DarkGray");
                scrollto.css("font-weight", "bold");
                const el_offset = scrollto.offset().top;
                const el_height = scrollto.height();
                const window_height = $(window).height();

                if (el_height < window_height) {
                    offset = el_offset - ((window_height / 2) - (el_height / 2));
                } else {
                    offset = el_offset;
                }

                $('html, body').animate({scrollTop: offset}, 500);
            }
        } else {
            if (window.innerDocClick) {
                window.scrollTo(0, 0);
            }
        }
    } else {
        $('#content').html('Page ' + hash + ' not found');
    }
}

$(window).bind('hashchange', hashChange);
$(window).bind('mouseover',  function() { window.innerDocClick = true; });
$(window).bind('mouseleave', function() { window.innerDocClick = false; });
