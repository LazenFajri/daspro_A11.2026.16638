/* PrismJS 1.29.0 - Bundled for C/C++ with Line Numbers */
var _self = "undefined" != typeof window ? window : "undefined" != typeof WorkerGlobalScope && self instanceof WorkerGlobalScope ? self : {},
    Prism = function(u) {
        var c = /\blang(?:uage)?-([\w-]+)\b/i,
            n = 0,
            _ = {},
            e = {
                manual: u.Prism && u.Prism.manual,
                disableWorkerMessageHandler: u.Prism && u.Prism.disableWorkerMessageHandler,
                util: {
                    encode: function e(n) {
                        return n instanceof a ? new a(n.type, e(n.content), n.alias) : Array.isArray(n) ? n.map(e) : n.replace(/&/g, "&amp;").replace(/</g, "&lt;").replace(/\u00a0/g, " ")
                    },
                    type: function(e) {
                        return Object.prototype.toString.call(e).slice(8, -1)
                    },
                    objId: function(e) {
                        return e.__id || Object.defineProperty(e, "__id", {
                            value: ++n
                        }), e.__id
                    },
                    clone: function t(e, r) {
                        var a, n;
                        switch (r = r || {}, e.type || e) {
                            case "Object":
                                if (n = util.objId(e), r[n]) return r[n];
                                for (var i in a = {}, r[n] = a, e) e.hasOwnProperty(i) && (a[i] = t(e[i], r));
                                return a;
                            case "Array":
                                return a = [], e.forEach(function(e, n) {
                                    a[n] = t(e, r)
                                }), a;
                            default:
                                return e
                        }
                    },
                    getLanguage: function(e) {
                        for (; e;) {
                            var n = c.exec(e.className);
                            if (n) return n[1].toLowerCase();
                            e = e.parentElement
                        }
                        return "none"
                    },
                    currentScript: function() {
                        if ("undefined" == typeof document) return null;
                        if ("currentScript" in document) return document.currentScript;
                        try {
                            throw new Error
                        } catch (e) {
                            var n = (/at [^(\r\n]*\((.*):.+:.+\)$/gi.exec(e.stack) || [0, ""])[1];
                            if (n) {
                                var t = document.getElementsByTagName("script");
                                for (var r in t)
                                    if (t[r].src == n) return t[r]
                            }
                            return null
                        }
                    },
                    isActive: function(e, n, t) {
                        for (var r = "no-" + n; e;) {
                            var a = e.classList;
                            if (a.contains(n)) return !0;
                            if (a.contains(r)) return !1;
                            e = e.parentElement
                        }
                        return !!t
                    }
                },
                languages: {
                    plain: _,
                    plaintext: _,
                    text: _,
                    txt: _,
                    extend: function(e, n) {
                        var t = e.util.clone(e.languages[e]);
                        for (var r in n) t[r] = n[r];
                        return t
                    },
                    insertBefore: function(t, e, n, r) {
                        var a = (r = r || e.languages)[t],
                            i = {};
                        for (var l in a)
                            if (a.hasOwnProperty(l)) {
                                if (l == e)
                                    for (var o in n) n.hasOwnProperty(o) && (i[o] = n[o]);
                                n.hasOwnProperty(l) || (i[l] = a[l])
                            }
                        var s = r[t];
                        return r[t] = i, e.languages.DFS(e.languages, function(e, n) {
                            n === s && e != t && (this[e] = i)
                        }), i
                    },
                    DFS: function e(n, t, r, a) {
                        a = a || {};
                        var i = e.util.objId;
                        for (var l in n)
                            if (n.hasOwnProperty(l)) {
                                t.call(n, l, n[l], r || l);
                                var o = n[l],
                                    s = e.util.type(o);
                                "Object" !== s || a[i(o)] ? "Array" !== s || a[i(o)] || (a[i(o)] = !0, e(o, t, l, a)) : (a[i(o)] = !0, e(o, t, l, a))
                            }
                    }
                },
                plugins: {},
                highlightAll: function(e, n) {
                    e.highlightAllUnder(document, e, n)
                },
                highlightAllUnder: function(e, n, t) {
                    var r = {
                        callback: t,
                        container: e,
                        selector: 'code[class*="language-"], [class*="language-"] code, code[class*="lang-"], [class*="lang-"] code'
                    };
                    e.hooks.run("before-highlightall", r), r.elements = Array.prototype.slice.apply(r.container.querySelectorAll(r.selector)), e.hooks.run("before-all-elements-highlight", r);
                    for (var a, i = 0; a = r.elements[i++];) e.highlightElement(a, !0 === n, r.callback)
                },
                highlightElement: function(e, n, t) {
                    var r = e.util.getLanguage(e),
                        a = e.languages[r];
                    e.className = e.className.replace(c, "").replace(/\s+/g, " ") + " language-" + r;
                    var i = e.parentElement;
                    i && "pre" === i.nodeName.toLowerCase() && (i.className = i.className.replace(c, "").replace(/\s+/g, " ") + " language-" + r);
                    var l = {
                        element: e,
                        language: r,
                        grammar: a,
                        code: e.textContent
                    };

                    function o(e) {
                        l.highlightedCode = e, e.hooks.run("before-insert", l), l.element.innerHTML = l.highlightedCode, e.hooks.run("after-highlight", l), e.hooks.run("complete", l), t && t.call(l.element)
                    }
                    if (e.hooks.run("before-sanity-check", l), (i = l.element.parentElement) && "pre" === i.nodeName.toLowerCase() && !i.hasAttribute("tabindex") && i.setAttribute("tabindex", "0"), !l.code) return e.hooks.run("complete", l), void(t && t.call(l.element));
                    if (e.hooks.run("before-highlight", l), l.grammar)
                        if (n && u.Worker) {
                            var s = new Worker(e.filename);
                            s.onmessage = function(e) {
                                o(e.data)
                            }, s.postMessage(JSON.stringify({
                                language: l.language,
                                code: l.code,
                                immediateClose: !0
                            }))
                        } else o(e.highlight(l.code, l.grammar, l.language));
                    else o(e.util.encode(l.code))
                },
                highlight: function(e, n, t) {
                    var r = {
                        code: e,
                        grammar: n,
                        language: t
                    };
                    if (e.hooks.run("before-tokenize", r), !r.grammar) throw new Error('The language "' + r.language + '" has no grammar.');
                    return r.tokens = e.tokenize(r.code, r.grammar), e.hooks.run("after-tokenize", r), a.stringify(e.util.encode(r.tokens), r.language)
                },
                tokenize: function(e, n) {
                    var t = n.rest;
                    if (t) {
                        for (var r in t) n[r] = t[r];
                        delete n.rest
                    }
                    var a = new s;
                    return u(a, a.head, e),
                        function e(n, t, r, a, i, l) {
                            for (var o in r)
                                if (r.hasOwnProperty(o) && r[o]) {
                                    var s = r[o];
                                    s = Array.isArray(s) ? s : [s];
                                    for (var u = 0; u < s.length; ++u) {
                                        if (l && l.cause == o + "," + u) return;
                                        var c = s[u],
                                            g = c.inside,
                                            f = !!c.lookbehind,
                                            h = !!c.greedy,
                                            d = c.alias;
                                        if (h && !c.pattern.global) {
                                            var p = c.pattern.toString().match(/[imsuy]*$/)[0];
                                            c.pattern = RegExp(c.pattern.source, p + "g")
                                        }
                                        for (var v = c.pattern || c, m = a.next, y = i; m !== t.tail; y += m.value.length, m = m.next) {
                                            if (l && y >= l.reach) return;
                                            var b = m.value;
                                            if (t.length > n.length) return;
                                            if (!(b instanceof _)) {
                                                var k, x = 1;
                                                if (h) {
                                                    if (!(k = z(v, y, n, f)) || k.index >= n.length) break;
                                                    var w = k.index,
                                                        A = k.index + k[0].length,
                                                        P = y;
                                                    for (P += m.value.length; P <= w;) m = m.next, P += m.value.length;
                                                    if (P -= m.value.length, y = P, m.value instanceof _) continue;
                                                    for (var E = m; E !== t.tail && (P < A || "string" == typeof E.value); E = E.next) x++, P += E.value.length;
                                                    x--, b = n.slice(y, P), k.index -= y
                                                } else if (!(k = z(v, 0, b, f))) continue;
                                                var w = k.index,
                                                    S = k[0],
                                                    O = b.slice(0, w),
                                                    L = b.slice(w + S.length),
                                                    N = y + b.length;
                                                l && N > l.reach && (l.reach = N);
                                                var j = m.prev;
                                                O && (j = C(t, j, O), y += O.length), O && (y -= O.length);
                                                var M = new _(o, g ? e.tokenize(S, g) : S, d, S);
                                                if (m = C(t, j, M), L && C(t, m, L), 1 < x) {
                                                    var T = {
                                                        cause: o + "," + u,
                                                        reach: N
                                                    };
                                                    e(n, t, r, m.prev, y, T), l && T.reach > l.reach && (l.reach = T.reach)
                                                }
                                            }
                                        }
                                    }
                                }
                        }(e, a, n, a.head, 0),
                        function(e) {
                            var n = [],
                                t = e.head.next;
                            for (; t !== e.tail;) n.push(t.value), t = t.next;
                            return n
                        }(a)
                },
                hooks: {
                    all: {},
                    add: function(e, n) {
                        var t = this.all;
                        t[e] = t[e] || [], t[e].push(n)
                    },
                    run: function(e, n) {
                        var t = this.all[e];
                        if (t && t.length)
                            for (var r, a = 0; r = t[a++];) r(n)
                    }
                },
                Token: _
            };

        function a(e, n, t, r) {
            this.type = e, this.content = n, this.alias = t, this.length = 0 | (r || "").length
        }

        function _(e, n, t, r) {
            this.type = e, this.content = n, this.alias = t, this.length = 0 | (r || "").length
        }

        function s() {
            var e = {
                    value: null,
                    prev: null,
                    next: null
                },
                n = {
                    value: null,
                    prev: e,
                    next: null
                };
            e.next = n, this.head = e, this.tail = n, this.length = 0
        }

        function u(e, n, t) {
            var r = n.next,
                a = {
                    value: t,
                    prev: n,
                    next: r
                };
            return n.next = a, r.prev = a, e.length++, a
        }

        function C(e, n, t) {
            var r = n.next,
                a = {
                    value: t,
                    prev: n,
                    next: r
                };
            return n.next = a, r.prev = a, e.length++, a
        }

        function z(e, n, t, r) {
            e.lastIndex = n;
            var a = e.exec(t);
            if (a && r && a[1]) {
                var i = a[1].length;
                a.index += i, a[0] = a[0].slice(i)
            }
            return a
        }
        return a.stringify = function n(e, t) {
            if ("string" == typeof e) return e;
            if (Array.isArray(e)) return e.map(function(e) {
                return n(e, t)
            }).join("");
            var r = {
                type: e.type,
                content: n(e.content, t),
                tag: "span",
                classes: ["token", e.type],
                attributes: {},
                language: t
            };
            var a = e.alias;
            a && (Array.isArray(a) ? Array.prototype.push.apply(r.classes, a) : r.classes.push(a)), e.hooks.run("wrap", r);
            var i = "";
            for (var l in r.attributes) i += " " + l + '="' + (r.attributes[l] || "").replace(/"/g, "&quot;") + '"';
            return "<" + r.tag + ' class="' + r.classes.join(" ") + '"' + i + ">" + r.content + "</" + r.tag + ">"
        }, _self.Prism = e, e
    }(_self);

// C-like & C++ Grammar
Prism.languages.clike = {
    comment: [{
        pattern: /(^|[^\\])\/\*[\s\S]*?(?:\*\/|$)/,
        lookbehind: !0,
        greedy: !0
    }, {
        pattern: /(^|[^\\:])\/\/.*/,
        lookbehind: !0,
        greedy: !0
    }],
    string: {
        pattern: /(["'])(?:\\(?:\r\n|[\s\S])|(?!\1)[^\\\r\n])*\1/,
        greedy: !0
    },
    "class-name": {
        pattern: /(\b(?:class|interface|extends|implements|trait|instanceof|new)\s+|\bcatch\s+\()[\w.\\]+/i,
        lookbehind: !0,
        inside: {
            punctuation: /[.\\]/
        }
    },
    keyword: /\b(?:if|else|while|do|for|return|in|instanceof|function|new|try|throw|catch|finally|null|break|continue|switch|case|default|struct|typedef|void|int|float|double|char|bool|string|long|short|unsigned|signed|const|auto|namespace|using|std|cin|cout|endl|fixed|setprecision|getline|sizeof|true|false)\b/,
    boolean: /\b(?:false|true)\b/,
    function: /\b\w+(?=\()/,
    number: /\b0x[\da-f]+\b|(?:\b\d+(?:\.\d*)?|\B\.\d+)(?:e[+-]?\d+)?/i,
    operator: /[<>]=?|[!=]=?=?|--?|\+\+?|&&?|\|\|?|[?*/~^%]/,
    punctuation: /[{}[\];(),.:]/
};

Prism.languages.c = Prism.languages.extend("clike", {
    comment: {
        pattern: /\/\/(?:[^\r\n\\]|\\(?:\r\n?|\n|(?![\r\n])))*|\/\*[\s\S]*?(?:\*\/|$)/,
        greedy: !0
    },
    string: {
        pattern: /"(?:\\(?:\r\n|[\s\S])|[^"\\\r\n])*"/,
        greedy: !0
    },
    "macro": {
        pattern: /(^[\t ]*)#\s*[a-z](?:[^\r\n\\/]|\/(?!\*)|\/\*(?:[^*]|\*(?!\/))*\*\/|\\(?:\r\n|[\s\S]))*/im,
        lookbehind: !0,
        greedy: !0,
        alias: "property",
        inside: {
            string: [{
                pattern: /^(#\s*include\s*)<[^>]+>/,
                lookbehind: !0
            }, Prism.languages.clike.string],
            directive: {
                pattern: /^(#\s*)[a-z]+/,
                lookbehind: !0,
                alias: "keyword"
            }
        }
    }
});

Prism.languages.cpp = Prism.languages.extend("c", {
    keyword: /\b(?:alignas|alignof|asm|auto|bool|break|case|catch|char|char16_t|char32_t|char8_t|class|compl|concept|const|const_cast|consteval|constexpr|constinit|continue|co_await|co_return|co_yield|decltype|default|delete|do|double|dynamic_cast|else|enum|explicit|export|extern|false|final|float|for|friend|goto|if|import|inline|int|long|module|mutable|namespace|new|noexcept|nullptr|operator|override|private|protected|public|register|reinterpret_cast|requires|return|short|signed|sizeof|static|static_assert|static_cast|struct|switch|template|this|thread_local|throw|true|try|typedef|typeid|typename|union|unsigned|using|virtual|void|volatile|wchar_t|while|cin|cout|endl|fixed|setprecision|getline|substr|stoi|stod|pow|sqrt)\b/,
    number: {
        pattern: /(?:\b0b[01']+|\b0x(?:[\da-f']+(?:\.[\da-f']*)?|\.[\da-f']+)(?:p[+-]?[\d']+)?|(?:\b[\d']+(?:\.[\d']*)?|\B\.[\d']+)(?:e[+-]?[\d']+)?)[ful]{0,4}/i,
        greedy: !0
    },
    operator: />>=?|<<=?|->[*&]?|--|\+\+|&&|\|\||[?:~]|<=>|[-+*/%&|^!=<>]=?|\b(?:and|and_eq|bitand|bitor|compl|not|not_eq|or|or_eq|xor|xor_eq)\b/,
    boolean: /\b(?:false|true)\b/
});

// Helper for rendering syntax highlighted code with line numbers
window.renderHighlightedCpp = function(code) {
    if (!code) return "";
    var highlighted = Prism.highlight(code, Prism.languages.cpp, 'cpp');
    var lines = highlighted.split("\n");
    var html = '<table class="code-table"><tbody>';
    for (var i = 0; i < lines.length; i++) {
        var lineNum = i + 1;
        var lineContent = lines[i] || "&nbsp;";
        html += '<tr class="code-line-row" id="L' + lineNum + '">';
        html += '<td class="line-number" data-line-number="' + lineNum + '">' + lineNum + '</td>';
        html += '<td class="line-code">' + lineContent + '</td>';
        html += '</tr>';
    }
    html += '</tbody></table>';
    return html;
};
