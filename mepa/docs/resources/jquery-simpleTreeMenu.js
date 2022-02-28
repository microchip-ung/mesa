/*
 Copyright (c) 2017 Simon Freytag

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
*/

(function($) {

    var methods = {

        init: function() {
            return this.each(function() {
                var $this = $(this);
                if ($this.hasClass("simpleTreeMenu") === false) {
                    $this.hide();
                    $(this).addClass("simpleTreeMenu");
                    $this.children("li").each(function() {
                        methods.buildNode($(this));
                    });
                    methods.initDeserialize();
                    $(this).show();
                }
            });
        },

        initDeserialize: function() {
            if (private.hasLocalStorage() === true) {
                var state = localStorage.getItem(
                    private.localStorageKey.apply(this)
                );
                if (state != null) {
                    state = state.split(",");
                    if (state.length > 0) {
                        methods.deserialize.call(this, state);
                    }
                }
            }
        },

        rebuild: function() {
            return this.each(function() {
                var $this = $(this);
                $this.hide();
                $this.children("li").each(function() {
                    methods.buildNode($(this));
                });
                $(this).show();
            });
        },

        buildNode: function($li) {
            if ($li.children("ul").length > 0) {
                var built = false;
                if ($li.hasClass("Node")) built = true;
                if (!built) {
                    $li.children("ul").hide();
                    $li.addClass("Node").click(function(event) {
                        var $t = $(this);
                        if ($t.hasClass("expanded")) {
                            $t.removeClass("expanded").children("ul").hide();
                        }
                        else {
                            $t.addClass("expanded").children("ul").show();
                        }
                        event.stopPropagation();
                    });
                    $li.find("a").click(function(event) {
                        var $t = $(this);
                        var $li = $t.closest("li.Node");
                        if (event.offsetX >= 0) {
                            event.stopPropagation();
                        }
                    });
                }
                if ($li.children("ul").children("li").length == 0) {
                    $li.addClass("EmptyNode");
                }
                else $li.removeClass("EmptyNode");
                $li.children("ul").children("li").each(function() {
                    methods.buildNode($(this));
                });
            } else {
                if ($li.hasClass("Leaf")) return;
                $li.addClass("Leaf").click(function(event) {
                    event.stopPropagation();
                });
                return;
            }
        },

        serialize: function() {
            state = [];
            $('.Node').each(function() {
                var s = $(this).hasClass("expanded") ?
                    private.EXPANDED : private.COLLAPSED;
                state.push(s);
            });
            if (private.hasLocalStorage() === true) {
                localStorage.setItem(
                    private.localStorageKey.apply(this), state.join()
                );
            }
        },

        deserialize: function(state) {
            $('.Node').each(function(index) {
                if (state[index] == private.EXPANDED) {
                    $(this).addClass("expanded").children("ul").show();
                }
            });
        },

        expandToNode: function($li) {
            if ($li.parent().hasClass("simpleTreeMenu")) {
                if (!$li.hasClass("expanded")) {
                    if ($li.children("ul").length > 0)
                        $li.addClass("expanded").children("ul").show();
                }
            }
            $li.parents("li", "ul.simpleTreeMenu").each(function() {
                var $t = $(this);
                if (!$t.hasClass("expanded")) {
                    $t.addClass("expanded").children("ul").show();
                }
            });

            if ($li.hasClass("node") && !$li.hasClass("expanded")) {
                $li.addClass("expanded").children("ul").show();
            }
        },

        searchForUrl: function() {
            $('.Leaf', $(this)).each(function() {
                $leaf = $(this);
                current_url = document.location.pathname.slice(1);
                if ($leaf.find('a').attr('href').indexOf(current_url) >= 0) {
                    methods.expandToNode($leaf);
                    $leaf.addClass('selected');
                }
            });
        },

        searchForPath: function(path) {
            $('.Leaf', $(this)).each(function() {
                $leaf = $(this);
                if ($leaf.find('a').attr('href').indexOf(path) >= 0) {
                    methods.expandToNode($leaf);
                    $leaf.addClass('selected');
                }
            });
        },

        expandAll: function() {
            $(this).find("li.Node").each(function() {
                $t = $(this);
                if (!$t.hasClass("expanded")) {
                    $t.addClass("expanded").children("ul").show();
                }
            });
        },

        closeAll: function() {
            $("ul", $(this)).hide();
            var $li = $("li.Node");
            if ($li.hasClass("expanded")) {
                $li.removeClass("expanded");
            }
        },
    };

    var private = {

        EXPANDED: "expanded",
        COLLAPSED: "collapsed",
        localStorageKeyPrefix: "jQuery-simpleTreeMenu-treeState-",

        hasLocalStorage: function() {
            return (
                'localStorage' in window && 'setItem' in window.localStorage
                && 'getItem' in window.localStorage
            );
        },

        localStorageKey: function() {
            return private.localStorageKeyPrefix + $(this).attr("id");
        }

    };

    $.fn.simpleTreeMenu = function(method) {
        if (methods[method]) {
            return methods[method].apply(
                this, Array.prototype.slice.call(arguments, 1)
            );
        }
        else if (typeof method === 'object' || !method) {
            return methods.init.apply(this, arguments);
        }
        else {
            $.error(
                'Method ' +  method + ' does not exist on jQuery.simpleTreeMenu'
            );
        }
    };
})(jQuery);
